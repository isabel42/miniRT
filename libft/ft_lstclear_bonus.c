/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:22:53 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/08 12:11:15 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		cp = (*lst)->next;
		if (!lst)
			return ;
		else
		{
			del((*lst)->content);
			free(*lst);
		}
		*lst = cp;
	}
}
