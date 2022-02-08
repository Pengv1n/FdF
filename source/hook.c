/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <aregenia@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:42:08 by aregenia          #+#    #+#             */
/*   Updated: 2022/02/08 12:42:16 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_2(int code, t_fdf *t_main)
{
	if (code == 120)
		change_proj(t_main);
	else if (code == 99)
	{
		t_main->color_code++;
		color(t_main);
	}
	else if (code == 109)
	{
		t_main->menu = !t_main->menu;
		menu(t_main);
	}
	else if (code >= 49 && code <= 54)
		change_rotate(t_main, code);
	else if (code == 101)
		center(t_main);
}

int	hook(int code, void *param)
{
	t_fdf	*t_main;

	t_main = (t_fdf *)param;
	if (code == 65307)
		free_fdf(t_main, 1);
	else if (code == 119 || code == 115)
		change_height(t_main, code);
	else if (code == 45 || code == 61)
		change_zoom(t_main, code);
	else if (code == 65361 || code == 65362
		|| code == 65363 || code == 65364)
		change_shift(t_main, code);
	else if (code == 122)
		reset(t_main, t_main->proj);
	else
		hook_2(code, t_main);
	calc_1(t_main);
	color(t_main);
	disp(t_main);
	return (1);
}
