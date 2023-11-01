/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:32:59 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 10:09:25 by lsohler          ###   ########.fr       */
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
	return (0);
}

int	key_press_view(int key, t_scenario *scena)
{
	if (key == KEY_SHIFT && scena->view->s_state != 1)
		scena->view->s_state = 1;
	if (key == KEY_CTRL && scena->view->c_state != 1)
		scena->view->c_state = 1;
	if (key == KEY_ALT && scena->view->a_state != 1)
		scena->view->a_state = 1;
	if (key == KEY_CMD && scena->view->cmd_state != 1)
		scena->view->cmd_state = 1;
	if (key == KEY_ENTER)
	{
		render(scena);
		mlx_do_sync(scena->mlx->ptr);
	}
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
	return (0);
}

int	mouse_released(int key, int x, int y, t_scenario *scena)
{
	(void) x;
	(void) y;
	if (key == 1)
		scena->view->click_state = 0;
	return (0);
}
