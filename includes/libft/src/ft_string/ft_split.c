/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:10:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:02:05 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int	ft_free_array(char **tab, int offset, int is_tab)
{
	while (offset--)
		free(tab[offset]);
	if (is_tab)
		free(tab);
	return (1);
}

static int	ft_count_word(char const *s, size_t s_len, char sep)
{
	size_t	count;
	int		index;

	if (!s_len)
		return (0);
	count = 1;
	index = 1;
	while (s[index])
	{
		if (s[index - 1] == sep && s[index] != sep)
			count++;
		index++;
	}
	return (count);
}

static int	ft_get_substr(char **res, char *s, char sep, int offset)
{
	char	*tmp;
	char	*next;

	if (s == NULL || res == NULL || offset < 0)
		return (-1);
	next = ft_strchr(s + 1, sep);
	while (next && *next)
	{
		if (next > s)
		{
			tmp = ft_substr(s, 0, (size_t)(next - s));
			if (tmp == NULL && ft_free_array(res, offset, 1))
				return (-1);
			res[offset++] = tmp;
		}
		s = next + 1;
		next = ft_strchr(s, sep);
	}
	if (!ft_strlen(s))
		return (offset);
	tmp = ft_substr(s, 0, ft_strlen(s));
	if (tmp == NULL && ft_free_array(res, offset, 1))
		return (-1);
	res[offset++] = tmp;
	return (offset);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*trim;
	int		offset;
	int		word_c;

	if (s == NULL)
		return (NULL);
	trim = ft_strstrim(s, c);
	if (trim == NULL)
		return (NULL);
	word_c = ft_count_word(trim, ft_strlen(trim), c);
	if (word_c < 0 && ft_free_array(&trim, 1, 0))
		return (NULL);
	res = malloc((word_c + 1) * sizeof(char *));
	if (res == NULL && ft_free_array(&trim, 1, 0))
		return (NULL);
	offset = 0;
	if (word_c)
		offset = ft_get_substr(res, trim, c, 0);
	free(trim);
	if (offset < 0)
		return (NULL);
	res[word_c] = NULL;
	return (res);
}
