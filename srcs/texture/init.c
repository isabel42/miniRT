/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:52:07 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/05 14:43:18 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data_img	*get_texture_to_img(void *mlx, char *path)
{
	t_data_img	*texture;

	texture = malloc(sizeof(t_data_img));
	if (!texture)
		ft_exit("Malloc");
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		ft_exit("Texture error");
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	printf("Texture address: %p\n", texture);
	printf("Texture->img address: %p\n", texture->img);
	printf("Texture->addr address: %p\n", texture->addr);
	return (texture);
}

t_texture_list	*new_texture(char *path, t_scenario *scena)
{
	t_texture_list	*new;

	new = malloc(sizeof(t_texture_list));
	if (!new)
		ft_exit("Malloc");
	new->texture_name = ft_strdup(path);
	printf("texture_name address: %p\n", new->texture_name);
	new->texture = get_texture_to_img(scena->mlx->ptr, path);
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