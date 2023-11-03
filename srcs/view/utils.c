/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:21:02 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:32:27 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_p(t_quat q, t_scenario *sc)
{
	t_point	res;

	res.x = (q.x * sc->view->ratio) + sc->view->box_offset_x;
	res.y = (q.y * sc->view->ratio) + sc->view->box_offset_y;
	return (res);
}

void	render_view(t_scenario *sc)
{
	mlx_clear_window(sc->view->mlx->ptr, sc->view->mlx->win);
	draw_scenario(sc);
	mlx_put_image_to_window(sc->view->mlx->ptr,
		sc->view->mlx->win, sc->view->img_data->img, 0, 0);
	mlx_destroy_image(sc->view->mlx->ptr, sc->view->img_data->img);
	my_new_mlx_img_data_view(sc);
}
