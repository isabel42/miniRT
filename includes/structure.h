/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:27:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 17:26:49 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
/*---MLX---*/
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
/*---------*/

/*---OBJECTS---*/
typedef struct s_amblux
{
	float			ratio;
	float			ratio_norm;
	struct s_rgb	rgb;
}				t_amblux;

typedef struct s_cam
{
	int					fov;
	int					dist;
	struct s_vec3d		pos;
	struct s_vec3d		vdir;
	t_quat				dir;
}				t_cam;

typedef struct s_spotlux
{
	float				ratio;
	float				ratio_norm;
	struct s_vec3d		pos;
	struct s_rgb		rgb;
	t_quat				*axis;
	struct s_spotlux	*next;
}				t_spotlux;

typedef struct s_obj
{
	int				id;
	float			diam;
	float			high;
	t_quat			*axis;
	t_quat			q_dir;
	struct s_vec3d	pos;
	struct s_rgb	rgb;
	struct s_vec3d	dir;
	struct s_obj	*next;
}			t_obj;
/*-------------*/

/*---SCENARIO---*/
typedef struct s_scenario
{
	struct s_amblux		*amb_lux;
	struct s_cam		*cam;
	struct s_spotlux	*spot_lux;
	struct s_obj		*obj;
	struct s_data_img	*img_data;
	struct s_mlx		*mlx;
	struct s_view		*view;
}				t_scenario;

typedef struct s_view
{
	struct s_data_img	*img_data;
	struct s_mlx		*mlx;
	t_quat				identity_quat;
	t_quat				rotation_quat;
	t_quat				scena_quat;
	t_quat				*camera;
	t_quat				*box;
	float				ratio;
	int					c_state;
	int					s_state;
	int					a_state;
	int					cmd_state;
	int					click_state;
	int					rclick_state;
	int					box_offset_x;
	int					box_offset_y;
}				t_view;
/*--------------*/

/*---TRACING---*/
typedef struct s_hit
{
	bool			hit;
	float			dst;
	struct s_vec3d	pos;
	struct s_vec3d	normal;
	struct s_rgb	rgb;
	int				id;
}				t_hit;

typedef struct s_ray
{
	struct s_vec3d	origin;
	struct s_vec3d	dir;
	struct s_vec3d	p2;
}				t_ray;
/*-----------*/

/*---VIEW---*/
typedef struct s_point
{
	int	x;
	int	y;
}				t_point;
/*-----------*/

#endif