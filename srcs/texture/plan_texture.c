/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 15:28:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_texture_from_plane(t_vec3d pos, t_vec3d normal, t_data_img *texture)
{
	int	x;
	int	y;

	(void)normal;
	x = abs((int)(pos.x * texture->width) % (texture->width - 1));
	y = abs((int)(pos.y * texture->height) % (texture->height - 1));
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}