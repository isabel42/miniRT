/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:20:56 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:21:04 by lsohler          ###   ########.fr       */
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
