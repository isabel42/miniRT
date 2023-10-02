/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:50:20 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	ft_free_ii(int **split, int j)
// {
// 	int	i;

// 	i = 0;
// 	while (i < j)
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

// void	ft_free_cc(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

void	ft_free_cc_c(char **cc, char *c)
{
	ft_free_cc(cc);
	free(c);
}

void	ft_free_c_c(char *a, char *b)
{
	free(a);
	free(b);
}
