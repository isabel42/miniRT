/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/15 17:06:58 by lsohler          ###   ########.fr       */
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
	mlx_hook(scena->mlx->win, 2, 2, key_press, scena);
	mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	mlx_loop(scena->mlx->ptr);
	return (0);
}
