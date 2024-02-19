/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:36:45 by ahornstr          #+#    #+#             */
/*   Updated: 2024/02/19 14:43:54 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	dupe_texture(t_data *data, char *line, int i)
{
	char	*temp;
	
	temp = ft_substr(line, i, i + 2);
	if (ft_strcmp(temp, "NO") < 0 && ft_strcmp(temp, "SO") < 0 && \
		ft_strcmp(temp, "WE") < 0 && ft_strcmp(temp, "EA") < 0)
	{
			free(temp);
			err_msg("Wrong texture assignments");
	}
	data->texture_count++;
	free (temp);
}

void	syntax_check(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
			return ;
		if (!ft_strchr("NSWFCE1 \t", line[i]))
			err_msg("Invalid line in file");
		if (ft_strchr("FC1 \t", line [i]))
		{
			if (ft_strchr("FC", line [i]))
				data->texture_count++;
			return ;
		}
		if (ft_strchr("NSEW", line[i]))
		{
			dupe_texture(data, line, i);
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

void	find_player(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NESW", map[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player > 1)
		err_msg("Too many players");
	if (player < 1)
		err_msg("No player found");
}
