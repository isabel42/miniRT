/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/10 23:10:32 by itovar-n         ###   ########.fr       */
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
void		parse_line(char *line, t_scenario *scena);
void		new_sphere(char **split, t_scenario *scena);
void		new_plan(char **split, t_scenario *scena);
void		new_cylinder(char **split, t_scenario *scena);
void		new_abm_lux(char **split, t_scenario *scena);
void		new_cam(char **split, t_scenario *scena);
void		new_spot_lux(char **split, t_scenario *scena);
t_rgb		ft_rgb(char *line);
float		ft_get_float_d(char *line);
float		ft_get_float(char *line);
t_vec3d		ft_pos(char *line);
t_meta		*meta_init(void);

/*---TEST---*/
void		bresenham_draw_line(t_point a, t_point b,
				t_scenario *meta, t_rgb color);
void		print_parsing(t_scenario *sc);
void		print_q(t_quat q);
void		print_q_cache(t_quat_cache cache);
void		test_print_vecteur(t_vec3d v);
t_quat		*init_quat_camera(int plane_height, int plane_width, t_vec3d pos, int dist);
void		test_print_meta(t_meta *meta);
int			mouse_move(int x, int y, t_meta *meta);
int			mouse_pressed(int button, int x, int y, t_meta *meta);
int			mouse_released(int button, int x, int y, t_meta *meta);
t_quat		*init_box(void);
t_quat		*init_cube(t_vec3d center, float size);

void		rotate_camera(t_cam *cam, t_quat rotation);
int			render(t_scenario *scena);
void		apply_rotation_scenario(t_scenario *scena);
void		apply_rotation(t_scenario *scena);
t_quat		*apply_rotation_box(t_scenario *scena, t_quat *c);
void		camera_param(t_cam *cam);
void		draw_ray(t_scenario *scena);
void		draw_scenario(t_scenario *scena);
void		draw_box(t_quat *c, t_scenario *scena, t_rgb color);
t_hit		sphere_hit(t_ray ray, t_quat center_q, float sphere_r);
t_hit		sphere_hit2(t_ray ray, t_obj sphere);

void		my_mlx_pixel_put(t_data_img *imgdata, int x, int y, int color);
void draw_circle(t_data_img *imgdata, int x, int y, int r, int color);
t_rgb		int_to_rgb(int icolor);
int			rgb_to_int(t_rgb color);
/*---KEY---*/
int			key_press(int key, t_meta *meta);
int			key_release(int key, t_meta *meta);

// free.c
void	ft_free_ii(int **split, int j);
void	ft_free_c_c(char *a, char *b);

// get_next_line
char	*get_next_line(int fd);
char	*ft_testret(char *line, int ret, char *buf, int limit);
void	ft_free_ii(int **s, int j);
char	*ft_strjoin_free(char *s1, char *s2);

// parsing_pos.c


// parsing_rgb.c
int		ft_get_rgb(char *line);


// parsing_diam.c

// parsing_obj.c
t_obj	*ft_obj_init(t_obj *obj);

//parsing_scena.c

// parsing.c
void	ft_scena_init(t_scenario **scena);



void	in_pl(t_ray ray, t_obj *pl, t_hit *hit);
void	in_sp(t_ray ray, t_obj *sp, t_hit *hit);
void 	in_cy(t_ray ray, t_obj *cy, t_hit *hit);

t_vec3d    new_point(t_quat q);
#endif