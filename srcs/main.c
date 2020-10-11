/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:27:43 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/11 15:26:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <print.h>
#include <linux/unistd.h> /* __NR_execve */

extern const char	*__progname;

static void					sigint(int32_t sig)
{
	(void)sig;
	dprintf(STDERR_FILENO, "%s: Process %d detached\n", __progname, g_pid);
	exit(EXIT_SUCCESS);
}

static bool					exec_tracer(pid_t pid, const int8_t* tracee_path)
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
	if (ptrace(PTRACE_SEIZE, pid, 0L, PTRACE_O_TRACESYSGOOD) >= 0 \
		&& ptrace(PTRACE_INTERRUPT, pid, 0L, 0L) >= 0)
	{
		signwait(pid, &wstatus);
		while (42)
		{
			/* wait until have the syscall arguments and store it*/
			wait_until_next_syscall(pid, SIGTRAP);
			get_syscall_info(pid, &ret_cathed_syscall, &cathed_syscall, &registers);
			if (once && cathed_syscall == __NR_execve && !(once = false))
				write_possible_error(&ret_cathed_syscall);
			/* PTRACE_SEIZE -> Attach to the process specified in pid, making it a tracee (does not stop the process). */
			ptrace(PTRACE_SEIZE, pid, 0L, PTRACE_O_TRACESYSGOOD);
			/* wait until have the return value and store it */
			wait_until_next_syscall(pid, NONE);
			get_syscall_info(pid, &ret_cathed_syscall, &cathed_syscall, &registers);
			/* print syscall and its arguments */
			if ((once && cathed_syscall == __NR_execve && !(once = false)) || !once)
				print_syscall(pid, &cathed_syscall, &registers);
			write_possible_error(&ret_cathed_syscall);
		}
		return (true);
	}
	return (false); // exit
}

static bool					exec_tracee(const int8_t* tracee_path, const int8_t** av, int8_t** envp)
{
	/* SIGSTOP -> stops the pid process in its current status and it will be resumed with SIGCONT */
	kill(getpid(), SIGSTOP);
	if (execve(tracee_path, av + 1, envp) < 0)
	{
		free(tracee_path);
		return (false); // exit error status here, error to handle
	}
	return (true);
}

static bool					routine(const int8_t* tracee_path, const int8_t** av, int8_t** envp)
{
	if (!(g_pid = fork()))
		return (exec_tracee(tracee_path, av, envp));
	else if (g_pid < 0)
		return (false); // error fork have to handle
	else
		return (exec_tracer(tracee_path, getpid()));
}

int							main(int32_t ac, const int8_t** av, int8_t** envp)
{
	const int8_t*			tracee_path;

	if (ac < 2)
		return (false); // error to handle
	if (!(tracee_path = get_tracee_path(av[1])))
		return (false); // error to handle
	return (routine(tracee_path, av, envp) ? 0 : 1);
}