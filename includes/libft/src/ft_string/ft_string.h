/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 07:31:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 09:59:35 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include "../ft_error/ft_error.h"
# include "../ft_memory/ft_memory.h" // ft_memcpy
# include "../ft_char/ft_char.h" // ft_isinbase

# include <stdlib.h>                 //	malloc, free
# include <string.h>                 //	size_t

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_substr_if(char *str, int start, int len, int (*cmp)(int));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinline(char const *s1, char const *s2, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strstrim(char const *s1, char sep);
char	*ft_strtrim_if(char *str, int (*cmp)(int));
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_strcount(const char *str, int (*cmp)(int));
int		ft_strcount_arg(const char *str, int (*cmp)(int, void*), void *arg);
void	ft_strswapc(char *str, int index1, int index2);
void	ft_strreverse(char *str);
int		ft_strcindex(const char *str, int c);
void	ft_strsort(char *str);
int		ft_isbase_valid(char *base, char *forbidden_char);
int		ft_strcmp(const char *s1, const char *s2);

char	*ft_strskip(char *str, int (*cmp)(int), int *is_eol);
char	*ft_getnth_word(char *str, int n, int (*is_sep)(int), int (*cmp)(int));

char	**ft_fctsplit(char *str, int (*cmp)(int));

#endif
