CC = cc
CFLAGS := -Wall -Wextra -Werror

RESET_COLOR = \033[0m
COMPILING_COLOR = \033[38;5;57m
AR_COLOR = \033[38;5;34m

GRAY_COLOR = \033[38;5;234m
G1_COLOR = \033[38;5;160m
G2_COLOR = \033[38;5;125m
G3_COLOR = \033[38;5;90m
G4_COLOR = \033[38;5;55m
G5_COLOR = \033[38;5;20m

NAME = libft.a
OBJ_DIR = obj
SRC_DIR = src

FT_CHAR_SRCS =	ft_islower.c				\
				ft_isupper.c				\
				ft_isalpha.c				\
				ft_isdigit.c				\
				ft_isalnum.c				\
				ft_isascii.c				\
				ft_isprint.c				\
				ft_iswspace.c				\
				ft_isinbase.c				\
				ft_toupper.c				\
				ft_tolower.c				\
				ft_isword.c					\
				ft_isquote.c
FT_CHAR_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_CHAR_SRCS}}

FT_STRING_SRCS =	ft_strlen.c					\
					ft_strchr.c					\
					ft_strrchr.c				\
					ft_strncmp.c				\
					ft_strlcpy.c				\
					ft_strlcat.c				\
					ft_strnstr.c				\
					ft_strdup.c					\
					ft_substr.c					\
					ft_strjoin.c				\
					ft_strtrim.c				\
					ft_split.c					\
					ft_strmapi.c				\
					ft_striteri.c				\
					ft_strcount.c				\
					ft_strreverse.c				\
					ft_strcindex.c				\
					ft_strsort.c				\
					ft_isbase_valid.c			\
					ft_strcmp.c					\
					ft_strtrim_if.c				\
					ft_substr_if.c				\
					ft_strskip.c				\
					ft_getnth_word.c			\
					ft_fctsplit.c				\
					ft_strchr_if.c				\
					ft_strlen_if.c				\
					ft_truncate.c
FT_STRING_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_STRING_SRCS}}

FT_MEMORY_SRCS =	ft_memchr.c				\
					ft_memcmp.c				\
					ft_memcpy.c				\
					ft_memmove.c			\
					ft_memset.c				\
					ft_bzero.c				\
					ft_calloc.c
FT_MEMORY_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_MEMORY_SRCS}}

FT_LINKED_LIST_SRCS =	ft_lstnew.c					\
						ft_lstsize.c				\
						ft_lstlast.c				\
						ft_lstadd_front.c			\
						ft_lstadd_back.c			\
						ft_lstclear.c				\
						ft_lstdelone.c				\
						ft_lstiter.c				\
						ft_lstmap.c
FT_LINKED_LIST_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_LINKED_LIST_SRCS}}

FT_CONVERSION_SRCS =	ft_itoa.c					\
						ft_utoa.c					\
						ft_ultoa.c					\
						ft_htoa.c					\
						ft_lhtoa.c					\
						ft_atoi.c					\
						ft_btoi.c
FT_CONVERSION_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_CONVERSION_SRCS}}

FT_PUT_SRCS =	ft_putchar.c				\
				ft_putstr.c					\
				ft_putnbr.c					\
				ft_putnbr_base.c			\
				ft_putendl.c
FT_PUT_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_PUT_SRCS}}

FT_PRINTF_SRCS =	ft_printf.c					\
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
FT_PRINTF_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_PRINTF_SRCS}}

FT_GET_NEXT_LINE_SRCS =	ft_get_next_line.c			\
						ft_get_next_line_utils.c	\
						ft_get_next_line_nonl.c
FT_GET_NEXT_LINE_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_GET_NEXT_LINE_SRCS}}

FT_ERROR_SRCS =	ft_error.c				\
				ft_errno.c				\
				ft_strerror.c			\
				ft_error_caller.c
FT_ERROR_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_ERROR_SRCS}}

FT_BITMAP_SRCS =	ft_mask.c
FT_BITMAP_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_BITMAP_SRCS}}

FT_BTREE_SRCS =	ft_btree_create_node.c				\
				ft_btree_iter_prefix.c				\
				ft_btree_iter_infix.c				\
				ft_btree_iter_postfix.c				\
				ft_btree_iter_breadth.c				\
				ft_btree_iter_depth.c				\
				ft_btree_traverse.c					\
				ft_clear_btree.c					\
				ft_sbtree_find_last.c				\
				ft_sbtree_insert.c
FT_BTREE_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_BTREE_SRCS}}

FT_QUEUE_SRCS =	ft_create_queue.c			\
				ft_clear_queue.c			\
				ft_queue_pop.c				\
				ft_queue_push.c				\
				ft_print_queue.c
FT_QUEUE_OBJS = ${patsubst %.c, ${OBJ_DIR}/%.o, ${FT_QUEUE_SRCS}}


SRCS =	${FT_CHAR_SRCS}						\
		${FT_STRING_SRCS}					\
		${FT_MEMORY_SRCS}					\
		${FT_LINKED_LIST_SRCS}				\
		${FT_CONVERSION_SRCS}				\
		${FT_PUT_SRCS}						\
		${FT_PRINTF_SRCS}					\
		${FT_GET_NEXT_LINE_SRCS}			\
		${FT_ERROR_SRCS}					\
		${FT_BITMAP_SRCS}					\
		${FT_BTREE_SRCS}					\
		${FT_QUEUE_SRCS}
OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}
TOTAL_OBJS := $(words ${OBJS})

PROGRESS_PERCENT := 0
FINAL_LEN := 40
PERCENT_PER_EQUAL_SIGN := ${shell echo "scale=2; 100 / ${FINAL_LEN}" | bc}
PERCENT_PER_FILE := $(shell echo "scale=2; 100 / $(TOTAL_OBJS)" | bc)

all : build

build : init_ascii ${NAME}

${NAME} : ${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\033[A\033[K"
	@printf "\r"
	@make init_ascii

init_ascii :
	@echo "${GRAY_COLOR}/+ ======================================== +\\"
	@echo "||                                          ||"
	@echo "||     ${G1_COLOR}       __ _  __     ____ __    ${RESET_COLOR}${GRAY_COLOR}      ||"
	@echo "||     ${G2_COLOR}      / /(_)/ /_   / __// /_   ${RESET_COLOR}${GRAY_COLOR}      ||"
	@echo "||     ${G3_COLOR}     / // // __ \ / /_ / __/   ${RESET_COLOR}${GRAY_COLOR}      ||"
	@echo "||     ${G4_COLOR}    / // // /_/ // __// /_     ${RESET_COLOR}${GRAY_COLOR}      ||"
	@echo "||     ${G5_COLOR}   /_//_//_.___//_/   \__/     ${RESET_COLOR}${GRAY_COLOR}      ||"
	@echo "||                                          ||"
	@echo "||                               by @lgreau ||"
	@echo "\\+ ======================================== +/${RESET_COLOR}"

define compile_with_progress_bar
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval EQUALS_COUNT=$(shell echo "$(PROGRESS_PERCENT) / (${PERCENT_PER_EQUAL_SIGN} * 100)" | bc))
	@$(eval PROGRESS_PERCENT=$(shell echo "$(PROGRESS_PERCENT) + $(PERCENT_PER_FILE) * 100" | bc))
	@$(eval NEW_EQUALS_COUNT=$(shell echo "$(PROGRESS_PERCENT) / (${PERCENT_PER_EQUAL_SIGN} * 100)" | bc))
	@if [ "$(NEW_EQUALS_COUNT)" -ne "${EQUALS_COUNT}" ]; then \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A"; \
		printf "\033[A\033[K"; \
		printf "\r${GRAY_COLOR}/+ "; \
		for i in `seq 1 $(FINAL_LEN)`; do \
			if [ $$i -le $(NEW_EQUALS_COUNT) ]; then \
				printf "="; \
			else \
				printf " "; \
			fi; \
		done; \
		printf " +\\"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B"; \
		printf "\033[B\033[K"; \
		printf "\r${GRAY_COLOR}\\+ "; \
		for i in `seq 1 $(FINAL_LEN)`; do \
			if [ $$i -le $(shell echo "$(FINAL_LEN) - $(NEW_EQUALS_COUNT)" | bc) ]; then \
				printf " "; \
			else \
				printf "="; \
			fi; \
		done; \
		printf " +/${RESET_COLOR}"; \
		printf "\033[B"; \
	fi
endef

${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

${FT_CHAR_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_char/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_STRING_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_string/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_MEMORY_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_memory/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_LINKED_LIST_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_linked_list/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_CONVERSION_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_conversion/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_PUT_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_put/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_PRINTF_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_printf/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_GET_NEXT_LINE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_get_next_line/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_ERROR_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_error/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_BITMAP_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_bitmap/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_BTREE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_btree/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

${FT_QUEUE_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/ft_queue/%.c | ${OBJ_DIR}
	@${compile_with_progress_bar}

move_objs:
	@for sub in ${SRC_SUB}; do \
		make -sC ${SRC_DIR}/$$sub move_$$sub; \
	done

clean :
	@rm -f ${OBJS}

fclean : clean
	@rm -f ${NAME}

re : fclean build

.PHONY: all compile_all map_sources move_objs
