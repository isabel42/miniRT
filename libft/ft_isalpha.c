/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:19 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/28 11:38:59 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int letter)
{
	if (('A' <= letter && letter <= 'Z') || ('a' <= letter && letter <= 'z'))
		return (1);
	else
		return (0);
}
/*
int main()
{
	unsigned char letter;
	letter	= 'R';
	printf("%d\n",ft_isalpha(letter));
	printf("%d\n",isalpha(letter));
}*/
