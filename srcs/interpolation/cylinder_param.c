/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:36:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 11:01:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_cy_param(t_vec3d *abc, t_ray ray, t_obj *cy)
{
	t_vec3d	x;
	t_vec3d	d;
	t_vec3d	v;

	x = ft_v_sub(ray.origin, cy->pos);
	d = ray.dir;
	v = ft_normalize(cy->dir);
	(*abc).x = ft_dot(d, d) - powf(ft_dot(d, v), 2);
	(*abc).y = 2 * (ft_dot(d, x) - ft_dot(d, v) * ft_dot(x, v));
	(*abc).z = ft_dot(x, x) - powf(ft_dot(x, v), 2) - powf(cy->diam / 2, 2);
}
