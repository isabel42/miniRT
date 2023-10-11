/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/11 13:57:21 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	close_w(int keycode, t_mlx *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->ptr, vars->win);
	exit(0);
	return (0);
}
// int	close_w(t_scenario *scena)
// {
// 	mlx_destroy_window(scena->mlx->ptr, scena->mlx->win);
// 	//free_lists(meta);
// 	printf("     CLOSING FROM CLICK !\n");
// 	exit (0);
// }

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		exit (0);
	}
}


void	hit_redirect(t_vec3d *p1, t_vec3d *p2, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_vec3d , t_vec3d , t_obj *, t_hit *);

	ptr_ft[0] = &in_sp;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[obj->id](*p1, *p2, obj, hit_loc);
}

t_hit *hit_init(t_hit *hit)
{
	hit = malloc (sizeof(t_hit));
	if(!hit)
		return (NULL);
	hit->hit = false;
	hit->dst = -1;
	return (hit);
}

void get_hit(t_scenario *sc, t_vec3d *p1, t_vec3d *p2, t_hit *hit)
{
	t_hit hit_loc;
	t_obj *obj;

	hit->dst = -1;
	hit_loc.dst = -1;
	obj = sc->obj;
	while (obj)
	{
		hit_redirect(p1, p2, obj, &hit_loc);
		if (hit_loc.dst > -1.0 && (hit->dst > hit_loc.dst || hit->dst < 0))
		{
			hit->hit = true;
			hit->dst = hit_loc.dst;
			hit->pos = hit_loc.pos;
			hit->normal = hit_loc.normal;
			hit->rgb = hit_loc.rgb;
		}
		obj = obj->next;
	}
}


void check_ob(t_scenario *sc, t_data_img img)
{
	int i;
	int j;
	t_vec3d p1;
	t_vec3d p2;
	int d;
	t_hit hit;
	t_quat    pq2;
	
	p1 = sc->cam->pos;
	d = WIDTH / 2;	
	i = 0;
	while (i <= WIDTH)
	{
		j = 0;
		while (j <= HEIGHT)
		{
			p2.y = sc->cam->pos.y + j - HEIGHT / 2;
			p2.x = sc->cam->pos.x + i - WIDTH / 2;
			p2.z = sc->cam->pos.z + d;

			pq2 = quat_create(0, p2.x, p2.y, p2.z);
            pq2 = quat_multiply(
                quat_multiply((sc->cam->dir), pq2),
                quat_conjugate((sc->cam->dir)));
            p2 = new_point(pq2);

			get_hit(sc, &p1, &p2, &hit);	
			if (hit.dst > 0)
			{
				// my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(hit.rgb));
				my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(shadow_ray_rgb(hit.pos, sc->spot_lux->pos, sc, hit)));
			}

			j++;
		}
		i++;
	}
}



int	main(int argc, char **argv)
{
	t_scenario	*scena;
	t_mlx		vars;
	t_data_img	img;

	ft_check_argc(argc);
	vars.ptr = mlx_init();
	vars.win = mlx_new_window(vars.ptr, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(vars.ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	scena = parsing(argv[1]);
	check_ob(scena, img);
	// print_parsing(scena);
	// render_camera(scena);
	// mlx_hook(scena->mlx->win, 2, 2, keypress, scena);
	// mlx_hook(scena->mlx->win, 3, 3, shift_released, scena);
	// mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	// mlx_hook(scena->mlx->win, 6, 1L << 6, mouse_move, scena);
	// mlx_hook(scena->mlx->win, 4, 1L << 2, mouse_pressed, scena);
	// mlx_hook(scena->mlx->win, 5, 1L << 3, mouse_released, scena);
	// mlx_loop(scena->mlx->ptr);
	mlx_put_image_to_window(vars.ptr, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.ptr);
	free(img.img);
	return (0);
}
