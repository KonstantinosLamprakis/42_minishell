/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:18:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/15 10:41:24 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "../ft_bitmap/ft_bitmap.h"
# include "../ft_btree/ft_btree.h"
# include "../ft_string/ft_string.h"
# include "../ft_error/ft_error.h"

typedef enum e_operators
{
	AND,
	OR,
	PIPE,
	L_REDIRECT,
	R_REDIRECT,
	L_DELIMITER,
	R_APPEND,
	L_PARANTHESE,
	R_PARANTHESE,
	L_CBRACKET,
	R_CBRACKET,
	L_BRACKET,
	R_BRACKET,
	OPERATOR_COUNT
}				t_operators;

typedef struct s_token
{
	t_operators	op;
	char		*value;
}				t_token;

# define AND_OP "&&"
# define OR_OP "||"
# define PIPE_OP "|"
# define L_REDIRECT_OP "<"
# define R_REDIRECT_OP ">"
# define L_DELIMITER_OP "<<"
# define R_APPEND_OP ">>"
# define L_PARANTHESE_OP "("
# define R_PARANTHESE_OP ")"
# define L_CBRACKET_OP "{"
# define R_CBRACKET_OP "}"
# define L_BRACKET_OP "["
# define R_BRACKET_OP "]"

typedef struct s_parser_utils
{
	t_btree		*strings;
}				t_parser_utils;

char			**get_operators(void);
int				ft_is_operator(char *str, t_operators op);
t_token			*ft_tokenize(char *str, int *token_count);

#endif
