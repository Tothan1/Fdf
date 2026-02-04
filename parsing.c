/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/04 11:54:37 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int	fill_struct_point(int j, t_data *mlx, t_point **** point)
{
	char	**split;
	char	*buffer;
	int		i;

	i = 0;
	mlx->column = 0;
	buffer = get_next_line(mlx->fd);
	split = ft_split(buffer, ' ');
	while (split[mlx->column] != NULL)
		mlx->column++;
	(**point)[j] = malloc(sizeof(t_point) * mlx->column);
	// if(!(*point[j]))
		// close_window( mlx);
	while (i < mlx->column)
	{
		(**point)[j][i].x = i * mlx->zoom;
		(**point)[j][i].y = j * mlx->zoom;
		(**point)[j][i].z = ft_atoi(split[i]) * 10;
		(**point)[j][i].index_point = get_index(i, j, mlx->column);
			printf("tab[%d][%d]  y:%d x:%d z:%d index_point:%d\n", j, i, (**point)[j][i].x, (**point)[j][i].y, (**point)[j][i].z, (**point)[j][i].index_point);
		i++;
	}
	printf("\n\n");
	ft_free_all(split);
	free(buffer);
	return (j + 1);
}
void	recover_map(t_data *mlx, t_point ***point)
{
	int	i;

	mlx->line = 0;
	mlx->fd = open(mlx->av, O_RDONLY);
	while ((get_next_line(mlx->fd)) != NULL)
		mlx->line++;
	close(mlx->fd);
	mlx->fd = open(mlx->av, O_RDONLY);
	(*point) = malloc(sizeof(t_point *) * (mlx->line + 1));
	// if(!mlx->point)
		// close_window(mlx);
	i = 0;
	while (i < mlx->line)
		i = fill_struct_point(i, mlx, &point);
	(*point)[i] = NULL;
	close(mlx->fd);
}


void	transform_on_3d(t_data *mlx)
{
	int	j;
	int	i;
	int	tmp;

	j = 0;
		// printf("\n----------------------------------------ISO--------------------------\n");
	while (j < mlx->line)
	{
		i = 0;
		while (i < mlx->column)
		{
			tmp = mlx->iso[j][i].x;
			mlx->iso[j][i].x = (tmp - mlx->iso[j][i].y) * cos(0.523599)
				+ (mlx->img.length_win / 2);
			mlx->iso[j][i].y = (tmp + mlx->iso[j][i].y) * sin(0.523599)
				- mlx->iso[j][i].z + (mlx->img.width_win * 0.1);
			// printf("tab[%d][%d]  y:%d x:%d z:%d index_point:%d\n", j, i,
				// mlx->iso[j][i].y, mlx->iso[j][i].x, mlx->iso[j][i].z,
				// mlx->iso[j][i].index_point);
			i++;
		}
		// printf("\n\n");
		j++;
	}
}



int	main(int ac, char **av)
{
	t_data	mlx;
	if (ac == 2)
	{
		mlx.av = av[1];
		mlx.zoom = 40;
		mlx.img.length_win = 1920;
		mlx.img.width_win = 1080;
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, mlx.img.length_win, mlx.img.width_win,
			"FDF 42");
		mlx.img.img = mlx_new_image(mlx.mlx, mlx.img.length_win, mlx.img.width_win);

		recover_map(&mlx, &mlx.point);
		recover_map(&mlx, &mlx.iso);
		transform_on_3d(&mlx);
		draw(&mlx, &mlx.img);
		mlx_key_hook(mlx.win, redirection_event, &mlx);
		mlx_hook(mlx.win, 4, 0, zoom, &mlx);
		// mlx_mouse_hook(mlx.win, redirection_event, &mlx);
		mlx_hook(mlx.win, 17, 0, close_window, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
	return (2);
}



// 	printf("\n-------------------POINT-----------------------\n");
// 	while (j < mlx.line)
// {
// 	i = 0;
// 	while (i < mlx.column)
// 	{
// 		printf("tab[%d][%d]  y:%d x:%d z:%d index_point:%d\n", j, i, mlx.point[j][i].y, mlx.point[j][i].x, mlx.point[j][i].z,
// 			mlx.point[j][i].index_point);
// 		i++;
// 	}
// 	printf("\n\n");
// 	j++;
// }