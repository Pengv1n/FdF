/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:51:55 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:51:57 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 750
# define WIDTH 1250

# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define RED 0xFF0000
# define GREEN 0x008000
# define BLUE 0x0000FF
# define ORANGE 0xFFA500

# include "../libft/libft.h"
# include "fcntl.h"
# include "../minilibx/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "math.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	x2;
	int	y2;
	int	z2;
	int	color;
}	t_point;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;

}	t_mlx;

typedef struct s_fdf
{
	t_mlx	mlx;
	int		num_raws;
	int		num_clmn;
	int		num;
	t_point	*mtx;
	int		max_height;
	int		min_height;
	int		color;
	int		color_code;
	int		x_min;
	int		x_max;
	int		y_min;
	int		y_max;
	int		x_incr;
	int		y_incr;
	int		x_shift;
	int		y_shift;
	float	zoom;
	int		magn;
	int		height;
	float	x_rotation;
	float	y_rotation;
	float	z_rotation;
	char	proj;
	int		menu;
}	t_fdf;

typedef struct s_gradient
{
	t_point				start;
	t_point				finish;
}	t_gradient;

typedef struct s_rot_data
{
	float				a;
	float				b;
	float				c;
	float				d;
	float				e;
	float				f;
	float				ad;
	float				bd;
}	t_rot_data;

void	color(t_fdf *t_main);
void	disp(t_fdf *t_main);
void	center(t_fdf *t_main);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
void	calc(t_fdf *t_main);
void	only_shift(t_fdf *t_main, t_point *p);
void	init_zoom(t_fdf *t_main);
void	calc_zoom(t_fdf *t_main, t_point *p);
void	calc_1(t_fdf *t_main);
void	calc_rotate(t_fdf *t_main, t_point *p, t_rot_data *r);
void	set_rotate(t_fdf *t_main, t_rot_data *r);
void	get_edge_pos(t_fdf *t_main);
void	calc_proj(t_fdf *t_main, t_point *p);
void	calc_shift(t_fdf *t_main, t_point *p);
int		grad(t_gradient *grad, t_point *p, char axe);
int		hook(int code, void *param);
int		free_fdf(t_fdf *t_main, char do_exit);
void	change_height(t_fdf *t_main, int code);
void	change_zoom(t_fdf *t_main, int code);
void	change_shift(t_fdf *t_main, int code);
void	reset(t_fdf *t_main, int proj);
void	change_proj(t_fdf *t_main);
void	menu(t_fdf *t_main);
void	change_rotate(t_fdf *t_main, int code);
void	ft_error(char *str);
int		count_array(char **array);
void	free_raw(char **line, char ***raw);
void	menu(t_fdf *t_main);
void	voisins_point_r(t_fdf *t_main, t_point *p, t_point *r, int i);
void	voisins_point_u(t_fdf *t_main, t_point *p, t_point *u, int i);
void	swap_points(t_point *a, t_point *b);
void	fill_img_data(t_mlx *data, t_point p1, int color);

#endif
