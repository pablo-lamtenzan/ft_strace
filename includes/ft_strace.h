/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:29:30 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/10 00:00:15 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRACE_H
# define FT_STRACE_H

#define _GNU_SOURCE

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <errno.h>

extern int32_t						g_pid;

#define NONE						0
#define EXIT_STATUS 				" = ?\n+++ exited with %d +++\n"


void					get_syscall_info(pid_t pid, int64_t* ret_syscall,
		int64_t* syscall, struct user_regs_struct* registers);
bool					tracee_killed(pid_t pid, int32_t wstatus);

#endif
