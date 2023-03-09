/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:56:23 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/09 15:44:19 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "so_long.h"

int	read_map(char *file)
{
	int fd;
	int ret;
	char buf[1];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((ret = read(fd, buf, 1)))
	{
		if (buf[0] != '1' && buf[0] != '0' && buf[0] != 'P' && buf[0] != 'E' && buf[0] != 'C' && buf[0] != ' ' && buf[0] != ' ')
			return (0);
	}
	close(fd);
	return (1);
}

void draw_background(t_map *map, void *mlx, void *win)
{
    int x;
    int y;
    void *img;

    y = 0;
    x = 0;
    img = mlx_xpm_file_to_image(map->mlx, "images/floor.xpm", &map->width, &map->height);
    mlx_put_image_to_window(mlx, win, img, y * 64, x * 64);
    if (img == NULL)
    {
        ft_putstr_fd("Error\nCould not load image\n", 2);
        exit(1);
    }

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            mlx_put_image_to_window(mlx, win, img, x * map->width, y * map->height);
            x++;
        }
        y++;
    }
    mlx_destroy_image(map->mlx, img);
}

void draw_game_objects(t_map *map, void *mlx, void *win)
{
    void *img;
    int x;
    int y;

    y = 0;
    x = 0;
    while (x < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == '1')
            {
                img = mlx_xpm_file_to_image(map->mlx, "images/wall.xpm", &map->width, &map->height);
                  mlx_put_image_to_window(mlx, win, img, x * 64, y * 64);
            }
            else if (map->grid[y][x] == 'P')
            {
                img = mlx_xpm_file_to_image(map->mlx, "images/player.xpm", &map->width, &map->height);
                mlx_put_image_to_window(mlx, win, img, x * 64, y * 64);
            }
            else if (map->grid[y][x] == 'E')
            {
                img = mlx_xpm_file_to_image(map->mlx, "images/exit.xpm", &map->width, &map->height);
                mlx_put_image_to_window(mlx, win, img, x * 64, y * 64);
            }
            else
                img = NULL;
            if (img == NULL)
            {
                x++;
                continue;
            }
            //mlx_put_image_to_window(map->mlx, map->win, img, x * map->width, y * map->height);
            mlx_destroy_image(map->mlx, img);
            x++;
        }
        y++;
    }
}

void	draw_map(t_map *map , void *mlx, void *win)
{
    (void)mlx;
    (void)win;
	draw_background(map, map->mlx, map->win);
	draw_game_objects(map, map->mlx, map->win);
}

void	free_map(t_map *map)
{
	t_list	*current;
	t_list	*tmp;

	current = map->current;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->content);
		free(tmp);
	}
	free(map);
}

int create_window(t_map *map)
{
    map->mlx = mlx_init();
    map->win = mlx_new_window(map->mlx, map->width * 64, map->height * 64, "so_long");
    if (!map->win)
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
	t_map *map;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Error\nInvalid map file\n", 2);
		return (1);
	}
	if (!create_window(map))
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		free_map(map);
		return (1);
	}
	draw_map(map, map->mlx, map->win);
	mlx_loop(map->mlx);
	free_map(map);
	return (0);
}
