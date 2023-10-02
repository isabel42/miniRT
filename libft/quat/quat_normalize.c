/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_quat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:04:54 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/13 18:05:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_normalize(t_quat q)
{
	double	magnitude;

	magnitude = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= magnitude;
	q.x /= magnitude;
	q.y /= magnitude;
	q.z /= magnitude;
	return (q);
}
