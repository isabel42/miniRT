/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenariobox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:58:57 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 16:34:11 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat	*init_box(void)
{
	t_quat	*box;
	int half_size;

	box = malloc(sizeof(t_quat) * 8);
	if (!box)
		ft_exit("Malloc");
	// box[0] = quat_create(0, 0, 0, 0);
	// box[1] = quat_create(0, 0, 0, 500);
	// box[2] = quat_create(0, 500, 0, 500);
	// box[3] = quat_create(0, 500, 0, 0);
	// box[4] = quat_create(0, 0, 500, 0);
	// box[5] = quat_create(0, 0, 500, 500);
	// box[6] = quat_create(0, 500, 500, 500);
	// box[7] = quat_create(0, 500, 500, 0);
	half_size = 250;
	box[0] = quat_create(0, -half_size, -half_size, -half_size);
	box[1] = quat_create(0, -half_size, -half_size, half_size);
	box[2] = quat_create(0, -half_size, half_size, half_size);
	box[3] = quat_create(0, -half_size, half_size, -half_size);
	box[4] = quat_create(0, half_size, -half_size, -half_size);
	box[5] = quat_create(0, half_size, -half_size, half_size);
	box[6] = quat_create(0, half_size, half_size, half_size);
	box[7] = quat_create(0, half_size, half_size, -half_size);
	return (box);
}

t_quat	*apply_rotation_axis(t_scenario *scena, t_quat *c)
{
	c[0] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[0]),
			quat_conjugate(scena->rotation_quat));
	c[1] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[1]),
			quat_conjugate(scena->rotation_quat));
	c[2] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[2]),
			quat_conjugate(scena->rotation_quat));
	c[3] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[3]),
			quat_conjugate(scena->rotation_quat));
	return (c);
}

t_quat	*apply_rotation_box(t_scenario *scena, t_quat *c)
{
	c[0] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[0]),
			quat_conjugate(scena->rotation_quat));
	c[1] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[1]),
			quat_conjugate(scena->rotation_quat));
	c[2] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[2]),
			quat_conjugate(scena->rotation_quat));
	c[3] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[3]),
			quat_conjugate(scena->rotation_quat));
	c[4] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[4]),
			quat_conjugate(scena->rotation_quat));
	c[5] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[5]),
			quat_conjugate(scena->rotation_quat));
	c[6] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[6]),
			quat_conjugate(scena->rotation_quat));
	c[7] = quat_multiply(
			quat_multiply(scena->rotation_quat, c[7]),
			quat_conjugate(scena->rotation_quat));
	return (c);
}

void	apply_rotation_scenario(t_scenario *scena)
{
	t_obj	*objects;

	objects = scena->obj;
	scena->box = apply_rotation_box(scena, scena->box);
	scena->axis = apply_rotation_axis(scena, scena->axis);
	while (objects)
	{
		if (objects->id == pl && objects->cube)
			objects->cube = apply_rotation_axis(scena, objects->cube);
		if (objects->id == cy && objects->cube)
			objects->cube = apply_rotation_axis(scena, objects->cube);
		if (objects->id == sp && objects->cube)
			objects->cube = apply_rotation_axis(scena, objects->cube);
		objects = objects->next;
	}
}


t_point	get_point_b(t_quat q, t_scenario *scena)
{
	t_point	res;

	res.x = q.x + scena->meta->box_offset[0];
	res.y = q.y + scena->meta->box_offset[1];
	return (res);
}

void	draw_axis(t_quat *c, t_scenario *scena)
{
	bresenham_draw_line(get_point_b(c[0], scena), get_point_b(c[1], scena), scena, int_to_rgb(I_RED));
	bresenham_draw_line(get_point_b(c[0], scena), get_point_b(c[2], scena), scena, int_to_rgb(I_GREEN));
	bresenham_draw_line(get_point_b(c[0], scena), get_point_b(c[3], scena), scena, int_to_rgb(I_BLUE));
}

void	draw_box(t_quat *c, t_scenario *scena, t_rgb color)
{
	// (void)c;
	// (void)scena;
	// (void)color;
	bresenham_draw_line(get_point_b(c[0], scena), get_point_b(c[1], scena), scena, color);
	bresenham_draw_line(get_point_b(c[1], scena), get_point_b(c[2], scena), scena, color);
	bresenham_draw_line(get_point_b(c[2], scena), get_point_b(c[3], scena), scena, color);
	bresenham_draw_line(get_point_b(c[3], scena), get_point_b(c[0], scena), scena, color);
	bresenham_draw_line(get_point_b(c[4], scena), get_point_b(c[5], scena), scena, color);
	bresenham_draw_line(get_point_b(c[5], scena), get_point_b(c[6], scena), scena, color);
	bresenham_draw_line(get_point_b(c[6], scena), get_point_b(c[7], scena), scena, color);
	bresenham_draw_line(get_point_b(c[7], scena), get_point_b(c[4], scena), scena, color);
	bresenham_draw_line(get_point_b(c[0], scena), get_point_b(c[4], scena), scena, color);
	bresenham_draw_line(get_point_b(c[1], scena), get_point_b(c[5], scena), scena, color);
	bresenham_draw_line(get_point_b(c[2], scena), get_point_b(c[6], scena), scena, color);
	bresenham_draw_line(get_point_b(c[3], scena), get_point_b(c[7], scena), scena, color);
}

void	draw_objects(t_scenario *scena)
{
	t_obj	*objects;

	objects = scena->obj;
	while (objects)
	{
		if (objects->id == pl && objects->cube)
			draw_axis(objects->cube, scena);
		if (objects->id == cy && objects->cube)
			draw_axis(objects->cube, scena);
		if (objects->id == sp && objects->cube)
		{
			draw_axis(objects->cube, scena);
			draw_circle(scena->img_data, objects->cube->x + scena->meta->offset[0], objects->cube->y + scena->meta->offset[1], objects->diam / 2, I_DEEPBLUE);
		}
		objects = objects->next;
	}
}

void	draw_scenario(t_scenario *scena)
{
	draw_box(scena->box, scena, int_to_rgb(I_WHITE));
	draw_axis(scena->axis, scena);
	draw_objects(scena);
}