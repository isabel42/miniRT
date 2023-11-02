/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_to_quat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:06 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/15 13:30:59 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	vector_to_quat(t_vec3d v)
{
	t_quat	q;
	double	half_angle;
	double	sin_half_angle;

	half_angle = atan2(sqrt(v.x * v.x + v.y * v.y + v.z * v.z), 0.0) / 2.0;
	sin_half_angle = sin(half_angle);
	q.w = cos(half_angle);
	q.x = v.x * sin_half_angle;
	q.y = v.y * sin_half_angle;
	q.z = v.z * sin_half_angle;
	return (q);
}