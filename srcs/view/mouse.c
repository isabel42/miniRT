/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:40:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/24 18:41:22 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mouse_scroll(int key, t_scenario *scena)
{
	if (key == KEY_SCROLL_UP && scena->view->ratio < 2)
		scena->view->ratio *= 1.1;
	if (key == KEY_SCROLL_DOWN && scena->view->ratio > 0.1)
		scena->view->ratio *=0.9;
	render_view(scena);
}

void	mouse_rotate(int move_x, int move_y, t_scenario *scena)
{
	scena->view->rotation_quat = euler_to_quat(0,
			ft_deg_to_rad(atan(move_x / 1)) * 2,
			-ft_deg_to_rad(atan(move_y / 1)) * 2);
	scena->view->identity_quat = quat_multiply(scena->view->identity_quat, scena->view->rotation_quat);
	scena->cam->dir = scena->view->identity_quat;
	apply_rotation_o_cam(scena);
	return ;
}

void	mouse_rotate_scena(int move_x, int move_y, t_scenario *scena)
{
	scena->view->scena_quat = euler_to_quat(0,
			ft_deg_to_rad(atan(move_x / 1)) * 2,
			-ft_deg_to_rad(atan(move_y / 1)) * 2);
	apply_rotation_scena(scena);
	return ;
}

int	mouse_move(int x, int y, t_scenario *scena)
{
	static int	previous_x = 0;
	static int	previous_y = 0;
	int			move_x;
	int			move_y;

	move_x = x - previous_x;
	move_y = y - previous_y;
	if ((abs(move_x) || abs(move_y)) && (scena->view->click_state)
		&& (((x < WIDTH) && (x > 0)) && ((y < HEIGHT) && (y > 0))))
	{
		if (scena->view->s_state == 1)
			mouse_rotate_scena(move_x, move_y, scena);
		else if (scena->view->c_state == 1)
			mouse_rotate(move_x, move_y, scena);
		render_view(scena);
	}
	previous_x = x;
	previous_y = y;
	return (0);
}