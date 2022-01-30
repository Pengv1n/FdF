/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:50:32 by aregenia          #+#    #+#             */
/*   Updated: 2022/01/30 15:50:35 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_percentage(int start, int finish, int current)
{
	float	d;
	float	p;

	d = (float)finish - (float)start;
	p = (float)current - (float)start;
	if (d == 0.0)
		return (1.0);
	else
		return (p / d);
}

int	get_gradient_mix(int start, int finish, float percent)
{
	return ((int)(start * (1 - percent) + finish * percent));
}

int	grad(t_gradient *grad, t_point *p, char axe)
{
	float	percent;
	int		r;
	int		g;
	int		b;

	if (axe == 1)
		percent = get_percentage(grad->start.x2, grad->finish.x2, p->x2);
	else if (axe == 2)
		percent = get_percentage(grad->start.y2, grad->finish.y2, p->y2);
	else
		percent = get_percentage(grad->start.z, grad->finish.z, p->z);
	r = get_gradient_mix((grad->start.color >> 16) & 0xFF,
			(grad->finish.color >> 16) & 0xFF, percent);
	g = get_gradient_mix((grad->start.color >> 8) & 0xFF,
			(grad->finish.color >> 8) & 0xFF, percent);
	b = get_gradient_mix(grad->start.color & 0xFF,
			grad->finish.color & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}
