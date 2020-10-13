/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:58:07 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/13 19:15:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syscall_db.h>

sys_data_t      syscall_db(int64_t *index)
{
    const sys_data_t  db[333] = {
    {.index="read", .nb_args=3, .args={INT,PTR,UINT,NONE,NONE,NONE } },
    {.index="write", .nb_args=3, .args={UINT,PTR,UINT,NONE,NONE,NONE } },
	{.index="open", .nb_args=3, .args={STR,INT,INT,NONE,NONE,NONE } },
	{.index="close", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="stat", .nb_args = 2, .args={STR,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="fstat", .nb_args=2, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="lstat", .nb_args=2, .args={STR,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="poll", .nb_args=3, .args={STRUCT,UINT,INT,NONE,NONE,NONE } },
	{.index="lseek", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="mmap", .nb_args=6, .args={PTR,UINT,INT,INT,INT,PTR } },
	{.index="mprotect", .nb_args=3, .args={PTR,UINT,UINT,NONE,NONE,NONE } },
	{.index="munmap", .nb_args=2, .args={PTR,UINT,NONE,NONE,NONE,NONE } },
	{.index="brk", .nb_args=1, .args={PTR,NONE,NONE,NONE,NONE,NONE } },
	{.index="rt_sigaction", .nb_args=4, .args={INT,STRUCT,STRUCT,INT,NONE,NONE } },
	{.index="rt_sigprocmask", .nb_args=4, .args={INT,PTR,PTR,INT,NONE,NONE } },
	{.index="rt_sigreturn", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="ioctl", .nb_args=2, .args={INT,UINT,NONE,NONE,NONE,NONE } },
	{.index="pread64", .nb_args=4, .args={UINT,PTR,UINT,INT,NONE,NONE } },
	{.index="pwrite64", .nb_args=4, .args={UINT,PTR,UINT,INT,NONE,NONE } },
	{.index="readv", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="writev", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="access", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="pipe", .nb_args=1, .args={PTR,NONE,NONE,NONE,NONE,NONE } },
	{.index="select", .nb_args=5, .args={INT,PTR,PTR,PTR,STRUCT,NONE } },
	{.index="sched_yield", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="mremap", .nb_args=5, .args={PTR,UINT,UINT,INT,NONE,NONE } },
	{.index="msync", .nb_args=3, .args={PTR,UINT,INT,NONE,NONE,NONE } },
	{.index="mincore", .nb_args=3, .args={UINT,UINT,UINT,NONE,NONE,NONE } },
	{.index="madvise", .nb_args=3, .args={UINT,UINT,INT,NONE,NONE,NONE } },
	{.index="shmget", .nb_args=3, .args={INT,UINT,INT,NONE,NONE,NONE } },
	{.index="shmat", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="shmctl", .nb_args=3, .args={INT,INT,STRUCT,NONE,NONE,NONE } },
	{.index="dup", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="dup2", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="pause", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="nanosleep", .nb_args=2, .args={STRUCT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="getitimer", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="alarm", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="setitimer", .nb_args=3, .args={INT,STRUCT,STRUCT,NONE,NONE,NONE } },
	{.index="getpid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="sendfile", .nb_args=4, .args={INT,INT,PTR,UINT,NONE,NONE } },
	{.index="socket", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="connect", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="accept", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="sendto", .nb_args=6, .args={INT,PTR,UINT,UINT,STRUCT,INT } },
	{.index="recvfrom", .nb_args=6, .args={INT,PTR,UINT,UINT,STRUCT,INT } },
	{.index="sendmsg", .nb_args=3, .args={INT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="recvmsg", .nb_args=3, .args={INT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="shutdown", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="bind", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="listen", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="getsockname", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="getpeername", .nb_args=3, .args={INT,STRUCT,INT,NONE,NONE,NONE } },
	{.index="socketpair", .nb_args=4, .args={INT,INT,INT,INT,NONE,NONE } },
	{.index="setsockopt", .nb_args=5, .args={INT,INT,INT,STR,INT,NONE } },
	{.index="getsockopt", .nb_args=5, .args={INT,INT,INT,STR,INT,NONE } },
	{.index="clone", .nb_args=4, .args={UINT,PTR,INT,PTR,NONE,NONE } },
	{.index="fork", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="vfork", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="execve", .nb_args=3, .args={STR,PTR,PTR,NONE,NONE,NONE } },
	{.index="exit", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="wait4", .nb_args=4, .args={INT,PTR,INT,STRUCT,NONE,NONE } },
	{.index="kill", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="uname", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="semget", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="semop", .nb_args=3, .args={INT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="semctl", .nb_args=4, .args={INT,INT,INT,UINT,NONE,NONE } },
	{.index="shmdt", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="msgget", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="msgsnd", .nb_args=4, .args={INT,STRUCT,UINT,INT,NONE,NONE } },
	{.index="msgrcv", .nb_args=5, .args={INT,STRUCT,UINT,INT,INT,NONE } },
	{.index="msgctl", .nb_args=3, .args={INT,INT,STRUCT,NONE,NONE,NONE } },
	{.index="fcntl", .nb_args=3, .args={UINT,UINT,UINT,NONE,NONE,NONE } },
	{.index="flock", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="fsync", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="fdatasync", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="truncate", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="ftruncate", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="getdents", .nb_args=3, .args={UINT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="getcwd", .nb_args=2, .args={STR,UINT,NONE,NONE,NONE,NONE } },
	{.index="chdir", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="fchdir", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="rename", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="mkdir", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="rmdir", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="creat", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="link", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="unlink", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="symlink", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="readlink", .nb_args=3, .args={PTR,PTR,INT,NONE,NONE,NONE } },
	{.index="chmod", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="fchmod", .nb_args=2, .args={UINT,INT,NONE,NONE,NONE,NONE } },
	{.index="chown", .nb_args=3, .args={STR,INT,INT,NONE,NONE,NONE } },
	{.index="fchown", .nb_args=3, .args={UINT,INT,INT,NONE,NONE,NONE } },
	{.index="lchown", .nb_args=3, .args={STR,INT,INT,NONE,NONE,NONE } },
	{.index="umask", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="gettimeofday", .nb_args=2, .args={STRUCT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="getrlimit", .nb_args=1, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="getrusage", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="sysinfo", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="times", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="ptrace", .nb_args=4, .args={INT,INT,UINT,UINT,NONE,NONE } },
	{.index="getuid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="syslog", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="getgid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="setuid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="setgid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="geteuid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="getegid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="setpgid", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="getppid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="getpgrp", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="setsid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="setreuid", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="setregid", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="getgroups", .nb_args=2, .args={INT,PTR,NONE,NONE,NONE,NONE } },
	{.index="setgroups", .nb_args=2, .args={INT,PTR,NONE,NONE,NONE,NONE } },
	{.index="setresuid", .nb_args=3, .args={PTR,PTR,PTR,NONE,NONE,NONE } },
	{.index="getresuid", .nb_args=3, .args={PTR,PTR,PTR,NONE,NONE,NONE } },
	{.index="setresgid", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="getresgid", .nb_args=3, .args={PTR,PTR,PTR,NONE,NONE,NONE } },
	{.index="getpgid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="setfsuid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="setfsgid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="getsid", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="capget", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="capset", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="rt_sigpending", .nb_args=2, .args={PTR,UINT,NONE,NONE,NONE,NONE } },
	{.index="rt_sigtimedwait", .nb_args=4, .args={PTR,PTR,STRUCT,UINT,NONE,NONE } },
	{.index="rt_sigqueueinfo", .nb_args=3, .args={INT,INT,PTR,NONE,NONE,NONE } },
	{.index="rt_sigsuspend", .nb_args=2, .args={PTR,UINT,NONE,NONE,NONE,NONE } },
	{.index="sigaltstack", .nb_args=2, .args={PTR,PTR,NONE,NONE,NONE,NONE } },
	{.index="utime", .nb_args=2, .args={STR,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="mknod", .nb_args=3, .args={STR,INT,UINT,NONE,NONE,NONE } },
	{.index="uselib", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="personality", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="ustat", .nb_args=2, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="statfs", .nb_args=2, .args={STR,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="fstatfs", .nb_args=2, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="sysfs", .nb_args=3, .args={INT,UINT,UINT,NONE,NONE,NONE } },
	{.index="getpriority", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="setpriority", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="sched_setparam", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="sched_getparam", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="sched_setscheduler", .nb_args=3, .args={INT,INT,STRUCT,NONE,NONE,NONE } },
	{.index="sched_getscheduler", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="sched_get_priority_max", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="sched_get_priority_min", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="sched_rr_get_interval", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="mlock", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="munlock", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="mlockall", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="munlockall", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="vhangup", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="modify_ldt", .nb_args=3, .args={INT,PTR,UINT,NONE,NONE,NONE } },
	{.index="pivot_root", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="sysctl", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="prctl", .nb_args=4, .args={INT,UINT,UINT,UINT,NONE,NONE } },
	{.index="arch_prctl", .nb_args=2, .args={INT,PTR,NONE,NONE,NONE,NONE } },
	{.index="adjtimex", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="setrlimit", .nb_args=2, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="chroot", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="sync", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="acct", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="settimeofday", .nb_args=2, .args={STRUCT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="mount", .nb_args=5, .args={STR,STR,STR,UINT,PTR,NONE } },
	{.index="umount2", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="swapon", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="swapoff", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="reboot", .nb_args=4, .args={INT,INT,UINT,PTR,NONE,NONE } },
	{.index="sethostname", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="setdomainname", .nb_args=2, .args={STR,INT,NONE,NONE,NONE,NONE } },
	{.index="iopl", .nb_args=2, .args={UINT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="ioperm", .nb_args=3, .args={UINT,UINT,INT,NONE,NONE,NONE } },
	{.index="create_module", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="init_module", .nb_args=3, .args={PTR,UINT,STR,NONE,NONE,NONE } },
	{.index="delete_module", .nb_args=2, .args={STR,UINT,NONE,NONE,NONE,NONE } },
	{.index="get_kernel_syms", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="query_module", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="quotactl", .nb_args=4, .args={UINT,STR,INT,PTR,NONE,NONE } },
	{.index="nfsservctl", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="getpmsg", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="putpmsg", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="afs_syscall", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="tuxcall", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="security", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="gettid", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="readahead", .nb_args=3, .args={INT,INT,UINT,NONE,NONE,NONE } },
	{.index="setxattr", .nb_args=5, .args={STR,STR,PTR,UINT,INT,NONE } },
	{.index="lsetxattr", .nb_args=5, .args={STR,STR,PTR,UINT,INT,NONE } },
	{.index="fsetxattr", .nb_args=5, .args={INT,STR,PTR,UINT,INT,NONE } },
	{.index="getxattr", .nb_args=4, .args={STR,STR,PTR,UINT,NONE,NONE } },
	{.index="lgetxattr", .nb_args=4, .args={STR,STR,PTR,UINT,NONE,NONE } },
	{.index="fgetxattr", .nb_args=4, .args={INT,STR,PTR,UINT,NONE,NONE } },
	{.index="listxattr", .nb_args=3, .args={STR,STR,UINT,NONE,NONE,NONE } },
	{.index="llistxattr", .nb_args=3, .args={STR,STR,UINT,NONE,NONE,NONE } },
	{.index="flistxattr", .nb_args=3, .args={INT,STR,UINT,NONE,NONE,NONE } },
	{.index="removexattr", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="lremovexattr", .nb_args=2, .args={STR,STR,NONE,NONE,NONE,NONE } },
	{.index="fremovexattr", .nb_args=2, .args={INT,STR,NONE,NONE,NONE,NONE } },
	{.index="tkill", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="time", .nb_args=1, .args={PTR,NONE,NONE,NONE,NONE,NONE } },
	{.index="futex", .nb_args=6, .args={INT,INT,INT,STRUCT,INT,INT } },
	{.index="sched_setaffinity", .nb_args=3, .args={INT,UINT,UINT,NONE,NONE,NONE } },
	{.index="sched_getaffinity", .nb_args=3, .args={INT,UINT,UINT,NONE,NONE,NONE } },
	{.index="set_thread_area", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="io_setup", .nb_args=2, .args={UINT,PTR,NONE,NONE,NONE,NONE } },
	{.index="io_destroy", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="io_getevents", .nb_args=4, .args={INT,INT,INT,STRUCT,NONE,NONE } },
	{.index="io_submit", .nb_args=3, .args={INT,INT,STRUCT,NONE,NONE,NONE } },
	{.index="io_cancel", .nb_args=3, .args={INT,STRUCT,STRUCT,NONE,NONE,NONE } },
	{.index="get_thread_area", .nb_args=1, .args={STRUCT,NONE,NONE,NONE,NONE,NONE } },
	{.index="lookup_dcookie", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="epoll_create", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="epoll_ctl_old", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="epoll_wait_old", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="remap_file_pages", .nb_args=5, .args={UINT,UINT,UINT,UINT,UINT,NONE } },
	{.index="getdents64", .nb_args=3, .args={UINT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="set_tid_address", .nb_args=1, .args={PTR,NONE,NONE,NONE,NONE,NONE } },
	{.index="restart_syscall", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="semtimedop", .nb_args=4, .args={INT,STRUCT,UINT,STRUCT,NONE,NONE } },
	{.index="fadvise64", .nb_args=4, .args={INT,INT,UINT,INT,NONE,NONE } },
	{.index="timer_create", .nb_args=3, .args={INT,STRUCT,PTR,NONE,NONE,NONE } },
	{.index="timer_settime", .nb_args=4, .args={INT,INT,STRUCT,STRUCT,NONE,NONE } },
	{.index="timer_gettime", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="timer_getoverrun", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="timer_delete", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="clock_settime", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="clock_gettime", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="clock_getres", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="clock_nanosleep", .nb_args=4, .args={INT,INT,STRUCT,STRUCT,NONE,NONE } },
	{.index="exit_group", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="epoll_wait", .nb_args=4, .args={INT,STRUCT,INT,INT,NONE,NONE } },
	{.index="epoll_ctl", .nb_args=4, .args={INT,INT,INT,STRUCT,NONE,NONE } },
	{.index="tgkill", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="utimes", .nb_args=2, .args={STR,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="vserver", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="mbind", .nb_args=6, .args={UINT,UINT,UINT,UINT,UINT,UINT } },
	{.index="set_mempolicy", .nb_args=3, .args={INT,UINT,UINT,NONE,NONE,NONE } },
	{.index="get_mempolicy", .nb_args=5, .args={INT,UINT,UINT,UINT,UINT,NONE } },
	{.index="mq_open", .nb_args=4, .args={STR,INT,INT,STRUCT,NONE,NONE } },
	{.index="mq_unlink", .nb_args=1, .args={STR,NONE,NONE,NONE,NONE,NONE } },
	{.index="mq_timedsend", .nb_args=5, .args={INT,STR,UINT,UINT,STRUCT,NONE } },
	{.index="mq_timedreceive", .nb_args=5, .args={INT,STR,UINT,UINT,STRUCT,NONE } },
	{.index="mq_notify", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="mq_getsetattr", .nb_args=2, .args={STRUCT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="kexec_load", .nb_args=4, .args={UINT,UINT,STRUCT,UINT,NONE,NONE } },
	{.index="waitid", .nb_args=5, .args={INT,INT,STRUCT,INT,STRUCT,NONE } },
	{.index="add_key", .nb_args=4, .args={STR,STR,PTR,UINT,NONE,NONE } },
	{.index="request_key", .nb_args=4, .args={STR,STR,STR,INT,NONE,NONE } },
	{.index="keyctl", .nb_args=5, .args={INT,UINT,UINT,UINT,UINT,NONE } },
	{.index="ioprio_set", .nb_args=3, .args={INT,INT,INT,NONE,NONE,NONE } },
	{.index="ioprio_get", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="inotify_init", .nb_args=0, .args={NONE,NONE,NONE,NONE,NONE,NONE } },
	{.index="inotify_add_watch", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="inotify_rm_watch", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="migrate_pages", .nb_args=4, .args={INT,UINT,UINT,UINT,NONE,NONE } },
	{.index="openat", .nb_args=4, .args={INT,STR,INT,INT,NONE,NONE } },
	{.index="mkdirat", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="mknodat", .nb_args=4, .args={INT,STR,INT,UINT,NONE,NONE } },
	{.index="fchownat", .nb_args=5, .args={INT,STR,INT,INT,INT,NONE } },
	{.index="futimesat", .nb_args=3, .args={INT,STR,STRUCT,NONE,NONE,NONE } },
	{.index="newfstatat", .nb_args=4, .args={INT,STR,STRUCT,INT,NONE,NONE } },
	{.index="unlinkat", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="renameat", .nb_args=4, .args={INT,STR,INT,STR,NONE,NONE } },
	{.index="linkat", .nb_args=5, .args={INT,STR,INT,STR,INT,NONE } },
	{.index="symlinkat", .nb_args=3, .args={STR,INT,STR,NONE,NONE,NONE } },
	{.index="readlinkat", .nb_args=4, .args={INT,PTR,PTR,INT,NONE,NONE } },
	{.index="fchmodat", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="faccessat", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="pselect6", .nb_args=6, .args={INT,PTR,PTR,PTR,STRUCT,PTR } },
	{.index="ppoll", .nb_args=5, .args={STRUCT,UINT,STRUCT,PTR,UINT,NONE } },
	{.index="unshare", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="set_robust_list", .nb_args=2, .args={STRUCT,UINT,NONE,NONE,NONE,NONE } },
	{.index="get_robust_list", .nb_args=3, .args={INT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="splice", .nb_args=6, .args={INT,PTR,INT,PTR,UINT,UINT } },
	{.index="tee", .nb_args=4, .args={INT,INT,UINT,UINT,NONE,NONE } },
	{.index="sync_file_range", .nb_args=4, .args={INT,INT,INT,INT,NONE,NONE } },
	{.index="vmsplice", .nb_args=4, .args={INT,STRUCT,UINT,UINT,NONE,NONE } },
	{.index="move_pages", .nb_args=6, .args={INT,UINT,PTR,INT,INT,INT } },
	{.index="utimensat", .nb_args=4, .args={INT,STR,STRUCT,INT,NONE,NONE } },
	{.index="epoll_pwait", .nb_args=6, .args={INT,STRUCT,INT,INT,PTR,UINT } },
	{.index="signalfd", .nb_args=3, .args={INT,PTR,UINT,NONE,NONE,NONE } },
	{.index="timerfd_create", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="eventfd", .nb_args=1, .args={UINT,NONE,NONE,NONE,NONE,NONE } },
	{.index="fallocate", .nb_args=4, .args={INT,INT,INT,INT,NONE,NONE } },
	{.index="timerfd_settime", .nb_args=4, .args={INT,INT,STRUCT,STRUCT,NONE,NONE } },
	{.index="timerfd_gettime", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="accept4", .nb_args=4, .args={INT,STRUCT,INT,INT,NONE,NONE } },
	{.index="signalfd4", .nb_args=4, .args={INT,PTR,UINT,INT,NONE,NONE } },
	{.index="eventfd2", .nb_args=2, .args={UINT,INT,NONE,NONE,NONE,NONE } },
	{.index="epoll_create1", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="dup3", .nb_args=3, .args={UINT,UINT,INT,NONE,NONE,NONE } },
	{.index="pipe2", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="inotify_init1", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="preadv", .nb_args=5, .args={UINT,STRUCT,UINT,UINT,UINT,NONE } },
	{.index="pwritev", .nb_args=5, .args={UINT,STRUCT,UINT,UINT,UINT,NONE } },
	{.index="rt_tgsigqueueinfo", .nb_args=4, .args={INT,INT,INT,PTR,NONE,NONE } },
	{.index="perf_event_open", .nb_args=5, .args={STRUCT,INT,INT,INT,UINT,NONE } },
	{.index="recvmmsg", .nb_args=5, .args={INT,STRUCT,UINT,UINT,STRUCT,NONE } },
	{.index="fanotify_init", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="fanotify_mark", .nb_args=5, .args={INT,INT,INT,INT,INT,NONE } },
	{.index="prlimit64", .nb_args=4, .args={INT,UINT,STRUCT,STRUCT,NONE,NONE } },
	{.index="name_to_handle_at", .nb_args=5, .args={INT,STR,STRUCT,INT,INT,NONE } },
	{.index="open_by_handle_at", .nb_args=5, .args={INT,STR,STRUCT,INT,INT,NONE } },
	{.index="clock_adjtime", .nb_args=2, .args={INT,STRUCT,NONE,NONE,NONE,NONE } },
	{.index="syncfs", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="sendmmsg", .nb_args=4, .args={INT,STRUCT,UINT,UINT,NONE,NONE } },
	{.index="setns", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="getcpu", .nb_args=3, .args={UINT,UINT,STRUCT,NONE,NONE,NONE } },
	{.index="process_vm_readv", .nb_args=6, .args={INT,STRUCT,UINT,STRUCT,UINT,UINT } },
	{.index="process_vm_writev", .nb_args=6, .args={INT,STRUCT,UINT,STRUCT,UINT,UINT } },
	{.index="kcmp", .nb_args=5, .args={INT,INT,INT,UINT,UINT,NONE } },
	{.index="finit_module", .nb_args=3, .args={INT,STR,INT,NONE,NONE,NONE } },
	{.index="sched_setattr", .nb_args=3, .args={INT,STRUCT,UINT,NONE,NONE,NONE } },
	{.index="sched_getattr", .nb_args=4, .args={INT,STRUCT,UINT,UINT,NONE,NONE } },
	{.index="renameat2", .nb_args=5, .args={INT,STR,INT,STR,UINT,NONE } },
	{.index="seccomp", .nb_args=3, .args={UINT,UINT,STR,NONE,NONE,NONE } },
	{.index="getrandom", .nb_args=3, .args={STR,UINT,UINT,NONE,NONE,NONE } },
	{.index="memfd_create", .nb_args=2, .args={STR,UINT,NONE,NONE,NONE,NONE } },
	{.index="kexec_file_load", .nb_args=5, .args={INT,INT,UINT,STR,UINT,NONE } },
	{.index="bpf", .nb_args=3, .args={INT,PTR,UINT,NONE,NONE,NONE } },
	{.index="execveat", .nb_args=5, .args={INT,STR,PTR,PTR,INT,NONE } },
	{.index="userfaultfd", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="membarrier", .nb_args=2, .args={INT,INT,NONE,NONE,NONE,NONE } },
	{.index="mlock2", .nb_args=3, .args={UINT,UINT,INT,NONE,NONE,NONE } },
	{.index="copy_file_range", .nb_args=6, .args={INT,PTR,INT,PTR,UINT,UINT } },
	{.index="preadv2", .nb_args=6, .args={UINT,STRUCT,UINT,UINT,UINT,INT } },
	{.index="pwritev2", .nb_args=6, .args={UINT,STRUCT,UINT,UINT,UINT,INT } },
	/* ====================================================================================== */
	{.index="pkey_mprotect", .nb_args=4, .args={PTR,UINT,INT,INT,NONE,NONE } },
	{.index="pkey_alloc", .nb_args=2, .args={UINT,UINT,NONE,NONE,NONE,NONE } },
	{.index="pkey_free", .nb_args=1, .args={INT,NONE,NONE,NONE,NONE,NONE } },
	{.index="statx", .nb_args=5, .args={INT,STR,INT,UINT,STRUCT,NONE } }
    };
    return (db[*index]);
}
