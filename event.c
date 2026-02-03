/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:21:27 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/03 16:40:08 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>



int	close_window(void *old_mlx)
{
	t_data	*mlx;

	mlx = (t_data *)old_mlx;
	ft_free_all(&(mlx->point));
	ft_free_all(&(mlx->iso));
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window((mlx->mlx), mlx->win);
	mlx_loop_end(mlx->mlx);
	// free(mlx->img);
	// free(mlx->win);
	// free(mlx->mlx);
	exit (2);
}

void	zoom(t_data	*mlx, int nb)
{
	ft_free_all(mlx->point);
	ft_free_all(mlx->iso);
	mlx->iso = NULL;
	mlx->point = NULL;
	mlx->zoom += nb;
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->img.length_win, mlx->img.width_win);
	recover_map(&(*mlx), &(mlx->point));
	recover_map(&(*mlx), &(mlx->iso));
	transform_on_3d(mlx);
	draw(&(*mlx), &mlx->img);
}

int	redirection_event(int key, t_data *mlx)
{
	// int	i = 0;
	// printf("\n%d\n", key);
	// printf("\n%d\n", mlx->zoom);
	// printf("\n%d\n", mlx->zoom);
	if (key == 4 &&( mlx->zoom > 0))
		zoom(mlx, -5);
	else if (key == 5 && mlx->zoom < 200)
		zoom(mlx, +5);
	else if (key == 65307)
		close_window(mlx);
	return (1);
}


