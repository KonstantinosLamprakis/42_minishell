CC = cc

# CFLAGS = -Wall -Werror -Wextra

CFLAGS =

NAME = minishell

SRC_DIR = src

OBJ_DIR = obj

INCLUDES_DIR = includes

SRCS = ${addprefix ${SRC_DIR}/, builtin_funcs.c}

OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT = libft.a

all : ${NAME}

${NAME} : ${OBJS}
	$(MAKE) -C ./$(INCLUDES_DIR)/libft
	cc $(CFLAGS) $(OBJS) -L$(INCLUDES_DIR)/libft -lft -I $(INCLUDES_DIR)/minishell.h -o $@

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean :
	$(MAKE) clean -C ./$(INCLUDES_DIR)/libft
	rm -f ${OBJS}

fclean : clean
	$(MAKE) fclean -C ./$(INCLUDES_DIR)/libft
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re
