/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:35:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:41:32 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	ft_sp(char **split, t_list **obj)
{
	t_obj	*sph;

	if (!split || !split[3] || split[4])
		ft_exit();
	sph = NULL;
	sph = ft_obj_init(sph);
	sph->id = sp;
	sph->pos = ft_pos(split[1]);
	sph->diam = ft_get_float(split[2]);
	sph->rgb = ft_rgb(split[3]);
	ft_free_cc(split);
	ft_lstadd_back(obj, ft_lstnew(sph));
}

void	ft_pl(char **split, t_list **obj)
{
	t_obj	*pln;

	if (!split || !split[3] || split[4])
		ft_exit();
	pln = NULL;
	pln = ft_obj_init(pln);
	pln->id = pl;
	pln->pos = ft_pos(split[1]);
	pln->dir = ft_pos(split[2]);
	pln->rgb = ft_rgb(split[3]);
	ft_free_cc(split);
	ft_lstadd_back(obj, ft_lstnew(pln));
}

void	ft_cy(char **split, t_list **obj)
{
	t_obj	*cyh;

	if (!split || !split[5] || split[6])
		ft_exit();
	cyh = NULL;
	cyh = ft_obj_init(cyh);
	cyh->id = cy;
	cyh->pos = ft_pos(split[1]);
	cyh->dir = ft_pos(split[2]);
	cyh->diam = ft_get_float(split[3]);
	cyh->high = ft_get_float(split[4]);
	cyh->rgb = ft_rgb(split[5]);
	ft_free_cc(split);
	ft_lstadd_back(obj, ft_lstnew(cyh));
}
