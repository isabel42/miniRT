/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/06 19:04:26 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

// int	close_w(int keycode, t_mlx *vars)
// {
// 	if (keycode == 53)
// 		mlx_destroy_window(vars->ptr, vars->win);
// 	exit(0);
// 	return (0);
// }
int	close_w(t_scenario *scena)
{
	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
	//free_lists(meta);
	printf("     CLOSING FROM CLICK !\n");
	exit (0);
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	t_scenario	*scena;
	// t_vars		vars;
	// t_data_img	img;

	ft_check_argc(argc);
	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	// img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);
	scena = parsing(argv[1]);
	print_parsing(scena);
	test_print_meta(scena->meta);
	print_q_cache(*scena->meta->cache);
	apply_rotation(scena);
	render(scena);
	mlx_hook(scena->mlx->win, 2, 2, key_press, scena->meta);
	mlx_hook(scena->mlx->win, 3, 3, key_release, scena->meta);
	mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	mlx_hook(scena->mlx->win, 6, 1L << 6, mouse_move, scena->meta);
	mlx_hook(scena->mlx->win, 4, 1L << 2, mouse_pressed, scena->meta);
	mlx_hook(scena->mlx->win, 5, 1L << 3, mouse_released, scena->meta);
	mlx_loop(scena->mlx->ptr);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// mlx_hook(vars.win, 17, 0, close_w, &vars);
	// mlx_hook(vars.win, 2, 0, close_w, &vars);
	// mlx_loop(vars.mlx);
	// free(img.img);
	return (0);
}
