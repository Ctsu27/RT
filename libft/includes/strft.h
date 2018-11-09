/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:26:31 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/09 11:08:23 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRFT_H
# define STRFT_H
#include <string.h>

unsigned int	ft_strlen(const char *str);
int				ft_str2len(char **arr);
int				ft_strclen(const char *str, char c);
int				ft_strnlen(const char *str, char c);
char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, unsigned int size);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t len);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t len);
size_t			ft_strlcat(char *dest, const char *src, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_free_str2(char **arr);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_splitwhitespace(char const *s);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, int base);
int				gl_match(char const *s1, char const *s2);
#endif
