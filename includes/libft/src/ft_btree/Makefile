sCC = cc
CFLAGS = -Werror -Wextra -Wall

ft_btree_srcs =	ft_btree_create_node.c				\
				ft_btree_iter_prefix.c				\
				ft_btree_iter_infix.c				\
				ft_btree_iter_postfix.c				\
				ft_btree_iter_breadth.c				\
				ft_btree_iter_depth.c				\
				ft_btree_traverse.c					\
				ft_clear_btree.c					\
				ft_sbtree_find_last.c				\
				ft_sbtree_insert.c
SRC_DIR = src/ft_btree
OBJ_DIR = obj
FT_BTREE_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_BTREE_SRCS))

all : ${FT_BTREE_OBJS}

${FT_BTREE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@${CC} ${CFLAGS} -c $< -o $@
	@$(eval EQUALS_COUNT=$(shell echo "$(PROGRESS_PERCENT) / (${PERCENT_PER_EQUAL_SIGN} * 100)" | bc))
	@$(eval PROGRESS_PERCENT=$(shell echo "$(PROGRESS_PERCENT) + $(PERCENT_PER_FILE) * 100" | bc))
	@$(eval NEW_EQUALS_COUNT=$(shell echo "$(PROGRESS_PERCENT) / (${PERCENT_PER_EQUAL_SIGN} * 100)" | bc))
	@if [ "$(NEW_EQUALS_COUNT)" -ne "${EQUALS_COUNT}" ]; then \
		printf "\r${GRAY_COLOR}    /+ "; \
		for i in `seq 1 $(FINAL_LEN)`; do \
			if [ $$i -le $(NEW_EQUALS_COUNT) ]; then \
				printf "="; \
			else \
				printf " "; \
			fi; \
		done; \
		printf " +\\    ${RESET_COLOR}"; \
	fi

.PHONY: compile_file

move_ft_btree :
	@mv ${FT_BTREE_RELATIVE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_btree :
	@rm -f ${FT_BTREE_OBJS}

fclean_ft_btree : clean

re_ft_btree : fclean all

.PHONY: all move clean fclean re
