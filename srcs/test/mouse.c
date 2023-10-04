/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:39:23 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 17:00:16 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation(t_scenario *scena)
{
	t_quat	*c;

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
	// c[0] = quat_multiply(scena->cam->dir, c[0]);
	// c[1] = quat_multiply(scena->cam->dir, c[1]);
	// c[2] = quat_multiply(scena->cam->dir, c[2]);
	// c[3] = quat_multiply(scena->cam->dir, c[3]);
	// c[4] = quat_multiply(scena->cam->dir, c[4]);
	scena->cam->c = c;
}

void	mouse_rotate(int move_x, int move_y, t_meta *meta)
{
	// t_quat	rotation;
	// meta->rotation_quat = euler_to_quat(0,
	// 		deg_to_rad(atan(move_x / 1)) * 2,
	// 		-deg_to_rad(atan(move_y / 1)) * 2);
	// meta->idenditiy_quat = quat_multiply(meta->rotation_quat,
	// 		meta->idenditiy_quat);
	printf("Moving mouse x:%i y:%i\n", move_x, move_y);
	// if (move_x < 0)
	// 	rotate_camera(meta->scena->cam, meta->cache->yaw_m);
	// if (move_x > 0)
	// 	rotate_camera(meta->scena->cam, meta->cache->yaw_p);
	// if (move_y < 0)
	// 	rotate_camera(meta->scena->cam, meta->cache->pitch_m);
	// if (move_y > 0)
	// 	rotate_camera(meta->scena->cam, meta->cache->pitch_p);
	meta->scena->cam->dir = euler_to_quat(0,
			ft_deg_to_rad(atan(move_x / 1)) * 2,
			-ft_deg_to_rad(atan(move_y / 1)) * 2);
	// meta->scena->cam->dir = quat_multiply(meta->rotation_quat,
	// 		meta->idenditiy_quat);
	printf("Meta->scena->cam: ");
	print_q(meta->scena->cam->dir);
	apply_rotation(meta->scena);
	return ;
}

int	mouse_move(int x, int y, t_meta *meta)
{
	static int	previous_x = 0;
	static int	previous_y = 0;
	int			x_move;
	int			y_move;

	x_move = x - previous_x;
	y_move = y - previous_y;
	if ((abs(x_move) || abs(y_move)) && (meta->click_state)
		&& (((x < WIDTH) && (x > 0)) && ((y < HEIGHT) && (y > 0))))
	{
		if (meta->shift_state == 1)
			mouse_rotate(x_move, y_move, meta);
		else if (meta->ctrl_state == 1)
		{
			meta->offset[0] += x_move;
			meta->offset[1] += y_move;
			// mouse_translate(x_move, y_move, meta);
		}
		render_camera(meta->scena);
	}
	previous_x = x;
	previous_y = y;
	return (0);
}

int	mouse_pressed(int button, int x, int y, t_meta *meta)
{
	(void) x;
	(void) y;
	if (button == 1)
		meta->click_state = 1;
	return (0);
}

int	mouse_released(int button, int x, int y, t_meta *meta)
{
	(void) x;
	(void) y;
	if (button == 1)
		meta->click_state = 0;
	return (0);
}