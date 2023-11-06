/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:54:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 10:43:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>
#include <stdio.h>


void	my_mlx_pixel_put(t_data_img *imgdata, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH - 1 || y > HEIGHT -1 || x < 0 || y < 0)
		return ;
	dst = imgdata->addr + (y * imgdata->line_length
			+ x * (imgdata->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_new_mlx_img_data(t_scenario *scena)
{
	scena->img_data->img = mlx_new_image(scena->mlx->ptr, WIDTH, HEIGHT);
	scena->img_data->addr = mlx_get_data_addr(scena->img_data->img,
			&scena->img_data->bits_per_pixel,
			&scena->img_data->line_length, &scena->img_data->endian);
}

void	my_new_mlx_img_data_view(t_scenario *scena)
{
	scena->view->img_data->img = mlx_new_image(
			scena->view->mlx->ptr, V_WIDTH, V_HEIGHT);
	scena->view->img_data->addr = mlx_get_data_addr(
			scena->view->img_data->img,
			&scena->view->img_data->bits_per_pixel,
			&scena->view->img_data->line_length,
			&scena->view->img_data->endian);
}

int	render(t_scenario *scena)
{
	mlx_clear_window(scena->mlx->ptr, scena->mlx->win);
	tracing(scena);
	mlx_put_image_to_window(scena->mlx->ptr,
		scena->mlx->win, scena->img_data->img, 0, 0);
	mlx_destroy_image(scena->mlx->ptr, scena->img_data->img);
	my_new_mlx_img_data(scena);
	return (0);
}
