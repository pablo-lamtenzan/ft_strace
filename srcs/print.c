/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:47:46 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/10 23:33:01 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strace.h>
#include <tracee_signal.h>
#include <syscall_db.h>

void						write_possible_error(int64_t* ret_syscall)
{
	if (*ret_syscall != -ENOSYS)
	{
		if (*ret_syscall != -512) // search the define of this
		{
			if (*ret_syscall < 0)
				dprintf(STDERR_FILENO, " = %d (%s)\n", -1, strerror(-*ret_syscall));
			else
				dprintf(STDERR_FILENO, " = %ld (0x%lx)\n", *ret_syscall, *ret_syscall);
		}
		else
			dprintf(STDERR_FILENO, " = ?\n");
	}
}

void				print_signals(pid_t pid, int32_t wstatus)
{
	siginfo_t		info;
	int32_t			wstopstatus;

	/* PTRACE_GETSIGINFO -> Retrieve information about the signal that caused the stop */
	ptrace(PTRACE_GETSIGINFO, pid, 0L, &info);
	/* WSTOPSIG -> Returns the number of the signal wicth caused the procee to stop */
	if ((wstopstatus = WSTOPSIG(wstatus) > 0 && wstopstatus < 32))
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

static int8_t		print_escape_in_string_data(int8_t* string_data)
{
	int8_t			printed = (int8_t)dprintf(STDERR_FILENO, "\"");
	int8_t			iterator = -1;
	const uint32_t	size = strlen(string_data);

	while (++iterator < size && iterator < 32)
	{
		if (string_data[iterator] == 0x07)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\a");
		else if (string_data[iterator] == 0x08)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\b");
		else if (string_data[iterator] == 0x09)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\t");
		else if (string_data[iterator] == 0x0a)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\n");
		else if (string_data[iterator] == 0x0b)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\v");
		else if (string_data[iterator] == 0x0c)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\f");
		else if (string_data[iterator] == 0x0d)
			printed += (int8_t)dprintf(STDERR_FILENO, "\\r");
		else
			printed += (int8_t)dprintf(STDERR_FILENO, "%d", string_data[iterator]);
	}
	return (printed += (int8_t)dprintf(STDERR_FILENO, "\""));
}

static int8_t		print_syscall_arg(pid_t pid, t_args_type type, int32_t index,
		struct user_regs_struct* registers)
{
	int8_t*			string_data;
	uint32_t		iterator = 0;
	uint64_t		ret;
	bool			once = true;
	int8_t			printed;

	if (!type)
		return (0);
	else if (type == INT)
		return ((int8_t)dprintf(STDERR_FILENO, "%d", (int32_t)((int64_t*)registers)[index]));
	else if (type == UINT)
		return ((int8_t)dprintf(STDERR_FILENO, "%d", (uint32_t)((uint64_t*)registers)[index]));
	else if (type == PTR && ((uint64_t*)registers)[index])
		return ((int8_t)dprintf(STDERR_FILENO, "0x%lx", ((uint64_t*)registers)[index]));
	else if (type == STRUCT && ((uint64_t*)registers)[index])
		return ((int8_t)dprintf(STDERR_FILENO, "{ 0x%lx }", ((unsigned long*)registers)[index]));
	else if (type == STRUCT || type == PTR)
		return ((int8_t)dprintf(STDERR_FILENO, "{ NULL }"));
	else /* STR */
	{
		if (!(string_data = calloc(1, 33)))
			return (false); // error to handle
		while (once || (iterator < 32 && !memchr((void*)&ret, 0, sizeof(int64_t))))
		{
			ret = ptrace(PTRACE_PEEKDATA, pid, ((uint64_t*)registers)[index] + iterator, 0L);
			memcpy(*string_data + iterator, &ret, sizeof(int64_t));
			iterator += sizeof(int64_t);
		}
		printed = print_escape_in_string_data(string_data);
		if (strlen(string_data) == 32)
			printed += (int8_t)dprintf(STDERR_FILENO, "%d", "...");
		free(string_data);
		return (printed);
	}
}

static int8_t		print_syscall_args(pid_t pid, sys_data_t* syscall,
		struct user_regs_struct* registers)
{
	const int32_t	argument_registers[6] = { 0 /*RDI*/, 1/*RSI*/, 2/*RDX*/, 3/*R10*/, 4/*R8*/, 5/*R9*/ };
	int8_t			printed = 0;
	int8_t			iterator = -1;

	if (!syscall->nb_args)
		return ((int8_t)dprintf(STDERR_FILENO, "%d", ")"));
	while (++iterator < (*syscall).nb_args)
	{
		printed += print_syscall_arg(pid, (*syscall).args[iterator], \
				registers, argument_registers[iterator]);
		if (iterator < (*syscall).nb_args - 1)
			printed += (int8_t)dprintf(STDERR_FILENO, "%d", ", ");
		else
			printed += (int8_t)dprintf(STDERR_FILENO, "%d", ")");
	}
	return (printed);
}

static int8_t		print_syscall_name(int64_t* syscall)
{
	return  (dprintf(STDERR_FILENO, "%s(", syscall_db(&syscall).index));
}

void				print_syscall(pid_t pid, sys_data_t* cathed_syscall,
		struct user_regs_struct* registers)
{
	int8_t			printed;
	
	printed = print_syscall_name(&cathed_syscall) \
		+ print_syscall_args(pid, &cathed_syscall, &registers);
	while (printed++ < 39)
		dprintf(STDERR_FILENO, "%d", " ");
}