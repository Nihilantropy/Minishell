NAME		= minishell

MINISHELL_DIR	= ./srcs
MINISHELL_HEAD	= ./include

MAIN_DIR		= ./main
PARSER_DIR		= ./parser
BUILTIN_DIR		= ./builtin
SIGNAL_DIR		= ./signal
EXECUTOR_DIR	= ./executor

SRCS		=	$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/main_utils.c \
				$(MAIN_DIR)/init_shell.c \
				$(MAIN_DIR)/init_env.c \
				$(MAIN_DIR)/init_env_utils_1.c \
				$(MAIN_DIR)/init_env_utils_2.c \
				$(MAIN_DIR)/history.c \
				$(MAIN_DIR)/ft_getenv.c \
				$(PARSER_DIR)/parser.c \
				$(PARSER_DIR)/parser_utils_1.c \
				$(PARSER_DIR)/parser_utils_2.c \
				$(PARSER_DIR)/parser_list_utils.c \
				$(PARSER_DIR)/parser_polish_list.c \
				$(PARSER_DIR)/parser_polish_list_utils.c \
				$(PARSER_DIR)/parser_env.c \
				$(PARSER_DIR)/parser_env_utils.c \
				$(PARSER_DIR)/parser_cmd.c \
				$(PARSER_DIR)/parser_cmd_utils.c \
				$(PARSER_DIR)/parser_cmd_redir.c \
				$(PARSER_DIR)/parser_cmd_redir_utils.c \
				$(PARSER_DIR)/parser_cmd_list.c \
				$(PARSER_DIR)/parser_cmd_list_utils.c \
				$(PARSER_DIR)/parser_heredoc.c \
				$(SIGNAL_DIR)/signal.c \
				$(SIGNAL_DIR)/signal_sigint.c \
				$(SIGNAL_DIR)/signal_sigterm.c \
				$(SIGNAL_DIR)/signal_sigquit.c \
				$(BUILTIN_DIR)/builtin.c \
				$(BUILTIN_DIR)/builtin_export.c \
				$(BUILTIN_DIR)/builtin_export_utils_1.c \
				$(BUILTIN_DIR)/builtin_export_utils_2.c \
				$(BUILTIN_DIR)/builtin_export_print.c \
				$(BUILTIN_DIR)/builtin_export_print_utils.c \
				$(BUILTIN_DIR)/builtin_env.c \
				$(BUILTIN_DIR)/builtin_unset.c \
				$(BUILTIN_DIR)/builtin_unset_utils.c \
				$(BUILTIN_DIR)/builtin_echo.c \
				$(BUILTIN_DIR)/builtin_pwd.c \
				$(BUILTIN_DIR)/builtin_exit.c \
				$(BUILTIN_DIR)/builtin_cd.c \
				$(BUILTIN_DIR)/builtin_cd_utils.c \
				$(EXECUTOR_DIR)/executor.c \
				$(EXECUTOR_DIR)/executor_redir.c \
				$(EXECUTOR_DIR)/executor_process.c \
				$(EXECUTOR_DIR)/executor_command.c \
				$(EXECUTOR_DIR)/executor_command_utils.c

OBJS		= $(patsubst %.c, $(MINISHELL_DIR)/%.o, $(SRCS))

LIBFT_DIR	= ./libft
LIBFT		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
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

fclean:
			$(RM) $(OBJS)
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all


.PHONY:		all clean fclean re