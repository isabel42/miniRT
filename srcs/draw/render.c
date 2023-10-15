/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:54:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/15 14:12:25 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	int_to_rgb(int icolor)
{
	t_rgb	color;

	color.r = (icolor >> 16) & 0xFF;
	color.g = (icolor >> 8) & 0xFF;
	color.b = icolor & 0xFF;
	return (color);
}

int	rgb_to_int(t_rgb color)
{
	int	icolor;

	icolor = (color.r << 16) | (color.g << 8) | color.b;
	return (icolor);
}

void	my_mlx_pixel_put(t_data_img *imgdata, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH - 1 || y > HEIGHT -1 || x < 0 || y < 0)
		return ;
	dst = imgdata->addr + (y * imgdata->line_length
			+ x * (imgdata->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_new_mlx_img_data(t_scenario *meta)
{
	meta->img_data->img = mlx_new_image(meta->mlx->ptr, WIDTH, HEIGHT);
	meta->img_data->addr = mlx_get_data_addr(meta->img_data->img,
			&meta->img_data->bits_per_pixel,
			&meta->img_data->line_length, &meta->img_data->endian);
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
