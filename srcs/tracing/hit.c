/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/03 13:21:53 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d	get_offset_origin(t_vec3d ray_origin, t_vec3d sphere_c)
{
	t_vec3d	res;

	res.x = ray_origin.x - sphere_c.x;
	res.y = ray_origin.y - sphere_c.y;
	res.z = ray_origin.z - sphere_c.z;
	return (res);
}

t_vec3d	get_hit_point(t_vec3d origin, t_vec3d dir, float dst)
{
	t_vec3d	res;

	res.x = origin.x + dir.x * dst;
	res.y = origin.y + dir.y * dst;
	res.z = origin.z + dir.z * dst;
	return (res);
}

t_vec3d	get_normal(t_vec3d hit_point, t_vec3d sphere_c)
{
	t_vec3d	res;

	res.x = hit_point.x - sphere_c.x;
	res.y = hit_point.y - sphere_c.y;
	res.z = hit_point.z - sphere_c.z;
	res = ft_normalize(res);
	return (res);
}

s_hit	sphere_hit(t_ray ray, t_vec3d sphere_c, float sphere_r)
{
	s_hit	hit;
	t_vec3d	offset_origin;
	t_vec3d	q;
	float	discriminant;
	float	dst;

	offset_origin = get_offset_origin(ray.origin, sphere_c);
	q.a = ft_dot(ray.dir, ray.dir);
	q.b = 2 * ft_dot(offset_origin, ray.dir);
	q.c = ft_dot(offset_origin, offset_origin) - sphere_r * sphere_r;
	discriminant = q.b * q.b - 4 * a * c;
	if (discriminant >= 0)
	{
		dst = (-b - square(discriminant)) / (2 * a);
		if (dst >= 0)
		{
			hit.hit = true;
			hit.dst = dst;
			hit.pos = get_hit_point(ray.origin, ray.dir, dst);
			hit.normal = get_normal(hit.pos, sphere_c);
		}
	}
	else
		hit.hit = false;
	return (hit);
}
