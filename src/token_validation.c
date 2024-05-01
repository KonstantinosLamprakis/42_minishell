/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:31:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 09:33:02 by lgreau           ###   ########.fr       */
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
	if (end == 0)
		return (ms_syntax_error(ft_ltruncate(tmp[0], 1)), free_arr(tmp, 1), 1);
	return (0);
}

// int	is_right_empty(char *str)
// {
// 	char	**tmp;
// 	int		end;
// 	int		had_quotes;

// 	if (ft_strlen_if(str, ft_iswspace) == 0)
// 		return (ms_syntax_error("newline"), 0);
// 	had_quotes = (ft_strcount(str, ft_isquote) > 0);
// 	tmp = ft_escsplit(str, ft_iswspace, ft_isquote);
// 	if (!tmp)
// 		return (set_error((char *)__func__, ALLOC), 0);
// 	end = (ft_strop(tmp[0]) * !had_quotes + had_quotes * ft_strlen(tmp[0]));
// 	if (end <= 0)
// 	{
// 		if (had_quotes)
// 			return (ms_no_such_fd_error(""), 0);
// 		return (ms_syntax_error(ft_ltruncate(tmp[0], 1)), free_arr(tmp, 1),
// 			0);
// 	}
// 	return (1);
// }

int	validate_line(char *line)
{
	size_t	index;

	index = 0;
	while (index < ft_strlen(line))
	{
		if (ft_strop(line + index + 1) < 0)
			break ;
		index += ft_strop(line + index) + 1;
		if (is_right_empty(line + index))
			return (0);
	}
	return (1);
}
