/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:19 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/28 11:41:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int letter)
{
	if (32 <= letter && letter <= 126)
		return (1);
	else
		return (0);
}
/*
int main()
{
	unsigned char letter;
	letter	= 1;
	printf("%d\n",ft_isprint(letter));
	printf("%d\n",isprint(letter));
}*/
