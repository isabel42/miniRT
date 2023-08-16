/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/16 17:44:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_exit(int fd)
{
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
}

int	*ft_pos(char *line)
{
	char	**split;
	int		i;
	int		j;
	int		*pos;
	
	i = 0;
	split = ft_split(line, ',');
	pos = malloc(sizeof(int) * 3);
	if (!pos)
		return (NULL);
	while (i < 3)
	{
		pos[i] = ft_atoi(split[i]) * 10;
		j = 0;
		while (split[i][j] != '.')
		{
			if (ft_isdigit(split[i][j]) == 0)
			{
				printf("Errpr\n");
				exit (0);
			}
			j++;
		}
		j++;
		if (split[i][0] == '-' && ft_isdigit(split[i][j]) == 1)
			pos[i] = pos[i] - ft_atoi(split[i] + j);
		else if (ft_isdigit(split[i][j]) == 1)
			pos[i] = pos[i] + ft_atoi(split[i] + j);
		else if (ft_isdigit(split[i][j]) == 0 || split[i][j + 1] != '\0')
		{
			printf("Error\n");
			exit(0);
		}
		i++;
	}
	return (pos);
}

int	ft_sp(char **split, t_list **obj)
{
	t_obj	*sph;

	sph = malloc(sizeof(t_obj));
	if (!sph)
		return (0);
	sph->id = sp;
	sph->pos = ft_pos(split[1]);
	ft_lstadd_back(obj, ft_lstnew(&sph));
	printf("sp id: %d\n", sph->id);
	printf("sp id: %d\n", sph->pos[2]);
	return(3);
}

int	ft_get_ft_pars(char *line, t_list **obj)//, t_scenario *scena)
{
	char	**split;

	split = ft_split(line,' ');
	if (!ft_strncmp(split[0], "A", 3))
		return (0);	
	if (!ft_strncmp(line, "C", 3))
		return (1);	
	if (!ft_strncmp(line, "L", 3))
		return (2);	
	if (!ft_strncmp(split[0], "sp", 4))
		ft_sp(split, obj);
		// return (3);	
	if (!ft_strncmp(line, "pl", 3))
		return (4);	
	if (!ft_strncmp(line, "cy", 3))
		return (5);
	return(-1);
}

void	ft_scena_init(t_scenario *scena)
{
	scena = malloc(sizeof(t_scenario));
	if (!scena)
		return ;
	scena->amb_lux = NULL;
	scena->cam = NULL;
	scena->spot_lux = NULL;	
}

void ft_parsing(char *argv1, t_list **obj, t_scenario *scena)
{
	int		fd;
	char	*line;

	fd = open(argv1, O_RDONLY);
	ft_exit(fd);
	line = get_next_line(fd);
	if (!line || line == NULL)
	{
		ft_putstr_fd("Input file is empty!\n", 1);
		exit(0);
	}
	*obj = NULL;
	ft_scena_init(scena);
	while (line != NULL)
	{
		ft_get_ft_pars(line, obj);//, scena);
		// if (!ft_strncmp(split[0], "A", 3))
		// 	printf("testOK\n");
		// else
		// 	printf("adafd\n");
		line = get_next_line(fd);
	}
}