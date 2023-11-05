/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:36:50 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/05 17:45:08 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color_from_texture(t_data_img *imgdata, int x, int y)
{
	int	color;

	color = *(int *)(imgdata->addr
			+ (y * imgdata->line_length + x * (imgdata->bits_per_pixel / 8)));
	return (color);
}
