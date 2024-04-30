#apt-get install libreadline-dev : on linux

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRC_DIR = src

OBJ_DIR = obj

LIBFT_OBJS = ${LIBFT_DIR}/obj/*

INCLUDES_DIR = includes

SRCS =	main.c					\
		init_struct.c			\
		clean_struct.c			\
		quit_utils.c			\
		assign_op.c				\
		dollar_op.c				\
		custom_split.c			\
		utils2.c				\
		b_cd.c					\
		b_cd_utils.c			\
		b_echo.c				\
		b_env.c					\
		b_exit.c				\
		b_export.c				\
		b_export_utils.c		\
		b_pwd.c					\
		b_unset.c				\
		utils.c					\
		env_utils.c				\
		env_utils_2.c			\
		left_redirection.c		\
		ft_open.c				\
		cmd_handler.c			\
		misc.c					\
		left_delimiter.c		\
		and_handler.c			\
		or_handler.c			\
		signals.c				\
		pipe_handler.c			\
		reset_struct.c			\
		right_redirection.c		\
		right_append.c			\
		parantheses_handler.c	\
		op_utils.c				\
		ft_is_operator.c		\
		ft_encapsulators.c		\
		ft_parser.c				\
		ft_operators.c			\
		ft_handlers.c			\
		ft_findnext.c			\
		ft_handle_found.c

OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_DIR = ${INCLUDES_DIR}/libft
LIBFT = ${LIBFT_DIR}/libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

all : ${NAME}

${NAME} : ${OBJS} ${LIBFT}
	@$(CC) $(CFLAGS) ${INCLUDE_LIBFT} ${LIBFT_OBJS} ${OBJS} -o ${NAME} -lreadline

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
