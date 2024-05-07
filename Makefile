NAME		= minishell

MINISHELL_DIR	= ./srcs
MINISHELL_HEAD	= ./include

SRCS		= main.c

OBJS		= $(patsubst %.c, $(MINISHELL_DIR)/%.o, $(SRCS))

LIBFT_DIR	= ./libft
LIBFT		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Include directory for header files
INC 		= -I$(MINISHELL_HEAD) -I$(LIBFT_DIR)

# Compilation rule for the program
$(NAME):	$(OBJS) $(LIBFT) $(PRINTF_LIB)
			$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)


# Rule to compile object files
%.o:		%.c	$(MINISHELL_HEAD)
			$(CC) -c $< $(CFLAGS) -o $@ $(INC)

# Rule to make libft
$(LIBFT):	
			$(MAKE) -C $(LIBFT_DIR)


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all


.PHONY:		all clean fclean re