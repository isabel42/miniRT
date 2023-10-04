/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:35:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 15:49:04 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat_cache	*init_quat_cache(void)
{
	t_quat_cache *cache;

	cache = malloc(sizeof(t_quat_cache));
	if (!cache)
		ft_exit("Malloc");
	cache->yaw_m = euler_to_quat(-0.01, 0, 0);
	cache->yaw_p = euler_to_quat(0.01, 0, 0);
	cache->pitch_m = euler_to_quat(0, -0.01, 0);
	cache->pitch_p = euler_to_quat(0, 0.01, 0);
	cache->roll_m = euler_to_quat(0, 0, -0.01);
	cache->roll_p = euler_to_quat(0, 0, 0.01);
	return (cache);
}

void	meta_default_value(t_meta *meta)
{
	meta->offset[0] = WIDTH / 2;
	meta->offset[1] = HEIGHT / 2;
	meta->key = 0;
	meta->click_state = 0;
	meta->scroll_state = 0;
	meta->shift_state = 0;
	meta->ctrl_state = 0;
	meta->idenditiy_quat = quat_create(1, 0, 0, 0);
}

t_meta	*meta_init(void)
{
	t_meta	*meta;

	meta = malloc(sizeof (t_meta));
	if (!meta)
		ft_exit("Malloc");
	meta->offset[0] = WIDTH / 2;
	meta->offset[1] = HEIGHT / 2;
	meta->key = 0;
	meta->click_state = 0;
	meta->scroll_state = 0;
	meta->shift_state = 0;
	meta->ctrl_state = 0;
	printf("Init= ");
	test_print_meta(meta);
	meta->cache = init_quat_cache();
	meta->idenditiy_quat = quat_create(1, 0, 0, 0);
	return (meta);
}