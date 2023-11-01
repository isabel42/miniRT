/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:36:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 13:41:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_cn_param(t_vec3d *abc, t_ray ray, t_obj *cn, float k)
{
	t_vec3d X;
	t_vec3d D;
	t_vec3d V;

	X = ft_v_sub(ray.origin, cn->pos);
	D = ray.dir;
	V = cn->dir;

	(*abc).x = ft_dot(D, D) - (1 + k * k) * powf(ft_dot(D, V), 2);
	(*abc).y = 2 * (ft_dot(D, X) - (1 + powf(k, 2)) * ft_dot(D, V)
				* ft_dot(X, V));
	(*abc).z = ft_dot(X, X) - (1 + k * k) * powf(ft_dot(X, V), 2);
}
