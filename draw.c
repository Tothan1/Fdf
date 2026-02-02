/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/02 16:00:28 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}
void	draw_segment(t_point point1, t_point point2, t_data  *value)
{
	int i, step;
	float dx, dy, x, y;
	dx = point2.x - point1.x;
	dy = point2.y - point1.y;

	if (dx >= dy)
		step = dx;
	else
		step = dy;
	dx = dx / step;
	dy = dy / step;
	x = point1.x;
	y = point1.y;
	i = 1;
	while (i <= step)
	{
		value->buffer_img[get_index(x, y, value->size_line)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw(t_data *value)
{
	int y;
	int x;

	y = 0;
	value->buffer_img = (int *)mlx_get_data_addr(value->img,
			&value->bits_per_pixel, &value->size_line, &value->endian);
	value->size_line /= 4;
	while (y < (value->line))
	{
		x = 0;
		while (x < (value->column))
		{
			// value->buffer_img[get_index(value->iso[y][x].x,
				// value->iso[y][x].y, value->size_line)] = 0xFFFFFFFF;
			if (x > 0)
				draw_segment(value->iso[y][x - 1], value->iso[y][x], value);
			if (y > 0)
				draw_segment(value->iso[y - 1][x], value->iso[y][x], value);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(value->mlx, value->win, value->img, 0, 0);
}
