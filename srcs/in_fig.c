/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/11 19:00:23 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// https://www.kristakingmath.com/blog/intersection-of-a-ray-and-a-plane

void	in_pl(t_ray ray, t_obj *pl, t_hit *hit)
{
	float	pl_sing;
	float	t;

	pl_sing = pl->dir.x * pl->pos.x
		+ pl->dir.y * pl->pos.y + pl->dir.z * pl->pos.z;
	if (ray.dir.x * pl->dir.x + ray.dir.y * pl->dir.y
		+ ray.dir.z * pl->dir.z == 0
		&& pl->dir.x * ray.origin.x + pl->dir.y * ray.origin.y
		+ pl->dir.z * ray.origin.z != pl_sing)
		return ;
	t = (pl_sing - ray.origin.x * pl->dir.x - ray.origin.y * pl->dir.y
			- ray.origin.z * pl->dir.z) / (ray.dir.x * pl->dir.x
			+ (ray.dir.y * pl->dir.y + ray.dir.z * pl->dir.z));
	if (t > 0)
	{
		hit->pos.x = ray.origin.x + ray.dir.x * t;
		hit->pos.y = ray.origin.y + ray.dir.y * t;
		hit->pos.z = ray.origin.z + ray.dir.z * t;
		hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
		hit->normal = pl->dir;
		hit->rgb = pl->rgb;
		hit->hit = true;
		hit->id = 1;
	}
}

// https://paulbourke.net/geometry/circlesphere/index.html#raysphere

void	cal_sp_param(t_vec3d *abc, t_ray ray, t_obj *sp)
{
	(*abc).x = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	(*abc).y = 2 * (ray.dir.x * (ray.origin.x - sp->pos.x)
			+ ray.dir.y * (ray.origin.y - sp->pos.y)
			+ ray.dir.z * (ray.origin.z - sp->pos.z));
	(*abc).z = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
		+ pow(ray.origin.x, 2) + pow(ray.origin.y, 2) + pow(ray.origin.z, 2)
		- 2 * (sp->pos.x * ray.origin.x + sp->pos.y * ray.origin.x
			+ sp->pos.z * ray.origin.z) - pow(sp->diam / 2, 2);
}

void	in_sp_all(t_ray ray, t_obj *sp, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0)
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

// https://www.youtube.com/watch?v=IKQCtqvGTJM

void	cal_cy_param_b(t_vec3d *abc, t_ray ray, t_obj *cy)
{
	(*abc).y = 2 * (powf(cy->dir.x, 2) * ray.dir.x * ray.origin.x
			+ pow(cy->dir.y, 2) * ray.dir.y * ray.origin.y
			+ pow(cy->dir.z, 2) * ray.dir.z * ray.origin.z
			+ ray.dir.x * ray.origin.y * cy->dir.x * cy->dir.y
			+ ray.dir.y * ray.origin.x * cy->dir.x * cy->dir.y
			+ ray.dir.x * ray.origin.z * cy->dir.x * cy->dir.z
			+ ray.dir.z * ray.origin.x * cy->dir.x * cy->dir.z
			+ ray.dir.y * ray.origin.z * cy->dir.y * cy->dir.z
			+ ray.dir.z * ray.origin.y * cy->dir.x * cy->dir.z
			- ray.dir.x * (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x
				* cy->dir.y * cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
			- ray.dir.y * (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y
				* cy->dir.y * cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
			- ray.dir.z * (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z
				* cy->dir.y * cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z)
			- powf(ft_mod(cy->dir), 2) * (ray.origin. x * ray.dir.x
				+ ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z
				- ray.dir.x * cy->pos.x - ray.dir.y * cy->pos.y
				- ray.dir.z * cy->pos.z));
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
			- (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x * cy->dir.y
				* cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
			- (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y * cy->dir.y
				* cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
			- (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z * cy->dir.y
				* cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z))
		+ powf(a_a, 2) + powf(ft_mod(cy->dir), 2) * powf(cy->diam / 2, 2)
		+ powf(ft_mod(cy->dir), 2)
		* (-powf(ray.origin.x, 2) - powf(ray.origin.y, 2)
			- powf(ray.origin.z, 2) + 2 * (ray.origin.x * cy->pos.x
				+ ray.origin.y * cy->pos.y + ray.origin.z * cy->pos.z)
			- (powf(cy->pos.x, 2) + powf(cy->pos.y, 2) + powf(cy->pos.z, 2)));
}

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

void	in_cy_body(t_ray ray, t_obj *cy, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0)
	{
		sol2.z = ray.origin.z + t * ray.dir.z;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.x = ray.origin.x + t * ray.dir.x;
		if ((hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
			&& powf(ft_mod(ft_v_sub(sol2, cy->pos)), 2) - powf(cy->diam / 2, 2)
			<= powf(cy->high / 2, 2))
		{
			hit->pos.z = ray.origin.z + t * ray.dir.z;
			hit->pos.y = ray.origin.y + t * ray.dir.y;
			hit->pos.x = ray.origin.x + t * ray.dir.x;
			hit->dst = ft_mod(ft_v_sub(sol2, ray.origin));
			hit->normal = ft_v_sub(hit->pos, cy->pos);
			hit->rgb = cy->rgb;
			hit->hit = true;
			hit->id = 2;
		}
	}
}

void	in_cy_caps(t_ray ray, t_obj *cy, t_hit *hit, float t)
{
	t_obj	cap;
	t_hit	hit_loc;

	cap.dir = cy->dir;
	cap.pos.x = cy->pos.x + t * cy->dir.x;
	cap.pos.y = cy->pos.y + t * cy->dir.y;
	cap.pos.z = cy->pos.z + t * cy->dir.z;
	in_pl(ray, &cap, &hit_loc);
	if (hit_loc.dst > 0 && (hit->dst > hit_loc.dst || hit->hit == false)
		&& ft_mod(ft_v_sub(hit_loc.pos, cap.pos)) <= cy->diam / 2)
	{
		hit->pos = hit_loc.pos;
		hit->dst = hit_loc.dst;
		hit->normal = cy->dir;
		hit->rgb = cy->rgb;
		hit->hit = true;
		hit->id = 2;
	}
}

void	in_cy(t_ray ray, t_obj *cy, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;

	cal_cy_param(&abc, ray, cy);
	sq = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (sq >= 0 && abc.x != 0)
	{
		in_cy_body(ray, cy, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
		in_cy_body(ray, cy, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
	}
	in_cy_caps(ray, cy, hit, (cy->high / 2) / ft_mod(cy->dir));
	in_cy_caps(ray, cy, hit, -(cy->high / 2) / ft_mod(cy->dir));
}
