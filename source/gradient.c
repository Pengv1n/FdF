#include "fdf.h"

float	get_percentage(int start, int finish, int current)
{
	float	distance;
	float	position;

	distance = (float)finish - (float)start;
	position = (float)current - (float)start;
	return (distance == 0.0 ? 1.0 : position / distance);
}

int		get_gradient_mix(int start, int finish, float percent)
{
	return ((int)(start * (1 - percent) + finish * percent));
}

int	grad(t_gradient *grad, t_point *p, char axe)
{
	float	percent;
	int r;
	int g;
	int b;

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