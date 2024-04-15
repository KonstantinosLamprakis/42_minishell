CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

SRCS =
OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT = libft.a

all : ${NAME}

${NAME} : ${OBJS}
	@ar rcs ${NAME} ${OBJS}

clean :
	@rm -f ${OBJS}

fclean : clean
	@rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re
