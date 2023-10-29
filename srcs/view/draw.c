/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:29:04 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 17:34:50 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_point(t_quat q, t_scenario *scena)
{
	t_point	res;

	res.x = (q.x * scena->view->ratio) + scena->view->box_offset_x;
	res.y = (q.y * scena->view->ratio) + scena->view->box_offset_y;
	return (res);
}
void	draw_light(t_quat *c, t_scenario *scena)
{
	bresenham_draw_line(get_point(c[0], scena), get_point(c[1], scena), scena, int_to_rgb(I_YELLOW));
	bresenham_draw_line(get_point(c[0], scena), get_point(c[2], scena), scena, int_to_rgb(I_YELLOW));
	bresenham_draw_line(get_point(c[0], scena), get_point(c[3], scena), scena, int_to_rgb(I_YELLOW));
}

void	draw_axis(t_quat *c, t_scenario *scena)
{
	bresenham_draw_line(get_point(c[0], scena), get_point(c[1], scena), scena, int_to_rgb(I_RED));
	bresenham_draw_line(get_point(c[0], scena), get_point(c[2], scena), scena, int_to_rgb(I_GREEN));
	bresenham_draw_line(get_point(c[0], scena), get_point(c[3], scena), scena, int_to_rgb(I_BLUE));
}

void	draw_box(t_quat *c, t_scenario *scena, t_rgb color)
{
	bresenham_draw_line(get_point(c[0], scena), get_point(c[1], scena), scena, color);
	bresenham_draw_line(get_point(c[1], scena), get_point(c[2], scena), scena, color);
	bresenham_draw_line(get_point(c[2], scena), get_point(c[3], scena), scena, color);
	bresenham_draw_line(get_point(c[3], scena), get_point(c[0], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[5], scena), scena, color);
	bresenham_draw_line(get_point(c[5], scena), get_point(c[6], scena), scena, color);
	bresenham_draw_line(get_point(c[6], scena), get_point(c[7], scena), scena, color);
	bresenham_draw_line(get_point(c[7], scena), get_point(c[4], scena), scena, color);
	bresenham_draw_line(get_point(c[0], scena), get_point(c[4], scena), scena, color);
	bresenham_draw_line(get_point(c[1], scena), get_point(c[5], scena), scena, color);
	bresenham_draw_line(get_point(c[2], scena), get_point(c[6], scena), scena, color);
	bresenham_draw_line(get_point(c[3], scena), get_point(c[7], scena), scena, color);
}

void	draw_camera(t_quat *c, t_scenario *scena, t_rgb color)
{
	bresenham_draw_line(get_point(c[0], scena), get_point(c[1], scena), scena, color);
	bresenham_draw_line(get_point(c[1], scena), get_point(c[2], scena), scena, color);
	bresenham_draw_line(get_point(c[2], scena), get_point(c[3], scena), scena, color);
	bresenham_draw_line(get_point(c[3], scena), get_point(c[0], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[0], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[1], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[2], scena), scena, color);
	bresenham_draw_line(get_point(c[4], scena), get_point(c[3], scena), scena, color);
}

void	draw_scenario(t_scenario *scena)
{
	t_obj		*obj;
	t_spotlux	*lux;

	draw_box(scena->view->box, scena, int_to_rgb(I_WHITE));
	draw_camera(scena->view->camera, scena, int_to_rgb(I_WHITE));
	obj = scena->obj;
	while (obj)
	{
		draw_axis(obj->axis, scena);
		obj = obj->next;
	}
	lux = scena->spot_lux;
	while (lux)
	{
		draw_light(lux->axis, scena);
		lux = lux->next;
	}
}

void	render_view(t_scenario *scena)
{
	mlx_clear_window(scena->view->mlx->ptr, scena->view->mlx->win);
	draw_scenario(scena);
	mlx_put_image_to_window(scena->view->mlx->ptr,
		scena->view->mlx->win, scena->view->img_data->img, 0, 0);
	mlx_destroy_image(scena->view->mlx->ptr, scena->view->img_data->img);
	my_new_mlx_img_data_view(scena);
}