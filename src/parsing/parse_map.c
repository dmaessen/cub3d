/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:28 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/15 18:19:46 by dmaessen         ###   ########.fr       */
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
	{
		puts("NORTH");
		data->input->player_facing = P_NORTH;
	}
	if (id == 'S')
	{
		puts("SUD");
		data->input->player_facing = P_SOUTH;
	}
	if (id == 'W')
	{
		puts("OUEST");
		data->input->player_facing = P_WEST;
	}
	if (id == 'E')
	{
		puts("EST");
		data->input->player_facing = P_EAST;
	}
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
		err_msg("Invalid map");
}

static void	check_middlemap(t_data *data, char *line, size_t j)
{
	printf("line: %s\n", line);
	while (line[j])
	{
		if (j == 0 || j == ft_strlen(line))
		{
			if (line[j] != 49 && !line[j])
				err_msg("Invalid map, empty space instead of a wall\n");
		}
		else
		{
			if (line[j] != 'N' && line[j] != 'S' && line[j] != 'W'
				&& line[j] != 'E' && line[j] != 48 && line[j] != 49
				&& line[j] != '\0' && line[j] != '\n')
				err_msg("Invalid map, unidentified character in the map\n");
			else if ((line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
					|| line[j] == 'E') && data->input->player == true)
				err_msg("Invalid map, only one player allowed in the map\n");
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

static int	parse_map(t_data *data, char *line, int i)
{
	char	*newline;
	size_t	j;

	syntax_check(data, line);
	if (data->texture_count > 6)
		err_msg("Too many textures");
	newline = rm_spaces(line);
	j = -1;
	if (i > 6)
	{
		data->input->parsed_map[i - 7] = \
		calloc_exit(ft_strlen(line) + 1, sizeof(char));
		save_line(data, line, i - 7);
		if (i == 7 || i == data->input->nb_lines)
		{
			while (newline[j++])
				if (newline[j] != 49 && !newline[j])
					err_msg("Invalid map, empty space instead of a wall\n");
		}
		else
			check_middlemap(data, newline, j);
	}
	free(newline);
	return (0);
}

int	map_validation(t_data *data, char *file, int i)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	data->input->player = false;
	data->input->parsed_map = \
	calloc_exit((data->input->nb_lines - 6) + 1, sizeof(char *));
	data->texture_count = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n\0") != 0)
			i++;
		if (parse_map(data, line, i) == 1)
			return (free(line), close(fd), 1);
		free(line);
	}
	wall_check(data);
	close(fd);
	is_walkable_path(data);
	return (parse_spaces(data), 0);
}
