/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:13:16 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/16 16:07:37 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

enum form {sp, pl, cy};

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
	int		ratio;
	int		*rgb;
}				t_amblux;

typedef struct s_cam
{
	int		*pos;
	int		*orient;
	int		fov;
}				t_cam;

typedef struct s_spotlux
{
	int			*pos;
	int			ratio;
	int			*rgb;
}				t_spotlux;

typedef struct s_scenario
{
	t_amblux	*amb_lux;
	t_cam		*cam;
	t_spotlux	*spot_lux;
}				t_scenario;

typedef struct s_obj
{
	int		id;
	int		*pos;
	int		*rgb;
	int		*dir;
	int		diam;
	int		high;
}			t_obj;


// get_next_line
char	*get_next_line(int fd);
char	*ft_testret(char *line, int ret, char *buf, int limit);
void	ft_free_cc(char **s);
void	ft_free_ii(int **s, int j);

void ft_parsing(char *argv1, t_list **obj, t_scenario *scena);

#endif