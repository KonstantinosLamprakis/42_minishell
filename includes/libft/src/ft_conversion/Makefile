CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_conversion_srcs =	ft_itoa.c					\
						ft_utoa.c					\
						ft_ultoa.c					\
						ft_htoa.c					\
						ft_lhtoa.c					\
						ft_atoi.c					\
						ft_btoi.c
SRC_DIR = src/ft_conversion
OBJ_DIR = obj
FT_CONVERSION_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_CONVERSION_SRCS))

all : ${FT_CONVERSION_OBJS}

${FT_CONVERSION_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_conversion :
	@mv ${SRC_DIR}/${FT_CONVERSION_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_conversion :
	@rm -f ${FT_CONVERSION_OBJS}

fclean_ft_conversion : clean

re_ft_conversion : fclean all

.PHONY: all move clean fclean re
