/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fctsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:47:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 10:19:19 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int	ft_count_word(char *str, int (*cmp)(int))
{
	int	count;
	int	index;

	count = !(*cmp)(str[0]);
	index = -1;
	while (str[++index])
		if (ft_isword(str + index, cmp))
			count++;
	return (count);
}

static void	free_arr(char **arr, int offset, int is_allocated)
{
	if (arr)
		while (arr[--offset])
			free(arr[offset]);
	if (is_allocated)
		free(arr);
}

/**
 * @brief Splits str by characters that return 1 when given to cmp
 *
 * @param str
 * @param cmp
 * @return char**
 */
char	**ft_fctsplit(char *str, int (*cmp)(int))
{
	char	**res;
	int		wc;

	if (!str || !cmp)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	wc = ft_count_word(str, cmp);
	res = ft_calloc(wc + 1, sizeof(char *));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	while (wc-- > 0)
	{
		res[wc] = ft_getnth_word(str, wc + 1, cmp, cmp);
		if (!res[wc])
			return (free_arr(res, wc, 1), NULL);
	}
	return (res);
}
