/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/14 17:24:56 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_data(t_data *data)
{
	data->textures = calloc_exit(1, sizeof(t_textures));
	data->textures->no_texture = ft_strdup("-1");
	if (!data->textures->no_texture)
		err_msg("Malloc failed\n");
	data->textures->so_texture = ft_strdup("-1");
	if (!data->textures->so_texture)
		err_msg("Malloc failed\n");
	data->textures->we_texture = ft_strdup("-1");
	if (!data->textures->we_texture)
		err_msg("Malloc failed\n");
	data->textures->ea_texture = ft_strdup("-1");
	if (!data->textures->ea_texture)
		err_msg("Malloc failed\n");
	data->colors = calloc_exit(1, sizeof(t_colors));
	data->colors->c_color_b = -1;
	data->colors->c_color_g = -1;
	data->colors->c_color_r = -1;
	data->colors->f_color_b = -1;
	data->colors->f_color_g = -1;
	data->colors->f_color_r = -1;
	data->input = calloc_exit(1, sizeof(t_data_input));
}

static void	split_colorcode(t_data *data, char *color, int id)
{
	char	**color_code;

	color_code = ft_split(color, ',');
	if (!color_code)
		err_msg("Split failed\n");
	if (id == 1)
	{
		if (color_code[0])
			data->colors->c_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->c_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->c_color_r = ft_atoi(color_code[2]);
	}
	if (id == 2)
	{
		if (color_code[0])
			data->colors->f_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->f_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->f_color_r = ft_atoi(color_code[2]);
	}
	free_str(color_code);
}

void	add_data(t_data *data, char **str, int i)
{
	if (ft_strncmp(str[i], "NO", 2) == 0 && str[i + 1])
	{
		data->textures->no_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->no_texture);
	}
	if (ft_strncmp(str[i], "SO", 2) == 0 && str[i + 1])
	{
		data->textures->so_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->so_texture);
	}
	if (ft_strncmp(str[i], "WE", 2) == 0 && str[i + 1])
	{
		data->textures->we_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->we_texture);
	}
	if (ft_strncmp(str[i], "EA", 2) == 0 && str[i + 1])
	{
		data->textures->ea_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->ea_texture);
	}
	if (!data->textures->no_texture || !data->textures->so_texture
		|| !data->textures->we_texture || !data->textures->ea_texture)
		err_msg("Malloc failed\n");
}

int	parse_line(t_data *data, char *line)
{
	char	**str;
	int		i;

	str = ft_split(line, ' ');
	if (!str)
		err_msg("Spliting line\n");
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "NO", 2) == 0
			|| ft_strncmp(str[i], "SO", 2) == 0
			|| ft_strncmp(str[i], "WE", 2) == 0
			|| ft_strncmp(str[i], "EA", 2) == 0)
			add_data(data, str, i);
		else if (ft_strncmp(str[i], "C", 1) == 0 && str[i + 1])
			split_colorcode(data, str[i + 1], 1);
		else if (ft_strncmp(str[i], "F", 1) == 0 && str[i + 1])
			split_colorcode(data, str[i + 1], 2);
		i++;
	}
	free_str(str);
	return (0);
}

int	input_validation(t_data *data, char *file)
{
	int		fd;
	char	*line;

	if (format_validation(file) == 1)
		err_msg("Wrong file extension, should be: .cub\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	init_data(data);
	data->input->nb_lines = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n\0") != 0)
			data->input->nb_lines++;
		if (parse_line(data, line) == 1)
			return (free(line), close(fd), 1);
		free(line);
	}
	close(fd);
	check_doubles(data->textures);
	validate_colors(data->colors);
	return (0);
}
