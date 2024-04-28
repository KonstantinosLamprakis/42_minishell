/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encapsulators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:41:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 10:04:02 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	ft_which_enc(char *str)
{
	char	**encapsulators;
	int		index;

	encapsulators = get_encapsulators();
	index = -1;
	while (++index < ENCAPSULATOR_COUNT)
		if (str[index] == encapsulators[index][0])
			return (index);
	return (-1);
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
		return (set_error((char *)__func__, SYNTAX), -1);
	return (index + 1);
}
