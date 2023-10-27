/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:30:03 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 12:32:47 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quat	quat_rotate(t_quat	q, t_quat p)
{
	p = quat_multiply(
			quat_multiply(q, p),
			quat_conjugate(q));
	return (p);
}
