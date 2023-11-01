/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:16:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 12:17:21 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_copy(t_quat q)
{
	t_quat copy;

	copy.w = q.w;
	copy.x = q.x;
	copy.y = q.y;
	copy.z = q.z;
	return (copy);
}