/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/08 22:43:51 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	close_w(int keycode, t_mlx *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->ptr, vars->win);
	exit(0);
	return (0);
}
// int	close_w(t_scenario *scena)
// {
// 	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
// 	//free_lists(meta);
// 	printf("     CLOSING FROM CLICK !\n");
// 	exit (0);
// }

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		exit (0);
	}
}
void check_ob(t_scenario *sc, t_data_img img)
{
	t_obj *test;
	float i;
	float j;
	t_vec3d p1;
	t_vec3d p2;
	int d;
	t_vec3d *sol;
	
	test = sc->obj;
	i = 0;
	while (test)
	{
		if (test->id == 2)
			break ;
		test = test->next;
		i++;
	}
	p1.x = 0.0;
	p1.y = 0.0;
	p1.z = 0.0;
	d = WIDTH / 2;	
	i =  0;
	while (i < WIDTH)
	{
		p2.x = i - WIDTH / 2;
		p2.z = d;
		j = 0;
		while (j < HEIGHT)
		{
			p2.y = j - HEIGHT / 2;
			sol = in_cy_1(p1, p2, test);
			if (sol)
			{
				my_mlx_pixel_put(&img, i, HEIGHT - j, 0xFFFFFF);
			}
			sol = in_cy_2(p1, p2, test);
			if (sol)
			{
				my_mlx_pixel_put(&img, i, HEIGHT - j, 0xFFFFFF);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_scenario	*scena;
	t_mlx		vars;
	t_data_img	img;

	ft_check_argc(argc);
	vars.ptr = mlx_init();
	vars.win = mlx_new_window(vars.ptr, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(vars.ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	scena = parsing(argv[1]);
	check_ob(scena, img);
	// print_parsing(scena);
	// render_camera(scena);
	// mlx_hook(scena->mlx->win, 2, 2, keypress, scena);
	// mlx_hook(scena->mlx->win, 3, 3, shift_released, scena);
	// mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	// mlx_hook(scena->mlx->win, 6, 1L << 6, mouse_move, scena);
	// mlx_hook(scena->mlx->win, 4, 1L << 2, mouse_pressed, scena);
	// mlx_hook(scena->mlx->win, 5, 1L << 3, mouse_released, scena);
	// mlx_loop(scena->mlx->ptr);
	mlx_put_image_to_window(vars.ptr, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.ptr);
	free(img.img);
	return (0);
}
