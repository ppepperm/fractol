/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:27:23 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/09 17:27:24 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_press_s(t_mandelbrot *mand, int button, int x, int y)
{
	if (button == 1)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.re += (x - SIZE / 2) * (4 * mand->zoom / SIZE);
		mand->top_left.im -= (SIZE / 2 - y) * (4 * mand->zoom / SIZE);
		draw_spider1(*mand);
	}
	if (button == 2)
	{
		mand->mouse_press = 1;
	}
}

void	mouse_move_s(t_mandelbrot *mand, int x, int y)
{
	if (mand->mouse_pos.x < x - SIZE / 2)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.re -= (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (mand->mouse_pos.x > x - SIZE / 2)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.re += (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (mand->mouse_pos.y < SIZE / 2 - y)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.im += (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (mand->mouse_pos.x > SIZE / 2 - y)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.im -= (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
}

void	zoom_s(t_mandelbrot *mand, int key)
{
	if (key == 15)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->zoom *= 0.95;
		mand->top_left.re += (4 * mand->zoom / 0.95 - 4 * mand->zoom) / 2;
		mand->top_left.im += (4 * mand->zoom / 0.95 - 4 * mand->zoom) / 2;
		draw_spider1(*mand);
	}
	if (key == 3)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->zoom /= 0.95;
		mand->top_left.re += (4 * mand->zoom * 0.95 - 4 * mand->zoom) / 2;
		mand->top_left.im += (4 * mand->zoom * 0.95 - 4 * mand->zoom) / 2;
		draw_spider1(*mand);
	}
	if (key == 24)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->acc += 5;
		draw_spider1(*mand);
	}
}

void	move_s(t_mandelbrot *mand, int key)
{
	if (key == 13)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.im += (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (key == 1)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.im -= (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (key == 0)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.re += (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
	if (key == 2)
	{
		mlx_clear_window(mand->mlx_ptr, mand->win_ptr);
		mand->top_left.re -= (0.01 * mand->zoom);
		draw_spider1(*mand);
	}
}
