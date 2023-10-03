/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/03 16:47:05 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	else
		ft_exit("Parsing object identification");
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
	return (scena);
}

/*
float	ft_mod(t_vec3d a)
{
	float	mod;

	mod = sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2));
	return (mod);
}

float	ft_sin(float *a, float *b)
{
	float	sin;
	float	*mult;
	float	sign;

	if (ft_mod(a) == 0 || ft_mod(b) == 0)
		return (0.0);
	mult = malloc(sizeof (float) * 3);
	if (!mult)
		return (0);
	mult[0] = a[1] * b[2] - a[2] * b[1];
	mult[1] = a[2] * b[0] - a[0] * b[2];
	mult[2] = a[0] * b[1] - a[1] * b[0];
	if ((mult[0] > 0.0 && b[0] == 0.0) || (mult[1] < 0.0 && b[1] == 0.0))
		sign = -1.0;
	else
		sign = 1.0;
	sin = sign * ft_mod(mult) / (ft_mod(a) * ft_mod (b));
	free (mult);
	return (sin);
}

float	ft_cos(float *a, float *b)
{
	float	cos;
	float	mult;

	if (ft_mod(b) == 0)
		return (1.0);
	mult = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	cos = mult / (ft_mod(a) * ft_mod (b));
	return (cos);
}

float	*ft_vector(float a, float b, float c)
{
	float	*vector;

	vector = malloc(sizeof(float *) * 3);
	if (!vector)
		return (NULL);
	vector[0] = a;
	vector[1] = b;
	vector[2] = c;
	return (vector);
}

void ft_rotation_x(float *dir, float *a)
{
	float	*dir_x;
	float	*cp_a;
	float	*vector;
	float	sin;
	float	cos;

	dir_x = ft_vector(0.0, dir[1], dir[2]);
	vector = ft_vector(0.0, 0.0, 1.0);
	cp_a = ft_vector(a[0], a[1], a[2]);
	sin = ft_sin(vector, dir_x);
	cos = ft_cos(vector, dir_x);
	a[0] = cp_a[0];
	a[1] = cp_a[1] * cos - cp_a[2] * sin;
	a[2] = cp_a[1] * sin + cp_a[2] * cos;
	free(dir_x);
	free(vector);
	free(cp_a);
}

void ft_rotation_y(float *dir, float *a)
{
	float	*dir_y;
	float	*cp_a;
	float	*vector;
	float	sin;
	float	cos;

	dir_y = ft_vector(dir[0], 0.0, dir[2]);
	vector = ft_vector(0.0, 0.0, 1.0);
	cp_a = ft_vector(a[0], a[1], a[2]);
	sin = ft_sin(dir_y, vector);
	cos = ft_cos(dir_y, vector);
	a[0] = cp_a[0] * cos + cp_a[2] * sin;
	a[1] = cp_a[1];
	a[2] = -cp_a[0] * sin + cp_a[2] * cos;
	free(dir_y);
	free(vector);
	free(cp_a);
}

void	ft_cam_rot(t_list **obj, t_scenario *scena)
{
	t_list	*obj_single;
	t_obj	*content;

	if (ft_mod(scena->cam->dir) == 0)
		ft_exit("Module = 0");
	obj_single = *obj;
	while (obj_single)
	{
		content = (t_obj *)obj_single->content;
		ft_rotation_x(scena->cam->dir, content->pos);
		if (content->dir)
			ft_rotation_x(scena->cam->dir, content->dir);
		obj_single = obj_single->next;
	}
	ft_rotation_x(scena->cam->dir, scena->spot_lux->pos);
	ft_rotation_x(scena->cam->dir, scena->cam->dir);
	obj_single = *obj;
	while (obj_single)
	{
		content = (t_obj *)obj_single->content;
		ft_rotation_y(scena->cam->dir, content->pos);
		if (content->dir)
			ft_rotation_y(scena->cam->dir, content->dir);
		obj_single = obj_single->next;
	}	
	ft_rotation_y(scena->cam->dir, scena->spot_lux->pos);
	ft_rotation_y(scena->cam->dir, scena->cam->dir);
}

void	ft_cam_shift(t_list **obj, t_scenario *scena)
{
	t_list	*obj_single;
	t_obj	*content;
	int		i;

	obj_single = *obj;
	while (obj_single)
	{
		content = (t_obj *)obj_single->content;
		i = 0;
		while (i < 3)
		{
			content->pos[i] = content->pos[i] - scena->cam->pos[i];
			i++;
		}
		obj_single = obj_single->next;
	}
	i = 0;
	while (i < 3)
	{
		scena->spot_lux->pos[i] = scena->spot_lux->pos[i] - scena->cam->pos[i];
		i++;
	}
}
*/

 =0