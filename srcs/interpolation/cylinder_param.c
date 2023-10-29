/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:36:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 15:34:44 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_cy_param(t_vec3d *abc, t_ray ray, t_obj *cy)
{
	(*abc).x = powf(cy->dir.x, 2) * powf(ray.dir.x, 2)
		+ powf(cy->dir.y, 2) * powf(ray.dir.y, 2)
		+ powf(cy->dir.z, 2) * powf(ray.dir.z, 2)
		+ 2 * (ray.dir.x * ray.dir.y * cy->dir.x * cy->dir.y
			+ ray.dir.x * ray.dir.z * cy->dir.x * cy->dir.z
			+ ray.dir.y * ray.dir.z * cy->dir.y * cy->dir.z)
		- powf(ft_mod(ray.dir), 2) * powf(ft_mod(cy->dir), 2);
	cal_cy_param_b(abc, ray, cy);
	cal_cy_param_c(abc, ray, cy);
}

void	cal_cy_param_b(t_vec3d *abc, t_ray ray, t_obj *cy)
{
	float	a_a;

	a_a = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;
	// (*abc).y = 2 * (powf(cy->dir.x, 2) * ray.dir.x * ray.origin.x
	// 		+ pow(cy->dir.y, 2) * ray.dir.y * ray.origin.y
	// 		+ pow(cy->dir.z, 2) * ray.dir.z * ray.origin.z
	// 		+ ray.dir.x * ray.origin.y * cy->dir.x * cy->dir.y
	// 		+ ray.dir.x * ray.origin.z * cy->dir.x * cy->dir.z
	// 		+ ray.dir.y * ray.origin.x * cy->dir.x * cy->dir.y
	// 		+ ray.dir.y * ray.origin.z * cy->dir.y * cy->dir.z
	// 		+ ray.dir.z * ray.origin.x * cy->dir.x * cy->dir.z
	// 		+ ray.dir.z * ray.origin.y * cy->dir.x * cy->dir.z
	// 		- ray.dir.x * (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x
	// 			* cy->dir.y * cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
	// 		- ray.dir.y * (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y
	// 			* cy->dir.y * cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
	// 		- ray.dir.z * (cy->dir.z * cy->dir.x * cy->pos.x + cy->dir.z
	// 			* cy->dir.y * cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z)
	// 		- powf(ft_mod(cy->dir), 2) * (ray.origin. x * ray.dir.x
	// 			+ ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z
	// 			- ray.dir.x * cy->pos.x - ray.dir.y * cy->pos.y
	// 			- ray.dir.z * cy->pos.z));

	if (ray.dir.y == 0.0 && ray.dir.x == 0.0)
	{
		printf("ray.origin.x: %f\tray.origin.y: %f\t ray.origin.z: %f \n", ray.origin.x, ray.origin.y, ray.origin.z);
		printf("ray.dir.x: %f\tray.dir.y: %f\t ray.dir.z: %f \n", ray.dir.x, ray.dir.y, ray.dir.z);
	}
	(*abc).y = 2 * (ray.dir.x * ray.origin.x * powf(cy->dir.x, 2)
			+ ray.dir.y * ray.origin.y * powf(cy->dir.y, 2)
			+ ray.dir.z * ray.origin.z * powf(cy->dir.z, 2)
			+ cy->dir.x * cy->dir.y * ray.dir.x * ray.origin.y
			+ cy->dir.x * cy->dir.y * ray.dir.y * ray.origin.x
			+ cy->dir.x * cy->dir.z * ray.origin.z * ray.dir.x
			+ cy->dir.x * cy->dir.z * ray.origin.x * ray.dir.z
			+ cy->dir.y * cy->dir.z * ray.dir.y * ray.origin.z
			+ cy->dir.y * cy->dir.z * ray.dir.z * ray.origin.y
			- a_a * (cy->dir.x * ray.dir.x + cy->dir.y * ray.dir.y
			+ cy->dir.z * ray.dir.z)
			- powf(ft_mod(cy->dir), 2) * (ray.origin.x * ray.dir.x
			+ ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z
			- cy->pos.x * ray.dir.x - cy->pos.y * ray.dir.y
			- cy->pos.z * ray.dir.z
			)
			);
}

void	cal_cy_param_c(t_vec3d *abc, t_ray ray, t_obj *cy)
{
	float	a_a;

	a_a = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;
	(*abc).z = powf(cy->dir.x * ray.origin.x, 2)
		+ powf(cy->dir.y * ray.origin.y, 2) + powf(cy->dir.z * ray.origin.z, 2)
		+ 2 * (ray.origin.x * ray.origin.y * cy->dir.x * cy->dir.y
			+ ray.origin.x * ray.origin.z * cy->dir.x * cy->dir.z
			+ ray.origin.y * ray.origin.z * cy->dir.y * cy->dir.z
			- (cy->dir.x * ray.origin.x + cy->dir.y * ray.origin.y + cy->dir.z * ray.origin.z) * a_a)
		+ powf(a_a, 2) + powf(ft_mod(cy->dir), 2) * powf(cy->diam / 2, 2)
		+ powf(ft_mod(cy->dir), 2)
		* (-powf(ft_mod(ray.origin), 2) + 2 * (ray.origin.x * cy->pos.x
				+ ray.origin.y * cy->pos.y + ray.origin.z * cy->pos.z)
			- powf(ft_mod(cy->pos), 2) );
}
