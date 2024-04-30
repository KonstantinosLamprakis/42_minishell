/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:20:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 14:20:28 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("error: not closing quotes\n");
		return (0);
	}
	return (i);
}

char	*replace_quotes(char *str)
{
	int		i;
	int		start;
	char	quote;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	while(str[i])
	{
		start = i;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		temp = ft_substr(str, start, i - start);
		if (temp)
		{
			result = ft_strjoin(result, temp);
			free(temp);
		}
		if (!str[i])
			break ;
		start = i + 1;
		quote = str[i++];
		while (str[i] && str[i] != quote)
			i++;
		if (!str[i])
			break ;
		temp = ft_substr(str, start, i - start);
		if (temp)
		{
			result = ft_strjoin(result, temp);
			free(temp);
		}
		i++;
	}
	free(str);
	return (result);
}
