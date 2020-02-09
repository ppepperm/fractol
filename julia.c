/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:31:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/07 13:31:43 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_julia(t_julia julia)
{
	get_julia_image(julia, (int*)julia.img_data);
	mlx_put_image_to_window(julia.mlx_ptr, julia.win_ptr, julia.img_ptr, 0, 0);
}

void	do_julia(void)
{
	t_julia		julia;

	julia.x_size = SIZE;
	julia.y_size = SIZE;
	julia.endian = 1;
	julia.bpp = 32;
	julia.line_size = SIZE * 4;
	julia.c = init_complex(0 - 0.74543, 0.11301);
	julia.mlx_ptr = mlx_init();
	julia.win_ptr = mlx_new_window(julia.mlx_ptr, SIZE, SIZE, "fractol");
	julia.img_ptr = mlx_new_image(julia.mlx_ptr, julia.x_size, julia.y_size);
	julia.img_data = (int*)mlx_get_data_addr(julia.img_ptr,\
	&(julia.bpp), &(julia.line_size), &(julia.endian));
	julia.zoom = 1;
	julia.acc = 100;
	julia.top_left = init_complex(-2, -2);
	julia.mouse_press = 0;
	draw_julia(julia);
	mlx_hook(julia.win_ptr, 2, 1L << 0, deal_key, (void*)&julia);
	mlx_hook(julia.win_ptr, 4, 0L, deal_click, (void*)&julia);
	mlx_hook(julia.win_ptr, 5, 0L, deal_unclick, (void*)&julia);
	mlx_hook(julia.win_ptr, 6, 0L, deal_mish, (void*)&julia);
	mlx_hook(julia.win_ptr, 17, 0L, cls, (void*)&julia);
	mlx_loop(julia.mlx_ptr);
}

int		deal_key(int key, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	change_c(julia, key);
	zoom_j(julia, key);
	move_j(julia, key);
	if (key == 27)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->acc -= 5;
		draw_julia(*julia);
	}
	if (key == 36)
	{
		if (julia->mouse_stop)
			julia->mouse_stop = 0;
		else
			julia->mouse_stop = 1;
	}
	if (key == 53 || key == 65307)
	{
		free_julia(*julia);
		exit(0);
	}
	return (0);
}

int		deal_click(int button, int x, int y, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE)
	{
		if (button == 4)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->zoom *= 0.95;
			julia->top_left.re += (julia->zoom / 0.95 - julia->zoom) * 2;
			julia->top_left.im += (julia->zoom / 0.95 - julia->zoom) * 2;
			draw_julia(*julia);
		}
		if (button == 5)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->zoom /= 0.95;
			julia->top_left.re += (julia->zoom * 0.95 - julia->zoom) * 2;
			julia->top_left.im += (julia->zoom * 0.95 - julia->zoom) * 2;
			draw_julia(*julia);
		}
		press_j(julia, button, x, y);
	}
	return (0);
}

int		deal_mish(int x, int y, void *param)
{
	t_julia *julia;

	julia = (t_julia*)param;
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE)
	{
		if (!julia->mouse_stop)
			change_c_m(julia, x, y);
		if (julia->mouse_stop && julia->mouse_press)
			mouse_move_j(julia, x, y);
		julia->mouse_pos.x = x - SIZE / 2;
		julia->mouse_pos.y = SIZE / 2 - y;
	}
	return (0);
}
