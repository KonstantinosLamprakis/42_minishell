/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encapsulators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:41:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 12:42:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_which_enc(char *str)
{
	char	**encapsulators;
	int		index;

	encapsulators = get_encapsulators();
	index = -1;
	while (++index < ENCAPSULATOR_COUNT)
		if (str[0] == encapsulators[index][0])
			return (index);
	return (-1);
}

int	ft_is_encapsulator(int c)
{
	char	**encapsulators;
	int		index;

	encapsulators = get_encapsulators();
	index = -1;
	while (++index < ENCAPSULATOR_COUNT)
		if (c == encapsulators[index][0])
			return (1);
	return (0);
}

int	endof_paranthese(char *str, int start)
{
	int	index;
	int	count;
	int	enc;

	index = 0;
	count = 1;
	while (str[++index + start])
	{
		enc = ft_which_enc(str + start + index);
		if (enc >= 0 && (enc == L_PARANTHESE || enc == R_PARANTHESE))
			count += (enc == L_PARANTHESE) - (enc == R_PARANTHESE);
		if (count == 0)
			break ;
	}
	if (count != 0)
		return (ms_syntax_error(L_PARANTHESE_ENC), -1);
	return (index + 1);
}
