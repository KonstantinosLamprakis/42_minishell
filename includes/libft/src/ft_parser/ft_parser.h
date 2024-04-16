/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:18:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 15:06:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "../ft_bitmap/ft_bitmap.h"
# include "../ft_btree/ft_btree.h"
# include "../ft_error/ft_error.h"
# include "../ft_string/ft_string.h"

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

# define AND_PRE 3
# define OR_PRE 3
# define PIPE_PRE 4
# define L_REDIRECT_PRE 1
# define R_REDIRECT_PRE 5
# define L_DELIMITER_PRE 1
# define R_APPEND_PRE 5
# define L_PARANTHESE_PRE 2
# define R_PARANTHESE_PRE 2
# define L_CBRACKET_PRE 2
# define R_CBRACKET_PRE 2
# define L_BRACKET_PRE 2
# define R_BRACKET_PRE 2

typedef struct s_token
{
	t_operators	op;
	int			op_precedence;
	int			start;
	int			end;
	int			next;
}				t_token;

typedef struct s_parser_utils
{
	t_btree		*strings;
}				t_parser_utils;

char			**get_operators(void);
int				*get_precedence(void);
int				ft_is_operator(char *str, t_operators op);
int				ft_which_op(char *str);
t_token			*ft_tokenize(char *str, int *token_count);

int				ft_is_encapsulator_start(t_operators op);
int				ft_is_encapsulator_end(t_operators op);
int				ft_is_encapsulator(t_operators op);

int				endof_paranthese(char *str, t_token *token);
int				endof_cbrackets(char *str, t_token *token);
int				endof_brackets(char *str, t_token *token);

#endif
