/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:19 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/28 11:38:34 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int letter)
{
	if (('A' <= letter && letter <= 'Z') || ('a' <= letter && letter <= 'z')
		|| ('0' <= letter && letter <= '9'))
		return (1);
	else
		return (0);
}
/*
int main()
{
	int letter;
	letter	= 115;
	printf("%d\n",ft_isalnum(letter));
	printf("%d\n",isalnum(letter));
}*/
