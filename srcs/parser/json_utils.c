/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:16:53 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 17:31:08 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ts.h"

void		ft_zjump(t_cur *fcur, char *cfile)
{
	while (ft_iswhitespace(cfile[fcur->i]))
	{
		fcur->x++;
		if (cfile[fcur->i] == '\n')
		{
			fcur->x = 1;
			fcur->y++;
		}
		fcur->i++;
	}
}

void		free_lst(t_rtv1 *core)
{
	t_light	*lptr;
	t_light	*li;
	t_poly	*optr;
	t_poly	*oi;

	lptr = core->light;
	while (lptr != NULL)
	{
		li = lptr;
		lptr = lptr->next;
		free(li);
	}
	optr = core->objs;
	while (optr != NULL)
	{
		oi = optr;
		optr = optr->next;
		free(oi->data);
		free(oi);
	}
}

void		json_error(t_cur *fcur, int const err)
{
	static char	*err_s[9] = {"]: file not starting with '{'\n",
		"error: file not ending with '}'\n",
		"]: on key\n",
		"]: on sep\n",
		"]: on val\n",
		"]: not ending with '}'\n",
		"error: there is no camera to launch the rtv1\n",
		"]: need separator\n",
		"]: not enought data\n"};

	if (fcur != NULL)
	{
		ft_putstr_fd("error[", 2);
		ft_putnbr_fd(fcur->y, 2);
		ft_putstr_fd("][", 2);
		ft_putnbr_fd(fcur->x, 2);
	}
	if (err >= 1 && err <= 9)
		ft_putstr_fd(err_s[err - 1], 2);
	exit(EXIT_FAILURE);
}

/*
**	if (err == 1)
**		ft_putstr_fd("]: file not starting with '{'\n", 2);
**	if (err == 2)
**		ft_putstr_fd("error: file not ending with '}'\n", 2);
**	if (err == 3)
**		ft_putstr_fd("]: on key\n", 2);
**	if (err == 4)
**		ft_putstr_fd("]: on sep\n", 2);
**	if (err == 5)
**		ft_putstr_fd("]: on val\n", 2);
**	if (err == 6)
**		ft_putstr_fd("]: not ending with '}'\n", 2);
**	if (err == 7)
**		ft_putstr_fd("error: there is no camera to launch the rtv1\n", 2);
**	if (err == 8)
**		ft_putstr_fd("]: need separator\n", 2);
**	if (err == 9)
**		ft_putstr_fd("]: not enought data\n", 2);
*/
