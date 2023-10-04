/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:50:20 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 20:53:30 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_point_r(t_quat q, t_scenario *scena)
{
	t_point	res;

	res.x = q.x + scena->meta->offset[0];;
	res.y = q.y + scena->meta->offset[1];;
	return (res);
}

void	draw_ray(t_scenario *scena)
{
	t_vec3d	dx;
	t_vec3d	dy;
	t_quat	point;
	t_quat	ref;
	int		ix = 0;
	int		iy = 0;
	int		n = 30;
	float	xstep_x;
	float	xstep_y;
	float	xstep_z;
	float	ystep_x;
	float	ystep_y;
	float	ystep_z;
	t_rgb	color;

	color.r = 0;
	color.g = 128;
	color.b = 128;
	dx.x = scena->cam->c[1].x - scena->cam->c[0].x;
	dx.y = scena->cam->c[1].y - scena->cam->c[0].y;
	dx.z = scena->cam->c[1].z - scena->cam->c[0].z;
	dy.x = scena->cam->c[3].x - scena->cam->c[0].x;
	dy.y = scena->cam->c[3].y - scena->cam->c[0].y;
	dy.z = scena->cam->c[3].z - scena->cam->c[0].z;
	xstep_x = dx.x / (n - 1);
	xstep_y = dx.y / (n - 1);
	xstep_z = dx.z / (n - 1);
	ystep_x = dy.x / (n - 1);
	ystep_y = dy.y / (n - 1);
	ystep_z = dy.z / (n - 1);
	printf("--- step: x=%f y=%f z=%f\n", xstep_x, xstep_y, xstep_z);
	ref = scena->cam->c[0];
	while (iy <= n)
	{
		while (ix < n)
		{
			printf("Boucle while\n");
			point.x = ref.x + ix * xstep_x;
			point.y = ref.y + ix * xstep_y;
			point.z = ref.z + ix * xstep_z;
			point = quat_create(0, point.x, point.y, point.z);
			printf("New point ray: ");
			print_q(point);
			// printf("New point: %d %d\n", point.x, point.y);
			// printf("scena->cam->c[4]: ");
			// print_q(scena->cam->c[4]);
			// printf("scena->cam->c[0]: ");
			// print_q(scena->cam->c[0]);
			bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(point, scena), scena,color);
			ix++;
		}
		ref.x = scena->cam->c[0].x + iy * ystep_x;
		ref.y = scena->cam->c[0].y + iy * ystep_y;
		ref.z = scena->cam->c[0].z + iy * ystep_z;
		iy++;
		ix = 0;
	}
}