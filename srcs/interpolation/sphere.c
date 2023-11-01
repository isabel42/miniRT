/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:32:39 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 15:48:49 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/* https://paulbourke.net/geometry/circlesphere/index.html#raysphere */
/**/

void	cal_sp_param(t_vec3d *abc, t_ray ray, t_obj *sp)
{
	(*abc).x = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	(*abc).y = 2 * (ray.dir.x * (ray.origin.x - sp->pos.x)
			+ ray.dir.y * (ray.origin.y - sp->pos.y)
			+ ray.dir.z * (ray.origin.z - sp->pos.z));
	(*abc).z = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
		+ pow(ray.origin.x, 2) + pow(ray.origin.y, 2) + pow(ray.origin.z, 2)
		- 2 * (sp->pos.x * ray.origin.x + sp->pos.y * ray.origin.y
			+ sp->pos.z * ray.origin.z) - pow(sp->diam / 2, 2);
}

void	in_sp_all(t_ray ray, t_obj *sp, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0.0001)
	{
		sol2.z = ray.origin.z + t * ray.dir.z;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.x = ray.origin.x + t * ray.dir.x;
		if (hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
		{
			hit->pos.z = ray.origin.z + t * ray.dir.z;
			hit->pos.y = ray.origin.y + t * ray.dir.y;
			hit->pos.x = ray.origin.x + t * ray.dir.x;
			hit->dst = ft_mod(ft_v_sub(sol2, ray.origin));
			hit->normal = ft_v_sub(hit->pos, sp->pos);
			hit->rgb = sp->rgb;
			hit->hit = true;
			hit->id = 0;
			if (sp->id == 0)
				hit->rgb = get_texture_from_sphere(
					ft_v_sub((*hit).pos, (*sp).pos), sp->diam / 2, sp->texture);
		}
	}
}

void	in_sp(t_ray ray, t_obj *sp, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;

	cal_sp_param(&abc, ray, sp);
	sq = powf(abc.y, 2) - 4 * abc.x * abc.z;
	if (sq < 0 || (sq == 0 && abc.x == 0))
		return ;
	in_sp_all(ray, sp, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
	in_sp_all(ray, sp, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
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

t_vec3d	get_hit_point(t_vec3d origin, t_vec3d dir, float dst)
{
	t_vec3d	res;

	res.x = origin.x + dir.x * dst;
	res.y = origin.y + dir.y * dst;
	res.z = origin.z + dir.z * dst;
	return (res);
}

float	get_distance(t_ray ray, t_vec3d center, float radius)
{
	float	discriminant;
	t_vec3d	oc;
	float	a;
	float	b;
	float	c;

	oc = ft_v_sub(ray.origin, center);
	a = ft_dot(ray.dir, ray.dir);
	b = 2.0 * ft_dot(oc, ray.dir);
	c = ft_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0)
		return ((-b - sqrt(discriminant)) / (2 * a));
	else
		return (-1);
}

void	sphere_hit(t_ray ray, t_obj *obj, t_hit *hit)
{
	float	dst;

	hit->hit = false;
	hit->dst = -1;
	dst = get_distance(ray, obj->pos, obj->diam / 2);
	if (dst >= -0.001)
	{
		hit->hit = true;
		hit->dst = dst;
		hit->pos = get_hit_point(ray.origin, ray.dir, dst);
		hit->normal = get_normal(hit->pos, obj->pos);
		hit->rgb = obj->rgb;
		if (obj->id == sp)
			hit->rgb = get_texture_from_sphere(
				ft_v_sub((*hit).pos, (*obj).pos), obj->diam / 2, obj->texture);
	}
}
