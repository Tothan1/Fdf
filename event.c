/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:21:27 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/04 16:25:41 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>



int	close_window(void *old_mlx)
{
	t_data	*mlx;

	mlx = (t_data *)old_mlx;
	ft_free_all(*(mlx->point));
	// ft_free_all(*(mlx->iso));
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window((mlx->mlx), mlx->win);
	mlx_loop_end(mlx->mlx);
	// free(mlx->img);
	// free(mlx->win);
	// free(mlx->mlx);
	exit (2);
}

void all_process(t_data mlx)
{
	recover_map(&mlx, &mlx.point);
	recover_map(&mlx, &mlx.iso);
	transform_on_3d(&mlx);
	draw(&mlx, &mlx.img);
}

void	zoom_or_height(t_data	*mlx, int nb, char var)
{
	// ft_free_all(mlx->point);
	// ft_free_all(mlx->iso);
	mlx->iso = NULL;
	mlx->point = NULL;
	if(var == 'z')
		mlx->zoom += nb;
	if(var == 'h')
		mlx->height += nb;
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->img.length_win, mlx->img.width_win);
	all_process(*mlx);
}


int	check_height(t_data *mlx, int nb)
{
	int i;
	int tmp;
	int tmp2;
	int j = 0;

	while (j < mlx->line)
	{
		i = 0;
		while (i < mlx->column)
		{
			if(mlx->height != 0)
				tmp2 = mlx->point[j][i].z / mlx->height;
			else
				tmp2 = mlx->point[j][i].z;
			tmp = mlx->point[j][i].x;
			mlx->iso[j][i].x = (tmp - mlx->point[j][i].y) * cos(0.523599)
				+ (mlx->img.length_win / 2);
			mlx->iso[j][i].y = (tmp + mlx->point[j][i].y) * sin(0.523599)
				- (tmp2 * (mlx-> height +nb)) + (mlx->img.width_win * 0.1);
			if(mlx->iso[j][i].x < 0 || mlx->iso[j][i].x > mlx->img.length_win|| mlx->iso[j][i].y < 0 || mlx->iso[j][i].y > mlx->img.width_win )
					return (0);
			i++;
		}
		j++;
	}
	return(1);
}
void	redirection_event2(int key, int x, int y, t_data *mlx)
{
	(void)x;
	(void)y;


	if (key == 4 && mlx->zoom > 0)
		zoom_or_height(mlx, -5, 'z');
	else if (key == 5 && mlx->zoom < 200)
		zoom_or_height(mlx, +5, 'z');
}

void	redirection_event(int key, t_data *mlx)
{
	// int	i = 0;
	// printf("\n%d\n", key);
	// printf("\n%d\n", mlx->zoom);
	// printf("\n%d\n", key);

	
	if (key == 65362 && check_height(mlx, 5))
		zoom_or_height(mlx, +5, 'h');
	else if (key == 65364 && check_height(mlx, -5))
		zoom_or_height(mlx, -5, 'h');
	else if (key == 65307)
		close_window(mlx);
}

