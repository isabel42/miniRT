/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/27 15:24:51 by lsohler          ###   ########.fr       */
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
# define V_WIDTH 600
# define V_HEIGHT 600

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
# define KEY_CTRL 256
# define KEY_SHIFT 257
# define KEY_ALT 261
# define KEY_CMD 259
# define KEY_ENTER 36
# define KEY_SCROLL_UP 5
# define KEY_SCROLL_DOWN 4
# define KEY_SCROLL_UP_S 7
# define KEY_SCROLL_DOWN_S 6

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
t_mlx		*mlx_init_struct(int win_size_x, int win_size_y, char *name);
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
float		get_ratio(char *line, float min, float max);
t_vec3d		get_orientation(char *line, float min, float max);

/*---INTERPOLATION---*/
void		sphere_hit(t_ray ray, t_obj *obj, t_hit *hit);
void		cal_cy_param(t_vec3d *abc, t_ray ray, t_obj *cy);
void		cal_cy_param_b(t_vec3d *abc, t_ray ray, t_obj *cy);
void		cal_cy_param_c(t_vec3d *abc, t_ray ray, t_obj *cy);
void		in_pl(t_ray ray, t_obj *pl, t_hit *hit);
void		in_sp(t_ray ray, t_obj *sp, t_hit *hit);
void		in_cy(t_ray ray, t_obj *cy, t_hit *hit);
void		cylinder_hit(t_ray ray, t_obj *obj, t_hit *hit);
void		plane_hit(t_ray ray, t_obj *obj, t_hit *hit);
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
// void		shadow_ray_rgb(t_scenario *scena, t_hit object_hit, int i, int j);
t_rgb		shadow_ray_rgb(t_ray ray, t_scenario *scena, t_hit object_hit);
void		tracing(t_scenario *sc);

/*---VIEW---*/
t_view		*init_view(t_scenario *scena);
t_quat		*init_quat_camera(t_scenario *scena, int dist);
t_quat		*init_quat_box(void);
int			key_press_view(int key, t_scenario *scena);
int			key_release_view(int key, t_scenario *scena);
int			mouse_pressed(int key, int x, int y, t_scenario *scena);
int			mouse_released(int key, int x, int y, t_scenario *scena);
t_quat		*init_axis(t_vec3d center, float size);
void		bresenham_draw_line(t_point a, t_point b, t_scenario *meta, t_rgb color);
void		apply_rotation_scena(t_scenario *scena);
void		apply_rotation_o_cam(t_scenario *scena);
void		my_new_mlx_img_data_view(t_scenario *meta);
void		render_view(t_scenario *scena);
int			mouse_move(int x, int y, t_scenario *scena);
void		mouse_scroll(int key, t_scenario *scena);
void		apply_rotation_camera(t_scenario *scena);
void		apply_rotation_box(t_scenario *scena);
void		apply_rotation_scena(t_scenario *scena);


#endif