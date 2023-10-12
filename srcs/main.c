/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:43:57 by itovar-n          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/10/11 17:38:43 by lsohler          ###   ########.fr       */
=======
/*   Updated: 2023/10/11 17:22:19 by itovar-n         ###   ########.fr       */
>>>>>>> f2d9dc9bc5ffe24c83bab5036ee0521e21e87db0
=======
/*   Updated: 2023/10/11 23:13:44 by itovar-n         ###   ########.fr       */
>>>>>>> main
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

	ptr_ft[0] = &in_sp;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

<<<<<<< HEAD
t_hit *hit_init(t_hit *hit)
{
	hit = malloc (sizeof(t_hit));
	if(!hit)
		return (NULL);
	hit->hit = false;
	hit->dst = -1;
	return (hit);
}
=======
>>>>>>> f2d9dc9bc5ffe24c83bab5036ee0521e21e87db0

void get_hit(t_scenario *sc, t_ray ray, t_hit *hit)
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
			hit->hit = true;
			hit->dst = hit_loc.dst;
			hit->pos = hit_loc.pos;
			hit->normal = hit_loc.normal;
			hit->rgb = hit_loc.rgb;
			hit->id = hit_loc.id;
			hit->hit = true;
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
<<<<<<< HEAD
	t_hit hit;
	t_rgb new_col;
=======
	t_hit 	hit;
>>>>>>> main
	t_quat    pq2;
	t_ray	ray;
	t_ray	ray_lux;
	t_hit	hit_lux;
	t_obj	*sp = sc->obj;
	
	p1 = sc->cam->pos;
	printf("lum.x: %f\t", sc->spot_lux->pos.x);
	printf("lum.y: %f\t", sc->spot_lux->pos.y);
	printf("lum.z: %f\t", sc->spot_lux->pos.z);
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
			ray.dir = ft_v_sub(p2, p1);
			ray.origin = p1;
			get_hit(sc, ray, &hit);	
			if (hit.hit == true)
			{
<<<<<<< HEAD
				// my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(hit.rgb));
				new_col = shadow_ray_rgb(hit.pos, sc->spot_lux->pos, sc, hit);
				my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(new_col));
				// my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(shadow_ray_rgb(hit.pos, sc->spot_lux->pos, sc, hit)));
=======
				ray_lux.origin = hit.pos;
				ray_lux.dir = ft_v_sub(sc->spot_lux->pos, hit.pos);
				hit_lux.hit = false;
				if (hit.id == 1)
				{
					in_sp(ray_lux, sp, &hit_lux);
					if(hit_lux.hit == false)
						my_mlx_pixel_put(&img, i, HEIGHT - j, I_WHITE);
					else
						my_mlx_pixel_put(&img, i, HEIGHT - j, I_RED);
				}
				else
					my_mlx_pixel_put(&img, i, HEIGHT - j, I_GREEN);
				// my_mlx_pixel_put(&img, i, HEIGHT - j, rgb_to_int(hit.rgb));		
>>>>>>> main
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
	// mlx_hook(vars.win, 17, 0, close_w, &vars);
	// mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.ptr);
	free(img.img);
	return (0);
}
