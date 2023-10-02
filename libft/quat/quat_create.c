/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:03:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/02 10:05:36 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_create(float w, float x, float y, float z)
{
	t_quat	q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;
	return (q);
}
