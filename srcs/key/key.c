/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:17:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/31 14:20:47 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_w(t_scenario *scena)
{
	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
	mlx_destroy_window(scena->view->mlx->ptr, scena->view->mlx->win);
	free_scenario(scena);
	exit (0);
	// return (0);
}

int	close_esc(t_scenario *scena)
{
	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
	mlx_destroy_window(scena->view->mlx->ptr, scena->view->mlx->win);
	free_scenario(scena);
	exit (0);
	// return (0);
}

int	key_press(int key, t_scenario *scena)
{
	if (key == KEY_ESC)
		close_esc(scena);
	return (0);
}
