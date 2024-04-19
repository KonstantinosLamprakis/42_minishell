/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:18:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 13:37:27 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "../ft_bitmap/ft_bitmap.h"
# include "../ft_btree/ft_btree.h"
# include "../ft_error/ft_error.h"
# include "../ft_string/ft_string.h"

typedef int	(*t_operator_handler)(void *);

typedef enum e_operators
{
	AND,
	OR,
	PIPE,
	L_REDIRECT,
	R_REDIRECT,
	L_DELIMITER,
	R_APPEND,
	OPERATOR_COUNT
}					t_operators;

typedef enum e_encapsulators
{
	NO_OPERATOR,
	L_PARANTHESE,
	R_PARANTHESE,
	L_CBRACKET,
	R_CBRACKET,
	L_BRACKET,
	R_BRACKET,
	ENCAPSULATOR_COUNT
}					t_encapsulators;

# define AND_OP "&&"
# define OR_OP "||"
# define PIPE_OP "|"
# define L_REDIRECT_OP "<"
# define R_REDIRECT_OP ">"
# define L_DELIMITER_OP "<<"
# define R_APPEND_OP ">>"

# define L_PARANTHESE_ENC "("
# define R_PARANTHESE_ENC ")"
# define L_CBRACKET_ENC "{"
# define R_CBRACKET_ENC "}"
# define L_BRACKET_ENC "["
# define R_BRACKET_ENC "]"

typedef struct s_token
{
	char			*str;
	t_operators		op;
	t_encapsulators	enc;
	int				start;
	int				end;
	int				next_operator;
}					t_token;

typedef struct s_parser_utils
{
	t_btree			*strings;
}					t_parser_utils;

void				ft_parse(char *str);

char				**get_operators(void);
char				**get_encapsulators(void);
int					*get_lengths(void);

int					ft_is_operator(char *str, t_operators op);
int					ft_which_op(char *str);
int					ft_which_enc(char *str);

int					endof_paranthese(char *str, int start);
int					endof_cbrackets(char *str, int start);
int					endof_brackets(char *str, int start);

t_operator_handler	*get_handlers(void);
void				set_handler(t_operators op, t_operator_handler new_handler);

#endif
