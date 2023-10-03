/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/02 16:39:18 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_c_c(char *a, char *b)
{
	free(a);
	free(b);
}

void	free_scenario(t_scenario *scena)
{
	t_obj	*tmp;

	if (scena->amb_lux)
		free(scena->amb_lux);
	if (scena->cam)
		free(scena->cam);
	if (scena->spot_lux)
		free(scena->spot_lux);
	while (scena->obj)
	{
		tmp = scena->obj->next;
		free(scena->obj);
		scena->obj = tmp;
	}
}
