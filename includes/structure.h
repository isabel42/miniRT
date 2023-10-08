/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:27:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 16:32:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_obj
{
	int				id;
	float			diam;
	float			high;
	struct s_vec3d	pos;
	struct s_rgb	rgb;
	struct s_vec3d	dir;
	struct s_obj	*next;
	t_quat			*cube;
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
	struct s_meta		*meta;
	t_quat				identity_quat;
	t_quat				rotation_quat;
	t_quat				*box;
	t_quat				*axis;
}				t_scenario;

typedef struct s_meta
{
	struct s_scenario	*scena;
	struct s_quat_cache	*cache;
	t_quat		rotation_quat;
	t_quat		idenditiy_quat;
	int			key;
	int			size[2];
	int			offset[2];
	int			box_offset[2];
	int			click_state;
	int			scroll_state;
	int			shift_state;
	int			ctrl_state;
	int			c_state;
	int			b_state;
}				t_meta;

typedef struct s_quat_cache
{
	t_quat	yaw_m;
	t_quat	yaw_p;
	t_quat	pitch_m;
	t_quat	pitch_p;
	t_quat	roll_m;
	t_quat	roll_p;
}				t_quat_cache;
/*--------------*/

/*---TRACING---*/
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
/*-----------*/