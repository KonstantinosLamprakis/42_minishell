CC = cc
CFLAGS := -Wall -Wextra -Werror

ft_get_next_line_srcs =	ft_get_next_line.c			\
						ft_get_next_line_utils.c	\
						ft_get_next_line_nonl.c
SRC_DIR = src/ft_get_next_line
OBJ_DIR = obj
FT_GET_NEXT_LINE_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_GET_NEXT_LINE_SRCS))

all : ${FT_GET_NEXT_LINE_OBJS}

${FT_GET_NEXT_LINE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_get_next_line :
	@mv ${SRC_DIR}/${FT_GET_NEXT_LINE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_get_next_line :
	@rm -f ${FT_GET_NEXT_LINE_OBJS}

fclean_ft_get_next_line : clean

re_ft_get_next_line : fclean all

.PHONY: all move clean fclean re
