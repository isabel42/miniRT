/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:26:05 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 17:05:22 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_esc(t_scenario *scena)
{
	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
	//free_lists(meta);
	printf("     CLOSING FROM ESCAPE !\n");
	exit (0);
}

int	numpad_press(int key, t_meta *meta)
{
	if (key == KEY_N8)
		meta->scena->cam->vdir.x = -0.05;
	else if (key == KEY_N2)
		meta->scena->cam->vdir.x = 0.05;
	else if (key == KEY_N4)
		meta->scena->cam->vdir.y = 0.05;
	else if (key == KEY_N6)
		meta->scena->cam->vdir.y = -0.05;
	test_print_vecteur(meta->scena->cam->vdir);
	meta->scena->cam->dir = quat_normalize(vector_to_quat(meta->scena->cam->vdir));
	apply_rotation(meta->scena);
	render_camera(meta->scena);
	return (0);
}

int	key_release(int key, t_meta *meta)
{
	if (key == 257 && meta->shift_state == 1)
	{
		meta->shift_state = 0;
		printf("SHIFT RELEASE\n");
	}
	if (key == 256 && meta->ctrl_state == 1)
	{
		meta->ctrl_state = 0;
		printf("CTRL RELEASE\n");
	}
	return (0);
}

int	key_press(int key, t_meta *meta)
{
	printf("Key: %i\n", key);
	if (key == 257 && meta->shift_state != 1)
		meta->shift_state = 1;
	if (key == 256 && meta->ctrl_state != 1)
		meta->ctrl_state = 1;
	else if (key == KEY_ESC)
		close_esc(meta->scena);
	else if (key <= KEY_N8 && key >= KEY_N2)
		numpad_press(key, meta);
	return (0);
}