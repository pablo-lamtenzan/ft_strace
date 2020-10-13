/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:02:15 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 18:43:47 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# ifndef pid_t
	typedef int pid_t;
# endif

# ifndef int32_t
	typedef int int32_t;
# endif

#define PRINT_SIGNALS				dprintf(2, "+++ killed by %s +++\n", signal_db(WEXITSTATUS(wstatus)))
#define PRINT_REAL_TIME_SIGNALS		dprintf(2, "+++ killed by SIGRT_%d +++\n", WEXITSTATUS(wstatus) - 32)

void								print_signals(pid_t pid, int32_t wstatus);
void								print_return_value(int64_t ret_syscall);
void								print_syscall(pid_t pid, int64_t* cathed_syscall,
		struct user_regs_struct* registers);

#endif