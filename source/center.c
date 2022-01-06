#include "fdf.h"

void	get_edge_pos(t_fdf *t_main)
{
	int	i;

	i = -1;
	while (++i < t_main->num)
	{
		if (!i)
		{
			t_main->x_min = t_main->mtx[i].x2;
			t_main->x_max = t_main->mtx[i].x2;
			t_main->y_min = t_main->mtx[i].y2;
			t_main->y_max = t_main->mtx[i].y2;
		}
		else
		{
			t_main->x_min = ft_min(t_main->x_min, t_main->mtx[i].x2);
			t_main->x_max = ft_max(t_main->x_max, t_main->mtx[i].x2);
			t_main->y_min = ft_min(t_main->y_min, t_main->mtx[i].y2);
			t_main->y_max = ft_max(t_main->y_max, t_main->mtx[i].y2);
		}
	}
}

void	center(t_fdf *t_main)
{
	int	dx;
	int dy;

	get_edge_pos(t_main);
	dx = t_main->x_max - t_main->x_min;
	dy = t_main->y_max - t_main->y_min;
	t_main->x_incr = (WIDTH / 2) - (dx / 2) - t_main->x_min;
	t_main->y_incr = (HEIGHT / 2) - (dy / 2) - t_main->y_min;
	t_main->x_shift += t_main->x_incr;
	t_main->y_shift += t_main->y_incr;
	calc(t_main);
}