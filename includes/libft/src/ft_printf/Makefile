CC = cc
CFLAGS := -Wall -Wextra -Werror

ft_printf_srcs =	ft_printf.c					\
					ft_printunbr.c				\
					ft_printhex.c				\
					ft_printptr.c				\
					ft_printstr.c				\
					ft_printchar.c				\
					ft_printnbr.c				\
					ft_flag_util.c				\
					ft_quit_util.c				\
					ft_parse_flag.c				\
					ft_parse_width.c			\
					ft_parse_precision.c		\
					ft_parse_type.c				\
					ft_nbr_util.c				\
					ft_print_width.c
SRC_DIR = src/ft_printf
OBJ_DIR = obj
FT_PRINTF_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_PRINTF_SRCS))

all : ${FT_PRINTF_OBJS}

${FT_PRINTF_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

move_ft_printf :
	@mv ${SRC_DIR}/${FT_PRINTF_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_printf :
	@rm -f ${FT_PRINTF_OBJS}

fclean_ft_printf : clean

re_ft_printf : fclean all

.PHONY: all move clean fclean re
