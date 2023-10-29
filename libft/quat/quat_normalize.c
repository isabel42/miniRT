/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:04:54 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 15:38:36 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_normalize(t_quat q)
{
	float	magnitude;

	magnitude = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= magnitude;
	q.x /= magnitude;
	q.y /= magnitude;
	q.z /= magnitude;
	return (q);
}
