/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:04 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 13:44:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	ft_is_encapsulator_start(t_operators op)
{
	return (op == L_PARANTHESE || op == L_CBRACKET || op == L_BRACKET);
}

int	ft_is_encapsulator_end(t_operators op)
{
	return (op == R_PARANTHESE || op == R_CBRACKET || op == R_BRACKET);
}

int	ft_is_encapsulator(t_operators op)
{
	return (ft_is_encapsulator_start(op) || ft_is_encapsulator_end(op));
}
