/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:30:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 17:05:51 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct t_bres
{
	int		dx;
	int		dy;
	int		x;
	int		y;
	int		ix;
	int		iy;
	int		delta[2];
}				t_bres;

t_rgb	int_to_rgb(int icolor)
{
	t_rgb	color;

	color.r = (icolor >> 16) & 0xFF;
	color.g = (icolor >> 8) & 0xFF;
	color.b = icolor & 0xFF;
	return (color);
}

int	rgb_to_int(t_rgb color)
{
	int	icolor;

	icolor = (color.r << 16) | (color.g << 8) | color.b;
	return (icolor);
}

void	my_mlx_pixel_put(t_data_img *imgdata, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH - 1 || y > HEIGHT -1 || x < 0 || y < 0)
		return ;
	dst = imgdata->addr + (y * imgdata->line_length
			+ x * (imgdata->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	check_boundaries(t_point a, t_point b)
{
	int	check_a;
	int	check_b;

	check_a = 1;
	check_b = 1;
	if (a.x > WIDTH || a.y > HEIGHT || a.x < 0 || a.y < 0)
		check_a = 0;
	if (b.x > WIDTH || b.y > HEIGHT || b.x < 0 || b.y < 0)
		check_b = 0;
	if (check_a == 0 && check_b == 0)
		return (0);
	else
		return (1);
}

t_bres	define_bresenham(t_point a, t_point b)
{
	t_bres	bres;

	bres.dx = abs((int)b.x - (int)a.x);
	bres.dy = abs((int)b.y - (int)a.y);
	if ((int)a.x < (int)b.x)
		bres.x = 1;
	else
		bres.x = -1;
	if ((int)a.y < (int)b.y)
		bres.y = 1;
	else
		bres.y = -1;
	bres.delta[0] = bres.dx - bres.dy;
	bres.ix = (int)a.x;
	bres.iy = (int)a.y;
	return (bres);
}

void	bresenham_draw_line(t_point a, t_point b, t_scenario *meta, t_rgb color)
{
	t_bres		bres;
	// int			i;

	// i = 0;
	if (check_boundaries(a, b) == 0)
		return ;
	bres = define_bresenham(a, b);
	while (bres.ix != (int)b.x || bres.iy != (int)b.y)
	{
		my_mlx_pixel_put(meta->img_data, bres.ix, bres.iy,
			rgb_to_int(color));
		bres.delta[1] = 2 * bres.delta[0];
		if (bres.delta[1] > -bres.dy)
		{
			bres.delta[0] -= bres.dy;
			bres.ix += bres.x;
		}
		if (bres.delta[1] < bres.dx)
		{
			bres.delta[0] += bres.dx;
			bres.iy += bres.y;
		}
	}
}


void draw_circle(t_data_img *imgdata, int x, int y, int r, int color) {
    int x0 = 0;
    int y0 = r;
    int d = 3 - 2 * r;

    while (x0 <= y0) {
        my_mlx_pixel_put(imgdata, x + x0, y + y0, color);
        my_mlx_pixel_put(imgdata, x - x0, y + y0, color);
        my_mlx_pixel_put(imgdata, x + x0, y - y0, color);
        my_mlx_pixel_put(imgdata, x - x0, y - y0, color);
        my_mlx_pixel_put(imgdata, x + y0, y + x0, color);
        my_mlx_pixel_put(imgdata, x - y0, y + x0, color);
        my_mlx_pixel_put(imgdata, x + y0, y - x0, color);
        my_mlx_pixel_put(imgdata, x - y0, y - x0, color);

        if (d < 0) {
            d = d + 4 * x0 + 6;
        } else {
            d = d + 4 * (x0 - y0) + 10;
            y0--;
        }
        x0++;
    }
}