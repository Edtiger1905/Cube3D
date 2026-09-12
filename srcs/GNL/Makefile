NAME = gnl.a

OBJDIR = obj
SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

CC      = cc
RM      = rm -f

CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re