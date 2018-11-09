/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioft.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:18:36 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/18 19:28:28 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOFT_H
# define IOFT_H
# define GNL_BUFF_SIZE 400
# define GNL_OPEN_MAX 10
# define X '\n'

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putnbr_base(int n, int base);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_base_fd(int n, int base, int fd);
void			ft_putunbr_fd(unsigned int nb, int fd);
int				get_next_line(const int fd, char **line, char **noleaks);
int				gnl(const int fd, char **line);
#endif
