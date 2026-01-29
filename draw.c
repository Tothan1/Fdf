/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/29 18:41:43 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

draw_segment (int x1, int y1, int x2, int y2)
{
	int i, step;
	float dx, dy, x, y;
	dx=abs(x2-x1);
	dy=abs(y2-y1);

	if(dx>=dy)
		step = dx;
	else
		step=dy;

	dx=dx/step;
	dy=dy/step;

	x=x1;
	y=y1;

	i=1;
	
	while(i<=step)
	{
		buffer[get_index(x, y, value.size_line)] = 0xFFFFFFFF;
		x=x+dx;
		y=y+dy;
		i++;
	}
}


int get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}
void	draw(t_data value, t_point **point)
{
	int j;
	int i;
	
	j = 0;

	int * buffer = (int *)mlx_get_data_addr(value.img_ptr, &value.bits_per_pixel, &value.size_line, &value.endian);
	value.size_line /=4;
	while(j < (point[0][0].line))
	{
		i = 0;
		while (i < (point[0][0].column -1 ))
		{
			buffer[get_index(900 + i * 10 + point[j][i].x, 500+ j * 8 + point[j][i].y, value.size_line)] = 0xFFFFFFFF; 
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(value.mlx_ptr, value.win_ptr, value.img_ptr, 0, 0);
	}