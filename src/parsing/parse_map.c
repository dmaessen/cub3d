/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:28 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/13 15:17:48 by ahornstr         ###   ########.fr       */
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
			return (err_msg("Wrong texture assignments {1}")) ;
		if (ft_strchr("FC1 \t", line [i]))
		{
			if (ft_strchr("FC", line [i]))
				data->texture_count++;
			return ;
		}
		if (ft_strchr("NSEW", line[i]))
		{
			if (ft_strncmp(line, "NO", 2) < 0 && ft_strncmp(line, "SO", 2) < 0 &&\
			ft_strncmp(line, "WE", 2) < 0 && ft_strncmp(line, "EA", 2) < 0)
				return (err_msg("Wrong texture assignments {2}")) ;
			data->texture_count++;
			return ;
		}
	}
}

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
	data->input->parsed_map[row][i] = '\0';
	printf("%s", data->input->parsed_map[row]); // to rm
}

static void	check_middlemap(t_data *data, char *line, size_t j)
{
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
	j = 0;
	if (i > 6)
	{
		data->input->parsed_map[i - 7] = \
		calloc_exit(ft_strlen(line) + 1, sizeof(char));
		save_line(data, line, i - 7);
		if (i == 7 || i == data->input->nb_lines)
		{
			while (newline[j])
			{
				if (newline[j] != 49 && !newline[j])
					err_msg("Invalid map, empty space instead of a wall\n");
				j++;
			}
		}
		else
			check_middlemap(data, newline, j);
	}
	free(newline);
	return (0);
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
				if (!ft_strchr("1NSWE0", data->input->parsed_map[i + 1][j]) ||\
				(i > 0 && !ft_strchr("1NSWE0", data->input->parsed_map[i - 1][j])) ||\
				!ft_strchr("1NSWE0", data->input->parsed_map[i][j + 1]) ||\
				!ft_strchr("1NSWE0", data->input->parsed_map[i][j - 1]))
					err_msg("Invalid map, not closed off by walls\n");
			}
			j++;
		}
		i++;
	}
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
			return (free(line), close(fd), 1); // or exit??
		free(line);
	}
	wall_check(data);
	close(fd);
	is_walkable_path(data);
	parse_spaces(data);
	return (0);
}