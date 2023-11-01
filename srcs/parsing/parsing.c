/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/11/01 15:06:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mlx	*mlx_init_struct(int win_size_x, int win_size_y, char *name)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!new)
		return (NULL);
	new->ptr = mlx_init();
	new->win = mlx_new_window(new->ptr, win_size_x, win_size_y, name);
	return (new);
}

void	parse_line(char *line_b, t_scenario *scena)
{	
	char	**split;
	char	*line;

	line = ft_strtrim(line_b, "\n");
	split = ft_split(line, ' ');
	free(line);
	if (!ft_strncmp(split[0], "A", 3))
		new_abm_lux(split, scena);
	else if (!ft_strncmp(split[0], "C", 3))
		new_cam(split, scena);
	else if (!ft_strncmp(split[0], "L", 3))
		new_spot_lux(split, scena);
	else if (!ft_strncmp(split[0], "sp", 4))
		new_sphere(split, scena);
	else if (!ft_strncmp(split[0], "pl", 4))
		new_plan(split, scena);
	else if (!ft_strncmp(split[0], "cy", 4))
		new_cylinder(split, scena);
	else if (!ft_strncmp(split[0], "#", 1))
		free_array(split);
	else
		ft_exit("Parsing object identification");
}

void	assign_texture_to_object(t_scenario *scena)
{
	t_obj	*tmp;

	tmp = scena->obj;
	while (tmp)
	{
		if (tmp->id == sp || tmp->id == pl)
		{
			tmp->texture = scena->view->texture;
		}
		tmp = tmp->next;
	}
}

t_scenario	*parsing(char *argv1)
{
	int			fd;
	char		*line;
	t_scenario	*scena;

	fd = open(argv1, O_RDONLY);
	ft_exit_fd(fd);
	line = get_next_line(fd);
	if (!line || line == NULL)
		ft_exit("Parsing: File content");
	scena = init_scenario();
	while (line != NULL)
	{
		if (line[0] != '\n')
			parse_line(line, scena);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (!scena->cam || !scena->amb_lux || !scena->spot_lux)
		ft_exit("No camera or light source");
	scena->view = init_view(scena);
	assign_texture_to_object(scena);
	return (scena);
}
