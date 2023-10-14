/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/14 15:40:10 by itovar-n         ###   ########.fr       */
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

void	hit_redirect(t_ray ray, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_ray, t_obj *, t_hit *);

	ptr_ft[0] = &sphere_hit3;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

void get_hit(t_scenario *sc, t_ray ray, t_hit *hit, bool stop_first)
{
	t_hit hit_loc;
	t_obj *obj;

	hit->dst = -1;
	hit_loc.dst = -1;
	obj = sc->obj;
	hit_loc.hit = false;
	hit->hit = false;
	while (obj)
	{
		hit_redirect(ray, obj, &hit_loc);
		if (hit_loc.hit == true && (hit->dst > hit_loc.dst || hit->hit == false))
		{
			hit->dst = hit_loc.dst;
			hit->pos = hit_loc.pos;
			hit->normal = hit_loc.normal;
			hit->rgb = hit_loc.rgb;
			hit->id = hit_loc.id;
			hit->hit = true;
			if (stop_first == true)
				break;
		}
		obj = obj->next;
	}
}

void check_ob(t_scenario *sc)
{
	int i;
	int j;
	t_vec3d p2;
	int d;
	t_hit 	hit;
	t_quat    pq2;
	t_ray	ray;
	// t_ray	ray_lux;
	// float	scale;
	
	if (sc->cam->fov == 180)
		d = 0;
	else
		d = tan(ft_deg_to_rad(sc->cam->fov/2)) * WIDTH / 2;	
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
			ray.dir = ft_v_sub(p2, sc->cam->pos);
			ray.origin = sc->cam->pos;
			get_hit(sc, ray, &hit, false);	
			if (hit.hit == true)
				shadow_ray_rgb(sc, hit, i, j);
			j++;
		}
		i++;
	}
}



int	main(int argc, char **argv)
{
	t_scenario	*scena;
	// t_mlx		vars;
	// t_data_img	img;

	ft_check_argc(argc);
	// vars.ptr = mlx_init();
	// vars.win = mlx_new_window(vars.ptr, WIDTH, HEIGHT, "miniRT");
	// img.img = mlx_new_image(vars.ptr, WIDTH, HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);
	scena = parsing(argv[1]);
	render(scena);
	// print_parsing(scena);
	// render_camera(scena);
	// mlx_hook(scena->mlx->win, 2, 2, key_press, scena);
	// mlx_hook(scena->mlx->win, 3, 3, key_release, scena);
	mlx_hook(scena->mlx->win, 17, 0, close_w, scena);
	// mlx_hook(scena->mlx->win, 6, 1L << 6, mouse_move, scena);
	// mlx_hook(scena->mlx->win, 4, 1L << 2, mouse_pressed, scena);
	// mlx_hook(scena->mlx->win, 5, 1L << 3, mouse_released, scena);
	mlx_loop(scena->mlx->ptr);
	// mlx_put_image_to_window(vars.ptr, vars.win, img.img, 0, 0);
	// mlx_hook(vars.win, 17, 0, close_w, &vars);
	// mlx_hook(vars.win, 2, 0, close_w, &vars);
	// mlx_loop(vars.ptr);
	// free(img.img);
	return (0);
}