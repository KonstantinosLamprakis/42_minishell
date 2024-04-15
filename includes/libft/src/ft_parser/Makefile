CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_parser_srcs =	ft_is_operator.c			\
					ft_tokenize.c				\
					ft_operators.c
SRC_DIR = src/ft_parser
OBJ_DIR = obj
FT_PARSER_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_PARSER_SRCS))

all : ${FT_PARSER_OBJS}

${FT_PARSER_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_parser :
	@mv ${FT_PARSER_RELATIVE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_parser :
	@rm -f ${FT_PARSER_OBJS}

fclean_ft_parser : clean

re_ft_parser : fclean all

.PHONY: all move clean fclean re
