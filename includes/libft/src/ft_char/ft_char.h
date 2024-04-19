/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 07:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 11:44:03 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAR_H
# define FT_CHAR_H

# include "../ft_string/ft_string.h" // ft_strchr

# define SPACE 32

int	ft_islower(int c);
int	ft_isupper(int c);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_iswspace(int c);
int	ft_isprint(int c);
int	ft_isascii(int c);
int	ft_isinbase(int c, char *base);
int	ft_isinbasen(int c, char *base, int n);
int	ft_isword(char *str, int (*is_sep)(int));

#endif
