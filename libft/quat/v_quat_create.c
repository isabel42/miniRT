/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_quat_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:50:18 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 12:51:39 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	v_quat_create(t_quat p)
{
	t_vec3d	point;

	point.x = p.x;
	point.y = p.y;
	point.z = p.z;
	return (point);
}
