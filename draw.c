/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/07 15:02:48 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

void	draw_segment(t_point point1, t_point point2, t_img **img, int step)
{
	int		i;
	float	dx;
	float	dy;
	float	x;
	float	y;

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
		if (x >= 0 && x <= (*img)->length && y >= 0 && y <= (*img)->width)
			(*img)->buffer_img[get_index(x, y, (*img)->size_line)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw(t_data *val, t_img *img)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	img->buffer_img = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	img->size_line /= 4;
	while (y < (val->line))
	{
		x = 0;
		while (x < val->point[y]->column)
		{
			if (x > 0)
				draw_segment(val->point[y][x - 1], val->point[y][x], &img, i);
			if (y > 0)
				draw_segment(val->point[y - 1][x], val->point[y][x], &img, i);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(val->mlx, val->win, img->img, 0, 0);
}
