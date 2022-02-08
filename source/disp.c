/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:15:58 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:16:00 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_line_1(t_mlx *data, t_point p1, t_point p2,
								t_gradient g)
{
	int	e;
	int	dx;
	int	dy;
	int	y_incr;

	dx = p2.x2 - p1.x2;
	dy = ft_abs(p2.y2 - p1.y2);
	if (p2.y2 >= p1.y2)
		y_incr = 1;
	else
		y_incr = -1;
	e = (2 * dy) + dx;
	while (p1.x2 <= p2.x2)
	{
		e -= (2 * dy);
		if (e <= 0)
		{
			p1.y2 += y_incr;
			e += (2 * dx);
		}
		if (0 <= p1.x2 && p1.x2 < WIDTH && 0 <= p1.y2 && p1.y2 < HEIGHT)
			fill_img_data(data, p1, grad(&g, &p1, 1));
		p1.x2++;
	}
	return (1);
}

int	draw_line_2(t_mlx *data, t_point p1, t_point p2,
								t_gradient g)
{
	int	dx;
	int	dy;
	int	e;
	int	x_incr;

	if (p1.x2 <= p2.x2)
		x_incr = 1;
	else
		x_incr = -1;
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
		if (0 <= p1.x2 && p1.x2 < WIDTH && 0 <= p1.y2 && p1.y2 < HEIGHT)
			fill_img_data(data, p1, grad(&g, &p1, 2));
		p1.y2++;
	}
	return (1);
}

void	draw_line(t_mlx *mlx, t_point *p1, t_point *p2)
{
	int			dx;
	int			dy;
	t_gradient	g;

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
	int		i;
	t_point	r;
	t_point	u;

	i = -1;
	while (++i < t_main->num)
	{
		voisins_point_r(t_main, &(t_main->mtx[i]), &r, i);
		voisins_point_u(t_main, &(t_main->mtx[i]), &u, i);
		if (r.x != -1)
			draw_line(&(t_main->mlx), &(t_main->mtx[i]), &r);
		if (u.x != -1)
			draw_line(&(t_main->mlx), &(t_main->mtx[i]), &u);
	}
	mlx_put_image_to_window(t_main->mlx.mlx_ptr,
		t_main->mlx.win, t_main->mlx.img, 0, 0);
}

void	disp(t_fdf *t_main)
{
	if (t_main->mlx.img)
		ft_bzero(t_main->mlx.img_data, WIDTH * HEIGHT * 4);
	else
	{
		t_main->mlx.img = mlx_new_image(t_main->mlx.mlx_ptr, WIDTH, HEIGHT);
		t_main->mlx.img_data = mlx_get_data_addr(t_main->mlx.img,
				&(t_main->mlx.bpp),
				&(t_main->mlx.size_line), &(t_main->mlx.endian));
	}
	draw(t_main);
	menu(t_main);
}
