/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:29:30 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/11 15:24:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRACE_H
# define FT_STRACE_H

# ifndef __x86_64__
# error ARCH NOT SUPPORTED
# endif

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

int8_t*         		get_tracee_path(int8_t* binary_name);
void					get_syscall_info(pid_t pid, int64_t* ret_syscall,
		int64_t* syscall, struct user_regs_struct* registers);
bool					tracee_killed(pid_t pid, int32_t wstatus);

#endif
