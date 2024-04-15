CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_error_srcs =	ft_error.c				\
				ft_errno.c				\
				ft_strerror.c			\
				ft_error_caller.c
SRC_DIR = src/ft_error
OBJ_DIR = obj
FT_ERROR_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_ERROR_SRCS))

all : ${FT_ERROR_OBJS}

${FT_ERROR_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_error :
	@mv ${SRC_DIR}/${FT_ERROR_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_error :
	@rm -f ${FT_ERROR_OBJS}

fclean_ft_error : clean

re_ft_error : fclean all

.PHONY: all move clean fclean re