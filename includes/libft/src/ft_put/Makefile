CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_put_srcs =	ft_putchar.c				\
				ft_putstr.c					\
				ft_putnbr.c					\
				ft_putnbr_base.c			\
				ft_putendl.c
SRC_DIR = src/ft_put
FT_PUT_RELATIVE_SRCS = ${addprefix ${SRC_DIR}/, ${FT_PUT_SRCS}}
OBJ_DIR = obj
FT_PUT_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_PUT_SRCS))

all : ${FT_PUT_OBJS}

${FT_PUT_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_put :
	@mv ${SRC_DIR}/${FT_PUT_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_put :
	@rm -f ${FT_PUT_OBJS}

fclean_ft_put : clean

re_ft_put : fclean all

.PHONY: all move clean fclean re
.SILENT: all
