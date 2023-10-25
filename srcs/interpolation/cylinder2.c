/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:59:53 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/25 18:05:46 by lsohler          ###   ########.fr       */
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

void	transform_ray(t_ray *ray, t_obj	*obj)
{
	t_quat	qrdir;
	t_quat	qrorigin;
	t_quat	qcdir;

	qcdir = vector_to_quat(obj->dir); 
	// ray->origin = ft_v_sub(ray->origin, obj->pos);
	// ray->dir = ft_v_sub(ray->dir, obj->pos);
	qrorigin = quat_create(0, ray->origin.x, ray->origin.y, ray->origin.z);
	qrdir = quat_create(0, ray->dir.x, ray->dir.y, ray->dir.z);
	qrorigin = quat_multiply(quat_multiply(qrorigin, qcdir), quat_conjugate(qcdir));
	qrdir = quat_multiply(quat_multiply(qrdir, qcdir), quat_conjugate(qcdir));
	ray->origin = quat_to_vector(qrorigin);
	ray->dir = quat_to_vector(qrdir);
}

void	cylinder_hit(t_ray ray, t_obj *obj, t_hit *hit)
{
	float	t0;
	float	t1;
	float	y;

	hit->hit = false;
	transform_ray(&ray, obj);
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