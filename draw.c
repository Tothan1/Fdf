/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/07 11:00:59 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
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
		if(x >= 0 && x <= (*img)->length && y >= 0 && y <= (*img)->width)
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
		while (x < value->point[y]->column)
		{
			if (x > 0)
				draw_segment(value->point[y][x - 1], value->point[y][x], &img);
			if (y > 0)
				draw_segment(value->point[y - 1][x], value->point[y][x], &img);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(value->mlx, value->win, img->img, 0, 0);

}
