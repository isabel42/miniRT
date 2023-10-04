/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/04 16:48:21 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// https://www.kristakingmath.com/blog/intersection-of-a-line-and-a-plane

t_vec3d	*ft_is_pl(t_vec3d p1, t_vec3d p2, t_obj *pl)
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
			* p1.x + sp->pos.z * p1.z) - square(sp->diam / 2)
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

// https://www.youtube.com/watch?v=IKQCtqvGTJM

void cal_cy_param_a(float *a, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;

	line.x = p2.x - p1.x:
	line.y = p2.y - p1.y:
	line.z = p2.z - p1.z:
	*a = square(ft_mod(cy->dir)) * square(ft_mod(line))
		+ square(cy->dir.x * line.x + cy->dir.y + line.y)
		+ square(cy->dir.y * line.z)
		+ 2 * cy->dir.x * cy->dir.z * line.x * line.z
		+ 2 * cy->dir.y * cy->dir.z * line.y * line.z;
}
void cal_cy_param_b(float *b, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;
	float	A;

	line.x = p2.x - p1.x:
	line.y = p2.y - p1.y:
	line.z = p2.z - p1.z:
	A = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;
	*b = 2 * (square(ft_mod(cy->dir))
		* (cy->dir.x * p1.x + cy->dir.y * p1.y + cy->dir.z * p1.z
		- cy->pos.x * line.x - cy->pos.y * line.y - cy->pos.z * line.z)
		+ square(cy->dir.x) * line.x * p1.x
		+ square(cy->dir.y) * line.y * p1.y
		+ square(cy->dir.z) * line.z * p1.z
		- A * (cy->dir.x * line.x + cy->dir.y * line.y + cy->dir.z * line.z)
		+ (cy->dir.x * cy->dir.y) * (line.x * p1.y + line.y * p1.x)
		+ (cy->dir.x * cy->dir.z) * (line.x * p1.z + line.z * p1.x)
		+ (cy->dir.x * cy->dir.z) * (line.y * p1.z + line.x * p1.y));
	
}
void cal_cy_param_c(float *b, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;
	float	A;

	line.x = p2.x - p1.x:
	line.y = p2.y - p1.y:
	line.z = p2.z - p1.z:
	A = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;


	*c = square(ft_mod(cy->dir))
		* (square(p1.x - cy->pos.x) + square(p1.y - cy->pos.y)
		+ square(p1.z - cy->pos.z))
		+ square(cy->dir.x * p1.x - A + cy->dir.y * p1.y + cy->dir.z * p1.z)
		+ square(cy->diam / 2 * ft_mod(cy->dir));
	
}

t_vec3d *in_cy_1(t_vec3d p1, t_vec3d p2, t_obj *cy)
{ 
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_cy_param_a(&a, p1, p2, cy);
	cal_cy_param_b(&b, p1, p2, cy);
	cal_cy_param_c(&c, p1, p2, cy);
	sq = square(b) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
		return (NULL);
	else
	{
		sol.x = p1.x + ((-b + sqrt(square(b) - 4 * a * c)) / (2 * a))\ * p2.x;
		sol.y = p1.y + ((-b + sqrt(square(b) - 4 * a * c)) / (2 * a)) * p2.y;
		sol.z = p1.z + ((-b + sqrt(square(b) - 4 * a * c))/ (2 * a)) * p2.z;
	}
	return (sol);
}

t_vec3d *in_cy_2(t_vec3d p1, t_vec3d p2, t_obj *cy)
{ 
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_cy_param_a(&a, p1, p2, cy);
	cal_cy_param_b(&b, p1, p2, cy);
	cal_cy_param_c(&c, p1, p2, cy);
	sq = square(b) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
	{
		sol.x = p1.x + (-b / (2 * a)) * p2.x;
		sol.y = p1.y + (-b / (2 * a)) * p2.y;
		sol.z = p1.z + (-b / (2 * a)) * p2.z;
	}
	else
	{
		sol.x = p1.x + ((-b - sqrt(square(b) - 4 * a * c)) / (2 * a)) * p2.x;
		sol.y = p1.y + ((-b - sqrt(square(b) - 4 * a * c)) / (2 * a)) * p2.y;
		sol.z = p1.z + ((-b - sqrt(square(b) - 4 * a * c)) / (2 * a)) * p2.z;
	}
	return (sol);
}