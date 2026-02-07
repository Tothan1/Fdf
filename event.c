/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:21:27 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/07 11:06:24 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	close_window(void *old_mlx)
{
	t_data	*mlx;

	mlx = (t_data *)old_mlx;
	if(mlx->point != NULL)
		ft_free_all(mlx->point);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window((mlx->mlx), mlx->win);
	mlx_loop_end(mlx->mlx);
	// free(mlx->img.img);
	// free(mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(2);
}

void	zoom_or_height_or_discrepancy(t_data *mlx, int nb, char var)
{
	if (var == 'z')
		mlx->zoom += nb;
	if (var == 'h')
		mlx->height += nb;
	if (var == 'd')
		mlx->discrepancy += nb;
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->img.length,
		mlx->img.width);
	if(mlx->point != NULL)
		ft_free_all(mlx->point);
	recover_map(&(*mlx), &(*mlx).point);
	transform_on_3d(&(*mlx));
	draw(&(*mlx), &mlx->img);
}

void	redirection_event2(int key, int x, int y, t_data *mlx)
{
	(void)x;
	(void)y;
	if (key == 4)
		zoom_or_height_or_discrepancy(mlx, -5, 'z');
	else if (key == 5)
		zoom_or_height_or_discrepancy(mlx, +5, 'z');
}

void	redirection_event(int key, t_data *mlx)
{
	// int	i = 0;
	// printf("\n%d\n", key);
	// printf("\n%d\n", mlx->zoom);
	
	if (key == 65362)
		zoom_or_height_or_discrepancy(mlx, +5, 'h');
	else if (key == 65364)
		zoom_or_height_or_discrepancy(mlx, -5, 'h');
	else if (key == 65363)
		zoom_or_height_or_discrepancy(mlx, +5, 'd');
	else if (key == 65361)
		zoom_or_height_or_discrepancy(mlx, -5, 'd');
	else if (key == 65307)
		close_window(mlx);
}
