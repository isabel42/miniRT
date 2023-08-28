/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:43:02 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:44:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_scena_init(t_scenario **scena_first)
{
	t_scenario	*scena;

	scena = malloc(sizeof(t_scenario));
	if (!scena)
		return ;
	scena->amb_lux = NULL;
	scena->cam = NULL;
	scena->spot_lux = NULL;
	*scena_first = scena;
}

void	ft_abm_lux(char **split, t_scenario *scena)
{
	if (scena->amb_lux || !split || !split[2] || split[3])
		ft_exit();
	scena->amb_lux = malloc(sizeof(t_amblux));
	if (!scena->amb_lux)
		return ;
	scena->amb_lux->ratio = ft_get_float(split[1]);
	scena->amb_lux->rgb = ft_rgb(split[2]);
	ft_free_cc(split);
}

void	ft_cam(char **split, t_scenario *scena)
{
	if (scena->cam || !split || !split[3] || split[4])
		ft_exit();
	scena->cam = malloc(sizeof(t_cam));
	if (!scena->cam)
		return ;
	scena->cam->pos = ft_pos(split[1]);
	scena->cam->dir = ft_pos(split[2]);
	scena->cam->fov = ft_atoi(split[3]);
	ft_free_cc(split);
}

void	ft_spot_lux(char **split, t_scenario *scena)
{
	if (scena->spot_lux || !split || !split[3] || split[4])
		ft_exit();
	scena->spot_lux = malloc(sizeof(t_spotlux));
	if (!scena->spot_lux)
		return ;
	scena->spot_lux->pos = ft_pos(split[1]);
	scena->spot_lux->ratio = ft_get_float(split[2]);
	scena->spot_lux->rgb = ft_rgb(split[3]);
	ft_free_cc(split);
}
