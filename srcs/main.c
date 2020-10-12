/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:27:43 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 00:18:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <print.h>
#include <linux/unistd.h> /* __NR_execve */
#include <ft_error.h>

extern const char	*__progname;

int32_t						g_pid = 0;

static void					sigint(int32_t sig)
{
	(void)sig;
	dprintf(STDERR_FILENO, "%s: Process %d detached\n", __progname, g_pid);
	exit(EXIT_SUCCESS);
}

static bool					exec_tracer(pid_t tracee, char* tracee_path)
{
	int32_t					wstatus = 0;
	int64_t					cathed_syscall = 0;
	int64_t					ret_cathed_syscall = 0;
	struct user_regs_struct	registers;
	bool					once = true;
	
	free(tracee_path);
	/* enable ctrl + c */
	signal(SIGINT, sigint);
	/* PTRACE_SEIZE -> Attach to the process specified in pid, making it a tracee (does not stop the process). 
		Restart the stopped tracee as for PTRACEE_CONT, but arrange for the 
		tracee to be stopped at the next entry to or exit from a systhem call or after execution
		of a single instruction, respectively (the tracee will also, as usual, be stopped upon receit
		of a signal). From the tracer's perspective, the tracee will appear to have been stoped by
		receipt of a SIGTRAP
	*/
	/* PTRACE_O_TRACESYSGOOD -> When delivering systhem call traps, set bit 7 in the signal number. This makes it easy
		for the tracer to distinguish normal traps from those caused by a systhem call (using: (SIGTRAP | 0x80)).*/
	/* PTRACE_INTERRUPT -> Stop a tracee, if the tracee is running or sleeping in kernel space and PTRACE_SYSCALL is in
		effect, the systhem call is interrupted and syscall-exit-stop is reported */
	if (ptrace(PTRACE_SEIZE, tracee, 0L, PTRACE_O_TRACESYSGOOD) >= 0 \
		&& ptrace(PTRACE_INTERRUPT, tracee, 0L, 0L) >= 0)
	{
		signwait(tracee, &wstatus);
		while (42)
		{
			/* wait until have the syscall arguments and store it*/
			wait_until_next_syscall(tracee, ARGUMENTS);
			get_syscall_info(tracee, &ret_cathed_syscall, &cathed_syscall, &registers);
			
			//dprintf(2, "DATA IN ARG IS: sys: [%d] ---- ret: [%d] ---\n", cathed_syscall, ret_cathed_syscall);
			
			// wrong af cond -> if (once && cathed_syscall == __NR_execve && !(once = false))
			print_return_value(ret_cathed_syscall);
			/* PTRACE_SEIZE -> Attach to the process specified in pid, making it a tracee (does not stop the process). */
			ptrace(PTRACE_SEIZE, tracee, 0L, PTRACE_O_TRACESYSGOOD);
			/* wait until have the return value and store it */
			wait_until_next_syscall(tracee, RETURN);
			get_syscall_info(tracee, &ret_cathed_syscall, &cathed_syscall, &registers);

			//dprintf(2, "DATA IN RET IS: sys: [%d] ---- ret: [%d] ---\n", cathed_syscall, ret_cathed_syscall);
			
			/* print syscall and its arguments */
			//if ((once && cathed_syscall == __NR_execve && !(once = false)) || !once)
				print_syscall(tracee, &cathed_syscall, &registers);
			print_return_value(ret_cathed_syscall);
		}
		return (true);
	}
	return (error_exit("Error: ptrace failed"));
}

static bool					exec_tracee(char* tracee_path, char** av, char** envp)
{
	/* SIGSTOP -> stops the pid process in its current status and it will be resumed with SIGCONT */
	kill(getpid(), SIGSTOP);
	if (execve(tracee_path, av + 1, envp) < 0)
	{
		free(tracee_path);
		return (error_exit("Error: execve failded can't execute the tracee"));
	}
	return (true);
}

static bool					routine(char* tracee_path, char** av, char** envp)
{
	if (!(g_pid = fork()))
		return (exec_tracee(tracee_path, av, envp));
	else if (g_pid < 0)
		return (error_exit("Error: fork failed, can't execute the tracee"));
	else
		return (exec_tracer(g_pid, tracee_path));
}

int							main(int32_t ac, char** av, char** envp)
{
	char*					tracee_path;

	if (ac < 2)
		return (error_exit("usage: ./ft_strace PROG [ARGS]\n"));
	if (!(tracee_path = get_tracee_path(av[1])))
		return (error_exit("Error: unknown path for the given tracee"));
	return (routine(tracee_path, av, envp) ? 0 : 1);
}