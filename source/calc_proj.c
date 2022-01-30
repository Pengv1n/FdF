/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_proj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:08:15 by aregenia          #+#    #+#             */
/*   Updated: 2022/01/30 19:08:17 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_proj(t_fdf *t_main)
{
	if (t_main->proj == 1)
		t_main->proj = 2;
	else
		t_main->proj = 1;
	reset(t_main, t_main->proj);
}

void	reset(t_fdf *t_main, int proj)
{
	t_main->proj = proj;
	t_main->zoom = 1;
	t_main->height = 3;
	t_main->x_shift = 0;
	t_main->y_shift = 0;
	t_main->x_incr = 0;
	t_main->y_incr = 0;
	t_main->x_rotation = 0.0;
	t_main->y_rotation = 0.0;
	t_main->z_rotation = 0.0;
	color(t_main);
	calc_1(t_main);
	get_edge_pos(t_main);
	init_zoom(t_main);
	calc_1(t_main);
	center(t_main);
}

void	calc_proj(t_fdf *t_main, t_point *p)
{
	int	old_x2;
	int	old_y2;

	if (t_main->proj == 1)
	{
		old_x2 = p->x2;
		old_y2 = p->y2;
		p->x2 = (old_x2 - old_y2) * cos(0.523599);
		p->y2 = -(p->z2) + (old_x2 + p->y2) * sin(0.523599);
	}
	else
	{
		old_x2 = p->x2;
		old_y2 = p->y2;
		p->x2 = old_x2 + p->z2 * cos(-1) * 0.5;
		p->y2 = old_y2 + p->z2 * sin(-1) * 0.5;
	}
}
