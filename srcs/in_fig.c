/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/08 16:56:01 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// https://www.kristakingmath.com/blog/intersection-of-a-line-and-a-plane

t_vec3d	*ft_is_pl(t_vec3d p1, t_vec3d p2, t_obj *pl)
{
	t_vec3d	*sol;
	float	pl_sing;
	float	t;

	sol = malloc (sizeof(t_vec3d));
	if(!sol)
		return (NULL);
	pl_sing = pl->dir.x * pl->pos.x
		+ pl->dir.y * pl->pos.y + pl->dir.z * pl->pos.z;
	if ((p2.x - p1.x) * pl->dir.x + (p2.y - p1.y) * pl->dir.y + (p2.z - p1.z) * pl->dir.z == 0
		&& pl->dir.x * p1.x + pl->dir.y * p1.y + pl->dir.z * p1.z != pl_sing)
		return (NULL);
	t = (pl_sing - p1.x * pl->dir.x - p1.y * pl->dir.y
			- p1.z * pl->dir.z) / ((p2.x - p1.x) * pl->dir.x
		+ ((p2.y - p1.y) * pl->dir.y + (p2.z - p1.z) * pl->dir.z));
	sol->x = p1.x + (p2.x - p1.x) * t;
	sol->y = p1.y + (p2.y - p1.y)  * t;
	sol->z = p1.z + (p2.z - p1.z) * t;
	return (sol);
}

// https://paulbourke.net/geometry/circlesphere/index.html#linesphere

void cal_sp_param(float *a, float *b, float *c, t_vec3d p1, t_vec3d p2, t_obj *sp)
{
	*a = pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2);
	*b = 2 * ((p2.x - p1.x) * (p1.x - sp->pos.x)
			+ (p2.y - p1.y) * (p1.y - sp->pos.y)
			+ (p2.z - p1.z) * (p1.z - sp->pos.z));
	*c = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
		+ pow(p1.x, 2) + pow(p1.y, 2) + pow(p1.z, 2)
		- 2 * (sp->pos.x + p1.x + sp->pos.y
			* p1.x + sp->pos.z * p1.z) - pow(sp->diam / 2, 2);
}

t_vec3d	*ft_is_sp_1(t_vec3d p1, t_vec3d p2, t_obj *sp)
{
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_sp_param(&a, &b, &c, p1, p2, sp);
	sol = malloc (sizeof(t_vec3d));
	if(!sol)
		return (NULL);
	sq = pow(b, 2) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
	{
		sol->x = p1.x - (b / (2 * a)) * (p2.x - p1.x);
		sol->y = p1.y - (b / (2 * a)) * (p2.y - p1.y);
		sol->z = p1.z - (b / (2 * a)) * (p2.z - p1.z);
	}
	else
	{	sol->z = p1.z - ((b + sqrt(sq)) / (2 * a)) * (p2.z - p1.z);
		sol->y = p1.y - ((b + sqrt(sq)) / (2 * a)) * (p2.y - p1.y);
		sol->x = p1.x - ((b + sqrt(sq)) / (2 * a)) * (p2.x - p1.x);
	}
	return (sol);
}

t_vec3d	*ft_is_sp_2(t_vec3d p1, t_vec3d p2, t_obj *sp)
{
	float	a;
	float	b;
	float	c;
	float	sq;
	t_vec3d	*sol;

	cal_sp_param(&a, &b, &c, p1, p2, sp);
	sol = malloc (sizeof(t_vec3d));
	if(!sol)
		return (NULL);
	sq = pow(b, 2) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
		return (NULL);
	else
	{	sol->z = p1.z - ((b - sqrt(sq)) / (2 * a)) * (p2.z - p1.z);
		sol->y = p1.y - ((b - sqrt(sq)) / (2 * a)) * (p2.y - p1.y);
		sol->x = p1.x - ((b - sqrt(sq)) / (2 * a)) * (p2.x - p1.x);
	}
	return (sol);
}

// https://www.youtube.com/watch?v=IKQCtqvGTJM

void cal_cy_param_a(float *a, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;

	line.x = p2.x - p1.x;
	line.y = p2.y - p1.y;
	line.z = p2.z - p1.z;
	
	*a = powf(cy->dir.x, 2) * powf(line.x, 2)
		+ powf(cy->dir.y, 2) * powf(line.y, 2)
		+ powf(cy->dir.z, 2) * powf(line.z, 2)
		+ 2 * (line.x * line.y * cy->dir.x * cy->dir.y
		+ line.x * line.z * cy->dir.x * cy->dir.z
		+ line.y * line.z * cy->dir.y * cy->dir.z) - (powf(line.x, 2) + powf(line.y, 2) + powf(line.z, 2)) * powf(ft_mod(cy->dir), 2);
}
void cal_cy_param_b(float *b, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;

	line.x = p2.x - p1.x;
	line.y = p2.y - p1.y;
	line.z = p2.z - p1.z;

	*b = 2 * (powf(cy->dir.x, 2) * line.x * p1.x
		+ pow(cy->dir.y, 2) * line.y * p1.y
		+ pow(cy->dir.z, 2) * line.z * p1.z
		+ line.x * p1.y * cy->dir.x * cy->dir.y + line.y * p1.x * cy->dir.x * cy->dir.y
		+ line.x * p1.z * cy->dir.x * cy->dir.z + line.z * p1.x * cy->dir.x * cy->dir.z
		+ line.y * p1.z * cy->dir.y * cy->dir.z + line.z * p1.y * cy->dir.x * cy->dir.z
		- line.x * (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x * cy->dir.y * cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
		- line.y * (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y * cy->dir.y * cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
		- line.z * (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z * cy->dir.y * cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z)
		- powf(ft_mod(cy->dir), 2) * (p1. x * line.x + p1.y * line.y + p1.z * line.z - line.x * cy->pos.x - line.y * cy->pos.y - line.z * cy->pos.z));
	
}
void cal_cy_param_c(float *c, t_vec3d p1, t_vec3d p2, t_obj *cy)
{
	t_vec3d	line;
	float	A;

	line.x = p2.x - p1.x;
	line.y = p2.y - p1.y;
	line.z = p2.z - p1.z;
	A = cy->dir.x * cy->pos.x + cy->dir.y * cy->pos.y + cy->dir.z * cy->pos.z;
	*c = powf(cy->dir.x * p1.x ,2) + powf(cy->dir.y * p1.y ,2) + powf(cy->dir.z * p1.z ,2)
	+ 2 * (p1.x * p1.y * cy->dir.x * cy->dir.y + p1.x * p1.z * cy->dir.x * cy->dir.z + p1.y * p1.z * cy->dir.y * cy->dir.z
	- (cy->dir.x * cy->dir.x * cy->pos.x + cy->dir.x * cy->dir.y * cy->pos.y + cy->dir.x * cy->dir.z * cy->pos.z)
	- (cy->dir.y * cy->dir.x * cy->pos.x + cy->dir.y * cy->dir.y * cy->pos.y + cy->dir.y * cy->dir.z * cy->pos.z)
	- (cy->dir.z * cy->pos.x * cy->pos.x + cy->dir.z * cy->dir.y * cy->pos.y + cy->dir.z * cy->dir.z * cy->pos.z))
	+ powf(A, 2) + powf(ft_mod(cy->dir), 2) * powf(cy->diam / 2, 2) + powf(ft_mod(cy->dir), 2) * (- powf(p1.x, 2) - powf(p1.y, 2) - powf(p1.z, 2)
	+ 2 * (p1.x * cy->pos.x + p1.y * cy->pos.y + p1.z * cy->pos.z) - (powf(cy->pos.x, 2) + powf(cy->pos.y, 2) + powf(cy->pos.z, 2)));
	
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
	printf("a: %f\n", a);
	printf("b: %f\n", b);
	printf("c: %f\n", c);
	sol = malloc (sizeof(t_vec3d));
	if(!sol)
		return (NULL);
	sq = powf(b, 2) - (4 * a * c);
	printf(" sq: %f \n" ,sq);
	printf(" t: %f \n" ,(-b + sqrt(sq)) / (2 * a));
	if (sq < 0 || (sq == 0 && a == 0))
		return (NULL);
	if (sq == 0)
	{
		sol->x = p1.x + (-b / (2 * a)) * p2.x;
		sol->y = p1.y + (-b / (2 * a)) * p2.y;
		sol->z = p1.z + (-b / (2 * a)) * p2.z;
	}
	else
	{
		sol->x = p1.x + ((-b - sqrt(powf(b, 2) - (4 * a * c))) / (2 * a)) * p2.x;
		sol->y = p1.y + ((-b - sqrt(powf(b, 2) - (4 * a * c))) / (2 * a)) * p2.y;
		sol->z = p1.z + ((-b - sqrt(powf(b, 2) - (4 * a * c))) / (2 * a)) * p2.z;
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
	sol = malloc (sizeof(t_vec3d));
	if(!sol)
		return (NULL);
	sq = pow(b, 2) - 4 * a * c;
	if (sq < 0)
		return (NULL);
	if (sq == 0)
		return (NULL);
	else
	{
		sol->x = p1.x + ((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a)) * p2.x;
		sol->y = p1.y + ((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a)) * p2.y;
		sol->z = p1.z + ((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a)) * p2.z;
	}
	return (sol);
}