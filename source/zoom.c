/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:02:23 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:02:25 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_zoom(t_fdf *t_main, t_point *p)
{
	p->x2 = p->x * (t_main->magn * t_main->zoom);
	p->y2 = p->y * (t_main->magn * t_main->zoom);
}

void	change_zoom(t_fdf *t_main, int code)
{
	if (code == 61)
	{
		t_main->zoom += 0.02;
	}
	else
	{
		t_main->zoom -= 0.02;
		if (t_main->zoom < 0.02)
			t_main->zoom = 0.02;
	}
	calc_1(t_main);
}

void	init_zoom(t_fdf *t_main)
{
	int		dx;
	int		dy;
	float	incr;

	if (t_main->num > 1)
	{
		incr = 0.0;
		dx = t_main->x_max - t_main->x_min;
		dy = t_main->y_max - t_main->y_min;
		if (dx < (WIDTH / 4) && dy < (HEIGHT / 4))
		{
			while ((dx / t_main->zoom) * (t_main->zoom + incr) < WIDTH / 1.3
				&& (dy / t_main->zoom) * (t_main->zoom + incr) < HEIGHT / 1.3)
				incr += 0.02;
		}
		else if (dx > (WIDTH / 1.3) || dy > (HEIGHT / 1.3))
		{
			while (incr < 0.98
				&& ((dx / t_main->zoom) * (t_main->zoom + incr) > WIDTH / 1.3
					|| (dy / t_main->zoom) * (t_main->zoom + incr)
					> HEIGHT / 1.3))
				incr -= 0.02;
		}
		t_main->zoom += incr;
	}
}
