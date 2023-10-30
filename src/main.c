#include "../include/cub3d.h"
#include "../include/utils.h"
#include <stdio.h> // to rm ??

int main(int argc, char **argv)
{
	//mlx_t *mlx;
	t_data data;

	if (argc != 2)
		err_msg("Invalid number of arguments.\n");
	if (input_validation(&data, argv[1]) == 0)
	{
		printf("valid input\n"); // to rm
		//if (map_validation())
			// debating if need to check if the path to textures are valid
			// meaning the map is valid
			// so mlx can be initalized
	}
	// something to free??
	free_struct(&data); 
	return (0);
}