/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/01 15:50:15 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	fill_struct_point(int j, int line, t_point **point, int fd)
{
	char	**split;
	int		collumn;
	int		i;

	i = 0;
	collumn = 0;
	split = ft_split(get_next_line(fd), ' ');
	while (split[collumn] != NULL)
		collumn++;
	point[j] = malloc(sizeof(t_point) * collumn);
	while (i < collumn)
	{
		point[j][i].x = i * 30;
		point[j][i].y = j * 30;
		point[j][i].z = ft_atoi (split[i]);
		point[j][i].column = collumn;
		point[j][i].line = line;
		point[j][i].index_point = get_index(i, j, collumn);
		// printf("tab[%d][%d]  y:%d x:%d z:%d column: %d line: %d index_point:%d\n", j, i, point[j][i].y, point[j][i].x, point[j][i].z, point[j][i].column, point[j][i].line, point[j][i].index_point);
		i++;
	}
	ft_free_tab(split);
	// printf ("\n\n");
	// point[j][i].index_point = 0;
	j++;
	return(j);
}
t_point	**recover_map(char **av)
{
	t_point	**point;
	int		line;
	int		fd;
	int		i;

	line = 0;
	fd = open(av[1], O_RDONLY);
	while ((get_next_line(fd)) != NULL)
		line++;
	close(fd);
	fd = open(av[1], O_RDONLY);
	point = malloc(sizeof(t_point *) * (line + 1));
	i = 0;
	while (i < line)
		i = fill_struct_point(i, line, point, fd);
	point[i] = NULL;
	// printf("tab[2][0] x:%d y:%d\n", point[2][0].x, point[2][0].y);
	close(fd);
	return (point);
}

int	close_window(void *valu)
{
	t_data	*value;

	value = (t_data *)valu;
	mlx_destroy_image(value->mlx, value->img);
	mlx_destroy_window((value->mlx), value->win);
	mlx_loop_end(value->mlx);
	// free(value->img);
	// free(value->win);
	// free(value->mlx);
	return (1);
}

int	redirection_event(int key, void *valu)
{
	if (key == 65307)
		close_window(valu);
	return (1);
}
t_point ** transform_on_3d(t_point ** point)
{
	int j = 0;
	int i;
	// int a = 120;
	int tmp;
	t_point ** isométrique;
	isométrique = point;
	while(j < point[0][0].line)
	{
		i = 0;
		while(i < point[0][0].column)
		{
			// isométrique[j][i].x = point[j][i].x + cos(a) * (point[j][i].z * -1) ;
			// isométrique[j][i].y = point[j][i].y + sin(a) * (point[j][i].z * -1);
			tmp = isométrique[j][i].x;
			isométrique[j][i].x = (tmp - isométrique[j][i].y) * cos(0.523599);
			isométrique[j][i].y = (tmp + isométrique[j][i].y) * sin(0.523599) - isométrique[j][i].z;
			printf("tab[%d][%d]  y:%d x:%d z:%d column: %d line: %d index_point:%d\n", j, i, isométrique[j][i].y, isométrique[j][i].x, isométrique[j][i].z, isométrique[j][i].column, isométrique[j][i].line, isométrique[j][i].index_point);
			i++;
		}
	printf ("\n\n");
		j++;
	}
	return (isométrique);
}

int	main(int ac, char **av)
{
	t_data value;
	t_point **point;
	t_point **isométrique;
	if (ac == 2)
	{
		point = recover_map(av);
		isométrique = transform_on_3d(point);
		value.mlx = mlx_init();
		value.win = mlx_new_window(value.mlx, 1280, 720, "FDF 42");
		value.img = mlx_new_image(value.mlx, 1280, 720);
		draw(value, isométrique);
		// ft_free_tab(point);
		// ft_free_tab(isométrique);
		mlx_key_hook(value.win, redirection_event, &value);
		mlx_hook(value.win, 17, 0, close_window, &value);
		mlx_loop(value.mlx);
		mlx_loop_end(value.mlx);
	}
}