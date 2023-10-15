/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/15 15:30:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "structure.h"

# define WIDTH 1920
# define HEIGHT 1080

/*KEYS*/
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53
# define KEY_1	18
# define KEY_2	19
# define KEY_P	35
# define KEY_I	34
# define KEY_Q	12
# define KEY_W	13
# define KEY_E	14
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2
# define KEY_O	31
# define KEY_B	11
# define KEY_C	8
# define KEY_M	46
# define KEY_N8 91
# define KEY_N6 88
# define KEY_N4 86
# define KEY_N2 84

# define I_WHITE 0xFFFFFF
# define I_RED 0x960018
# define I_GREEN 0x00ab84
# define I_BLACK 0x000000
# define I_BLUE 0x005EFF
# define I_DEEPBLUE 0x1B2287
# define I_YELLOW 0xFFBC00
# define I_BROWN 0x9F6212
# define I_GRAY 0xACACAC

enum e_form {sp, pl, cy};

/*---ERROR---*/
void		ft_exit(char *msg);
void		ft_exit_fd(int fd);

/*---FREE---*/
void		free_scenario(t_scenario *scena);

/*---PARSING---*/
t_scenario	*init_scenario(void);
t_scenario	*parsing(char *argv1);
t_mlx		*mlx_init_struct(int win_size_x, int win_size_y);
void		parse_line(char *line, t_scenario *scena);
void		new_sphere(char **split, t_scenario *scena);
void		new_plan(char **split, t_scenario *scena);
void		new_cylinder(char **split, t_scenario *scena);
void		new_abm_lux(char **split, t_scenario *scena);
void		new_cam(char **split, t_scenario *scena);
void		new_spot_lux(char **split, t_scenario *scena);
t_rgb		ft_rgb(char *line);
t_vec3d		ft_pos(char *line);
int			ft_get_rgb(char *line);

/*---INTERPOLATION---*/
void		sphere_hit(t_ray ray, t_obj *obj, t_hit *hit);
void		cal_cy_param(t_vec3d *abc, t_ray ray, t_obj *cy);
void		cal_cy_param_b(t_vec3d *abc, t_ray ray, t_obj *cy);
void		cal_cy_param_c(t_vec3d *abc, t_ray ray, t_obj *cy);
void		in_pl(t_ray ray, t_obj *pl, t_hit *hit);
void		in_sp(t_ray ray, t_obj *sp, t_hit *hit);
void		in_cy(t_ray ray, t_obj *cy, t_hit *hit);

/*---RENDER---*/
void		my_mlx_pixel_put(t_data_img *imgdata, int x, int y, int color);
t_rgb		int_to_rgb(int icolor);
int			rgb_to_int(t_rgb color);
int			render(t_scenario *scena);

/*---GNL---*/
char		*get_next_line(int fd);
char		*ft_testret(char *line, int ret, char *buf, int limit);
void		ft_free_ii(int **s, int j);
char		*ft_strjoin_free(char *s1, char *s2);

/*---KEY---*/
int			key_press(int key, t_scenario *scena);
int			close_w(t_scenario *scena);

/*---TRACING---*/
void		get_hit(t_scenario *sc, t_ray ray, t_hit *hit, bool stop_first);
void		shadow_ray_rgb(t_scenario *scena, t_hit object_hit, int i, int j);
void		tracing(t_scenario *sc);

#endif