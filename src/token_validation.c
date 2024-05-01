/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:31:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 12:47:26 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_right_empty(char *str)
{
	char	**tmp;
	int		end;
	int		had_quotes;

	if (ft_strlen_if(str, ft_iswspace) == 0)
		return (ms_syntax_error("newline"), 1);
	tmp = ft_escsplit(str, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), 0);
	had_quotes = (ft_strcount(tmp[0], ft_isquote) > 0);
	if (had_quotes)
		return (0);
	end = ft_strop(tmp[0]);
	if (end == 0 && ft_which_enc(tmp[0]) < 0)
		return (ms_syntax_error(ft_ltruncate(tmp[0], 1)), free_arr(tmp, 1), 1);
	return (0);
}

static int	validate_sub(char *line, size_t *index)
{
	char	*sub;
	int		end;

	end = endof_paranthese(line + (*index)++, 0);
	if (*get_errno() != NO_ERROR)
		return (0);
	if (end <= 2)
		return (ms_syntax_error(")"), 0);
	sub = ft_substr(line, *index, end - 2);
	if (!sub)
		return (set_error((char *)__func__, ALLOC), 0);
	if (!validate_line(sub))
		return (0);
	free(sub);
	(*index) += (end - 2);
	return (1);
}

int	validate_line(char *line)
{
	size_t	index;
	int		op;

	index = 0;
	while (index < ft_strlen(line) && line[index])
	{
		if (ft_strop(line + index + 1) < 0)
			break ;
		index += ft_strop(line + index);
		op = ft_which_op(line + index);
		if (op < 0)
		{
			if (!validate_sub(line, &index))
				return (0);
			continue ;
		}
		else
		{
			index += get_lengths()[op];
			if (is_right_empty(line + index))
				return (0);
		}
	}
	return (1);
}
