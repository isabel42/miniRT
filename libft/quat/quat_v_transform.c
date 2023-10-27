/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_v_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:19:43 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 12:54:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	quat_v_transform(t_quat q, t_vec3d point)
{
	t_quat	p;

	p = quat_v_create(point);
	p = quat_rotate(q, p);
	return (v_quat_create(p));
}
