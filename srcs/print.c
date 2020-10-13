/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:47:46 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 19:29:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <syscall_db.h>
#include <string.h>
#include <sys/reg.h>
#include <ft_error.h>

void						print_return_value(int64_t ret_syscall)
{
	if (-ret_syscall != ENOSYS)
	{
		if (-ret_syscall != 512) // search the define of this
		{
			if (ret_syscall < 0)
				dprintf(STDERR_FILENO, " = %d (%s)\n", -1, strerror(-ret_syscall));
			else
				dprintf(STDERR_FILENO, " = %ld (0x%lx)\n", ret_syscall, ret_syscall);
		}
		else
			dprintf(STDERR_FILENO, " = ?\n");
	}
}

void				print_signals(pid_t tracee, int32_t wstatus)
{
	siginfo_t		info;
	int32_t			wstopstatus;

	/* PTRACE_GETSIGINFO -> Retrieve information about the signal that caused the stop */
	ptrace(PTRACE_GETSIGINFO, tracee, 0L, &info);
	/* WSTOPSIG -> Returns the number of the signal wicth caused the procee to stop */
	wstopstatus = WSTOPSIG(wstatus);
	if (wstopstatus > 0 && (wstopstatus < 32))
		dprintf(2, "--- %s {si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d} ---\n", 
		signal_db(WSTOPSIG(wstatus)), \
		signal_db(WSTOPSIG(wstatus)), \
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

static char		print_escape_in_string_data(char* string_data)
{
	char			printed = (char)dprintf(STDERR_FILENO, "\"");
	int32_t		iterator = -1;
	const uint32_t	size = strlen(string_data);

	while (++iterator < (int32_t)size && iterator < 32)
	{
		if (string_data[iterator] == 0x07)
			printed += (char)dprintf(STDERR_FILENO, "\\a");
		else if (string_data[iterator] == 0x08)
			printed += (char)dprintf(STDERR_FILENO, "\\b");
		else if (string_data[iterator] == 0x09)
			printed += (char)dprintf(STDERR_FILENO, "\\t");
		else if (string_data[iterator] == 0x0a)
			printed += (char)dprintf(STDERR_FILENO, "\\n");
		else if (string_data[iterator] == 0x0b)
			printed += (char)dprintf(STDERR_FILENO, "\\v");
		else if (string_data[iterator] == 0x0c)
			printed += (char)dprintf(STDERR_FILENO, "\\f");
		else if (string_data[iterator] == 0x0d)
			printed += (char)dprintf(STDERR_FILENO, "\\r");
		else
			printed += (char)write(2, string_data + iterator, 1);
	}
	return (printed += (char)dprintf(STDERR_FILENO, "\""));
}

static char		print_syscall_arg(pid_t tracee, t_args_type type, int32_t index,
		struct user_regs_struct* registers)
{
	char*			string_data = NULL;
	uint32_t		iterator = 0;
	uint64_t		ret;
	bool			once = true;
	char			printed;

	if (!type)
		return (0);
	else if (type == INT)
		return ((char)dprintf(STDERR_FILENO, "%d", (int32_t)((int64_t*)registers)[index]));
	else if (type == UINT)
		return ((char)dprintf(STDERR_FILENO, "%u", (uint32_t)((uint64_t*)registers)[index]));
	else if (type == PTR && ((uint64_t*)registers)[index])
		return ((char)dprintf(STDERR_FILENO, "0x%lx", ((uint64_t*)registers)[index]));
	else if (type == STRUCT && ((uint64_t*)registers)[index])
		return ((char)dprintf(STDERR_FILENO, "{ 0x%lx }", ((uint64_t*)registers)[index]));
	else if (type == STRUCT)
		return ((char)dprintf(STDERR_FILENO, "{ NULL }"));
	else if (type == PTR)
		return ((char)dprintf(STDERR_FILENO, "NULL"));
	else /* STR */
	{
		if (!(string_data = calloc(1, 33)))
			return (error_exit("Error: calloc failed allocating memory blocks"));
		while (once || (iterator < 32 && !memchr((void*)&ret, 0, sizeof(int64_t))))
		{
			ret = (uint64_t)ptrace(PTRACE_PEEKDATA, tracee, ((int64_t*)registers)[index] + iterator, 0L);
			memcpy(string_data + iterator, &ret, sizeof(int64_t));
			iterator += sizeof(int64_t);
			once = false;
		}
		printed = print_escape_in_string_data(string_data);
		if (strlen(string_data) == 32)
			printed += (char)dprintf(STDERR_FILENO, "%s", "...");
		free(string_data);
		return (printed);
	}
}

static char		print_syscall_args(pid_t tracee, int64_t* index,
		struct user_regs_struct* registers)
{
	const int32_t	argument_registers[6] = { RDI, RSI, RDX, R10, R8, R9 };
	char			printed = 0;
	int32_t			iterator = -1;
	sys_data_t		syscall = syscall_db(index);

	if (!syscall.nb_args)
		return ((char)dprintf(STDERR_FILENO, "%s", ")"));
	while (++iterator < syscall.nb_args)
	{
		printed += print_syscall_arg(tracee, syscall.args[iterator], \
				argument_registers[iterator], registers);
		if (iterator < syscall.nb_args - 1)
			printed += (char)dprintf(STDERR_FILENO, "%s", ", ");
		else
			printed += (char)dprintf(STDERR_FILENO, "%s", ")");
	}
	return (printed);
}

static char		print_syscall_name(int64_t* syscall)
{
	return  (dprintf(STDERR_FILENO, "%s(", syscall_db(syscall).index));
}

void				print_syscall(pid_t tracee, int64_t* cathed_syscall,
		struct user_regs_struct* registers)
{
	char			printed;
	
	printed = print_syscall_name(cathed_syscall) + print_syscall_args (tracee, cathed_syscall, registers);
	while (printed++ < 39)
		dprintf(STDERR_FILENO, "%s", " ");
}