/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 18:25:47 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

fill_struct_point(int i, t_point **point)
{
		point[i] = malloc(sizeof(t_point *) * (line + 1));

}
void	**recover_map(char **av)
{
	t_point **point;
	int collumn;
	int line;
	int fd;
	int i;
	char **split;

	i = 0;
	collumn = 1;
	line = 0;
	fd = open(av[1], O_RDONLY);
	split = ft_split (get_next_line(fd), ' ');
	while( split[line]!= NULL)
		line++;
	point = malloc(sizeof(t_point *) * (line + 1));
	while (i < line)
		fill_struct_point(i, point);
	// while (get_neinet_line(fd) != NULL)
	// 	collumn++;
	printf("collumn:%d\n", collumn);
	printf("line:%d\n", line);
}

int close_window(void * valu)
{
	t_data *value;

	value = (t_data*)valu;
	mlx_destroy_window((value->mlx_ptr), value->win_ptr);
	mlx_loop_end(value->mlx_ptr);
	return (1);
}

int redirection_event(int key, void * valu)
{
	if(key == 65307)
		close_window(valu);
	return (1);
}

int main (int ac, char **av)
{
	t_data value;
	t_point **point;
	if(ac == 2)
	{
		point = recover_map(av);
		value.mlx_ptr = mlx_init();
		value.win_ptr = mlx_new_window(value.mlx_ptr, 1920, 1080, "FDF 42");
		mlx_pixel_put  ( value.mlx_ptr, value.win_ptr, 20, 30, 0xFFFF00FF);
		mlx_key_hook(value.win_ptr, redirection_event, &value);
		mlx_hook(value.win_ptr, 17, 0, close_window, &value);
		mlx_loop(value.mlx_ptr);
	}
}