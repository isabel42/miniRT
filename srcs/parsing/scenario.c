/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   	                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:43:02 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:44:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	spot_add_back(t_scenario *scena, t_spotlux *spot)
{
	t_spotlux	*list;

	list = scena->spot_lux;
	if (!list)
		scena->spot_lux = spot;
	else
	{
		while (list->next)
			list = list->next;
		list->next = spot;
	}
}

t_scenario	*init_scenario(void)
{
	t_scenario	*scena;

	scena = malloc(sizeof (t_scenario));
	if (!scena)
		ft_exit("Malloc");
	scena->amb_lux = NULL;
	scena->cam = NULL;
	scena->spot_lux = NULL;
	scena->obj = NULL;
	scena->mlx = mlx_init_struct(WIDTH, HEIGHT, "MiniRT");
	scena->img_data = malloc(sizeof(t_data_img));
	if (!scena->img_data)
		ft_exit("Malloc");
	scena->img_data->img = mlx_new_image(scena->mlx->ptr, WIDTH, HEIGHT);
	scena->img_data->addr = mlx_get_data_addr(scena->img_data->img,
			&scena->img_data->bits_per_pixel,
			&scena->img_data->line_length, &scena->img_data->endian);
	return (scena);
}

void	new_abm_lux(char **split, t_scenario *scena)
{
	if (scena->amb_lux || !split || !split[2] || split[3])
		ft_exit("Ambiant ligh syntax");
	scena->amb_lux = malloc(sizeof(t_amblux));
	if (!scena->amb_lux)
		ft_exit("Malloc");
	scena->amb_lux->ratio = get_ratio(split[1], 0, 1);
	scena->amb_lux->rgb = ft_rgb(split[2]);
	free_array(split);
}

void	new_cam(char **split, t_scenario *scena)
{
	if (scena->cam || !split || !split[3] || split[4])
		ft_exit("Camera syntax");
	scena->cam = malloc(sizeof(t_cam));
	if (!scena->cam)
		ft_exit("Malloc");
	scena->cam->pos = ft_pos(split[1]);
	scena->cam->vdir = get_orientation(split[2], -2.0, 2);
	// scena->cam->dir = quat_normalize(o_vector_to_quat(ft_pos(split[2])));
	scena->cam->dir = euler_to_quat(scena->cam->vdir.z * M_PI, -scena->cam->vdir.y * M_PI, -scena->cam->vdir.x * M_PI);
	// scena->cam->dir = euler_to_quat(scena->cam->vdir.z * M_PI, 0, 0);
	// scena->cam->dir = o_vector_to_quat(ft_pos(split[2]));
	// scena->cam->dir = quat_multiply(scena->cam->dir, scena->cam->dir);
	// scena->cam->dir.y *= -1;
	scena->cam->fov = ft_atoi(split[3]);
	scena->cam->dist = 100;
	free_array(split);
}

void	new_spot_lux(char **split, t_scenario *scena)
{
	t_spotlux	*spot;

	if (!split || !split[3] || split[4])
		ft_exit("Spot light syntax");
	spot = malloc(sizeof(t_spotlux));
	if (!spot)
		ft_exit("Malloc");
	spot->pos = ft_pos(split[1]);
	spot->ratio = get_ratio(split[2], 0, 1);
	spot->rgb = ft_rgb(split[3]);
	spot->next = NULL;
	spot->axis = init_axis(spot->pos, 30);
	free_array(split);
	spot_add_back(scena, spot);
}
