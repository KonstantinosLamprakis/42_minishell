/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:20:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 13:06:12 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_result(char **result, int start, char *str, int i);

/**
 * @brief takes a string that in first char has a quote ' or "
 * and return how many positions should skip in order to reach the first
 * character after the quote
 * @param str
 * @param quote " or ' charakter
 * @return int how many position from beggining to skip in order to reach
 * the next character after quote
 */
int	skip_quotes(char const *str, char quote)
{
	int	i;

	if (!str || str[0] != quote)
		return (0);
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
	{
		printf("todo error: not closing quotes: %s\n", str);
		return (0);
	}
	return (i);
}

/**
 * @brief removes the quotes " and ' and returns the new string
 * any other-single quotes ex. "Konstantino's bike" are preserved
 * or ex. 'Konstantino's bike'
 *
 * @param str should be freeable, and this function free it
 * It is the initial string that contains the quotes
 * @return char* the new string after we remove the quotes from the
 * initial one
 */
char	*replace_quotes(char *str)
{
	int		i;
	int		start;
	char	quote;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		get_result(&result, start, str, i);
		if (!str[i])
			break ;
		start = i + 1;
		quote = str[i++];
		while (str[i] && str[i] != quote)
			i++;
		if (!str[i])
			break ;
		get_result(&result, start, str, i);
		i++;
	}
	return (free(str), result);
}

static void	get_result(char **result, int start, char *str, int i)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(str, start, i - start);
	if (temp)
	{
		temp2 = *result;
		*result = ft_strjoin(*result, temp);
		free(temp);
		free(temp2);
	}
}

/**
 * @brief check if character c is included on string of delimiters
 *
 * @param c
 * @param del
 * @return int -1 if not included, else the index of it starting from
 * zero
 */
int	is_included(char c, char *del)
{
	int	i;

	if (!del)
		return (-1);
	i = -1;
	while (del[++i])
		if (del[i] == c)
			return (i);
	return (-1);
}

t_program	*get_program(void)
{
	static t_program	program;

	return (&program);
}
