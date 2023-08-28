/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:35:39 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_exit_fd(int fd)
{
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
}

void	ft_exit(void)
{
	printf("Error\n");
	exit (0);
}

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

void ft_abm_lux(char **split, t_scenario *scena)
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

void ft_cam(char **split, t_scenario *scena)
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

void ft_spot_lux(char **split, t_scenario *scena)
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

t_obj	*ft_obj_init(t_obj *obj)
{
	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->id = 0;
	obj->pos = NULL;
	obj->rgb = NULL;
	obj->dir = NULL;
	obj->diam = 0;
	obj->high = 0;
	return (obj);
}

void	ft_get_ft_pars(char *line_b, t_list **obj, t_scenario *scena)
{	
	char	**split;
	char	*line;

	line = ft_strtrim(line_b, "\n");
	split = ft_split(line,' ');
	free(line);
	if (!ft_strncmp(split[0], "A", 3))
		ft_abm_lux(split, scena);
	else if (!ft_strncmp(split[0], "C", 3))
		ft_cam(split, scena);
	else if (!ft_strncmp(split[0], "L", 3))
		ft_spot_lux(split, scena);	
	else if (!ft_strncmp(split[0], "sp", 4))
		ft_sp(split, obj);
	else if (!ft_strncmp(split[0], "pl", 4))
		ft_pl(split, obj);
	else if (!ft_strncmp(split[0], "cy", 4))
		ft_cy(split, obj);
	else
		ft_exit();
}

void ft_parsing(char *argv1, t_list **obj, t_scenario *scena)
{
	int		fd;
	char	*line;

	fd = open(argv1, O_RDONLY);
	ft_exit_fd(fd);
	line = get_next_line(fd);
	if (!line || line == NULL)
	{
		ft_putstr_fd("Input file is empty!\n", 1);
		exit(0);
	}
	*obj = NULL;
	while (line != NULL)
	{
		if (line[0] != '\n')
			ft_get_ft_pars(line, obj, scena);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}