/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:32:59 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 16:25:48 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_release_view(int key, t_scenario *scena)
{
	if (key == KEY_SHIFT && scena->view->s_state == 1)
		scena->view->s_state = 0;
	if (key == KEY_CTRL && scena->view->c_state == 1)
		scena->view->c_state = 0;
	if (key == KEY_ALT && scena->view->a_state == 1)
		scena->view->a_state = 0;
	if (key == KEY_CMD && scena->view->cmd_state == 1)
		scena->view->cmd_state = 0;
	printf("RELEASE: S:%i C:%i A:%i CMD:%i\n", scena->view->s_state, scena->view->c_state, scena->view->a_state, scena->view->cmd_state);
	return (0);
}

int	key_press_view(int key, t_scenario *scena)
{
	t_quat	quat;
	if (key == KEY_SHIFT && scena->view->s_state != 1)
		scena->view->s_state = 1;
	if (key == KEY_CTRL && scena->view->c_state != 1)
		scena->view->c_state = 1;
	if (key == KEY_ALT && scena->view->a_state != 1)
		scena->view->a_state = 1;
	if (key == KEY_CMD && scena->view->cmd_state != 1)
		scena->view->cmd_state = 1;
	if (key == KEY_RIGHT)
	{
		quat = euler_to_quat(0, 0.1, 0);
		scena->cam->dir = quat_multiply(quat, scena->cam->dir);
		// printf("scena->cam->dir quat: %f %f %f %f", scena->cam->dir.w, scena->cam->dir.x, scena->cam->dir.y, scena->cam->dir.z);
	}
	if (key == KEY_DOWN)
	{
		quat = euler_to_quat(0, 0, 0.1);
		scena->cam->dir = quat_multiply(quat, scena->cam->dir);
	}
	if (key == KEY_ENTER)
	{
		render(scena);
		printf("cam pos: %f %f %f %f\n", scena->view->camera[4].w, scena->view->camera[4].x, scena->view->camera[4].y, scena->view->camera[4].z);
		scena->cam->dir = quat_multiply(quat, euler_to_quat(0, 0, -M_PI));
		mlx_do_sync(scena->mlx->ptr);
	}
	if (key == KEY_I)
	{
		scena->view->rotation_quat = quat_conjugate(scena->view->scena_quat);
		scena->view->scena_quat = quat_create(1, 0, 0, 0);
		printf("TESTETSTETST\n");
		apply_rotation_scena(scena);
		render_view(scena);
	}
	printf("PRESS:   S:%i C:%i A:%i CMD:%i\n", scena->view->s_state, scena->view->c_state, scena->view->a_state, scena->view->cmd_state);
	return (0);
}

int	mouse_pressed(int key, int x, int y, t_scenario *scena)
{
	(void) x;
	(void) y;
	if (key == 1)
		scena->view->click_state = 1;
	else if (key >= KEY_SCROLL_DOWN && key <= KEY_SCROLL_UP_S)
		mouse_scroll(key, scena);
	printf("Click state: %i\n", scena->view->click_state);
	printf("KEY:%i\n", key);
	return (0);
}

int	mouse_released(int key, int x, int y, t_scenario *scena)
{
	(void) x;
	(void) y;
	if (key == 1)
		scena->view->click_state = 0;
	printf("Click state: %i\n", scena->view->click_state);
	return (0);
}

// void	apply_rotation(t_scenario *scena)
// {
// 	t_quat	*c;

// 	c = scena->cam->c;
// 	// scena->cam->dir = quat_multiply(quat_multiply(scena->meta->rotation_quat, scena->cam->dir), quat_conjugate(scena->meta->rotation_quat));
// 	c[0] = quat_multiply(
// 			quat_multiply(scena->cam->dir, c[0]),
// 			quat_conjugate(scena->cam->dir));
// 	c[1] = quat_multiply(
// 			quat_multiply(scena->cam->dir, c[1]),
// 			quat_conjugate(scena->cam->dir));
// 	c[2] = quat_multiply(
// 			quat_multiply(scena->cam->dir, c[2]),
// 			quat_conjugate(scena->cam->dir));
// 	c[3] = quat_multiply(
// 			quat_multiply(scena->cam->dir, c[3]),
// 			quat_conjugate(scena->cam->dir));
// 	c[4] = quat_multiply(
// 			quat_multiply(scena->cam->dir, c[4]),
// 			quat_conjugate(scena->cam->dir));
// 	// c[0] = quat_multiply(scena->cam->dir, c[0]);
// 	// c[1] = quat_multiply(scena->cam->dir, c[1]);
// 	// c[2] = quat_multiply(scena->cam->dir, c[2]);
// 	// c[3] = quat_multiply(scena->cam->dir, c[3]);
// 	// c[4] = quat_multiply(scena->cam->dir, c[4]);
// 	scena->cam->c = c;
// }



