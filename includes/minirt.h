/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/04 16:48:14 by lsohler          ###   ########.fr       */
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
int			render_camera(t_scenario *scena);
void		camera_param(t_cam *cam);
t_quat		*init_quat_camera(int plane_height, int plane_width, t_vec3d pos, int dist);
void		test_print_meta(t_meta *meta);
void		rotate_camera(t_cam *cam, t_quat rotation);
int			mouse_move(int x, int y, t_meta *meta);
int			mouse_pressed(int button, int x, int y, t_meta *meta);
int			mouse_released(int button, int x, int y, t_meta *meta);
void		apply_rotation(t_scenario *scena);

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

#endif