/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:16:04 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:16:06 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	menu(t_fdf *t_main)
{
	if (t_main->menu)
	{
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 32, WHITE,
			"----- Reference (hide: M) -----");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 62, WHITE,
			"Zoom out/in: -/+");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 82, WHITE,
			"Lower/increase height: W/S");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 102, WHITE,
			"Move camera: up/down/left/right arrow");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 122, WHITE,
			"Center: E");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 142, WHITE,
			"X/Y/Z axes rotation: 1-2/3-4/5-6");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 162, WHITE,
			"Change color: C");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 182, WHITE,
			"Change/reset projection: X/Z");
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 202, WHITE,
			"Exit: ESC");
	}
	else
		mlx_string_put(t_main->mlx.mlx_ptr, t_main->mlx.win, 10, 32, WHITE,
			"----- Reference (show: M) -----");
}

void	voisins_point_r(t_fdf *t_main, t_point *p, t_point *r, int i)
{
	if (p->x == t_main->num_clmn - 1)
	{
		r->x = -1;
		r->y = -1;
		r->z = -1;
	}
	else
		*r = (t_main->mtx[i + 1]);
}

void	voisins_point_u(t_fdf *t_main, t_point *p, t_point *u, int i)
{
	if (p->y == t_main->num_raws - 1)
	{
		u->x = -1;
		u->y = -1;
		u->z = -1;
	}
	else
		*u = (t_main->mtx[i + t_main->num_clmn]);
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
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 1] = (color >> 8)
		& 0xFF;
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 2] = (color >> 16)
		& 0xFF;
	(data->img_data)[p1.x2 * 4 + data->size_line * p1.y2 + 3] = 0;
}
