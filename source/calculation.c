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

	i = -1;
	set_rotate(t_main, &r);
	get_edge_pos(t_main);
	while (i++ < t_main->num)
	{
		calc_rotate(t_main, &(t_main->mtx[i]), &r);
		calc_proj(t_main, &(t_main->mtx[i]));
		calc_shift(t_main, &(t_main->mtx[i]));
	}

}

void	calc_1(t_fdf *t_main)
{
	int	i;

	i = -1;
	while (++i < t_main->num)
	{
		calc_height(t_main, &(t_main->mtx[i]));
		calc_zoom(t_main, &(t_main->mtx[i]));
	}
	calc_2(t_main);
}

void	calc(t_fdf *t_main)
{
	int i;

	i = -1;
	while (++i < t_main->num)
		only_shift(t_main, &(t_main->mtx[i]));
}