/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/18 09:43:08 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERSION_H
# define FT_CONVERSION_H

# include "../ft_char/ft_char.h" // ft_iswspace
# include "../ft_string/ft_string.h" // ft_isbase_valid
# include "../ft_error/ft_error.h"

# include <stdlib.h> // NULL, malloc
# include <limits.h> // INT_MAX, INT_MIN

char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_ultoa(unsigned long int n);
char	*ft_htoa(unsigned int n, int lower);
char	*ft_lhtoa(size_t n);

int		ft_atoi(const char *str);
int		ft_btoi(char *n, char *base);

#endif
