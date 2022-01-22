#include "fdf.h"

void	change_rotate(t_fdf *t_main, int code)
{
	if (code == 49)
		t_main->x_rotation -= 0.261799;
	if (code == 50)
		t_main->x_rotation += 0.261799;
	if (code == 51)
		t_main->y_rotation -= 0.261799;
	if (code == 52)
		t_main->y_rotation += 0.261799;
	if (code == 53)
		t_main->z_rotation -= 0.261799;
	if (code == 54)
		t_main->z_rotation += 0.261799;
	calc_1(t_main);
}

void	calc_rotate(t_fdf *t_main,  t_point *p, t_rot_data *r)
{
	int	old_x2;
	int	old_y2;
	int	old_z2;

	old_x2 = p->x2 - ((t_main->x_max - t_main->x_min) / 2);
	old_y2 = p->y2 - ((t_main->y_max - t_main->y_min) / 2);
//	old_x2 = p->x2;
//	old_y2 = p->y2;
	old_z2 = p->z2;
	p->x2 = old_x2 * r->c * r->e - old_y2 * r->c * r->f + r->d * old_z2;
	p->y2 = old_x2 * r->bd * r->e + old_x2 * r->a * r->f
			- old_y2 * r->bd * r->f + old_y2 * r->a * r->e - old_z2 * r->b * r->c;
	p->z2 = -r->ad * r->e * old_x2 + r->b * r->f * old_x2
			+ r->ad * r->f * old_y2 + r->b * r->e * old_y2 + r->a * r->c * old_z2;
}

void	set_rotate(t_fdf *t_main, t_rot_data *r)
{
	r->a = cos(t_main->x_rotation);
	r->b = sin(t_main->x_rotation);
	r->c = cos(t_main->y_rotation);
	r->d = sin(t_main->y_rotation);
	r->e = cos(t_main->z_rotation);
	r->f = sin(t_main->z_rotation);
	r->ad = r->a * r->d;
	r->bd = r->b * r->d;
}
