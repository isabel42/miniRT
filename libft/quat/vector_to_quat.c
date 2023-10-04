/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_to_quat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:06 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 16:55:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	vector_to_quat(t_vec3d v)
{
	t_quat	q;
	double	halfAngle;
	double	sinHalfAngle;

	halfAngle = atan2(sqrt(v.x * v.x + v.y * v.y + v.z * v.z), 0.0) / 2.0;
	sinHalfAngle = sin(halfAngle);
	q.w = cos(halfAngle);
	q.x = v.x * sinHalfAngle;
	q.y = v.y * sinHalfAngle;
	q.z = v.z * sinHalfAngle;
	return q;
}
