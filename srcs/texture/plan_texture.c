/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 08:25:46 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_image_coord(t_hit *hit, t_data_img *texture,
	t_vec3d closest, t_vec3d v_plan)
{
	int	dist;
	int	x;

	dist = (int)ft_mod(ft_v_mul(ft_v_sub(hit->pos, closest), v_plan))
		/ ft_mod(closest);
	x = dist % texture->height;
	if (ft_dot(v_plan, ft_v_sub(hit->pos, closest)) < 0.0)
		x = texture->height - dist % texture->height;
	return (x);
}

t_rgb	get_texture_from_plane(t_hit *hit, t_data_img *texture, t_vec3d cam)
{
	t_vec3d	v_plan;
	t_vec3d	closest;
	int		x;
	int		y;
	float	t;

	t = (ft_dot(hit->normal, hit->pos) - ft_dot(hit->normal, cam))
		/ (ft_dot(hit->normal, hit->normal));
	closest.x = cam.x + t * hit->normal.x;
	closest.y = cam.y + t * hit->normal.y;
	closest.z = cam.z + t * hit->normal.z;
	v_plan = ft_v_product(hit->normal, ft_v_sub(closest, cam));
	if (!ft_mod(v_plan))
		return (int_to_rgb(get_color_from_texture(texture, 0, 0)));
	x = get_image_coord(hit, texture, closest, v_plan);
	v_plan = ft_v_product(hit->normal, v_plan);
	y = get_image_coord(hit, texture, closest, v_plan);
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
