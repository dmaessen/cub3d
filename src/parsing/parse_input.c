#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // needed?

static void init_data(t_data *data)
{
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
	data->colors->f_color = ft_strdup("");
	if (!data->colors->f_color)
		err_msg("Malloc failed\n");
	data->colors->c_color = ft_strdup("");
	if (!data->colors->c_color)
		err_msg("Malloc failed\n");
}

void add_data(t_data *data, char **str, int i)
{
	if (ft_strncmp(str[i], "C", 1) == 0 || ft_strncmp(str[i], "F", 1) == 0)
	{
		printf("str[i] == %s // str[i+1] == %s // i == %d\n", str[i], str[i + 1], i); // to rm
		// whats the prefered format here for int or char ?
		// perf atoi on it, 3 nb needed seperated with columns and spaces, check if between 0 and 255
	}
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

static void check_doubles(t_data *data)
{
	if (ft_strcmp(data->colors->f_color, data->colors->c_color) == 0 
		&& ft_strlen(data->colors->f_color) == ft_strlen(data->colors->c_color))
		err_msg("The colors for the floor and ceiling need to be different.\n");
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
	return (0);
}
