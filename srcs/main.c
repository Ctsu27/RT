/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:00:17 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/10 13:49:16 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "rt.h"
#include "parser.h"

static void	check_error(int *fd, int argc, char **argv)
{
	char	tmp[1];

	if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 5, ".json") != 0)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <file.json>\n", 2);
		exit(EXIT_FAILURE);
	}
	if ((*fd = open(argv[1], O_RDONLY)) == -1 || read(*fd, tmp, 0) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}

static int	handle_buffer(int *fsize, int byte, char *buf, char **cfile)
{
	*fsize += byte;
	buf[byte] = '\0';
	if (*fsize > 50000000)
	{
		ft_strdel(cfile);
		errno = EFBIG;
		return (-1);
	}
	return (0);
}

static int	take_file_content(int const fd, int *fsize, char **cfile)
{
	int		ret;
	char	buf[5001];
	char	*ptr;

	if ((*cfile = ft_strnew(0)) == NULL)
		return (-1);
	while ((ret = read(fd, buf, 5000)) > 0)
	{
		if (handle_buffer(fsize, ret, buf, cfile) == -1)
			return (-1);
		ptr = *cfile;
		if ((*cfile = ft_strjoin(*cfile, buf)) == NULL)
		{
			ft_strdel(&ptr);
			*fsize = 0;
			return (-1);
		}
		ft_strdel(&ptr);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		fd;
	int		fsize;
	char	*cfile;

	check_error(&fd, argc, argv);
	fsize = 0;
	if (take_file_content(fd, &fsize, &cfile) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	parser_json(&e.core, fsize, cfile);
	ft_strdel(&cfile);
	ft_raytracer(&e);
	free_lst(&e.core);
	return (0);
}
