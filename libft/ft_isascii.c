/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:19 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/28 11:39:50 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int letter)
{
	if (0 <= letter && letter <= 127)
		return (1);
	else
		return (0);
}
/*
int main()
{
	unsigned char letter;
	letter	= 'a';
	printf("%d\n",ft_isascii(letter));
	printf("%d\n",isascii(letter));
}*/
