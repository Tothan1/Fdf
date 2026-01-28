/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:10:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/01/28 11:49:27 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void close_window()
{

	
}

void redirection_event(int key, t_data)
{
	if(key == 27)
		mlx_destroy_window(.mlx_ptr, .win_ptr)
}

int main (void)
{
	void *mlx_ptr;
	void *win_ptr;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "FDF 42");
	mlx_pixel_put  ( mlx_ptr, win_ptr, 20, 30, 0xFFFF00FF);
	mlx_loop(mlx_ptr);
	mlx_key_hook(win_ptr, ,);
	mlx_mouse_hook(win_ptr, ,);
}