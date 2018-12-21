/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufranco <lufranco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:10:02 by lufranco          #+#    #+#             */
/*   Updated: 2018/12/22 00:10:02 by lufranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	rand1(t_vec3 tmp, t_vec3 *tab)
{
	tab->x = tmp.x + (rand() % (20 + 1)) - (20 / 2);
	tab->y = tmp.y + (rand() % (20 + 1)) - (20 / 2);
	tab->z = tmp.z + (rand() % (20 + 1)) - (20 / 2);
}

double rand3(double tmp1, double tmp2, int t)
{
	int i;

	i = 0;
	if (tmp1 != tmp2)
	{
		i = tmp1 - tmp2;
		i = (i < 0) ? -i / 2 : i / 2;
		return ((tmp1 < tmp2) ? tmp1 + i + t : tmp2 + i + t);
	}
	return (tmp1 + t);
}

void	rand2(t_vec3 tmp1, t_vec3 tmp2, t_vec3 *tab)
{
	int a;
	int t;

	a = 20 / 2;
	t = (tmp1.x < tmp2.x) ? (tmp1.x + a) - (tmp2.x - a)
		: (tmp2.x + a) - (tmp1.x - a);
	t = (t < 0) ? -t : t;
	t = (rand() % (t + 1)) - (t / 2);
	tab->x = rand3(tmp1.x, tmp2.x, t);
	t = (tmp1.y < tmp2.y) ? (tmp1.y + a) - (tmp2.y - a)
		: (tmp2.y + a) - (tmp1.y - a);
	t = (t < 0) ? -t : t;
	t = (rand() % (t + 1)) - (t / 2);
	tab->y = rand3(tmp1.y, tmp2.y, t);
	t = (tmp1.z < tmp2.z) ? (tmp1.z + a) - (tmp2.z - a)
		: (tmp2.z + a) - (tmp1.z - a);
	t = (t < 0) ? -t : t;
	t = (rand() % (t + 1)) - (t / 2);
	tab->z = rand3(tmp1.z, tmp2.z, t);
}

t_vec3	**perturbation(int y, int x)
{
	srand(time(NULL));
	y = -1;
	t_vec3 **tab = malloc(sizeof(t_vec3*) * Y_MAX);
	while (++y < Y_MAX)
	{
		tab[y] = malloc(sizeof(t_vec3) * X_MAX);
		x = -1;
		while (++x < X_MAX)
		{
			if (y == 0 && x == 0)
			{
				tab[0][0].x = (rand() % 170) - (170 / 2);
				tab[0][0].y = (rand() % 170) - (170 / 2);
				tab[0][0].z = (rand() % 170) - (170 / 2);
			}
			else if (y == 0)
				rand1(tab[0][x - 1], &tab[y][x]);
			else if (x == 0)
				rand1(tab[y - 1][0], &tab[y][x]);
			else
				rand2(tab[y - 1][x], tab[y][x - 1], &tab[y][x]);
		}
	}
	return (tab);
}
