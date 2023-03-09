/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:14 by sgomez-p          #+#    #+#             */
/*   Updated: 2023/03/09 15:17:08 by sgomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
//#include "minilibx-linux/mlx.h"
//#include <X11/X.h>
//#include <X11/keysym.h>
#include <mlx.h>

# define TILE_SIZE 32


typedef struct	t_map
{
	int		y;
	int		x;
	int		width;
	int		height;
	char	**grid; 
	void	*mlx;
	void	*win;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*exit_img;
	t_list	*current;
}				t_map;

int		read_map(char *file);
t_map	*parse_map(char *file_path);
void	free_map(t_map *map);
int is_valid_map(t_map *map);
int is_uniform_map(char **map, int rows, int cols);

#endif
