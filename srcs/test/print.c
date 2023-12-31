/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:42:02 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/04 20:14:59 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PINK "\033[0;35m"
#define TEAL "\033[0;36m"
#define WHITE "\033[0;37m"
#define GREY "\033[30;1m"
#define B_RED "\033[31;1m"
#define B_GREEN "\033[32;1m"
#define B_YELLOW "\033[33;1m"
#define B_BLUE "\033[34;1m"
#define B_PINK "\033[35;1m"
#define B_TEAL "\033[36;1m"
#define B_WHITE "\033[37;1m"
#define DEF_C "\033[0m"

void	print_amblux(t_amblux *al)
{
	printf("\n");
	printf("%sAMBIENT LIGHT:%s\n", B_YELLOW, DEF_C);
	printf("%s   RGB: %s%i %s%i %s%i%s\n", GREY,
		RED, al->rgb.r, GREEN, al->rgb.g, BLUE, al->rgb.b, DEF_C);
	printf("%s   RATIO: %f%s\n", WHITE, al->ratio, DEF_C);
	printf("\n");
}

void	print_spotlux(t_spotlux *sl)
{
	printf("%sSPOT LIGHT:%s\n", B_TEAL, DEF_C);
	printf("%s   POS: %f %f %f%s\n", WHITE,
		sl->pos.x, sl->pos.y, sl->pos.z, DEF_C);
	printf("%s   RGB: %s%i %s%i %s%i%s\n", GREY,
		RED, sl->rgb.r, GREEN, sl->rgb.g, BLUE, sl->rgb.b, DEF_C);
	printf("%s   RATIO: %f%s\n", WHITE, sl->ratio, DEF_C);
	printf("\n");
}

void	print_cam(t_cam *cam)
{
	printf("%sCAMERA:%s\n", B_PINK, DEF_C);
	printf("%s   POS: %f %f %f%s\n", WHITE,
		cam->pos.x, cam->pos.y, cam->pos.z, DEF_C);
	printf("%s   ORIENTATION QUATERNION: w:%f x:%f y:%f z:%f%s\n", WHITE,
		cam->dir.w, cam->dir.x, cam->dir.y, cam->dir.z, DEF_C);
	printf("\n");
}

void	print_obj(t_obj *obj)
{
	while (obj)
	{
		printf("%sOBJECT:%s\n", GREY, DEF_C);
		printf("ID: %i\n", obj->id);
		if (obj->diam)
			printf("Diameter: %f\n", obj->diam);
		if (obj->id == cy)
			printf("Height: %f\n", obj->high);
		printf("%s   POS: %f %f %f%s\n", WHITE,
			obj->pos.x, obj->pos.y, obj->pos.z, DEF_C);
		printf("%s   RGB: %s%i %s%i %s%i%s\n", GREY,
			RED, obj->rgb.r, GREEN, obj->rgb.g, BLUE, obj->rgb.b, DEF_C);
		if (obj->id == pl || obj->id == cy)
			printf("%s   VECTOR: x:%f y:%f z:%f%s\n", WHITE,
				obj->dir.x, obj->dir.y, obj->dir.z, DEF_C);
		obj = obj->next;
	}
}

void	print_parsing(t_scenario *sc)
{
	if (!sc)
		ft_exit("NO SCENARIO");
	print_amblux(sc->amb_lux);
	print_spotlux(sc->spot_lux);
	print_cam(sc->cam);
	print_obj(sc->obj);
	printf("address img: %p\n", &sc->img_data);
	printf("\n\nOK!!\n");
}

void	test_print_vecteur(t_vec3d v)
{
	printf("Vector x:%f y:%f z:%f\n", v.x, v.y, v.z);
}

void	test_print_meta(t_meta *meta)
{
	printf("Meta: key:%i click:%i shift:%i ctrl:%i\n", meta->key, meta->click_state, meta->shift_state, meta->ctrl_state);
}

void	print_q(t_quat q)
{
	printf("%s   QUATERNION: w:%f x:%f y:%f z:%f%s\n", WHITE,
		q.w, q.x, q.y, q.z, DEF_C);
}

void	print_q_cache(t_quat_cache cache)
{
	printf("Pitch_m: ");
	print_q(cache.pitch_m);
	printf("Pitch_p: ");
	print_q(cache.pitch_p);
	printf("Yaw_m: ");
	print_q(cache.yaw_m);
	printf("Yaw_p: ");
	print_q(cache.yaw_p);
	printf("Roll_m: ");
	print_q(cache.roll_m);
	printf("Rollpm: ");
	print_q(cache.roll_p);
}