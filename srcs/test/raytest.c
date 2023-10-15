/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:50:20 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/15 18:10:31 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_point_r(t_quat q, t_scenario *scena)
{
	t_point	res;

	res.x = q.x + scena->meta->offset[0];
	res.y = q.y + scena->meta->offset[1];
	// (void)scena;
	// res.x = q.x;
	// res.y = q.y;
	return (res);
}

t_vec3d	new_point(t_quat q)
{
	t_vec3d	res;

	res.x = q.x;
	res.y = q.y;
	res.z = q.z;
	return (res);
}

t_ray	new_ray(t_vec3d p1, t_vec3d p2)
{
	t_ray	ray;

	ray.origin = p1;
	ray.dir = p2;
	return (ray);
}

void	draw_ray(t_scenario *scena)
{
	t_vec3d	dx;
	t_vec3d	dy;
	t_quat	point;
	t_quat	ref;
	int		ix = 0;
	int		iy = 0;
	int		n = 50;
	float	xstep_x;
	float	xstep_y;
	float	xstep_z;
	float	ystep_x;
	float	ystep_y;
	float	ystep_z;
	t_rgb	color;
	t_obj	*objects;

	objects = scena->obj;
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
	// printf("--- step: x=%f y=%f z=%f\n", xstep_x, xstep_y, xstep_z);
	ref = scena->cam->c[0];
	while (iy <= n)
	{
		while (ix < n)
		{
			// printf("Boucle while\n");
			point.x = ref.x + ix * xstep_x;
			point.y = ref.y + ix * xstep_y;
			point.z = ref.z + ix * xstep_z;
			t_vec3d	point_dir;
			point_dir.x = point.x;
			point_dir.y = point.y;
			point_dir.z = point.z;
			if (iy == 0 || iy == n)
				bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(point, scena), scena, int_to_rgb(I_RED));
			if (ix == 0 || ix == n - 1)
				bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(point, scena), scena, int_to_rgb(I_RED));
			// point = quat_create(0, point.x, point.y, point.z);
			// printf("New point ray: ");
			// print_q(point);
			// printf("New point: %d %d\n", point.x, point.y);
			// printf("scena->cam->c[4]: ");
			// print_q(scena->cam->c[4]);
			// printf("scena->cam->c[0]: ");
			// print_q(scena->cam->c[0]);
			while (objects)
			{
				if (objects->cube && objects->id == sp)
				{
					t_hit	hit;
					t_ray	ray;

					ray = new_ray(new_point(scena->cam->c[4]), new_point(point));
					// bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(objects->cube[0], scena), scena,int_to_rgb(I_BROWN));
					objects->pos = quat_to_vector(objects->cube[0]);
					hit = sphere_hit3(ray, objects->pos, objects->diam / 2);
					// t_quat sphere_center = quat_create(0, objects->pos.x, objects->pos.y, objects->pos.z);
					// hit = sphere_hit(ray, sphere_center, objects->diam / 2);
					// hit = sphere_hit2(new_ray(new_point(scena->cam->c[4]), new_point(point)), *objects);
					if (hit.hit == true)
					{
						t_quat	hitq = quat_create(0, hit.pos.x, hit.pos.y, hit.pos.z);
						// hitq = quat_multiply(quat_multiply(scena->cam->dir, hitq),quat_conjugate(scena->cam->dir));
						bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(hitq, scena), scena, int_to_rgb(I_YELLOW));
						// my_mlx_pixel_put(scena->img_data, hitq.x + scena->meta->offset[0], hitq.y + scena->meta->offset[1], I_YELLOW);
						// bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(point, scena), scena, int_to_rgb(I_BLUE));
						// bresenham_draw_line(get_point_r(point, scena), get_point_r(hitq, scena), scena, int_to_rgb(I_YELLOW));
						// t_quat	ray_o = quat_create(0, ray.origin.x, ray.origin.y, ray.origin.z);
						// t_quat	ray_dir = quat_create(0, ray.dir.x, ray.dir.y, ray.dir.z);
						// bresenham_draw_line(get_point_r(ray_o, scena), get_point_r(ray_dir, scena), scena, int_to_rgb(I_RED));
						// my_mlx_pixel_put(scena->img_data, point.x + scena->meta->offset[0], point.y + scena->meta->offset[1], rgb_to_int(objects->rgb));
					}
				}
				objects = objects->next;
			}
			objects = scena->obj;
			// bresenham_draw_line(get_point_r(scena->cam->c[4], scena), get_point_r(point, scena), scena,color);
			ix++;
		}
		ref.x = scena->cam->c[0].x + iy * ystep_x;
		ref.y = scena->cam->c[0].y + iy * ystep_y;
		ref.z = scena->cam->c[0].z + iy * ystep_z;
		iy++;
		ix = 0;
	}
}

// void	ray_test(scena)
// {
// 	float	plane_width = cam->dist * tan(ft_deg_to_rad(cam->fov) * 0.5f) * 4;
// 	float	plane_height = plane_width * ((float)HEIGHT / (float)WIDTH);
// 	t_vec3d	bottom_left = new_vector(-plane_width / 2, -plane_height / 2, dist);
// 	int		n = 200;
	
// 	for (int x = 0; x < n)
// 	{
// 		for (int y = 0; y < n)
// 		{
			
// 		}
// 	}
// }