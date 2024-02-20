/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:28 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/20 12:08:11 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	startpos(t_data *data, char id)
{
	if (id == 'N')
		data->input->player_facing = P_NORTH;
	if (id == 'S')
		data->input->player_facing = P_SOUTH;
	if (id == 'W')
		data->input->player_facing = P_WEST;
	if (id == 'E')
		data->input->player_facing = P_EAST;
}

static void	save_line(t_data *data, char *line, int row)
{
	int	i;

	i = 0;
	while (line[i])
	{
		data->input->parsed_map[row][i] = line[i];
		i++;
	}
	if (line[0] != '\n')
		data->input->parsed_map[row][i] = '\0';
	else
		err_msg_free("Invalid map", 3, data);
}

static void	check_middlemap(t_data *data, char *line, int j)
{
	while (line[j] != '\0')
	{
		if (j == 0 || j == (int)ft_strlen(line))
		{
			if (line[j] != 49 && !line[j])
				err_msg_free("Invalid map, space instead of a wall\n", 3, data);
		}
		else
		{
			if (!ft_strchr("NESW01\0\n ", line[j])
				&& line[j] != '\n' && line[j] != '\0')
				err_msg_free("Invalid map, unidentified char\n", 3, data);
			else if ((line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
					|| line[j] == 'E') && data->input->player == true)
				err_msg_free("Invalid map, only one player allowed\n", 3, data);
			else if ((line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
					|| line[j] == 'E') && data->input->player == false)
			{
				startpos(data, line[j]);
				data->input->player = true;
			}
		}
		j++;
	}
}

static void	parse_map(t_data *data, char *line, int i, int j)
{
	char	*newline;

	syntax_check(data, line);
	newline = rm_spaces(line, 3, data, 0);
	if (i > 6)
	{
		data->input->parsed_map[i - 7] = \
		ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->input->parsed_map[i - 7])
			err_msg_free("Calloc failed\n", 3, data);
		save_line(data, line, i - 7);
		if (i == 7 || i == data->input->nb_lines)
		{
			while (newline[j])
			{
				if (newline[j] != 49 && !newline[j])
					err_msg_free("Invalid map\n", 3, data);
				j++;
			}
		}
		else
			check_middlemap(data, newline, j);
	}
	free(newline);
}

int	map_validation(t_data *data, char *file, int i)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg_free("Opening the file\n", 2, data);
	data->input->parsed_map = \
	calloc_exit((data->input->nb_lines - 6) + 1, sizeof(char *), data, 2);
	data->texture_count = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n\0") != 0)
			i++;
		else if (ft_strcmp(line, "\n\0") == 0 && i > 6)
			err_msg_free("Invalid map\n", 3, data);
		parse_map(data, line, i, 0);
		free(line);
	}
	find_player(data, data->input->parsed_map);
	wall_check(data);
	close(fd);
	return (is_walkable_path(data), parse_spaces(data), 0);
}
