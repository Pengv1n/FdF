#include "fdf.h"

void	calc_shift(t_fdf *t_main, t_point *p)
{
	p->x2 += t_main->x_shift;
	p->y2 += t_main->y_shift;
}

void	change_shift(t_fdf *t_main, int code)
{
	t_main->x_incr = 0;
	t_main->y_incr =0;
	if (code == 65361)
		t_main->x_incr -= 10;
	else if (code == 65362)
		t_main->y_incr -= 10;
	else if (code == 65363)
		t_main->x_incr += 10;
	else if (code == 65364)
		t_main->y_incr += 10;
	t_main->x_shift += t_main->x_incr;
	t_main->y_shift += t_main->y_incr;
	calc(t_main);
}

void	only_shift(t_fdf *t_main, t_point *p)
{
	p->x2 += t_main->x_incr;
	p->y2 += t_main->y_incr;
}