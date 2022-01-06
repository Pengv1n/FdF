# include "fdf.h"

void	menu(t_fdf *t_main)
{
	if (t_main->menu)
	{
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 32, 0xFDEE00,
					   "----- LIST OF COMMANDS (hide: H) -----");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 62, 0xFDEE00,
					   "Zoom out/in: -/+");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 82, 0xFDEE00,
					   "Lower/increase altitude: W/S");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 102, 0xFDEE00,
					   "Move camera: up/down/left/right arrow");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 122, 0xFDEE00,
					   "Center: C");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 142, 0xFDEE00,
					   "X/Y/Z/all axes rotation: 3-4/5-6/7-8/9-0");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 162, 0xFDEE00,
					   "Change color: C");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 182, 0xFDEE00,
					   "Change/reset projection: X/Z");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 202, 0xFDEE00,
					   "Exit: ESC");
	}
	else
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 32, 0xFDEE00,
					   "----- LIST OF COMMANDS (show: H) -----");
}

void	voisins_point(t_fdf *t_main, t_point *p, t_point *r, t_point *u, int i)
{
	if (p->x == t_main->num_clmn - 1)
	{
		r->x = -1;
		r->y = -1;
		r->z = -1;
	}
	else
		*r = (t_main->mtx[i + 1]);
	if (p->y == t_main->num_raws - 1)
	{
		u->x = -1;
		u->y = -1;
		u->z = -1;
	}
	else
		*u = (t_main->mtx[i + t_main->num_clmn]);
}

int ft_abs(int a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

void	swap_points(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp.x2 = a->x2;
	tmp.y2 = a->y2;
	tmp.z2 = a->z2;
	tmp.color = a->color;
	a->x2 = b->x2;
	a->y2 = b->y2;
	a->z2 = b->z2;
	a->color = b->color;
	b->x2 = tmp.x2;
	b->y2 = tmp.y2;
	b->z2 = tmp.z2;
	b->color = tmp.color;
}

void	fill_img_data(t_mlx *data, t_point p1, int color)
{
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2] = color & 0xFF;
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 1] =
			(color >> 8) & 0xFF;
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 2] =
			(color >> 16) & 0xFF;
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 3] = 0;
}

int		draw_line_1(t_mlx *data, t_point p1, t_point p2,
								t_gradient g)
{
	int	e;
	int	dx;
	int	dy;
	int	y_incr;

	dx = p2.x2 - p1.x2;
	dy = ft_abs(p2.y2 - p1.y2);
	y_incr = (p2.y2 >= p1.y2) ? 1 : -1;
	e = (2 * dy) + dx;
	while (p1.x2 <= p2.x2)
	{
		e -= (2 * dy);
		if (e <= 0)
		{
			p1.y2 += y_incr;
			e += (2 * dx);
		}
		if (0 <= p1.x2 && p1.x2 < WIDTH && 0 <= p1.y2 && p1.y2 < WIDTH)
			fill_img_data(data, p1, grad(&g, &p1, 1));
		p1.x2++;
	}
	return (1);
}

int		draw_line_2(t_mlx *data, t_point p1, t_point p2,
								t_gradient g)
{
	int	dx;
	int	dy;
	int	e;
	int	x_incr;

	x_incr = (p1.x2 <= p2.x2) ? 1 : -1;
	dx = ft_abs(p2.x2 - p1.x2);
	dy = p2.y2 - p1.y2;
	e = (2 * dx) + dy;
	while (p1.y2 <= p2.y2)
	{
		e -= (2 * dx);
		if (e <= 0)
		{
			p1.x2 += x_incr;
			e += (2 * dy);
		}
		if (0 <= p1.x2 && p1.x2 < WIDTH && 0 <= p1.y2 && p1.y2 < WIDTH)
			fill_img_data(data, p1, grad(&g, &p1, 2));
		p1.y2++;
	}
	return (1);
}

void	draw_line(t_mlx *mlx, t_point *p1, t_point *p2)
{
	int	dx;
	int dy;
	t_gradient g;

	dx = ft_abs(p2->x2 - p1->x2);
	dy = ft_abs(p2->y2 - p1->y2);
	if (dx >= dy)
	{
		if (p1->x2 > p2->x2)
			swap_points(p1, p2);
		g.start = *p1;
		g.finish = *p2;
		draw_line_1(mlx, *p1, *p2, g);
	}
	else
	{
		if (p1->y2 > p2->y2)
			swap_points(p1, p2);
		g.start = *p1;
		g.finish = *p2;
		draw_line_2(mlx, *p1, *p2, g);
	}
}

void	draw(t_fdf *t_main)
{
	int i;
	t_point	r;
	t_point u;

	i = -1;
	while (++i < t_main->num)
	{
		voisins_point(t_main, &(t_main->mtx[i]), &r, &u, i);
		if (r.x != -1)
			draw_line(&(t_main->mlx), &(t_main->mtx[i]), &r);
		if (u.x != -1)
			draw_line(&(t_main->mlx), &(t_main->mtx[i]), &u);
	}
	mlx_put_image_to_window(t_main->mlx.mlx_ptr, t_main->mlx.win, t_main->mlx.img, 0 ,0);
}

void	disp(t_fdf *t_main)
{
	if (t_main->mlx.img)
		ft_bzero(t_main->mlx.img_data, WIDTH * HEIGHT * 4);
	else
	{
		t_main->mlx.img = mlx_new_image(t_main->mlx.mlx_ptr, WIDTH, HEIGHT);
		t_main->mlx.img_data = mlx_get_data_addr(t_main->mlx.img,
			&(t_main->mlx.bpp), &(t_main->mlx.size_line), &(t_main->mlx.endian));
	}
	draw(t_main);
	menu(t_main);
}