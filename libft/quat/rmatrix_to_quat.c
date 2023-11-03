/* ************************************************************************** */
/*																		    */
/*														:::      ::::::::   */
/*   rmatrix_to_quat.c								  :+:      :+:    :+:   */
/*												    +:+ +:+		 +:+     */
/*   By: lsohler <lsohler@student.42.fr>		    +#+  +:+       +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/03 14:18:58 by lsohler		   #+#    #+#		     */
/*   Updated: 2023/11/03 14:19:39 by lsohler		  ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#include "libft.h"

t_quat	rmatrix_to_quat(int matrix[3][3])
{
	t_quat quaternion;
	double trace;
	double s;
	
	trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
	if (trace > 0)
	{
		s = 0.5 / sqrt(trace + 1.0);
		quaternion.w = 0.25 / s;
		quaternion.x = (matrix[2][1] - matrix[1][2]) * s;
		quaternion.y = (matrix[0][2] - matrix[2][0]) * s;
		quaternion.z = (matrix[1][0] - matrix[0][1]) * s;
	}
	else
	{
		if (matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2])
		{
			s = 2.0 * sqrt(1.0 + matrix[0][0] - matrix[1][1] - matrix[2][2]);
			quaternion.w = (matrix[2][1] - matrix[1][2]) / s;
			quaternion.x = 0.25 * s;
			quaternion.y = (matrix[0][1] + matrix[1][0]) / s;
			quaternion.z = (matrix[0][2] + matrix[2][0]) / s;
		}
		else if (matrix[1][1] > matrix[2][2])
		{
			s = 2.0 * sqrt(1.0 + matrix[1][1] - matrix[0][0] - matrix[2][2]);
			quaternion.w = (matrix[0][2] - matrix[2][0]) / s;
			quaternion.x = (matrix[0][1] + matrix[1][0]) / s;
			quaternion.y = 0.25 * s;
			quaternion.z = (matrix[1][2] + matrix[2][1]) / s;
		}
		else
		{
			s = 2.0 * sqrt(1.0 + matrix[2][2] - matrix[0][0] - matrix[1][1]);
			quaternion.w = (matrix[1][0] - matrix[0][1]) / s;
			quaternion.x = (matrix[0][2] + matrix[2][0]) / s;
			quaternion.y = (matrix[1][2] + matrix[2][1]) / s;
			quaternion.z = 0.25 * s;
		}
	}
	return quaternion;
}
