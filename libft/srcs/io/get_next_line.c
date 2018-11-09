/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:36:46 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:34:50 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ioft.h"
#include "strft.h"

static char	*ft_join_free(char *t, char *buf, int rf)
{
	char		*tmp;

	buf[rf] = '\0';
	tmp = t;
	t = ft_strjoin(t, buf);
	ft_strdel(&tmp);
	return (t);
}

static char	*ft_take_rest(char *t)
{
	char	*tmp;

	tmp = t;
	t = ft_strsub(ft_strchr(t, X), 1, ft_strlen(ft_strchr(t, X)) - 1);
	ft_strdel(&tmp);
	return (t);
}

static char	*ft_dup_zero(char *t)
{
	char	*tmp;

	tmp = t;
	t = ft_strnew(0);
	ft_strdel(&tmp);
	return (t);
}

static int	take_line(char **line, char *buf, const int fd, char **stock)
{
	int		rf;

	while ((rf = read(fd, buf, GNL_BUFF_SIZE)) > 0)
	{
		stock[fd] = ft_join_free(stock[fd], buf, rf);
		if (!(ft_strchr(buf, X)))
			break ;
	}
	if (ft_strchr(stock[fd], X))
	{
		*line = ft_strsub(stock[fd], 0,
				ft_strlen(stock[fd]) - ft_strlen(ft_strchr(stock[fd], X)));
		stock[fd] = ft_take_rest(stock[fd]);
		return (1);
	}
	if (stock[fd][0] != '\0')
	{
		*line = ft_strjoin(stock[fd], buf);
		stock[fd] = ft_dup_zero(stock[fd]);
		return (1);
	}
	ft_strdel(&stock[fd]);
	return (0);
}

int			get_next_line(const int fd, char **line, char **noleaks)
{
	char		buf[GNL_BUFF_SIZE + 1];
	char		tmp[1];
	static char	*stock[GNL_OPEN_MAX];
	int			ret_val;

	if (fd < 0 || fd > GNL_OPEN_MAX || line == (void *)0
			|| read(fd, tmp, 0) == -1)
		return (-1);
	stock[fd] = (!stock[fd]) ? ft_strnew(0) : stock[fd];
	ret_val = take_line(line, buf, fd, stock);
	*noleaks = stock[fd];
	return (ret_val);
}
