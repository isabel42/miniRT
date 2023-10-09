/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 17:28:38 by itovar-n         ###   ########.fr       */
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

t_hit	sphere_hit(t_ray ray, t_quat center_q, float sphere_r)
{
	t_hit	hit;
	t_vec3d	offset_origin;
	t_vec3d	q;
	float	discriminant;
	float	dst;
	t_vec3d	sphere_c;

	hit.hit = false;
	sphere_c.x = center_q.x;
	sphere_c.y = center_q.y;
	sphere_c.z = center_q.z;
	// printf("Ray origin: ");
	// test_print_vecteur(ray.origin);
	// printf("Ray dir: ");
	// test_print_vecteur(ray.dir);
	// printf("Sphere: ");
	// test_print_vecteur(sphere_c);
	offset_origin = get_offset_origin(ray.origin, sphere_c);
	// printf("  offset_origin: ");
	// test_print_vecteur(offset_origin);
	q.x = ft_dot(ray.dir, ray.dir);
	q.y = 2 * ft_dot(offset_origin, ray.dir);
	q.z = ft_dot(offset_origin, offset_origin) - sphere_r * sphere_r;
	// printf("a:%f b:%f c:%f\n", q.x, q.y, q.z);
	discriminant = q.y * q.y - 4 * q.x * q.z;
	// dst = (-q.y - sqrt(discriminant)) / (2 * q.x);
	// if (discriminant >= 0)
	// {
	// 	printf("Discriminant: %f\n", discriminant);
	// 	printf("Dst:%f\n", dst);
	// }
	if (discriminant >= 0)
	{
		dst = (-q.y + sqrt(discriminant)) / (2 * q.x);
		// printf("Dst:%f\n", dst);
		if (dst <= 0.0)
		{
			hit.hit = true;
			hit.dst = dst;
			hit.pos = get_hit_point(ray.origin, ray.dir, dst);
			hit.normal = get_normal(hit.pos, sphere_c);
			printf("---DID HIT SPHERE\n");
		}
	}
	return (hit);
}

// void cal_sp_param(float *a, float *b, float *c, t_vec3d p1, t_vec3d p2, t_obj *sp)
// {
// 	*a = pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2);
// 	*b = 2 * ((p2.x - p1.x) * (p1.x - sp->pos.x)
// 			+ (p2.y - p1.y) * (p1.y - sp->pos.y)
// 			+ (p2.z - p1.z) * (p1.z - sp->pos.z));
// 	*c = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
// 		+ pow(p1.x, 2) + pow(p1.y, 2) + pow(p1.z, 2)
// 		- 2 * (sp->pos.x + p1.x + sp->pos.y
// 			* p1.x + sp->pos.z * p1.z) - pow(sp->diam / 2, 2);
// }


// t_vec3d	*ft_is_sp_1(t_vec3d p1, t_vec3d p2, t_obj *sp)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	sq;
// 	t_vec3d	*sol;

// 	cal_sp_param(&a, &b, &c, p1, p2, sp);
// 	sol = malloc (sizeof(t_vec3d));
// 	if(!sol)
// 		return (NULL);
// 	sq = pow(b, 2) - 4 * a * c;
// 	if (sq < 0)
// 		return (NULL);
// 	if (sq == 0)
// 	{
// 		sol->x = p1.x - (b / (2 * a)) * (p2.x - p1.x);
// 		sol->y = p1.y - (b / (2 * a)) * (p2.y - p1.y);
// 		sol->z = p1.z - (b / (2 * a)) * (p2.z - p1.z);
// 	}
// 	else
// 	{	sol->z = p1.z - ((b + sqrt(sq)) / (2 * a)) * (p2.z - p1.z);
// 		sol->y = p1.y - ((b + sqrt(sq)) / (2 * a)) * (p2.y - p1.y);
// 		sol->x = p1.x - ((b + sqrt(sq)) / (2 * a)) * (p2.x - p1.x);
// 	}
// 	return (sol);
// }

// t_vec3d	*ft_is_sp_2(t_vec3d p1, t_vec3d p2, t_obj *sp)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	sq;
// 	t_vec3d	*sol;

// 	cal_sp_param(&a, &b, &c, p1, p2, sp);
// 	sol = malloc (sizeof(t_vec3d));
// 	if(!sol)
// 		return (NULL);
// 	sq = pow(b, 2) - 4 * a * c;
// 	if (sq < 0)
// 		return (NULL);
// 	if (sq == 0)
// 		return (NULL);
// 	else
// 	{	sol->z = p1.z - ((b - sqrt(sq)) / (2 * a)) * (p2.z - p1.z);
// 		sol->y = p1.y - ((b - sqrt(sq)) / (2 * a)) * (p2.y - p1.y);
// 		sol->x = p1.x - ((b - sqrt(sq)) / (2 * a)) * (p2.x - p1.x);
// 	}
// 	return (sol);
// }

t_hit	sphere_hit2(t_ray ray, t_obj sphere)
{
	t_hit	hit;
	t_vec3d	*sol;

	hit.hit = false;
	sol = ft_is_sp_1(ray.origin, ray.dir, &sphere);
	if (!sol)
		sol = ft_is_sp_2(ray.origin, ray.dir, &sphere);
	if (!sol)
	{
		free(sol);
		return (hit);
	}
	hit.pos = *sol;
	hit.hit = true;
	free(sol);
	return (hit);
}