/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:26:18 by itovar-n         ###   ########.fr       */
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

void	ft_free_scena(t_scenario *scena)
{
	if (!scena)
		return ;
	if (scena->amb_lux)
	{
		free(scena->amb_lux->rgb);
		free(scena->amb_lux);
	}
	if (scena->cam)
	{
		free(scena->cam->pos);
		free(scena->cam->dir);
		free(scena->cam);
	}
	if (scena->spot_lux)
	{
		free(scena->spot_lux->pos);
		free(scena->spot_lux->rgb);
		free(scena->spot_lux);
	}
	free(scena);
}

void	ft_free_obj(t_list *obj)
{
	t_obj	*content;
	t_list	*next;

	if (!obj)
		return ;
	while (obj)
	{
		content = (t_obj *) (obj->content);
		next = obj->next;
		if (content->pos)
			free(content->pos);
		if (content->rgb)
			free(content->rgb);
		if (content->dir)
			free(content->dir);
		free(content);
		free(obj);
		obj = next;
	}
}

void	ft_image( t_data_img img, char *argv1)
{
	// int			i;
	t_scenario	*scena;
	t_list		*obj;

	scena = NULL;
	ft_scena_init(&scena);
	ft_parsing(argv1, &obj, scena);
	ft_free_obj(obj);
	ft_free_scena(scena);
	printf("address img: %p\n", &img);
	printf("argv1: %s\n", argv1);
	printf("OK!!\n");
	// i = 0;
	// while (i < 100)
	// {
	// 	my_mlx_pixel_put(&img, i, i, 0x0000FFFF);
	// 	i++;
	// }
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;


	ft_check_argc(argc);
	// ft_parsing(argv[1]);
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
