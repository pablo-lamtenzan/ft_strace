/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:43:18 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 19:17:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>

const char*		signal_db(int8_t index)
{
	const char*	db[64] = {
		"",
		"SIGHUP",
		"SIGINT",
		"SIGQUIT",
		"SIGILL",
		"SIGTRAP",
		"SIGABRT",
		"SIGBUS",
		"SIGFPE",
		"SIGKILL",
		"SIGUSR1",
		"SIGSEGV",
		"SIGUSR2",
		"SIGPIPE",
		"SIGALRM",
		"SIGTERM",
		"SIGSTKFLT",
		"SIGCHLD",
		"SIGCONT",
		"SIGSTOP",
		"SIGTSTP",
		"SIGTTIN",
		"SIGTTOU",
		"SIGURG",
		"SIGXCPU",
		"SIGXFSZ",
		"SIGVTALRM",
		"SIGPROF",
		"SIGWINCH",
		"SIGIO",
		"SIGPWR",
		"SIGSYS"
	};
	return (db[index]);
}

bool			block_signals()
{
	sigset_t	set;
	
	/*	SIGINT == Interrumpt from the keyboard
		SIGQUIT == Quit from keyboard
		SIGTERM == Default action is to terminate the process
		SIGPIPE == Broken pipe (write to pipe with no readers)
		SIGHUP == Hangup detected on controlling terminal or 
			death of controlling process
		sigprocmask with "how" as SIG_BLOCK -> Signals in set are blocked
	*/
	return (!(sigemptyset(&set) \
			|| sigaddset(&set, SIGHUP) \
			|| sigaddset(&set, SIGINT) \
			|| sigaddset(&set, SIGQUIT) \
			|| sigaddset(&set, SIGPIPE) \
			|| sigaddset(&set, SIGTERM) \
			|| sigprocmask(SIG_BLOCK, &set, NULL)));
}

bool			unblock_signals()
{
	sigset_t	set;

	/* sigprocmask with "how" as SIG_SETMASK -> The blocked signals are the set argument signals.
	*/

	return (!(sigemptyset(&set) \
			|| sigprocmask(SIG_SETMASK, &set, NULL)));
}


bool			tracee_killed(int32_t wstatus)
{
	/* WSTOPSIG -> Returns the number of the signal wicth caused the procee to stop. */
	/*
		SIGCONT == Default action is to continue the process if it is currently stopped
		SIGCHILD == Child stopped or terminated
		SIGURG == Urgent condition on socket
		SIGWINCH == Window resize signal
		SIGSTOP == Default action is to stop the process
		SIGTSTP == Stop typed at terminal
		SIGTTIN == Terminal input for background process
		SIGTRAP == Exection (or trap) in process
		SIGTTOU == Terminal output for background process
	*/
	return (WSTOPSIG(wstatus) != SIGCONT \
			&& WSTOPSIG(wstatus) != SIGCHLD \
			&& WSTOPSIG(wstatus) != SIGURG \
			&& WSTOPSIG(wstatus) != SIGWINCH \
			&& WSTOPSIG(wstatus) != SIGSTOP \
			&& WSTOPSIG(wstatus) != SIGTSTP \
			&& WSTOPSIG(wstatus) != SIGTTIN \
			&& WSTOPSIG(wstatus) != SIGTRAP \
			&& WSTOPSIG(wstatus) != SIGTTOU);
}
