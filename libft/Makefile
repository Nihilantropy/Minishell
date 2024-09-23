NAME		= libft.a

LIBFT_DIR	= ./srcs

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c ft_memset.c ft_strlen.c \
				ft_atoi.c ft_memset.c ft_bzero.c ft_memmove.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
				ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_calloc.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putchar.c ft_atol.c ft_putnl.c \
				ft_exit_result.c ft_isdigit_str.c ft_strcmp.c get_next_line.c get_next_line_utils.c ft_isspace_str.c
					
B_SRCS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		= $(patsubst %.c, $(LIBFT_DIR)/%.o, $(SRCS))

B_OBJS		= $(patsubst %.c, $(LIBFT_DIR)/%.o, $(B_SRCS))

HEADER_DIR	= ./include

HEADER		= libft.h

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

AR			= ar rcs

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

%.o: 		%.c $(HEADER_DIR)
			$(CC) -c $< $(CFLAGS) -o $@  -I$(HEADER)

all:		$(NAME)

bonus:		$(B_OBJS)
			$(AR) $(NAME) $(B_OBJS)

clean:
			$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re