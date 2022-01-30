/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:40:03 by aregenia          #+#    #+#             */
/*   Updated: 2022/01/30 11:40:06 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_border(t_fdf *t_main)
{
	int	i;

	i = 0;
	t_main->max_height = t_main->mtx[0].z;
	t_main->min_height = t_main->mtx[0].z;
	while (++i < t_main->num)
	{
		if (t_main->max_height < t_main->mtx[i].z)
			t_main->max_height = t_main->mtx[i].z;
		if (t_main->min_height > t_main->mtx[i].z)
			t_main->min_height = t_main->mtx[i].z;
	}
}

void	color_point(t_fdf *t_main, t_point *p)
{
	t_gradient	g;

	if (t_main->color > -1)
	{
		g.start.z = t_main->min_height;
		g.finish.z = t_main->max_height;
		g.start.color = t_main->color;
		if (t_main->min_height == t_main->max_height)
			g.finish.color = t_main->color;
		else if (t_main->color != WHITE)
			g.finish.color = 0xFFFFFF;
		else
			g.finish.color = RED;
		p->color = grad(&g, p, 3);
	}
}

void	color(t_fdf *t_main)
{
	int	i;

	find_border(t_main);
	if (t_main->color_code >= 7)
		t_main->color_code = 1;
	if (t_main->color_code == 1)
		t_main->color = WHITE;
	if (t_main->color_code == 2)
		t_main->color = YELLOW;
	if (t_main->color_code == 3)
		t_main->color = RED;
	if (t_main->color_code == 4)
		t_main->color = GREEN;
	if (t_main->color_code == 5)
		t_main->color = BLUE;
	if (t_main->color_code == 6)
		t_main->color = ORANGE;
	i = -1;
	while (++i < t_main->num)
		color_point(t_main, &(t_main->mtx[i]));
}
