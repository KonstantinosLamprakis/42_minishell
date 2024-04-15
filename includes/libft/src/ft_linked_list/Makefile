CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_linked_list_srcs =	ft_lstnew.c					\
						ft_lstsize.c				\
						ft_lstlast.c				\
						ft_lstadd_front.c			\
						ft_lstadd_back.c			\
						ft_lstclear.c				\
						ft_lstdelone.c				\
						ft_lstiter.c				\
						ft_lstmap.c
SRC_DIR = src/ft_linked_list
OBJ_DIR = obj
FT_LINKED_LIST_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_LINKED_LIST_SRCS))

all : ${FT_LINKED_LIST_OBJS}

${FT_LINKED_LIST_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_linked_list :
	@mv ${FT_LINKED_LIST_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_linked_list :
	@rm -f ${FT_LINKED_LIST_OBJS}

fclean_ft_linked_list : clean

re_ft_linked_list : fclean all

.PHONY: all move clean fclean re