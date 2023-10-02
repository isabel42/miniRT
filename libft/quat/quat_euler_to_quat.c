/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_euler_to_quat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:06:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/02 10:10:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct t_angle
{
	float	cy;
	float	sy;
	float	cp;
	float	sp;
	float	cr;
	float	sr;
}				t_angle;

t_quat	quat_euler_to_quat(float yaw, float pitch, float roll)
{
	t_quat	q;
	t_angle	qa;

	qa.cy = cos(yaw * 0.5);
	qa.sy = sin(yaw * 0.5);
	qa.cp = cos(pitch * 0.5);
	qa.sp = sin(pitch * 0.5);
	qa.cr = cos(roll * 0.5);
	qa.sr = sin(roll * 0.5);
	q.w = qa.cy * qa.cp * qa.cr + qa.sy * qa.sp * qa.sr;
	q.x = qa.cy * qa.cp * qa.sr - qa.sy * qa.sp * qa.cr;
	q.y = qa.sy * qa.cp * qa.sr + qa.cy * qa.sp * qa.cr;
	q.z = qa.sy * qa.cp * qa.cr - qa.cy * qa.sp * qa.sr;
	q = quat_normalize(q);
	return (q);
}
