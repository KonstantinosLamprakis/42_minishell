CC = cc
CFLAGS = -Werror -Wextra -Wall

ft_string_srcs =	ft_strlen.c					\
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
					ft_strcmp.c
SRC_DIR = src/ft_string
OBJ_DIR = obj
FT_STRING_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(FT_STRING_SRCS))

all : ${FT_STRING_OBJS}

${FT_STRING_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
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

# @echo "    ${GRAY_COLOR}/+=======================================+\\"
# @echo "    ||                                       ||"
# @echo "    ||    ${G1_COLOR}       __ _  __     ____ __    ${RESET_COLOR}${GRAY_COLOR}    ||"
# @echo "    ||    ${G2_COLOR}      / /(_)/ /_   / __// /_   ${RESET_COLOR}${GRAY_COLOR}    ||"
# @echo "    ||    ${G3_COLOR}     / // // __ \ / /_ / __/   ${RESET_COLOR}${GRAY_COLOR}    ||"
# @echo "    ||    ${G4_COLOR}    / // // /_/ // __// /_     ${RESET_COLOR}${GRAY_COLOR}    ||"
# @echo "    ||    ${G5_COLOR}   /_//_//_.___//_/   \__/     ${RESET_COLOR}${GRAY_COLOR}    ||"
# @echo "    ||                                       ||"
# @echo "    ||                             by @lgreau||"
# @echo "    \\+=======================================+/${RESET_COLOR}"

# @if [ "$(NEW_EQUALS_COUNT)" -ne "${EQUALS_COUNT}" ]; then \
# 		printf "${COMPILING_COLOR}\r[%3d%%] ${RESET_COLOR}" $(shell echo "$(PROGRESS_PERCENT)/100" | bc); \
# 		printf "${COMPILING_COLOR}"; \
		for i in `seq 1 $(NEW_EQUALS_COUNT)`; do \
			printf "="; \
		done; \
# 		printf "${RESET_COLOR}"; \
# 	fi

move_ft_string :
	@mv ${SRC_DIR}/${FT_STRING_SRCS:.c=.o} ${OBJ_DIR}

clean_ft_string :
	@rm -f ${FT_STRING_OBJS}

fclean_ft_string : clean

re_ft_string : fclean all

.PHONY: all clean fclean re
