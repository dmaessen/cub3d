/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:36:45 by ahornstr          #+#    #+#             */
/*   Updated: 2024/02/14 17:44:56 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	syntax_check(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\0' || line[i] == '\n')
			return ;
		if (!ft_strchr("NSWFCE1 \t", line[i]))
			err_msg("Wrong texture assignments {1}");
		if (ft_strchr("FC1 \t", line [i]))
		{
			if (ft_strchr("FC", line [i]))
				data->texture_count++;
			return ;
		}
		if (ft_strchr("NSEW", line[i]))
		{
			if (ft_strncmp(line, "NO", 2) < 0 && \
			ft_strncmp(line, "SO", 2) < 0 && \
			ft_strncmp(line, "WE", 2) < 0 && ft_strncmp(line, "EA", 2) < 0)
				err_msg("Wrong texture assignments {2}");
			data->texture_count++;
			return ;
		}
	}
}

void	wall_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->input->parsed_map[i])
	{
		j = 0;
		while (data->input->parsed_map[i][j])
		{
			if (data->input->parsed_map[i][j] == '0')
			{
				if (i == 0 || i == ft_strarrlen(data->input->parsed_map) - 1)
					err_msg("Invalid map, not closed off by walls\n");
				if (!ft_strchr("1NSWE0", data->input->parsed_map[i + 1][j]) || \
				(i > 0 && !ft_strchr("1NSWE0", \
				data->input->parsed_map[i - 1][j])) || \
				!ft_strchr("1NSWE0", data->input->parsed_map[i][j + 1]) || \
				!ft_strchr("1NSWE0", data->input->parsed_map[i][j - 1]))
					err_msg("Invalid map, not closed off by walls\n");
			}
			j++;
		}
		i++;
	}
}
