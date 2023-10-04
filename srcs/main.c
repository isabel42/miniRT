/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/04 16:45:37 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	close_w(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset + (data->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		exit (0);
	}
}

void check_cy(t_scenario *sc)
{
	t_obj *test;
	int i;
	t_vec3d p1;
	t_vec3d p2;
	
	test = sc->obj;
	i = 0;
	while (test && test->id != 2)
	{
		test = test->next;
		i++;
	}
	printf("i: %d\n", i);
	p1.x = 0.0;
	p1.y = 0.0;
	p1.z = 0.0;
	p2.x = 10.0;
	p2.y = 0.0;
	p2.z = 0.0;

	if (i>0)
		printf("WORKED!! \n");
	else
		printf("FAIL \n");


}

void	ft_image(t_data_img img, char *argv1)
{
	t_scenario	*sc;

	sc = parsing(argv1);
	check_cy(sc);
	// print_parsing(sc);
	free_scenario(sc);
	printf("address img: %p\n", &img);
	printf("\n\nOK!!\n");
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;

	ft_check_argc(argc);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "miniRT");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	ft_image(img, argv[1]);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
	free(img.img);
	return (0);
}
