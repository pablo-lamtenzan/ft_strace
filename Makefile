NAME=ft_strace

SRCS=srcs/main.c srcs/error.c srcs/get_tracee_path.c srcs/print.c srcs/signal.c srcs/wait.c srcs/syscall.c srcs/syscall_db.c
OBJDIR=bin
OBJS= $(SRCS:srcs/%.c=$(OBJDIR)/%.o)


all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) $(OBJS)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : srcs/%.c
	gcc -c -o $(OBJDIR)/$(shell basename $@)  -I./includes $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all