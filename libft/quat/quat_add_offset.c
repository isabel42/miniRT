/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_add_offset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:09:18 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/24 18:17:28 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_add_offset(t_quat point, t_vec3d offset)
{
	t_quat	res;

	res.w = point.w;
	res.x = point.x + offset.x;
	res.y = point.y + offset.y;
	res.z = point.z + offset.z;
	return (res);
}
