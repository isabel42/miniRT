/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:32:50 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 17:33:58 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	new_vector(float x, float y, float z)
{
	t_vec3d	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}