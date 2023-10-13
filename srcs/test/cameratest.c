/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameratest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:56:17 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/12 13:54:02 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat	*init_quat_camera(int plane_height, int plane_width, t_vec3d pos, int dist)
{
	t_quat	*c;

	c = malloc(sizeof(t_quat) * 5);
	if (!c)
		ft_exit("Malloc");
	c[0] = quat_create(0, pos.x - (plane_width / 2), pos.y + (plane_height / 2), -dist + pos.z);
	c[1] = quat_create(0, pos.x + (plane_width / 2), pos.y + (plane_height / 2), -dist + pos.z);
	c[2] = quat_create(0, pos.x + (plane_width / 2), pos.y - (plane_height / 2), -dist + pos.z);
	c[3] = quat_create(0, pos.x - (plane_width / 2), pos.y - (plane_height / 2), -dist + pos.z);
	c[4] = quat_create(0, pos.x, pos.y, pos.z);
	// (void)pos;
	// c[0] = quat_create(0, - (plane_width / 2), (plane_height / 2), -dist);
	// c[1] = quat_create(0, (plane_width / 2), (plane_height / 2), -dist);
	// c[2] = quat_create(0,(plane_width / 2), -(plane_height / 2), -dist);
	// c[3] = quat_create(0, -(plane_width / 2), -(plane_height / 2), -dist);
	// c[4] = quat_create(0, 0, 0, 0);
	return (c);
}

void	camera_param(t_cam *cam)
{
	float plane_height;
	float plane_width;

	plane_width = cam->dist * tan(ft_deg_to_rad(cam->fov) * 0.5f) * 4;
	plane_height = plane_width * ((float)HEIGHT / (float)WIDTH);
	// printf("Plane: width = %f height:%f\n", plane_width, plane_height);
	cam->c = init_quat_camera(plane_height, plane_width, cam->pos, cam->dist);
}

t_point	get_point(t_quat q, t_scenario *scena)
{
	t_point	res;

	res.x = q.x + scena->meta->offset[0];
	res.y = q.y + scena->meta->offset[1];
	// (void)scena;
	// res.x = q.x;
	// res.y = q.y;
	return (res);
}

void	rotate_camera(t_cam *cam, t_quat rotation)
{
	// cam->dir = quat_multiply(
	// 		quat_multiply(rotation, cam->dir),
	// 		quat_conjugate(rotation));
	cam->dir = rotation;
	//cam->dir = quat_normalize(cam->dir);
}
//scena->c = init_camera(param_to_rect(scena->cam));
void	draw_camera(t_scenario *scena)
{
	t_quat	*c;
	t_rgb	color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	c = scena->cam->c;
	// c[0] = quat_multiply(
	// 		quat_multiply(scena->cam->dir, c[0]),
	// 		quat_conjugate(scena->cam->dir));
	// c[1] = quat_multiply(
	// 		quat_multiply(scena->cam->dir, c[1]),
	// 		quat_conjugate(scena->cam->dir));
	// c[2] = quat_multiply(
	// 		quat_multiply(scena->cam->dir, c[2]),
	// 		quat_conjugate(scena->cam->dir));
	// c[3] = quat_multiply(
	// 		quat_multiply(scena->cam->dir, c[3]),
	// 		quat_conjugate(scena->cam->dir));
	// c[4] = quat_multiply(
	// 		quat_multiply(scena->cam->dir, c[4]),
	// 		quat_conjugate(scena->cam->dir));
	// c[0] = quat_multiply(scena->cam->dir, c[0]);
	// c[1] = quat_multiply(scena->cam->dir, c[1]);
	// c[2] = quat_multiply(scena->cam->dir, c[2]);
	// c[3] = quat_multiply(scena->cam->dir, c[3]);
	// c[4] = quat_multiply(scena->cam->dir, c[4]);
	// bresenham_draw_line(get_point(c[0]), get_point(c[1]), scena, color);
	// bresenham_draw_line(get_point(c[1]), get_point(c[2]), scena, color);
	// bresenham_draw_line(get_point(c[2]), get_point(c[3]), scena, color);
	// bresenham_draw_line(get_point(c[3]), get_point(c[0]), scena, color);
	// bresenham_draw_line(get_point(c[4]), get_point(c[0]), scena, color);
	// bresenham_draw_line(get_point(c[4]), get_point(c[1]), scena, color);
	// bresenham_draw_line(get_point(c[4]), get_point(c[2]), scena, color);
	// bresenham_draw_line(get_point(c[4]), get_point(c[3]), scena, color);
	bresenham_draw_line(get_point(c[0], scena), get_point(c[1], scena), scena, color);
	bresenham_draw_line(get_point(c[1], scena), get_point(c[2], scena), scena, color);
	bresenham_draw_line(get_point(c[2], scena), get_point(c[3], scena), scena, color);
	bresenham_draw_line(get_point(c[3], scena), get_point(c[0], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[0], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[1], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[2], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[3], scena), scena, color);
}

void	my_new_mlx_img_data(t_scenario *meta)
{
	meta->img_data->img = mlx_new_image(meta->mlx->ptr, WIDTH, HEIGHT);
	meta->img_data->addr = mlx_get_data_addr(meta->img_data->img,
			&meta->img_data->bits_per_pixel,
			&meta->img_data->line_length, &meta->img_data->endian);
}

int	render(t_scenario *scena)
{
	mlx_clear_window(scena->mlx->ptr, scena->mlx->win);
	// draw_camera(scena);
	// draw_scenario(scena);
	// draw_ray(scena);
	check_ob(scena);
	mlx_put_image_to_window(scena->mlx->ptr,
		scena->mlx->win, scena->img_data->img, 0, 0);
	mlx_destroy_image(scena->mlx->ptr, scena->img_data->img);
	my_new_mlx_img_data(scena);
	return (0);
}
