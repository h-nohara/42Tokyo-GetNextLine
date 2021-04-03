/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnohara <hnohara@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:36:20 by hnohara           #+#    #+#             */
/*   Updated: 2021/04/03 15:58:43 by hnohara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static	char	**static_buff;
	int				res;

	if (init_buff(&buff, &static_buff, BUFFER_SIZE, 1) == -1)
	{
		free_two(&buff, &static_buff, -1);
		return (-1);
	}
	while (1)
	{
		if (init_buff(&buff, &static_buff, BUFFER_SIZE, 0) == -1)
			break ;
		res = check_sbuff_newline(static_buff, line);
		if (res != 0)
			break ;
		res = read(fd, buff, BUFFER_SIZE);
		if (res == 0 || res == -1)
		{
			res = move_sbuff(static_buff, line, res);
			break ;
		}
		res = check_buff_newline(buff, static_buff, line);
		if (res != 0)
			break ;
		if ((res = move_buff(&buff, static_buff)) == -1)
			break ;
	}
	free_two(&buff, &static_buff, res);
	return (res);
}

int	check_sbuff_newline(char **sbuff, char **line)
{
	int		i;
	char	*s;

	if (sbuff && *sbuff)
	{
		i = 0;
		while ((*sbuff)[i])
		{
			if ((*sbuff)[i] == '\n')
			{
				*line = ft_slice(*sbuff, 0, i);
				if (!(*line))
					return (-1);
				s = ft_slice(*sbuff, i + 1, -1);
				if (!s)
					return (-1);
				free(*sbuff);
				*sbuff = s;
				return (1);
			}
			++i;
		}
	}
	return (0);
}

int	check_buff_newline(char *buff, char **sbuff, char **line)
{
	int		i;
	char	*tmp_s;

	i = 0;
	while (buff[i] && (buff[i] != '\n'))
		++i;
	if (buff[i] != '\n')
		return (0);
	tmp_s = ft_slice(buff, 0, i);
	if (!tmp_s)
		return (-1);
	if (sbuff && *sbuff)
	{
		*line = ft_concat(*sbuff, tmp_s);
		free(tmp_s);
		if (!(*line))
			return (-1);
	}
	else
		*line = tmp_s;
	free(*sbuff);
	*sbuff = ft_slice(buff, i + 1, -1);
	if (!(*sbuff))
		return (-1);
	return (1);
}

int	move_sbuff(char **sbuff, char **line, int res_read)
{
	if (sbuff && *sbuff)
	{
		if (res_read == 0)
		{
			if (!(*line = ft_slice(*sbuff, 0, -1)))
				res_read = -1;
		}
	}
	return (res_read);
}

int	move_buff(char **buff, char **sbuff)
{
	char	*tmp_s;

	if (sbuff && *sbuff)
	{
		tmp_s = ft_concat(*sbuff, *buff);
		if (!tmp_s)
			return (-1);
		free(*sbuff);
		*sbuff = tmp_s;
	}
	else
	{
		tmp_s = ft_slice(*buff, 0, -1);
		if (!tmp_s)
			return (-1);
		*sbuff = tmp_s;
	}
	return (0);
}
