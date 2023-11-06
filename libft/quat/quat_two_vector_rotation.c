/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_two_vector_rotation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:45:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 14:53:36 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_two_vector_rotation(t_vec3d v1, t_vec3d v2)
{
	t_quat	q;
	double	sin_half_angle;
	double	half_angle;
	t_vec3d	axis;

	axis = ft_v_cprod(v1, v2);
	half_angle = acos(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / 2;
	sin_half_angle = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis.x * sin_half_angle;
	q.y = axis.y * sin_half_angle;
	q.z = axis.z * sin_half_angle;
	return (q);
}
