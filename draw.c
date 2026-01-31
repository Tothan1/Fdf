/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/31 13:15:21 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_segment(t_point point1, t_point point2, t_data value)
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
		value.buffer_img[get_index(x, y, value.size_line)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}
void	draw(t_data value, t_point **point)
{
	int y;
	int x;

	y = 0;

	value.buffer_img = (int *)mlx_get_data_addr(value.img,
			&value.bits_per_pixel, &value.size_line, &value.endian);
	value.size_line /= 4;
	while (y < (point[0][0].line))
	{
		x = 0;
		while (x < (point[0][0].column))
		{
			value.buffer_img[get_index(point[y][x].x,
				point[y][x].y, value.size_line)] = 0xFFFFFFFF;
			if (x > 0)
				draw_segment(point[y][x - 1], point[y][x], value);
			if (y > 0)
				draw_segment(point[y - 1][x], point[y][x], value);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(value.mlx, value.win, value.img, 200, 50);
}