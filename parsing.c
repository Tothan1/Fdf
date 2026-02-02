/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/02 11:31:14 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	fill_struct_point(int j, int line, t_point **point, int fd)
{
	char	**split;
	char *buffer;
	int		collumn;
	int		i;

	i = 0;
	collumn = 0;
	buffer = get_next_line(fd);
	split = ft_split(buffer, ' ');
	while (split[collumn] != NULL)
		collumn++;
	point[j] = malloc(sizeof(t_point) * collumn);
	while (i < collumn)
	{
		point[j][i].x = i * 50;
		point[j][i].y = j * 50;
		point[j][i].z = ft_atoi (split[i]);
		point[j][i].column = collumn;
		point[j][i].line = line;
		point[j][i].index_point = get_index(i, j, collumn);
		i++;
	}
	ft_free_tab(split);
	free (buffer);
	return(j + 1);
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
	close(fd);
	return (point);
}

int	close_window(void *valu)
{
	t_data	*mlx;

	mlx = (t_data *)valu;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window((mlx->mlx), mlx->win);
	mlx_loop_end(mlx->mlx);
	// free(mlx->img);
	// free(mlx->win);
	// free(mlx->mlx);
	return (1);
}

int	redirection_event(int key, void *valu)
{
	if (key == 65307)
		close_window(valu);
	return (1);
}
t_point ** transform_on_3d(t_point ** point, t_data mlx)
{
	int j = 0;
	int i;
	// double a = 120;
	int tmp;
	t_point ** isométrique;
	isométrique = point;
	while(j < point[0][0].line)
	{
		i = 0;
		while(i < point[0][0].column)
		{
			tmp = isométrique[j][i].x;
			isométrique[j][i].x = (tmp - isométrique[j][i].y) * cos(0.523599) + (mlx.length_win / 2);
			isométrique[j][i].y = (tmp + isométrique[j][i].y) * sin(0.523599) - isométrique[j][i].z + (mlx.width_win * 0.1);
			printf("tab[%d][%d]  y:%d x:%d z:%d column: %d line: %d index_point:%d\n", j, i, isométrique[j][i].y, isométrique[j][i].x, isométrique[j][i].z, isométrique[j][i].column, isométrique[j][i].line, isométrique[j][i].index_point);
			i++;
		}
		j++;
	}
	return (isométrique);
}

int	main(int ac, char **av)
{
	t_data mlx;
	t_point **point;
	t_point **isométrique;
	if (ac == 2)
	{
		mlx.length_win = 1920;
		mlx.width_win = 1080;
		point = recover_map(av);
		isométrique = transform_on_3d(point, mlx);
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, mlx.length_win, mlx.width_win, "FDF 42");
		mlx.img = mlx_new_image(mlx.mlx, mlx.length_win, mlx.width_win);
		draw(mlx, isométrique);
		// ft_free_tab(point);
		// ft_free_tab(isométrique);
		mlx_key_hook(mlx.win, redirection_event, &mlx);
		mlx_hook(mlx.win, 17, 0, close_window, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
		return (2);
}