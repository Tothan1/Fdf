/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/04 19:43:23 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}


int	check_point(t_data *mlx)
{
	int i;
	int j = 0;

	while (j < mlx->line)
	{
		i = 0;
		while (i < mlx->column)
		{
			if(mlx->iso[j][i].x < 0 || mlx->iso[j][i].x > mlx->img.length_win|| mlx->iso[j][i].y < 0 || mlx->iso[j][i].y > mlx->img.width_win )
				return (0);
			i++;
		}
		j++;
	}
	return(1);
}
void	draw_segment(t_point point1, t_point point2, t_img  **img)
{
	int i, step;
	float dx, dy, x, y;
	dx = point2.x - point1.x;
	dy = point2.y - point1.y;

		step = fmax(fabs(dx), fabs(dy));
	dx = dx / step;
	dy = dy / step;
	x = point1.x;
	y = point1.y;
	i = 0;
	while (i <= step)
	{
		(*img)->buffer_img[get_index(x, y, (*img)->size_line)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw(t_data *value, t_img *img)
{
	int y;
	int x;

	y = 0;
	img->buffer_img = (int *)mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	img->size_line /= 4;
	while (y < (value->line))
	{
		x = 0;
		while (x < (value->column))
		{
			// img->buffer_img[get_index(value->iso[y][x].x,
				// value->iso[y][x].y, img->size_line)] = 0xFFFFFFFF;
			if (x > 0)
				draw_segment(value->iso[y][x - 1], value->iso[y][x], &img);
			if (y > 0)
				draw_segment(value->iso[y - 1][x], value->iso[y][x], &img);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(value->mlx, value->win, img->img, 0, 0);
	ft_free_all(value->old_point);
	value->old_point = value->point;
	ft_free_all(value->point);
	ft_free_all(value->iso);
}
