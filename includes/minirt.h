/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/02 11:09:33 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

enum e_form {sp, pl, cy};

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}				t_vec3d;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_data_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_amblux
{
	float			ratio;
	struct s_rgb	rgb;
}				t_amblux;

typedef struct s_cam
{
	int				fov;
	struct s_vec3d	pos;
	struct s_vec3d	dir;
}				t_cam;

typedef struct s_spotlux
{
	float			ratio;
	struct s_vec3d	pos;
	struct s_rgb	color;
}				t_spotlux;

typedef struct s_scenario
{
	t_amblux	*amb_lux;
	t_cam		*cam;
	t_spotlux	*spot_lux;
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

// free.c

void	ft_free_ii(int **split, int j);
void	ft_free_cc(char **tab);
void	ft_free_cc_c(char **cc, char *c);
void	ft_free_c_c(char *a, char *b);

// get_next_line
char	*get_next_line(int fd);
char	*ft_testret(char *line, int ret, char *buf, int limit);
void	ft_free_cc(char **s);
void	ft_free_ii(int **s, int j);
char	*ft_strjoin_free(char *s1, char *s2);

// parsing_pos.c
float	ft_get_float(char *line);
t_vec3d	ft_pos(char *line);

// parsing_rgb.c
int		ft_get_rgb(char *line);
t_rgb	ft_rgb(char *line);

// parsing_diam.c
float	ft_get_float_d(char *line);

// parsing_obj.c
t_obj	*ft_obj_init(t_obj *obj);
void	ft_sp(char **split, t_list **obj);
void	ft_pl(char **split, t_list **obj);
void	ft_cy(char **split, t_list **obj);

//parsing_scena.c
void	ft_scena_init(t_scenario **scena_first);
void	ft_abm_lux(char **split, t_scenario *scena);
void	ft_cam(char **split, t_scenario *scena);
void	ft_spot_lux(char **split, t_scenario *scena);

// parsing.c
void	ft_exit_fd(int fd);
void	ft_exit(char *msg);
void	ft_sp(char **split, t_list **obj);
void	ft_get_ft_pars(char *line, t_list **obj, t_scenario *scena);
void	ft_scena_init(t_scenario **scena);
t_obj	*ft_obj_init(t_obj *obj);
void	ft_parsing(char *argv1, t_list **obj, t_scenario *scena);

#endif