/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:06:39 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:30:27 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

# include "../ft_string/ft_string.h" // ft_strreverse, ft_strcindex

# include <unistd.h> // write
# include <limits.h> // INT_MIN

# define INT_MAX_LOG 12

int	ft_putchar(int c);
int	ft_putchar_fd(int c, int fd);

int	ft_putstr(char *str);
int	ft_putstr_fd(char *str, int fd);

int	ft_putnbr(int n);
int	ft_putnbr_fd(int n, int fd);

int	ft_putendl_fd(char *str, int fd);
int	ft_putendl(char *str);

int	ft_putnbr_base(char *n, char *base);
int	ft_putnbr_base_fd(char *n, char *base, int fd);

#endif
