/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 12:25:30 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_image_coord(t_hit *hit, int texture_size,
	t_vec3d closest, t_vec3d v_plan)
{
	int	dist;
	int	x;

	dist = (ft_mod(ft_v_mul(ft_v_sub(hit->pos, closest), v_plan))
		/ ft_mod(v_plan));
	x = dist % texture_size;
	if (ft_dot(v_plan, ft_v_sub(hit->pos, closest)) < 0.0)
		x = texture_size - (dist % texture_size);
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
	v_plan = ft_v_product(hit->normal,(t_vec3d){1,0,0});
	if (!ft_mod(v_plan))
	{
		v_plan = ft_v_product(hit->normal,(t_vec3d){0,1,0});
		if (!ft_mod(v_plan))
			v_plan = ft_v_product(hit->normal,(t_vec3d){0,0,1});
			if (!ft_mod(v_plan))
				return (int_to_rgb(get_color_from_texture(texture, 0, 0)));
	}
	x = get_image_coord(hit, texture->height, closest, v_plan);
	v_plan = ft_v_product(hit->normal, v_plan);
	y = get_image_coord(hit, texture->width, closest, v_plan);
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
