/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:37:22 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/09 23:39:48 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <print.h>


bool		signwait(pid_t pid, int32_t* wstatus)
{
	if (!unblock_signals())
	{
		exit(EXIT_FAILURE); // error to handle
		return (false);
	}
	waitpid(pid, wstatus, NULL);
	if (!block_signals())
	{
		exit(EXIT_FAILURE); // error to handle
		return (false);
	}
	return (true);
}

/* Inf loop until a syscall stops, print the signals between the syscalls, 
	checks if the child has been killed or exited and print it */
int8_t			wait_until_next_syscall(pid_t pid, int32_t sigtrap)
{
	int32_t		wstatus;
	int32_t		wstopstatus;

	while (42)
	{
		/* PTRACE_SYSCALL -> Restart the stopped tracee as for PTRACEE_CONT, but arrange for the 
			tracee to bee stopped at the next entry to or exit from a systhem call or after execution
			of a single instruction, respectively (the tracee will also, as usual, be stopped upon receit
			of a signal). From the tracer's perspective, the tracee will appear to have been stoped by
			receipt of a SIGTRAP. */
		ptrace(PTRACE_SYSCALL, pid, 0L, 0L);
		signwait(pid, &wstatus);
		/* WIFSTOPPED -> returns true if the child process was stoped by delivey of a signal */
		/* WSTOPSIG -> returns the number of the signal wicth caused the child to stop */
		if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) & (sigtrap | 0x80))
			return (true);
		/* WIFEXITED -> returns true if the child process has exited normally */
		if (WIFEXITED(wstatus))
		{
			/* WEXITSTATUS -> returns the exit status of the child process */
			dprintf(STDERR_FILENO, EXIT_STATUS, WEXITSTATUS(wstatus));
			exit(EXIT_SUCCESS);
			return (true);
		}
		else
			print_signals(pid, wstatus);
		if (tracee_killed(pid, wstatus))
		{
			kill(pid, wstopstatus = WSTOPSIG(wstatus));
			wstopstatus < 32 ? PRINT_SIGNALS : PRINT_REAL_TIME_SIGNALS;
			dprintf(STDERR_FILENO, "%s\n", strsignal(WSTOPSIG(wstatus)));
			exit(EXIT_SUCCESS);
		}
	}
	return (true);
}