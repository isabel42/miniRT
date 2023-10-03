/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/03 13:09:52 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "minirt.h"

// https://www.kristakingmath.com/blog/intersection-of-a-line-and-a-plane

t_vec3d	*ft_is_pl(t_vec3d p1, t_vec3d p2, t_vec, t_obj *pl)
{
	t_vec3d	mult;
	t_vec3d	*sol;
	float	pl_sing;
	float	t;
	float	mod;

	mult.x = (p2.y - p1.y) * pl->dir.z - (p2.z - p1.z) * pl->dir.y;
	mult.y = (p2.z - p1.z) * pl->dir.x - (p2.x - p1.x) * pl->dir.z;
	mult.z = (p2.x - p1.x) * pl->dir.y - (p2.y - p1.y) * pl->dir.x;
	if (ft_mod(mult))
		return (NULL);
	pl_sing = pl->dir.x * pl->pos.x
		+ pl->dir.y * pl->pos.y + pl->dir.z * pl->pos.z;
	t = (pl_sing - p1.x * pl->dir.x - p1.y * pl->dir.y
			- p1.z * pl->dir.z) / (p2.x - p1.x) * pl->dir.x
		+ ((p2.y - p1.y) * pl->dir.y + (p2.z - p1.z) * pl->dir.z);
	sol->x = p1.x * t;
	sol->y = p1.y * t;
	sol->z = p1.z * t;
	return (sol);
}

// https://paulbourke.net/geometry/circlesphere/index.html#linesphere

void cal_sp_param(float *a, float *b, float *c)
{
	a = square(p2.x - p1.x) + square(p2.y - p1.y) + square(p2.z - p1.z);
	b = 2 * ((p2.x - p1.x) * (p1.x - sp->pos.x)
			+ (p2.y - p1.y) * (p1.y - sp->pos.y)
			+ (p2.z - p1.z) * (p1.z - sp->pos.z));
	c = square(sp->pos.x) + square(sp->pos.y) + square(sp->pos.z)
		+ square(p1.x) + square(p1.y) + square(p1.z)
		- 2 (sp->pos.x + p1.x + sp->pos.y
			* p1.x + sp->pos.z * p1.z) - square(sp->diam)
}

t_vec3d	*ft_is_sp_1(t_vec3d p1, t_vec3d p2, t_vec, t_obj *sp)
{
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_sp_param(&a, &b, &c);
	sq = square(b) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
	{
		sol.x = p1.x - (b / (2 * a)) * (p2.x - p1.x);
		sol.y = p1.y - (b / (2 * a)) * (p2.y - p1.y);
		sol.z = p1.z - (b / (2 * a)) * (p2.z - p1.z);
	}
	else
	{	sol.z = p1.z - ((b + sq) / (2 * a)) * (p2.z - p1.z)
		sol.y = p1.y - ((b + sq) / (2 * a)) * (p2.y - p1.y)
		sol.x = p1.x - ((b + sq) / (2 * a)) * (p2.x - p1.x)
	}
	return (sol);
}

t_vec3d	*ft_is_sp_2(t_vec3d p1, t_vec3d p2, t_vec, t_obj *sp)
{
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_sp_param(&a, &b, &c);
	sq = square(b) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
		return (NULL);
	else
	{	sol.z = p1.z - ((b - sq) / (2 * a)) * (p2.z - p1.z)
		sol.y = p1.y - ((b - sq) / (2 * a)) * (p2.y - p1.y)
		sol.x = p1.x - ((b - sq) / (2 * a)) * (p2.x - p1.x)
	}
	return (sol);
}