CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

SRCS =	main.c					\
		init_struct.c			\
		env_utils.c				\
		utils.c					\
		quit_utils.c

OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_DIR = ${INCLUDES_DIR}/libft
LIBFT = ${LIBFT_DIR}/libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

all : ${NAME}

${NAME} : ${OBJS} ${LIBFT}
	@$(CC) $(CFLAGS) ${INCLUDE_LIBFT} ${OBJS} -o ${NAME} -lreadline

${OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

${LIBFT} :
	@make -sC ${LIBFT_DIR} all

clean :
	@rm -f ${OBJS}
	@make -sC ${LIBFT_DIR} clean

fclean : clean
	@rm -f ${NAME}
	@make -sC ${LIBFT_DIR} fclean

re : fclean all

.PHONY: all clean fclean re
