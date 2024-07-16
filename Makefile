NAME		= minishell

MINISHELL_DIR	= ./srcs
MINISHELL_HEAD	= ./include

SRCS		= main.c main_utils.c init_shell.c init_env.c init_env_utils.c parser.c parser_utils_1.c parser_utils_2.c parser_list_utils.c parser_polish_list.c parser_env.c \
				parser_matrix.c parser_matrix_utils.c parser_matrix_list.c parser_matrix_list_utils.c signals.c signals_utils.c history.c \
				builtin.c builtin_export.c builtin_export_utils_1.c builtin_export_utils_2.c builtin_export_print.c builtin_export_print_utils.c \
				builtin_env.c builtin_unset.c builtin_unset_utils.c builtin_echo.c ft_getenv.c

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