/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:39:23 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/06 18:43:53 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation(t_scenario *scena)
{
	t_quat	*c;

	c = scena->cam->c;
	// scena->cam->dir = quat_multiply(quat_multiply(scena->meta->rotation_quat, scena->cam->dir), quat_conjugate(scena->meta->rotation_quat));
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
	// printf("Moving mouse x:%i y:%i\n", move_x, move_y);
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
	// printf("Meta->scena->cam: ");
	// print_q(meta->scena->cam->dir);
	apply_rotation(meta->scena);
	return ;
}

void	mouse_rotate_box(int move_x, int move_y, t_meta *meta)
{
	// printf("BOX Moving mouse x:%i y:%i\n", move_x, move_y);
	meta->scena->rotation_quat = euler_to_quat(0,
			ft_deg_to_rad(atan(move_x / 1)) * 2,
			-ft_deg_to_rad(atan(move_y / 1)) * 2);
	apply_rotation_scenario(meta->scena);
	return ;
}

int	mouse_move(int x, int y, t_meta *meta)
{
	static int	previous_x = 0;
	static int	previous_y = 0;
	int			move_x;
	int			move_y;

	move_x = x - previous_x;
	move_y = y - previous_y;
	if ((abs(move_x) || abs(move_y)) && (meta->click_state)
		&& (((x < WIDTH) && (x > 0)) && ((y < HEIGHT) && (y > 0))))
	{
		if (meta->shift_state == 1)
		{
			mouse_rotate(move_x, move_y, meta);
			mouse_rotate_box(move_x, move_y, meta);
		}
		else if (meta->ctrl_state == 1)
		{
			meta->offset[0] += move_x;
			meta->offset[1] += move_y;
			meta->box_offset[0] += move_x;
			meta->box_offset[1] += move_y;
		}
		else if (meta->c_state == 1)
			// mouse_rotate_box(move_x, move_y, meta);
		{
			free(meta->scena->cam->c);
			camera_param(meta->scena->cam);
			meta->scena->cam->pos.x += move_x;
			meta->scena->cam->pos.y += move_y;
			// apply_rotation(meta->scena);
		}
		else if (meta->b_state == 1)
		{
			meta->box_offset[0] += move_x;
			meta->box_offset[1] += move_y;
		}
		render(meta->scena);
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