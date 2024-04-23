CC = cc

CFLAGS = #-Wall -Werror -Wextra

NAME = minishell

SRC_DIR = src

OBJ_DIR = obj

INCLUDES_DIR = includes

SRCS =	main.c					\
		init_struct.c			\
		quit_utils.c			\
		b_cd.c					\
		b_echo.c				\
		b_env.c					\
		b_exit.c				\
		b_export.c				\
		b_pwd.c					\
		b_unset.c				\
		utils.c					\
		env_utils.c

OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_DIR = ${INCLUDES_DIR}/libft
LIBFT = ${LIBFT_DIR}/libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

all : ${NAME}

${NAME} : ${OBJS} ${LIBFT}
	@$(CC) $(CFLAGS) ${INCLUDE_LIBFT} ${OBJS} -o ${NAME}

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
