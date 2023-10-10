/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/10 17:03:23 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// https://www.kristakingmath.com/blog/intersection-of-a-ray-and-a-plane

void	in_pl(t_vec3d p1, t_vec3d p2, t_obj *pl, t_hit *hit)
{
	float	pl_sing;
	float	t;
	t_vec3d	ray;

	ray = ft_v_sub(p2, p1);
	pl_sing = pl->dir.x * pl->pos.x
		+ pl->dir.y * pl->pos.y + pl->dir.z * pl->pos.z;
	if (ray.x * pl->dir.x + ray.y * pl->dir.y + ray.z * pl->dir.z == 0
		&& pl->dir.x * p1.x + pl->dir.y * p1.y + pl->dir.z * p1.z != pl_sing)
		return ;
	t = (pl_sing - p1.x * pl->dir.x - p1.y * pl->dir.y
			- p1.z * pl->dir.z) / (ray.x * pl->dir.x
			+ (ray.y * pl->dir.y + ray.z * pl->dir.z));
	if (t < 0)
		return ;
	hit->pos.x = p1.x + ray.x * t;
	hit->pos.y = p1.y + ray.y * t;
	hit->pos.z = p1.z + ray.z * t;
	hit->dst = ft_mod(ft_v_sub(hit->pos, p1));
	hit->nomal = pl->dir;
	hit->rgb = pl->rgb;
}

// https://paulbourke.net/geometry/circlesphere/index.html#raysphere

void	cal_sp_param(t_vec3d *abc, t_vec3d p1, t_vec3d p2, t_obj *sp)
{
	t_vec3d	ray;

	ray = ft_v_sub(p2, p1);
	(*abc).x = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
	(*abc).y = 2 * (ray.x * (p1.x - sp->pos.x)
			+ ray.y * (p1.y - sp->pos.y)
			+ ray.z * (p1.z - sp->pos.z));
	(*abc).z = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
		+ pow(p1.x, 2) + pow(p1.y, 2) + pow(p1.z, 2)
		- 2 * (sp->pos.x * p1.x + sp->pos.y * p1.x
			+ sp->pos.z * p1.z) - pow(sp->diam / 2, 2);
}

void	in_sp(t_vec3d p1, t_vec3d p2, t_obj *sp, t_hit *hit)
{
	t_vec3d	abc;
	t_vec3d	sol2;
	float	sq;

	cal_sp_param(&abc, p1, p2, sp);
	sq = powf(abc.y, 2) - 4 * abc.x * abc.z;
	if (sq < 0 || (sq == 0 && abc.x == 0))
		return ;
	if (((-abc.y - sqrt(sq)) / (2 * abc.x) >= 0))
	{
		hit->pos.z = p1.z + ((-abc.y - sqrt(sq)) / (2 * abc.x)) * (p2.z - p1.z);
		hit->pos.y = p1.y + ((-abc.y - sqrt(sq)) / (2 * abc.x)) * (p2.y - p1.y);
		hit->pos.x = p1.x + ((-abc.y - sqrt(sq)) / (2 * abc.x)) * (p2.x - p1.x);
		hit->dst = ft_mod(ft_v_sub(hit->pos, p1));
		hit->normal = ft_v_sub(hit->pos, sp->pos);
	}
	if ((-abc.y + sqrt(sq)) / (2 * abc.x) > 0)
	{
		sol2.z = p1.z + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.z - p1.z);
		sol2.y = p1.y + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.y - p1.y);
		sol2.x = p1.x + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.x - p1.x);
		if (hit->dst > ft_mod(ft_v_sub(sol2, p1)) || hit->dst < 0)
		{
			hit->pos.z = p1.z + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.z - p1.z);
			hit->pos.y = p1.y + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.y - p1.y);
			hit->pos.x = p1.x + ((-abc.y + sqrt(sq)) / (2 * abc.x)) * (p2.x - p1.x);
			hit->dst = ft_mod(ft_v_sub(sol2, p1));
			hit->normal = ft_v_sub(hit->pos, sp->pos);
		}
	}
	hit->rgb = sp->rgb;
}

// https://www.youtube.com/watch?v=IKQCtqvGTJM

void	cal_cy_param_b(t_vec3d *abc, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	ray;

	ray = ft_v_sub(p2, p1);
	(*abc).y = 2 * (powf(cy->dir.x, 2) * ray.x * p1.x
			+ pow(cy->dir.y, 2) * ray.y * p1.y
			+ pow(cy->dir.z, 2) * ray.z * p1.z
			+ ray.x * p1.y * cy->dir.x * cy->dir.y
			+ ray.y * p1.x * cy->dir.x * cy->dir.y
			+ ray.x * p1.z * cy->dir.x * cy->dir.z
			+ ray.z * p1.x * cy->dir.x * cy->dir.z
			+ ray.y * p1.z * cy->dir.y * cy->dir.z
			+ ray.z * p1.y * cy->dir.x * cy->dir.z
			- ray.x * (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x
				* cy->dir.y * cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
			- ray.y * (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y
				* cy->dir.y * cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
			- ray.z * (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z
				* cy->dir.y * cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z)
			- powf(ft_mod(cy->dir), 2) * (p1. x * ray.x + p1.y * ray.y + p1.z
				* ray.z - ray.x * cy->pos.x
				- ray.y * cy->pos.y - ray.z * cy->pos.z));
}

void	cal_cy_param_c(t_vec3d *abc, t_vec3d p1, t_obj *cy)
{
	float	a_a;

	a_a = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;
	(*abc).z = powf(cy->dir.x * p1.x, 2) + powf(cy->dir.y * p1.y, 2)
		+ powf(cy->dir.z * p1.z, 2) + 2 * (p1.x * p1.y * cy->dir.x * cy->dir.y
			+ p1.x * p1.z * cy->dir.x * cy->dir.z
			+ p1.y * p1.z * cy->dir.y * cy->dir.z
			- (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x * cy->dir.y
				* cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
			- (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y * cy->dir.y
				* cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
			- (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z * cy->dir.y
				* cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z))
		+ powf(a_a, 2) + powf(ft_mod(cy->dir), 2) * powf(cy->diam / 2, 2)
		+ powf(ft_mod(cy->dir), 2)
		* (-powf(p1.x, 2) - powf(p1.y, 2) - powf(p1.z, 2)
			+ 2 * (p1.x * cy->pos.x + p1.y * cy->pos.y + p1.z * cy->pos.z)
			- (powf(cy->pos.x, 2) + powf(cy->pos.y, 2) + powf(cy->pos.z, 2)));
}

void	cal_cy_param(t_vec3d *abc, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	ray;

	ray = ft_v_sub(p2, p1);
	(*abc).x = powf(cy->dir.x, 2) * powf(ray.x, 2)
		+ powf(cy->dir.y, 2) * powf(ray.y, 2)
		+ powf(cy->dir.z, 2) * powf(ray.z, 2)
		+ 2 * (ray.x * ray.y * cy->dir.x * cy->dir.y
			+ ray.x * ray.z * cy->dir.x * cy->dir.z
			+ ray.y * ray.z * cy->dir.y * cy->dir.z)
		- powf(ft_mod(ray), 2) * powf(ft_mod(cy->dir), 2);
	cal_cy_param_b(abc, p1, p2, cy);
	cal_cy_param_c(abc, p1, cy);

}

void	in_cy(t_vec3d p1, t_vec3d p2, t_obj *cy, t_hit *hit)
{
	t_vec3d	abc;
	t_vec3d	sol2;
	float	sq;
	float	t;

	cal_cy_param(&abc, p1, p2, cy);
	sq = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (sq < 0 || (sq == 0 && abc.x == 0))
		return ;
	t = (-abc.y - sqrt(sq)) / (2 * abc.x);
	if (t >= 0)
	{
		hit->pos.x = p1.x + t * (p2.x - p1.x);
		hit->pos.y = p1.y + t * (p2.y - p1.y);
		hit->pos.z = p1.z + t * (p2.z - p1.z);
		if (powf(ft_mod(ft_v_sub(hit->pos, cy->pos)), 2) - powf(cy->diam / 2, 2)
			<= cy->high / 2)
			hit->dst = ft_mod(ft_v_sub(hit->pos, p1));
		hit->normal = ft_v_sub(hit->pos, cy->pos);
	}
	t = (-abc.y + sqrt(sq)) / (2 * abc.x);
	if (t >= 0)
	{
		sol2.z = p1.z + t * (p2.z - p1.z);
		sol2.y = p1.y + t * (p2.y - p1.y);
		sol2.x = p1.x + t * (p2.x - p1.x);
		if ((hit->dst > ft_mod(ft_v_sub(sol2, p1)) || hit->dst < 0)
			&& powf(ft_mod(ft_v_sub(sol2, cy->pos)), 2) - powf(cy->diam / 2, 2)
			<= cy->high / 2)
		{
			hit->pos.z = p1.z + t * (p2.z - p1.z);
			hit->pos.y = p1.y + t * (p2.y - p1.y);
			hit->pos.x = p1.x + t * (p2.x - p1.x);
			hit->dst = ft_mod(ft_v_sub(sol2, p1));
			hit->normal = ft_v_sub(hit->pos, cy->pos);
		}
	}
	
	hit->rgb = cy->rgb;
}
