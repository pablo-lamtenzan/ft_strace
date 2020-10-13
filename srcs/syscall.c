/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:09:47 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 20:06:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>

void		get_syscall_info(pid_t tracee, int64_t* ret_syscall, int64_t* syscall, 
		struct user_regs_struct* registers)
{
	/* PTRACE_GETREGS -> Copy the tracee's registers into a struct user_regs_struct given as "data" argument */
	ptrace(PTRACE_GETREGS, tracee, 0L, registers);
	*ret_syscall = registers->rax;
	*syscall = registers->orig_rax;
}