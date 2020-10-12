/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracee_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:10:31 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/12 19:19:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEE_SIGNAL_H
# define TRACEE_SIGNAL_H

#include <stdbool.h>

# ifndef pid_t
	typedef int pid_t;
# endif

# ifndef int32_t
	typedef int int32_t;
# endif

bool					signwait(pid_t pid, int32_t* wstatus);
char					wait_until_next_syscall(pid_t pid, int32_t sigtrap);
const char*				signal_db(char index);
bool					block_signals();
bool					unblock_signals();

#endif