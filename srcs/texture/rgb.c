/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:44:54 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/05 17:52:27 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rgb_scale(t_rgb	rgb, float scale)
{
	t_rgb	res;

	res.r = rgb.r * scale;
	res.g = rgb.g * scale;
	res.b = rgb.b * scale;
	return (res);
}

t_rgb	rgb_scale_from_ref(t_rgb rgb, t_rgb ref)
{
	t_rgb	res;

	res.r = rgb.r * ((float)ref.r / 255);
	res.g = rgb.g * ((float)ref.g / 255);
	res.b = rgb.r * ((float)ref.b / 255);
	return (res);
}