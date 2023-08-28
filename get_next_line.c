/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:09:15 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 20:49:36 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_until_nl(char *s, int loopret)
{
	int		i;
	int		j;
	char	*temp;
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	temp = malloc((ft_strlen(s) + 1) * sizeof(*temp));
	if (!temp)
		return (NULL);
	while (s[i] != '\0' && pos <= loopret)
	{
		if (pos == loopret)
		{
			temp[j] = s[i];
			j++;
		}
		if (s[i] == '\n' || s[i] == '\0')
			pos++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

int	ft_totalloop(char *buf)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			count++;
		i++;
	}
	if (ft_strlen(buf) < 10)
		count++;
	return (count);
}

char	*ft_get_line(char *line, char *buf, int fd)
{
	int	ret;

	ret = read (fd, buf, 10);
	if (ret == 0)
	{
		buf[0] = '\0';
		if (line[0] != '\0')
			return (line);
	}
	line = ft_testret(line, ret, buf, 1);
	if (line == NULL)
		return (NULL);
	buf[ret] = '\0';
	while (ft_totalloop(buf) == 0)
	{
		line = ft_strjoin_free(line, buf);
		ret = read (fd, buf, 10);
		line = ft_testret(line, ret, buf, 0);
		if (line == NULL)
			return (NULL);
		buf[ret] = '\0';
	}
	return (line);
}

char	*ft_loopbuf(int looprep, char *buf)
{
	char	*temp;

	temp = get_until_nl(buf, looprep);
	if (ft_strlen(temp) == 0)
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	buf[10 + 1];
	static int	looprep = 0;

	if (fd < 0)
		return (NULL);
	if (looprep < ft_totalloop(buf) - 1)
	{
		looprep++;
		temp = ft_loopbuf(looprep, buf);
		return (temp);
	}
	line = get_until_nl(buf, looprep + 1);
	if (!line)
		return (NULL);
	line = ft_get_line(line, buf, fd);
	if (!line)
		return (NULL);
	temp = get_until_nl(buf, 0);
	line = ft_strjoin_free(line, temp);
	free(temp);
	looprep = 0;
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;
	int i = 0;

	fd = open("42", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (1);
	}
	while(i < 6)
	{
			line = get_next_line(fd);
			printf("New Line: %s",  line);
			i++;
	}
	if (close(fd) == -1)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}*/