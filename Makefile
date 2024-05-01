# apt-get install libreadline-dev : on linux

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj

LIBFT_OBJS = ${LIBFT_DIR}/obj/*

INCLUDES_DIR = includes

RESET_COLOR = \033[0m
G1_COLOR = \033[38;5;160m
G2_COLOR = \033[38;5;125m
G3_COLOR = \033[38;5;90m
G4_COLOR = \033[38;5;55m
G5_COLOR = \033[38;5;20m

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
		utils3.c				\
		left_redirection.c		\
		ft_open.c				\
		cmd_handler.c			\
		misc.c					\
		left_delimiter.c		\
		left_delimiter2.c		\
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
		ft_handle_found.c		\
		ms_error.c				\
		ft_escsplit.c			\
		token_validation.c		\
		rel_path.c

OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_DIR = ${INCLUDES_DIR}/libft
LIBFT = ${LIBFT_DIR}/libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

all : ${NAME}
	@make ascii_art

ascii_art :
	@echo "${G1_COLOR}                 _         _        __           __ __  ${RESET_COLOR}"
	@echo "${G2_COLOR}     ____ ___   (_)____   (_)_____ / /_   ___   / // /  ${RESET_COLOR}"
	@echo "${G3_COLOR}    / __ \`__ \ / // __ \ / // ___// __ \ / _ \ / // /   ${RESET_COLOR}"
	@echo "${G4_COLOR}   / / / / / // // / / // /(__  )/ / / //  __// // /    ${RESET_COLOR}"
	@echo "${G5_COLOR}  /_/ /_/ /_//_//_/ /_//_//____//_/ /_/ \___//_//_/     ${RESET_COLOR}"
	@echo "                                                        "
	@echo "                              by: @klamprak & @lgreau   "

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
