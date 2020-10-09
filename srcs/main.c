/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:27:43 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/10 00:22:42 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <linux/unistd.h> /* __NR_execve */
extern const char	*__progname;

static void					sigint(int32_t sig)
{
	(void)sig;
	dprintf(STDERR_FILENO, "%s: Process %d detached\n", __progname, g_pid);
	exit(EXIT_SUCCESS);
}

static void					handle_possible_error(int64_t ret_syscall)
{
	if (ret_syscall != -ENOSYS)
	{
		if (ret_syscall != -512) // search the define of this
		{
			if (ret_syscall < 0)
				dprintf(STDERR_FILENO, " = %d (%s)\n", -1, strerror(-ret_syscall));
			else
				dprintf(STDERR_FILENO, " = %ld (0x%lx)\n", ret_syscall, ret_syscall);
		}
		else
			dprintf(STDERR_FILENO, " = ?\n");
	}
}

static bool					exec_tracer(pid_t pid, const int8_t* execution_path)
{
	int32_t					wstatus = 0;
	int64_t					cathed_syscall = 0;
	int64_t					ret_cathed_syscall = 0;
	struct user_regs_struct	registers;
	bool					once = true;
	
	free(execution_path);
	/* enable ctrl + c */
	signal(SIGINT, sigint);
	/* PTRACE_SEIZE -> Attach to the process specified in pid, making it a tracee (does not stop the process). */
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
			wait_until_next_syscall(pid, SIGTRAP);
			get_syscall_info(pid, &ret_cathed_syscall, &cathed_syscall, &registers);
			if (once && cathed_syscall == __NR_execve && !(once = false))
				handle_possible_error(ret_cathed_syscall);
			/* PTRACE_SEIZE -> Attach to the process specified in pid, making it a tracee (does not stop the process). */
			ptrace(PTRACE_SEIZE, pid, 0L, PTRACE_O_TRACESYSGOOD);
			wait_until_next_syscall(pid, NONE);
			get_syscall_info(pid, &ret_cathed_syscall, &cathed_syscall, &registers);
			if ((once && cathed_syscall == __NR_execve && !(once = false)) || !once)
				print_syscall(pid, &ret_cathed_syscall, &cathed_syscall, &registers);// here i can only have pid and register as args
		}
	}
	return (true);
}

static bool					exec_tracee(const int8_t* execution_path, const int8_t** av, int8_t** envp)
{
	/* SIGSTOP -> stops the pid process in its current status and it will be resumed with SIGCONT */
	kill(getpid(), SIGSTOP);
	if (execve(execution_path, av + 1, envp) < 0)
	{
		free(execution_path);
		return (false); // exit error status here, error to handle
	}
	return (true);
}

static bool					routine(const int8_t* execution_path, const int8_t** av, int8_t** envp)
{
	if (!(g_pid = fork()))
		return (exec_tracee(execution_path, av, envp));
	else if (g_pid < 0)
		return (false); // error fork have to handle
	else
		return (exec_tracer(execution_path, getpid()));
}

int							main(int32_t ac, const int8_t** av, int8_t** envp)
{
	const int8_t*			execution_path;

	if (ac < 2)
		return (false); // error to handle
	if (!(execution_path = get_execution_path(av[1])))
		return (false); // error to handle
	return (routine(execution_path, av, envp) ? 0 : 1);
}