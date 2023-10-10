/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_lenght                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:03:17 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/03 13:04:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_vector_lenght(t_vec3d v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}