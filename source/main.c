/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 23:01:33 by aregenia          #+#    #+#             */
/*   Updated: 2022/01/22 23:01:38 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fill_mtx(t_fdf *t_main, char **raw)
{
	t_point	*p;
	int		i;
	int		start;

	i = 0;
	start = t_main->num_clmn * (t_main->num_raws - 1);
	p = (t_point *) malloc(sizeof(t_point)
			* t_main->num_clmn * t_main->num_raws);
	if (!p)
		return (0);
	if (t_main->mtx)
	{
		ft_memcpy(p, t_main->mtx, sizeof(t_point)
			* t_main->num_clmn * (t_main->num_raws - 1));
	}
	i = -1;
	while (raw[++i])
	{
		p[start + i].x = i;
		p[start + i].y = t_main->num_raws - 1;
		p[start + i].z = ft_atoi(raw[i]);
	}
	free(t_main->mtx);
	t_main->mtx = p;
	return (1);
}

int	parse_map(int fd, t_fdf *t_main)
{
	char	*line;
	char	**raw;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		t_main->num_raws++;
		raw = ft_split(line, ' ');
		if (!raw)
		{
			free_raw(&line, &raw);
			ft_error("Error: split line");
		}
		t_main->num_clmn = count_array(raw);
		t_main->num += t_main->num_clmn;
		if (!fill_mtx(t_main, raw))
		{
			ft_error("Error: malloc mtx");
		}
		free_raw(&line, &raw);
	}
	return (1);
}

void	init_main(t_fdf *t_main)
{
	t_main->num_raws = 0;
	t_main->num_clmn = 0;
	t_main->mtx = NULL;
	t_main->num = 0;
	t_main->mlx.mlx_ptr = NULL;
	t_main->mlx.win = NULL;
	t_main->color_code = 5;
	t_main->mlx.img = NULL;
	t_main->mlx.img_data = NULL;
	t_main->x_incr = 0;
	t_main->y_incr = 0;
	t_main->x_shift = 0;
	t_main->y_shift = 0;
	t_main->zoom = 1;
	t_main->magn = 30;
	t_main->height = 3;
	t_main->proj = 1;
	t_main->x_rotation = 0.0;
	t_main->y_rotation = 0.0;
	t_main->z_rotation = 0.0;
	t_main->menu = 0;
}

int	fdf(int fd)
{
	t_fdf	t_main;

	init_main(&t_main);
	parse_map(fd, &t_main);
	t_main.mlx.mlx_ptr = mlx_init();
	t_main.mlx.win = mlx_new_window(t_main.mlx.mlx_ptr, WIDTH, HEIGHT, "FDF");
	color(&t_main);
	calc_1(&t_main);
	get_edge_pos(&t_main);
	init_zoom(&t_main);
	calc_1(&t_main);
	center(&t_main);
	disp(&t_main);
	mlx_hook(t_main.mlx.win, 2, 1L << 0, &hook, &t_main);
	mlx_loop(t_main.mlx.mlx_ptr);
	free_fdf(&t_main, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		ft_error("Error: invalid number arguments");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_error("Error: open file");
		fdf(fd);
		close(fd);
	}
	return (0);
}
