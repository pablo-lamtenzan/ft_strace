/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracee_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:10:31 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/10 23:38:05 by pablo            ###   ########.fr       */
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
int8_t					wait_until_next_syscall(pid_t pid, int32_t sigtrap);
const char*				signal_db(int8_t index);

#endif