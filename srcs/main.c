/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/11/06 08:06:08 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scenario	*scena;

	if (argc != 2)
		ft_exit("Usage: ./minirt <file.rt>");
	scena = parsing(argv[1]);
	render(scena);
	printf("helloooo\n");
	// apply_rotation_scena(scena);
	// render_view(scena);
	// mlx_hook(scena->mlx->win, 2, 2, key_press, scena);
	// mlx_hook(scena->view->mlx->win, 2, 2, key_press_view, scena);
	// mlx_hook(scena->view->mlx->win, 3, 3, key_release_view, scena);
	// mlx_hook(scena->view->mlx->win, 6, 1L << 6, mouse_move, scena);
	// mlx_hook(scena->view->mlx->win, 4, 1L << 2, mouse_pressed, scena);
	// mlx_hook(scena->view->mlx->win, 5, 1L << 3, mouse_released, scena);
	// mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	// mlx_do_sync(scena->mlx->ptr);
	mlx_loop(scena->view->mlx->ptr);
	return (0);
}
