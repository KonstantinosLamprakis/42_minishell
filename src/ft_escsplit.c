/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:40:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:29:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(char *str, int (*cmp)(int), int (*esc)(int))
{
	int	index;
	int	count;
	int	tmp;

	index = -1;
	count = (!(*cmp)(str[0]) || (*esc)(str[0]));
	while (str[++index])
	{
		if ((*esc)(str[index]))
		{
			count++;
			tmp = str[index++];
			while (str[index] && str[index] != tmp)
				index++;
			if (!str[index])
				return (-1);
		}
		else if (index > 0 && ft_isword(str + index - 1, cmp))
			count++;
	}
	return (count);
}

static int	save_word(char **arr, char *str, int *count, int (*cmp)(int))
{
	char	*tmp;

	tmp = ft_strchr_if(str + 1, cmp);
	arr[(*count)++] = ft_substr_if(str, 0, tmp - str, cmp);
	if (!arr[(*count) - 1])
		set_error((char *)__func__, ALLOC);
	return (*get_errno());
}

static void	fill_arr(char **arr, char *str, int (*cmp)(int), int (*esc)(int))
{
	int		index;
	int		wc;
	char	*tmp;

	index = -1;
	wc = 0;
	if ((!(*cmp)(str[0]) && !(*esc)(str[0])) && save_word(arr, str + ++index,
			&wc, cmp) != 0)
		return ;
	while (str[++index])
	{
		if ((*esc)(str[index]))
		{
			tmp = ft_strchr(str + index + 1, str[index]);
			if (!tmp)
				return (ms_syntax_error(ft_ltruncate(str + index, 1)));
			arr[wc++] = ft_substr(str, index + 1, tmp - (str + index) - 1);
			if (!arr[wc - 1])
				return (free_arr(arr, 1), set_error((char *)__func__, ALLOC));
			index += (tmp - (str + index) + 1);
		}
		else if (index > 0 && ft_isword(str + index - 1, cmp) && save_word(arr,
				str + index, &wc, cmp) != 0)
			return ;
	}
}

/**
 * @brief Splits str by the cmp == 1 characters
 * while respecting the esc == 1 characters
 *
 * @param str
 * @param cmp
 * @param esc
 * @return char**
 */
char	**ft_escsplit(char *str, int (*cmp)(int), int (*esc)(int))
{
	char	**res;
	int		wc;

	if (!str || !cmp || !esc)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	wc = count_words(str, cmp, esc);
	res = ft_calloc(wc + 1, sizeof(char *));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	fill_arr(res, str, cmp, esc);
	if (*get_errno() != 0)
		return (NULL);
	return (res);
}
