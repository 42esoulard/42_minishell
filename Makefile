
SRCS		= ./sources/main.c ./sources/general_parser.c ./sources/env_utils.c \
				./sources/export.c ./sources/env_utils2.c ./sources/cmd_utils.c \
				./sources/cmd_utils2.c ./sources/obj_utils.c ./sources/obj_utils2.c \
				./sources/string_utils.c ./sources/string_utils2.c ./sources/redir.c \
				./sources/redir_utils.c ./sources/redir_err.c ./sources/parse_var.c \
				./sources/env_utils3.c ./sources/err_utils.c ./sources/exec_utils.c \
				./sources/check_path.c ./sources/cmd_utils3.c ./sources/sample_str.c \
				./sources/parsing.c ./sources/export2.c ./sources/export3.c ./sources/init.c \
				./sources/pipes.c ./sources/fork_utils.c ./sources/exec_utils2.c \
				./sources/exec_utils3.c ./sources/gnl_ms.c ./sources/env_utils4.c \
				./sources/string_utils3.c ./sources/split_var.c ./sources/env_utils5.c \
				./sources/string_utils4.c

INC_DIR		= ./includes/
INCLUDES	= ./includes/minishell.h

OBJS		= ${SRCS:.c=.o}

CC			= clang
CFLAGS		= -Wall -Wextra -Werror

NAME		= minishell

LIBFT		= ./libft/libft.a
LIBFTINC	= ./libft

.c.o:		${SRCS} ${INCLUDES}
			${CC} ${CFLAGS} -I ${LIBFTINC} -I ${INC_DIR} -c $^ -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			make -C ./libft
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

clean :
			rm -f ${OBJS}

fclean :	clean
			make fclean -C ./libft
			rm -f ${NAME}

re :		fclean all
