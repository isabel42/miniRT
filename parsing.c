/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:46:58 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_exit_fd(int fd)
{
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
}

void	ft_exit(void)
{
	printf("Error\n");
	exit (0);
}

void	ft_get_ft_pars(char *line_b, t_list **obj, t_scenario *scena)
{	
	char	**split;
	char	*line;

	line = ft_strtrim(line_b, "\n");
	split = ft_split(line, ' ');
	free(line);
	if (!ft_strncmp(split[0], "A", 3))
		ft_abm_lux(split, scena);
	else if (!ft_strncmp(split[0], "C", 3))
		ft_cam(split, scena);
	else if (!ft_strncmp(split[0], "L", 3))
		ft_spot_lux(split, scena);
	else if (!ft_strncmp(split[0], "sp", 4))
		ft_sp(split, obj);
	else if (!ft_strncmp(split[0], "pl", 4))
		ft_pl(split, obj);
	else if (!ft_strncmp(split[0], "cy", 4))
		ft_cy(split, obj);
	else
		ft_exit();
}

void	ft_parsing(char *argv1, t_list **obj, t_scenario *scena)
{
	int		fd;
	char	*line;

	fd = open(argv1, O_RDONLY);
	ft_exit_fd(fd);
	line = get_next_line(fd);
	if (!line || line == NULL)
	{
		ft_putstr_fd("Input file is empty!\n", 1);
		exit(0);
	}
	*obj = NULL;
	while (line != NULL)
	{
		if (line[0] != '\n')
			ft_get_ft_pars(line, obj, scena);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
