/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:15:54 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:45:48 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_address	*new_collector_node(void *address)
{
	t_address	*new;

	new = malloc(sizeof(t_address));
	if (!new)
		ft_exit("Malloc");
	new->address = address;
	new->next = NULL;
	return (new);
}

void	address_collector(t_address **collector, void *address)
{
	t_address	*tmp;

	if (*collector == NULL)
		*collector = new_collector_node(address);
	else
	{
		tmp = *collector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_collector_node(address);
	}
}

void	free_address_list(t_address *list)
{
	t_address	*tmp;

	tmp = list;
	while (list)
	{
		tmp = list->next;
		free(list->address);
		free(list);
		list = tmp;
	}
}
