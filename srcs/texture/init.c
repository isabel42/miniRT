/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:52:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 20:45:14 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_texture_list	*new_texture(char *path, t_scenario *scena)
{
	t_texture_list	*new;

	new = malloc(sizeof(t_texture_list));
	if (!new)
		ft_exit("Malloc");
	new->texture_name = ft_strdup(path);
	new->texture = get_texture_to_img(scena->mlx, path);
	new->next = NULL;
	return (new);
}

t_texture_list	*find_texture_in_list(t_texture_list **list, char *path)
{
	t_texture_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(path, tmp->texture_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	texture_add_back(t_texture_list **list, char *path, t_scenario *scena)
{
	t_texture_list	*tmp;

	if (!*list)
		*list = new_texture(path, scena);
	else if (!find_texture_in_list(list, path))
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_texture(path, scena);
	}
}

t_data_img	*assign_texture(t_texture_list **list, char *path, t_scenario *scena)
{
	texture_add_back(list, path, scena);
	return (find_texture_in_list(list, path)->texture);
}