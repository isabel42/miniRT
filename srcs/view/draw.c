/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:29:04 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:32:20 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_light(t_quat *c, t_scenario *sc)
{
	bresenham_draw_line(get_p(c[0], sc), get_p(c[1], sc), sc,
		int_to_rgb(I_YELLOW));
	bresenham_draw_line(get_p(c[0], sc), get_p(c[2], sc), sc,
		int_to_rgb(I_YELLOW));
	bresenham_draw_line(get_p(c[0], sc), get_p(c[3], sc), sc,
		int_to_rgb(I_YELLOW));
}

void	draw_axis(t_quat *c, t_scenario *sc)
{
	bresenham_draw_line(get_p(c[0], sc), get_p(c[1], sc), sc,
		int_to_rgb(I_RED));
	bresenham_draw_line(get_p(c[0], sc), get_p(c[2], sc), sc,
		int_to_rgb(I_GREEN));
	bresenham_draw_line(get_p(c[0], sc), get_p(c[3], sc), sc,
		int_to_rgb(I_BLUE));
}

void	draw_box(t_quat *c, t_scenario *sc, t_rgb color)
{
	bresenham_draw_line(get_p(c[0], sc), get_p(c[1], sc), sc, color);
	bresenham_draw_line(get_p(c[1], sc), get_p(c[2], sc), sc, color);
	bresenham_draw_line(get_p(c[2], sc), get_p(c[3], sc), sc, color);
	bresenham_draw_line(get_p(c[3], sc), get_p(c[0], sc), sc, color);
	bresenham_draw_line(get_p(c[4], sc), get_p(c[5], sc), sc, color);
	bresenham_draw_line(get_p(c[5], sc), get_p(c[6], sc), sc, color);
	bresenham_draw_line(get_p(c[6], sc), get_p(c[7], sc), sc, color);
	bresenham_draw_line(get_p(c[7], sc), get_p(c[4], sc), sc, color);
	bresenham_draw_line(get_p(c[0], sc), get_p(c[4], sc), sc, color);
	bresenham_draw_line(get_p(c[1], sc), get_p(c[5], sc), sc, color);
	bresenham_draw_line(get_p(c[2], sc), get_p(c[6], sc), sc, color);
	bresenham_draw_line(get_p(c[3], sc), get_p(c[7], sc), sc, color);
}

void	draw_camera(t_quat *c, t_scenario *sc, t_rgb color)
{
	bresenham_draw_line(get_p(c[0], sc), get_p(c[1], sc), sc, color);
	bresenham_draw_line(get_p(c[1], sc), get_p(c[2], sc), sc, color);
	bresenham_draw_line(get_p(c[2], sc), get_p(c[3], sc), sc, color);
	bresenham_draw_line(get_p(c[3], sc), get_p(c[0], sc), sc, color);
	bresenham_draw_line(get_p(c[4], sc), get_p(c[0], sc), sc, color);
	bresenham_draw_line(get_p(c[4], sc), get_p(c[1], sc), sc, color);
	bresenham_draw_line(get_p(c[4], sc), get_p(c[2], sc), sc, color);
	bresenham_draw_line(get_p(c[4], sc), get_p(c[3], sc), sc, color);
}

void	draw_scenario(t_scenario *sc)
{
	t_obj		*obj;
	t_spotlux	*lux;

	draw_box(sc->view->box, sc, int_to_rgb(I_WHITE));
	draw_camera(sc->view->camera, sc, int_to_rgb(I_WHITE));
	obj = sc->obj;
	while (obj)
	{
		draw_axis(obj->axis, sc);
		obj = obj->next;
	}
	lux = sc->spot_lux;
	while (lux)
	{
		draw_light(lux->axis, sc);
		lux = lux->next;
	}
}
