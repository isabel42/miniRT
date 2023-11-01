/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:36:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 16:36:17 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_cn_param(t_vec3d *abc, t_ray ray, t_obj *cn)
{
	t_vec3d	x;
	t_vec3d	d;
	t_vec3d	v;
	double	k;

	k = (cn->diam / 2.0) / cn->high;
	x = ft_v_sub(ray.origin, cn->pos);
	d = ray.dir;
	v = ft_normalize(cn->dir);
	(*abc).x = ft_dot(d, d) - (1 + k * k) * powf(ft_dot(d, v), 2);
	(*abc).y = 2 * (ft_dot(d, x) - (1 + k * k) * ft_dot(d, v)
			* ft_dot(x, v));
	(*abc).z = ft_dot(x, x) - (1 + k * k) * powf(ft_dot(x, v), 2);
}
