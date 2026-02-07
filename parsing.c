/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/07 16:43:27 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fill_struct_point(int j, t_data *mlx, t_point ****point)
{
	char	**split;
	char	*buffer;
	int		i;

	i = 0;
	mlx->column = 0;
	buffer = get_next_line(mlx->fd);
	split = ft_split(buffer, ' ');
	free(buffer);
	while (split[mlx->column] != NULL)
		mlx->column++;
	(**point)[j] = malloc(sizeof(t_point) * mlx->column);
	if (!(**point)[j])
		close_window(&(*mlx));
	while (i < mlx->column)
	{
		(**point)[j][i].x = i * mlx->zoom;
		(**point)[j][i].y = j * mlx->zoom;
		(**point)[j][i].z = ft_atoi(split[i]) * mlx->height;
		(**point)[j][i].index_point = get_index(i, j, mlx->column);
		i++;
	}
	(**point)[j]->column = mlx->column;
	ft_free_tab(split);
	return (j + 1);
}

void	recover_map(t_data *mlx, t_point ***point)
{
	int		i;
	char	*buffer;

	mlx->line = 0;
	mlx->fd = open(mlx->av, O_RDONLY);
	buffer = get_next_line(mlx->fd);
	while (buffer != NULL)
	{
		mlx->line++;
		free(buffer);
		buffer = get_next_line(mlx->fd);
	}
	free(buffer);
	close(mlx->fd);
	mlx->fd = open(mlx->av, O_RDONLY);
	(*point) = malloc(sizeof(t_point *) * (mlx->line + 1));
	if (!(*point))
		close_window(&(*mlx));
	i = 0;
	while (i < mlx->line)
		i = fill_struct_point(i, mlx, &point);
	buffer = get_next_line(mlx->fd);
	free(buffer);
	(*point)[i] = NULL;
	close(mlx->fd);
}

void	transform_on_3d(t_data *mlx)
{
	int	j;
	int	i;
	int	tmp;

	j = 0;
	while (j < mlx->line)
	{
		i = 0;
		while (i < mlx->point[j]->column)
		{
			tmp = mlx->point[j][i].x;
			mlx->point[j][i].x = (tmp - mlx->point[j][i].y) * cos(0.523599)
				+ (mlx->img.length / 2) + mlx->discrepancy;
			mlx->point[j][i].y = (tmp + mlx->point[j][i].y) * sin(0.523599)
				- mlx->point[j][i].z + (mlx->img.width * 0.1);
			i++;
		}
		j++;
	}
}

void	initialise_struct_mlx(t_data *mlx, char **av)
{
	mlx->av = av[1];
	mlx->zoom = 40;
	mlx->height = 10;
	mlx->discrepancy = 0;
	mlx->img.length = 1920;
	mlx->img.width = 1080;
	mlx->mlx = mlx_init();
	mlx->point = NULL;
	mlx->win = mlx_new_window(mlx->mlx, mlx->img.length, mlx->img.width, "42");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->img.length, mlx->img.width);
}

int	main(int ac, char **av)
{
	t_data	mlx;
	int		tmp_fd;

	if (ac == 2)
	{
		tmp_fd = open(av[1], O_RDONLY);
		if (tmp_fd == -1)
			return (2);
		close(tmp_fd);
		initialise_struct_mlx(&mlx, av);
		recover_map(&mlx, &mlx.point);
		transform_on_3d(&mlx);
		draw(&mlx, &mlx.img);
		mlx_key_hook(mlx.win, redirection_event, &mlx);
		mlx_mouse_hook(mlx.win, redirection_event2, &mlx);
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
// 		printf("tab[%d][%d]  y:%d x:%d z:%d index_point:%d\n", j, i,
// mlx.point[j][i].y, mlx.point[j][i].x, mlx.point[j][i].z,
// 			mlx.point[j][i].index_point);
// 		i++;
// 	}
// 	printf("\n\n");
// 	j++;
// }