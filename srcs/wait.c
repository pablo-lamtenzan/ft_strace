/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:37:22 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 00:18:50 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tracee_signal.h>
#include <ft_strace.h>
#include <print.h>
#include <print.h>
#include <string.h>
#include <ft_error.h>

bool		signwait(pid_t tracee, int32_t* wstatus)
{
	if (!unblock_signals())
		return (error_exit("Error: unblock_signals failed"));
	waitpid (tracee, wstatus, 0);
	if (!block_signals())
		return (error_exit("Error: block_signals failed"));
	return (true);
}

/* Inf loop until a syscall stops, print the signals between the syscalls, 
	checks if the child has been killed or exited and print it */
char			wait_until_next_syscall(pid_t tracee, int32_t sigtrap)
{
	int32_t		wstatus;
	int32_t		wstopstatus;

	while (42)
	{
		/* PTRACE_SYSCALL -> Restart the stopped tracee as for PTRACEE_CONT, but arrange for the 
			tracee to be stopped at the next entry to or exit from a systhem call or after execution
			of a single instruction, respectively (the tracee will also, as usual, be stopped upon receit
			of a signal). From the tracer's perspective, the tracee will appear to have been stoped by
			receipt of a SIGTRAP.
			So, for PTRACE_SYSCALL, for
            example, the idea is to inspect the arguments to the system call  at
            the  first  stop, then do another PTRACE_SYSCALL and inspect the re‐
            turn value of the system call at the second stop.  The data argument
            is treated as for PTRACE_CONT.
		*/
		ptrace(PTRACE_SYSCALL, tracee, 0L, 0L);
		signwait (tracee, &wstatus);
		/* WIFSTOPPED -> returns true if the child process was stoped by delivey of a signal */
		/* WSTOPSIG -> returns the number of the signal wicth caused the child to stop */
		if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) & (sigtrap | 0x80))
		{
			//dprintf(2, "CATCH SYSCALL RET OT CALL\n");
			return (true);
		}
		/* WIFEXITED -> returns true if the child process has exited normally */
		if (WIFEXITED(wstatus))
		{
			/* WEXITSTATUS -> returns the exit status of the child process */
			dprintf(STDERR_FILENO, EXIT_STATUS, WEXITSTATUS(wstatus));
			exit(EXIT_SUCCESS);
			return (true);
		}
		else
			print_signals (tracee, wstatus);
		if (tracee_killed(wstatus))
		{
			kill (tracee, wstopstatus = WSTOPSIG(wstatus));
			wstopstatus < 32 ? PRINT_SIGNALS : PRINT_REAL_TIME_SIGNALS;
			dprintf(STDERR_FILENO, "%s\n", strsignal(WSTOPSIG(wstatus)));
			exit(EXIT_SUCCESS);
		}
	}
	return (true);
}