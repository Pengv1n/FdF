#include "fdf.h"

int	free_fdf(t_fdf *t_main, char do_exit)
{
	free(t_main->mtx);
	t_main->mtx = NULL;
	if (t_main->mlx.mlx_ptr && t_main->mlx.img)
		mlx_destroy_image(t_main->mlx.mlx_ptr, t_main->mlx.img);
	t_main->mlx.mlx_ptr = NULL;
	t_main->mlx.img = NULL;
	if (t_main->mlx.mlx_ptr && t_main->mlx.win)
		mlx_destroy_window(t_main->mlx.mlx_ptr, t_main->mlx.win);
	t_main->mlx.mlx_ptr = NULL;
	t_main->mlx.win = NULL;
	if (do_exit)
		exit(0);
	return (1);
}