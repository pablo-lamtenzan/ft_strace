/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:47:46 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/09 22:39:59 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>

void				print_signals(pid_t pid, int32_t wstatus)
{
	siginfo_t		info;
	int32_t			wstopstatus;

	/* PTRACE_GETSIGINFO -> Retrieve information about the signakl that caused the stop */
	ptrace(PTRACE_GETSIGINFO, pid, 0L, &info);
	/* WSTOPSIG -> Returns the number of the signal wicth caused the procee to stop */
	if ((wstopstatus = WSTOPSIG(wstatus) > 0 && wstopstatus < 32))
		dprintf(2, "--- %s {si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d} ---\n", 
		"to do", \
		"to do", \
		info.si_code,
		info.si_pid,
		info.si_uid);
	else if (wstopstatus > 32 && wstopstatus < 64)
		dprintf(2, "--- SIGRT_%d {si_signo=SIGRT_%d, si_code=%d, si_pid=%d, si_uid=%d}\n",
		wstopstatus - 32, \
		wstopstatus - 32, \
		info.si_code,
		info.si_pid,
		info.si_uid);
}