/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fv_mul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:06 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/31 15:22:36 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	ft_fv_mul(float mul, t_vec3d vct)
{
	t_vec3d	res;

	res.x = vct.x * mul;
	res.y = vct.y * mul;
	res.z = vct.z * mul;
	return (res);
}
