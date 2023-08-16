/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:19 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/28 14:24:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int letter)
{
	if ('0' <= letter && letter <= '9')
		return (1);
	else
		return (0);
}
/*
int	main()
{
	unsigned char	letter;
	letter	= '8';
	printf("%d\n",ft_isdigit(letter));
	printf("%d\n",isdigit(letter));
}*/
