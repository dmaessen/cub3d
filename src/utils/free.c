#include "../include/cub3d.h"
#include "../include/utils.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void free_struct(t_data *data) // something else to free here??
{
	free(data->textures->no_texture);
	data->textures->no_texture = NULL;
	free(data->textures->so_texture);
	data->textures->so_texture = NULL;
	free(data->textures->we_texture);
	data->textures->we_texture = NULL;
	free(data->textures->ea_texture);
	data->textures->ea_texture = NULL;
	free(data->colors->f_color);
	data->colors->f_color = NULL;
	free(data->colors->c_color);
	data->colors->c_color = NULL;
}
