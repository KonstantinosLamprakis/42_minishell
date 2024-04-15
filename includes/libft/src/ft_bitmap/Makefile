CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_bitmap_srcs =	ft_mask.c
SRC_DIR = src/ft_bitmap
OBJ_DIR = obj
FT_BITMAP_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_BITMAP_SRCS))

all : ${FT_BITMAP_OBJS}

${FT_BITMAP_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_bitmap :
	@mv ${FT_BITMAP_RELATIVE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_bitmap :
	@rm -f ${FT_BITMAP_OBJS}

fclean_ft_bitmap : clean

re_ft_bitmap : fclean all

.PHONY: all move clean fclean re
