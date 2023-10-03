/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/03 18:03:21 by lsohler          ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080

enum e_form {sp, pl, cy};

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct s_amblux
{
	float			ratio;
	struct s_rgb	rgb;
}				t_amblux;

typedef struct s_cam
{
	int					fov;
	int					dist;
	struct s_vec3d		pos;
	struct s_vec3d		vdir;
	t_quat				dir;
	t_quat				*c;
}				t_cam;

typedef struct s_spotlux
{
	float			ratio;
	struct s_vec3d	pos;
	struct s_rgb	rgb;
}				t_spotlux;

typedef struct s_scenario
{
	struct s_amblux		*amb_lux;
	struct s_cam		*cam;
	struct s_spotlux	*spot_lux;
	struct s_obj		*obj;
	struct s_data_img	*img_data;
	struct s_mlx		*mlx;
}				t_scenario;

typedef struct s_obj
{
	int				id;
	float			diam;
	float			high;
	struct s_vec3d	pos;
	struct s_rgb	rgb;
	struct s_vec3d	dir;
	struct s_obj	*next;
}			t_obj;

typedef struct s_hit
{
	bool			hit;
	float			dst;
	struct s_vec3d	pos;
	struct s_vec3d	normal;
}				t_hit;

typedef struct s_ray
{
	struct s_vec3d	origin;
	struct s_vec3d	dir;
}				t_ray;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_rectangle
{
	t_vec3d	a;
	t_vec3d	b;
	t_vec3d	c;
	t_vec3d	d;
}				t_rectangle;
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

/*---TEST---*/
void		print_parsing(t_scenario *sc);
void		bresenham_draw_line(t_point a, t_point b,
				t_scenario *meta, t_rgb color);
void		test_print_vecteur(void);
int			render_camera(t_scenario *scena);
void		camera_param(t_cam *cam);
t_quat		*init_quat_camera(int plane_height, int plane_width, t_vec3d pos, int dist);
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