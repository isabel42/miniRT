/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:36:50 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 18:49:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data_img	*get_texture_to_img(t_mlx *mlx, char *path)
{
	t_data_img	*texture;

	texture = malloc(sizeof(t_data_img));
	if (!texture)
		ft_exit("Malloc");
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		ft_exit("Texture error");
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	printf("Texture address: %p\n", texture);
	return (texture);
}

int	get_color_from_texture(t_data_img *imgdata, int x, int y)
{
	int	color;

	color = *(int *)(imgdata->addr
			+ (y * imgdata->line_length + x * (imgdata->bits_per_pixel / 8)));
	return (color);
}
