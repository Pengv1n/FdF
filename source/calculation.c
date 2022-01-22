#include "fdf.h"

void	change_height(t_fdf *t_main, int code)
{
	if (code == 119)
		t_main->height += 3;
	else
		t_main->height -= 3;
	calc_1(t_main);
}

void	calc_height(t_fdf *t_main, t_point *p)
{
	p->z2 = p->z * (t_main->height * t_main->zoom);
}

void	calc_2(t_fdf *t_main)
{
	int i;
	t_rot_data r;
	t_point *p;

	i = -1;
	set_rotate(t_main, &r);
	get_edge_pos(t_main);
	while (i++ < (t_main->num - 1))
	{
		p = &(t_main->mtx[i]);
		calc_rotate(t_main, p, &r);
		calc_proj(t_main, p);
		calc_shift(t_main, p);
	}

}

void	calc_1(t_fdf *t_main)
{
	int	i;
	t_point *p;

	i = -1;
	while (++i < t_main->num)
	{
		p = &(t_main->mtx[i]);
		calc_height(t_main, p);
		calc_zoom(t_main, p);
	}
	calc_2(t_main);
}

void	calc(t_fdf *t_main)
{
	int i;
	t_point *p;

	i = -1;
	while (++i < t_main->num)
	{
		p = &(t_main->mtx[i]);
		only_shift(t_main, p);
	}
}