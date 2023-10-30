#include "../include/cub3d.h"
#include "../include/utils.h"
#include <unistd.h>

void	err_msg(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit (1);
}
