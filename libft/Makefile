FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c \
get_next_line_utils_bonus.c conversions.c conversions2.c ft_isdigit.c ft_itoa.c \
ft_memcpy.c ft_printf.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_unsigned_itoa.c \
init_tab.c parse_functions.c precision_functions.c print_util.c width_functions.c \
ft_strncmp.c ft_strlcat.c ft_substr.c ft_strlen_original.c ft_realloc.c \
is_sp.c free_array.c free_array2.c ft_dprintf.c ft_sprintf.c ft_numstr.c \
ft_strjoin_utils.c check_llong.c ft_strjointrue.c
INCLUDES_DIR = ./
INCLUDES = libft.h ft_printf.h
OPTIONS = -I ${INCLUDES}
SRCSBONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
ft_lstmap_bonus.c
OBJS = ${SRCS:.c=.o}
OBJSBONUS = ${SRCSBONUS:.c=.o}

.c.o:		${SRCS} ${SRCSBONUS} ${INCLUDES}
	clang $(FLAGS) -I ${INCLUDES_DIR} -c $^ -o ${<:.c=.o}

$(NAME):	${OBJS} ${INCLUDES}
	ar rcs $@ $^

all:		$(NAME)

bonus: ${OBJS} ${INCLUDES} ${OBJSBONUS}
	ar rcs ${NAME} $^

clean :
	rm -f $(OBJS) ${OBJSBONUS}

fclean :	clean
	rm -f $(NAME)

re:			fclean all

