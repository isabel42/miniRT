/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:19:59 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/31 14:03:22 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_view_quat(t_view *view)
{
	// view->identity_quat = quat_create(1, 0, 0, 0);
	view->identity_quat = quat_create(1, 0, 0, 0);
	view->scena_quat = quat_create(1, 0, 0, 0);
	view->rotation_quat = euler_to_quat(0, 0, M_PI);
	// view->rotation_quat = euler_to_quat(0, 0, 0);
}

void	init_view_zero(t_view *view)
{
	view->c_state = 0;
	view->s_state = 0;
	view->a_state = 0;
	view->cmd_state = 0;
	view->click_state = 0;
	view->rclick_state = 0;
	view->ratio = 1.0f;
	view->box_offset_x = V_WIDTH / 2;
	view->box_offset_y = V_HEIGHT / 2;
}

t_view	*init_view(t_scenario *scena)
{
	t_view	*view;

	view = malloc(sizeof(t_view));
	printf("View:%p\n", view);
	if (!view)
		ft_exit("Malloc");
	view->mlx = mlx_init_struct(V_WIDTH, V_HEIGHT, "MiniRT Camera");
	printf("View->mlx:%p\n", view->mlx);
	view->img_data = malloc(sizeof(t_data_img));
	printf("View->imgdata:%p\n", view->img_data);
	if (!view->img_data)
		ft_exit("Malloc");
	view->img_data->img = mlx_new_image(view->mlx->ptr, V_WIDTH, V_HEIGHT);
	view->img_data->addr = mlx_get_data_addr(view->img_data->img,
			&view->img_data->bits_per_pixel,
			&view->img_data->line_length, &view->img_data->endian);
	init_view_quat(view);
	init_view_zero(view);
	view->camera = init_quat_camera(scena, 50);
	printf("init view ok\n");
	view->box = init_quat_box();
	return (view);
}
