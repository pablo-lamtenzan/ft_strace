# ft_strace

Implememtation of my own strace cmd (as 42 schools's project) from scracth, using ptrace but the options PTRACE_TRACEME and PTRACE_ATTACH aren't allowed.

ISSUES:
- Works well but the argumenet must be preceded by "./" (it doesn't works not because i don't wanna fix it, but because i have to test my parsing in ubutu before the fix it (i ve developepd it in arch)).
