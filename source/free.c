/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:41:31 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:41:32 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		free(*raw);
	}
}

int	free_fdf(t_fdf *t_main, char do_exit)
{
	free(t_main->mtx);
	t_main->mtx = NULL;
	if (t_main->mlx.mlx_ptr && t_main->mlx.img)
		mlx_destroy_image(t_main->mlx.mlx_ptr, t_main->mlx.img);
	t_main->mlx.img = NULL;
	t_main->mlx.img_data = NULL;
	if (t_main->mlx.mlx_ptr && t_main->mlx.win)
		mlx_destroy_window(t_main->mlx.mlx_ptr, t_main->mlx.win);
	free(t_main->mlx.mlx_ptr);
	t_main->mlx.win = NULL;
	if (do_exit)
		exit(0);
	return (1);
}
