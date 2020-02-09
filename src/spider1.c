/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:05:33 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/05 15:05:35 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_spider1(t_mandelbrot mand)
{
	get_spider1_image(mand, mand.img_data);
	mlx_put_image_to_window(mand.mlx_ptr, mand.win_ptr, mand.img_ptr, 0, 0);
}

void	do_spider1(void)
{
	t_mandelbrot mand;

	mand.x_size = SIZE;
	mand.y_size = SIZE;
	mand.endian = 1;
	mand.bpp = 32;
	mand.line_size = SIZE * 4;
	mand.mlx_ptr = mlx_init();
	mand.win_ptr = mlx_new_window(mand.mlx_ptr, SIZE, SIZE, "fractol");
	mand.img_ptr = mlx_new_image(mand.mlx_ptr, mand.x_size, mand.y_size);
	mand.img_data = (int*)mlx_get_data_addr(mand.img_ptr, &(mand.bpp),\
	&(mand.line_size), &(mand.endian));
	mand.zoom = 1;
	mand.acc = 100;
	mand.top_left = init_complex(-2, -2);
	mand.mouse_press = 0;
	draw_spider1(mand);
	mlx_hook(mand.win_ptr, 2, 1L << 0, deal_key_s1, (void*)&mand);
	mlx_hook(mand.win_ptr, 4, 0L, deal_click_s1, (void*)&mand);
	mlx_hook(mand.win_ptr, 5, 0L, deal_unclick_s1, (void*)&mand);
	mlx_hook(mand.win_ptr, 6, 0L, deal_mish_s1, (void*)&mand);
	mlx_hook(mand.win_ptr, 17, 0L, cls_m, (void*)&mand);
	mlx_loop(mand.mlx_ptr);
}

int		deal_key_s1(int key, void *param)
{
	t_mandelbrot *mand;

	mand = (t_mandelbrot*)param;
	zoom_s(mand, key);
	move_s(mand, key);
	if (key == 27)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->acc -= 5;
		draw_spider1(*mand);
	}
	if (key == 53 || key == 65307)
	{
		free_mand(*mand);
		exit(0);
	}
	return (0);
}

int		deal_click_s1(int button, int x, int y, void *param)
{
	t_mandelbrot *mand;

	mand = (t_mandelbrot*)param;
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE)
	{
		if (button == 4)
		{
			mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
			mand->zoom *= 0.95;
			mand->top_left.re += (4 * mand->zoom / 0.95 - 4 * mand->zoom) / 2;
			mand->top_left.im += (4 * mand->zoom / 0.95 - 4 * mand->zoom) / 2;
			draw_spider1(*mand);
		}
		if (button == 5)
		{
			mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
			mand->zoom /= 0.95;
			mand->top_left.re += (4 * mand->zoom * 0.95 - 4 * mand->zoom) / 2;
			mand->top_left.im += (4 * mand->zoom * 0.95 - 4 * mand->zoom) / 2;
			draw_spider1(*mand);
		}
		mouse_press_s(mand, button, x, y);
	}
	return (0);
}

int		deal_mish_s1(int x, int y, void *param)
{
	t_mandelbrot *mand;

	mand = (t_mandelbrot*)param;
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE)
	{
		if (mand->mouse_press)
			mouse_move_s(mand, x, y);
		mand->mouse_pos.x = x - SIZE / 2;
		mand->mouse_pos.y = SIZE / 2 - y;
	}
	return (0);
}
