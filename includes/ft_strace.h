/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:29:30 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 18:51:37 by pablo            ###   ########.fr       */
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
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <errno.h>

#define GET_ARGUMENTS					SIGTRAP
#define GET_RETURN 						0
#define EXIT_STATUS 				" = ?\n+++ exited with %d +++\n"

char*         		get_tracee_path(char* binary_name);
void					get_syscall_info(pid_t pid, int64_t* ret_syscall,
		int64_t* syscall, struct user_regs_struct* registers);
bool					tracee_killed(int32_t wstatus);

#endif
