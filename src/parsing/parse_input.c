/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:23 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/31 12:55:38 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // needed?

static void init_data(t_data *data)
{
	data->textures = ft_calloc(1, sizeof(t_textures));
	if (!data->textures)
		err_msg("Calloc failed\n");
	data->textures->no_texture = ft_strdup("");
	if (!data->textures->no_texture)
		err_msg("Malloc failed\n");
	data->textures->so_texture = ft_strdup("");
	if (!data->textures->so_texture)
		err_msg("Malloc failed\n");
	data->textures->we_texture = ft_strdup("");
	if (!data->textures->we_texture)
		err_msg("Malloc failed\n");
	data->textures->ea_texture = ft_strdup("");
	if (!data->textures->ea_texture)
		err_msg("Malloc failed\n");
	data->colors = ft_calloc(1, sizeof(t_colors));
	if (!data->colors)
		err_msg("Calloc failed\n");
	data->colors->c_color_b = -1;
	data->colors->c_color_g = -1;
	data->colors->c_color_r = -1;
	data->colors->f_color_b = -1;
	data->colors->f_color_g = -1;
	data->colors->f_color_r = -1;
}

static void split_colorcode(t_data *data, char *color, int id)
{
	char **color_code;

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

void add_data(t_data *data, char **str, int i)
{
	if (ft_strncmp(str[i], "C", 1) == 0)
		if (str[i+1])
			split_colorcode(data, str[i+1], 1);
	if (ft_strncmp(str[i], "F", 1) == 0)
		if (str[i+1])
			split_colorcode(data, str[i+1], 2);
	if (ft_strncmp(str[i], "NO", 2) == 0)
		data->textures->no_texture = ft_strdup(str[i+1]);
	if (ft_strncmp(str[i], "SO", 2) == 0)
		data->textures->so_texture = ft_strdup(str[i+1]);
	if (ft_strncmp(str[i], "WE", 2) == 0)
		data->textures->we_texture = ft_strdup(str[i+1]);
	if (ft_strncmp(str[i], "EA", 2) == 0)
		data->textures->ea_texture = ft_strdup(str[i+1]);
	if (!data->textures->no_texture || !data->textures->so_texture 
		|| !data->textures->we_texture || !data->textures->ea_texture)
			err_msg("Malloc failed\n");
	// check if the path exists ?
}

int parse_line(t_data *data, char *line)
{
	char **str;
	int i;

	str = ft_split(line, ' ');
	if (!str)
		err_msg("Spliting line\n");
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "NO", 2) == 0 || ft_strncmp(str[i], "SO", 2) == 0 
		|| ft_strncmp(str[i], "WE", 2) == 0 || ft_strncmp(str[i], "EA", 2) == 0
		|| ft_strncmp(str[i], "C", 1) == 0 || ft_strncmp(str[i], "F", 1) == 0)
			add_data(data, str, i);
		i++;
	}
	free_str(str);
	return (0);
}

static int format_validation(char *file)
{
	char	*res;

	if (ft_strnstr(file, ".cub", ft_strlen(file)) == 0)
		return (1);
	res = ft_strnstr(file, ".cub", ft_strlen(file));
	if (ft_strlen(res) == 4)
		return (0);
	return (0);
}

static void validate_colors(t_colors *colors)
{
	if ((colors->c_color_b < 0) || (colors->c_color_b > 255) 
		|| (colors->c_color_r < 0) || (colors->c_color_r > 255) 
		|| (colors->c_color_g < 0) || (colors->c_color_g > 255))
		err_msg("Invalid color code for the ceiling.\n");
	if ((colors->f_color_b < 0) || (colors->f_color_b > 255) 
		|| (colors->f_color_r < 0) || (colors->f_color_r > 255) 
		|| (colors->f_color_g < 0) || (colors->f_color_g > 255))
		err_msg("Invalid color code for the floor.\n");
	if ((colors->f_color_b == colors->c_color_b) 
		&& (colors->f_color_r == colors->c_color_r) 
		&& (colors->f_color_g == colors->c_color_g))
		err_msg("Colors of the floor and ceiling need to be different.\n");
}

static void check_doubles(t_data *data)
{
	if (ft_strcmp(data->textures->no_texture, data->textures->so_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->so_texture))
		err_msg("The textures of NO and SO need to be different.\n");
	if (ft_strcmp(data->textures->no_texture, data->textures->we_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->we_texture))
		err_msg("The textures of NO and WE need to be different.\n");
	if (ft_strcmp(data->textures->no_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->no_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of NO and EA need to be different.\n");
	if (ft_strcmp(data->textures->so_texture, data->textures->we_texture) == 0
	&& ft_strlen(data->textures->so_texture) == ft_strlen(data->textures->we_texture))
		err_msg("The textures of WE and SO need to be different.\n");
	if (ft_strcmp(data->textures->so_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->so_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of SO and EA need to be different.\n");
	if (ft_strcmp(data->textures->we_texture, data->textures->ea_texture) == 0
	&& ft_strlen(data->textures->we_texture) == ft_strlen(data->textures->ea_texture))
		err_msg("The textures of WE and EA need to be different.\n");
}

int input_validation(t_data *data, char *file)
{
	int fd;
	char *line;

	if (format_validation(file) == 1)
		err_msg("Wrong file extension, should be: .cub\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	init_data(data);
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break;
		if (parse_line(data, line) == 1)
			return (free(line), close(fd), 1); // or exit??
		free(line);
	}
	close(fd);
	check_doubles(data);
	validate_colors(data->colors);
	return (0);
}
