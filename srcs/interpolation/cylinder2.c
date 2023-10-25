/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:59:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/25 17:12:42 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int solve_quadratic(float *t0, float *t1, t_obj *obj, t_ray ray)
{
	float a;
	float b;
	float c;
	float discriminant;
	t_vec3d oc;

	oc = ft_v_sub(ray.origin, obj->pos);
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2 * (oc.x * ray.dir.x + oc.z * ray.dir.z);
	c = oc.x * oc.x + oc.z * oc.z - (obj->diam / 2) * (obj->diam / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0;
	float sqrt_discriminant = sqrtf(discriminant);
	*t0 = (-b + sqrt_discriminant) / (2 * a);
	*t1 = (-b - sqrt_discriminant) / (2 * a);
	return 1;
}

void cylinder_hit(t_ray ray, t_obj *obj, t_hit *hit)
{
	float	t0;
	float	t1;
	float	y;

	hit->hit = false;  // Assume no intersection
	if (!solve_quadratic(&t0, &t1, obj, ray))
		return;
	float t_min = fminf(t0, t1);
	float t_max = fmaxf(t0, t1);
	float y_min = obj->pos.y;
	float y_max = y_min + obj->high;

	if (t_min < 0)
		t_min = t_max;
	if (t_min > 0 && t_min < t_max)
	{
		y = ray.origin.y + t_min * ray.dir.y;
		if (y >= y_min && y <= y_max)
		{
			hit->hit = true;
			hit->dst = t_min;
			hit->pos = ft_v_add(ray.origin, ft_v_scale(ray.dir, t_min));
			hit->normal = ft_normalize(
				ft_v_sub(hit->pos, (t_vec3d){obj->pos.x, y, obj->pos.z}));
			hit->rgb = obj->rgb;
			hit->id = obj->id;
		}
	}
}