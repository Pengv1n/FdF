#include "fdf.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	count_array(char **array)
{
	int ret;

	ret = -1;
	while (array[++ret])
		;
	return (ret);
}

int	split_line(char **line, char ***ret_line)
{
	*ret_line = ft_split(*line, ' ');
	if (!(*ret_line))
		return (0);
	return (1);
}

int fill_mtx(t_fdf *t_main, char **raw)
{
	t_point	*p;
	int i;
	int	start;

	i = 0;
	start = t_main->num_clmn * (t_main->num_raws - 1);
	p = (t_point *) malloc(sizeof(t_point) * t_main->num_clmn * t_main->num_raws);
	if (!p)
	{
		return (0);
	}
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

void	free_raw(char **line, char ***raw)
{
	int	i;

	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (*raw)
	{
		i = -1;
		while ((*raw)[++i])
		{
			free((*raw)[i]);
			(*raw)[i] = NULL;
		}
//		free((*raw)[i]);
		free(*raw);
	}
}

int parse_map(int fd, t_fdf *t_main)
{
	char *line;
	char **raw;

	while (line = get_next_line(fd))
	{
		line[ft_strlen(line) - 1] = '\0';
		t_main->num_raws++;
		if (!split_line(&line, &raw))
		{
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
//	int i = -1;
//	while (++i < t_main->num)
//	{
//		printf("%d ", t_main->mtx[i].z);
//		if ((i + 1) % t_main->num_clmn == 0)
//			printf("\n");
//	}
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

void	find_border(t_fdf *t_main)
{
	int i;

	i = -1;
	t_main->max_height = t_main->mtx[0].z;
	t_main->min_height = t_main->mtx[0].z;
	while (++i < t_main->num)
	{
		if (t_main->max_height < t_main->mtx[i].z)
			t_main->max_height = t_main->mtx[i].z;
		if (t_main->min_height > t_main->mtx[i].z)
			t_main->min_height = t_main->mtx[i].z;
	}
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

	mlx_hook(t_main.mlx.win, 2, 1L<<0, &hook, &t_main);
	mlx_loop(t_main.mlx.mlx_ptr);
	free_fdf(&t_main, 0);
	return (0);
}

int	main(int argc, char ** argv)
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