NAME		= minishell

MINISHELL_DIR	= ./srcs
MINISHELL_HEAD	= ./include

SRCS		= main.c main_utils.c init_shell.c parser.c parser_utils.c parser_list_utils.c parser_env.c signals.c signals_utils.c history.c 

OBJS		= $(patsubst %.c, $(MINISHELL_DIR)/%.o, $(SRCS))

LIBFT_DIR	= ./libft
LIBFT		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Include directory for header files
INC 		= -I$(MINISHELL_HEAD) -I$(LIBFT_DIR)

# Compilation rule for the program
$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

# Rule to compile object files
%.o:		%.c
			$(CC) -c $< $(CFLAGS) -o $@ $(INC)

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all


.PHONY:		all clean fclean re