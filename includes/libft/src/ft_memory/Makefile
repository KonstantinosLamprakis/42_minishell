CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_memory_srcs =	ft_memchr.c				\
					ft_memcmp.c				\
					ft_memcpy.c				\
					ft_memmove.c			\
					ft_memset.c				\
					ft_bzero.c				\
					ft_calloc.c
SRC_DIR = src/ft_memory
OBJ_DIR = obj
FT_MEMORY_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_MEMORY_SRCS))

all : ${FT_MEMORY_OBJS}

${FT_MEMORY_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_memory :
	@mv ${SRC_DIR}/${FT_MEMORY_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_memory :
	@rm -f ${FT_MEMORY_OBJS}

fclean_ft_memory : clean

re_ft_memory : fclean all

.PHONY: all move clean fclean re
