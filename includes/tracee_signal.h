/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracee_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:10:31 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/09 23:04:31 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEE_SIGNAL_H
# define TRACEE_SIGNAL_H

# ifndef pid_t
	typedef int pid_t;
# endif

# ifndef int32_t
	typedef int int32_t;
# endif

# ifndef int8_t
	typedef char int8_t;
# endif

bool					signwait(pid_t pid, int32_t* wstatus);
bool					unblock_signals();
bool					block_signals();
int8_t					wait_until_next_syscall(pid_t pid, int32_t sigtrap);

#endif