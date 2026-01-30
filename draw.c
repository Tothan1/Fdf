/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/30 18:43:15 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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
		printf("step:%d", step);
		value.buffer_img[get_index(x * 40, y * 32, value.size_line)] = 0xFFFF25FF;
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
	int j;
	int i;

	j = 0;

	value.buffer_img = (int *)mlx_get_data_addr(value.img_ptr,
			&value.bits_per_pixel, &value.size_line, &value.endian);
	value.size_line /= 4;
	while (j < (point[0][0].line))
	{
		i = 0;
		while (i < (point[0][0].column - 1))
		{
			value.buffer_img[get_index(i * 40 + point[j][i].x, j * 32
				+ point[j][i].y, value.size_line)] = 0xFFFFFFFF;
			if (i > 0 && j == 0)
				draw_segment(point[j][i - 1], point[j][i], value);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(value.mlx_ptr, value.win_ptr, value.img_ptr, 700,
		500);
}