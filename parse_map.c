//#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"

#define BUFFER_SIZE 1000000

char	**ft_create_map(char *buffer);

int	main(int ac, char **av)
{
	char	buffer[BUFFER_SIZE];
	int		fd;
	ssize_t	bytes_read;
	const char *map_path = "./maps/map.ber";
	int	i;
	char **map;
	int	window_width;
	int	window_height;
	int counter;

	fd = open(map_path, O_RDONLY);
	if (fd == -1) 
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	bytes_read = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (bytes_read == -1) 
		{
		perror("Error reading file");
		close(fd);
		exit(EXIT_FAILURE);
   		}
	}
	/* i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '0')
			printf("render floor\n");
		if (buffer[i] == '1')
			printf("render wall\n");
		if (buffer[i] == 'C')
			printf("render collectible\n");
		if (buffer[i] == 'E')
			printf("render exit\n");
		if (buffer[i] == 'P')
			printf("render player\n");
		i++;
	} */
	map = ft_split(buffer, '\n');
	i = 0;
	window_height = 0;
	while (map[i] != NULL)
	{
		window_height++;
		i++;
	}

	window_width = ft_strlen(map[0]);

	if (close(fd) == -1) 
	{
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}

	return (0);
}

char	**ft_create_map(t_data data, char *buffer)
{
	int		i;
	char	**map;
	int		window_height;

	map = ft_split(buffer, '\n');
	return (map);
}