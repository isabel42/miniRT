/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameratest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:56:17 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/03 18:51:04 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat	*init_quat_camera(int plane_height, int plane_width, t_vec3d pos, int dist)
{
	t_quat	*c;

	c = malloc(sizeof(t_quat) * 5);
	if (!c)
		ft_exit("Malloc quaternion");
	c[0] = quat_create(0, pos.x - (plane_width / 2), pos.y + (plane_height / 2), -dist);
	c[1] = quat_create(0, pos.x + (plane_width / 2), pos.y + (plane_height / 2), -dist);
	c[2] = quat_create(0, pos.x + (plane_width / 2), pos.y - (plane_height / 2), -dist);
	c[3] = quat_create(0, pos.x - (plane_width / 2), pos.y - (plane_height / 2), -dist);
	c[4] = quat_create(0, pos.x, pos.y, pos.z);
	return (c);
}

void	camera_param(t_cam *cam)
{
	float plane_height;
	float plane_width;

	plane_width = cam->dist * tan(ft_deg_to_rad(cam->fov) * 0.5f) * 2;
	plane_height = plane_width * (WIDTH / HEIGHT);
	cam->c = init_quat_camera(plane_height, plane_width, cam->pos, cam->dist);
}

t_point	get_point(t_quat q)
{
	t_point	res;

	res.x = q.x;
	res.y = q.y;
	return (res);
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
	c[0] = quat_multiply(
			quat_multiply(scena->cam->dir, c[0]),
			quat_conjugate(scena->cam->dir));
	c[1] = quat_multiply(
			quat_multiply(scena->cam->dir, c[1]),
			quat_conjugate(scena->cam->dir));
	c[2] = quat_multiply(
			quat_multiply(scena->cam->dir, c[2]),
			quat_conjugate(scena->cam->dir));
	c[3] = quat_multiply(
			quat_multiply(scena->cam->dir, c[3]),
			quat_conjugate(scena->cam->dir));
	c[4] = quat_multiply(
			quat_multiply(scena->cam->dir, c[4]),
			quat_conjugate(scena->cam->dir));
	bresenham_draw_line(get_point(c[0]), get_point(c[1]), scena, color);
	bresenham_draw_line(get_point(c[1]), get_point(c[2]), scena, color);
	bresenham_draw_line(get_point(c[2]), get_point(c[3]), scena, color);
	bresenham_draw_line(get_point(c[3]), get_point(c[0]), scena, color);
	bresenham_draw_line(get_point(c[4]), get_point(c[0]), scena, color);
	bresenham_draw_line(get_point(c[4]), get_point(c[1]), scena, color);
	bresenham_draw_line(get_point(c[4]), get_point(c[2]), scena, color);
	bresenham_draw_line(get_point(c[4]), get_point(c[3]), scena, color);
}

void	my_new_mlx_img_data(t_scenario *meta)
{
	meta->img_data->img = mlx_new_image(meta->mlx->ptr, WIDTH, HEIGHT);
	meta->img_data->addr = mlx_get_data_addr(meta->img_data->img,
			&meta->img_data->bits_per_pixel,
			&meta->img_data->line_length, &meta->img_data->endian);
}

int	render_camera(t_scenario *scena)
{
	mlx_clear_window(scena->mlx->ptr, scena->mlx->win);
	draw_camera(scena);
	mlx_put_image_to_window(scena->mlx->ptr,
		scena->mlx->win, scena->img_data->img, 0, 0);
	mlx_destroy_image(scena->mlx->ptr, scena->img_data->img);
	my_new_mlx_img_data(scena);
	return (0);
}
