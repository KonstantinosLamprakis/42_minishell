CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_char_srcs =	ft_islower.c				\
				ft_isupper.c				\
				ft_isalpha.c				\
				ft_isdigit.c				\
				ft_isalnum.c				\
				ft_isascii.c				\
				ft_isprint.c				\
				ft_iswspace.c				\
				ft_isinbase.c				\
				ft_toupper.c				\
				ft_tolower.c
SRC_DIR = src/ft_char
OBJ_DIR = obj
FT_CHAR_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_CHAR_SRCS))

all : ${FT_CHAR_OBJS}

${FT_CHAR_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_char :
	@mv ${FT_CHAR_RELATIVE_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_char :
	@rm -f ${FT_CHAR_OBJS}

fclean_ft_char : clean

re_ft_char : fclean all

.PHONY: all move clean fclean re
