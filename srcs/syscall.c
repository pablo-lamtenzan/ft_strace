/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:09:47 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/09 22:45:00 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>

void		get_syscall_info(pid_t pid, int64_t* ret_syscall, int64_t* syscall, 
		struct user_regs_struct* registers)
{
	/* PTRACE_GETREGS -> Copy the tracee's registers into a struct user_regs_struct given as "data" argument */
	ptrace(PTRACE_GETREGS, pid, 0L, registers);
	*ret_syscall = registers->rax;
	*syscall = registers->orig_rax;
}