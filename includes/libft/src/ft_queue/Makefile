CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_queue_srcs =	ft_create_queue.c			\
				ft_clear_queue.c			\
				ft_queue_pop.c				\
				ft_queue_push.c				\
				ft_print_queue.c
SRC_DIR = src/ft_queue
OBJ_DIR = obj
FT_QUEUE_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_QUEUE_SRCS))

all : ${FT_QUEUE_OBJS}

${FT_QUEUE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_queue :
	@mv ${FT_QUEUE_RELATIVE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_queue :
	@rm -f ${FT_QUEUE_OBJS}

fclean_ft_queue : clean

re_ft_queue : fclean all

.PHONY: all move clean fclean re
