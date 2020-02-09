/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:34:26 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/09 15:34:27 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_c(t_julia *julia, int key)
{
	if (key == 65362 || key == 126)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65364 || key == 125)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65361 || key == 123)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 65363 || key == 124)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
}

void	move_j(t_julia *julia, int key)
{
	if (key == 13)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.im += (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 1)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.im -= (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 0)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re += (0.01 * julia->zoom);
		draw_julia(*julia);
	}
	if (key == 2)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re -= (0.01 * julia->zoom);
		draw_julia(*julia);
	}
}

void	zoom_j(t_julia *julia, int key)
{
	if (key == 15)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom *= 0.95;
		julia->top_left.re += (4 * julia->zoom / 0.95 - 4 * julia->zoom) / 2;
		julia->top_left.im += (4 * julia->zoom / 0.95 - 4 * julia->zoom) / 2;
		draw_julia(*julia);
	}
	if (key == 3)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->zoom /= 0.95;
		julia->top_left.re += (4 * julia->zoom * 0.95 - 4 * julia->zoom) / 2;
		julia->top_left.im += (4 * julia->zoom * 0.95 - 4 * julia->zoom) / 2;
		draw_julia(*julia);
	}
	if (key == 24)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->acc += 5;
		draw_julia(*julia);
	}
}

void	press_j(t_julia *julia, int button, int x, int y)
{
	if (button == 1)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->top_left.re += (x - SIZE / 2) * (4 * julia->zoom / SIZE);
		julia->top_left.im -= (SIZE / 2 - y) * (4 * julia->zoom / SIZE);
		draw_julia(*julia);
	}
	if (button == 2)
		julia->mouse_press = 1;
}

void	change_c_m(t_julia *julia, int x, int y)
{
	if (julia->mouse_pos.x < x - SIZE / 2)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (julia->mouse_pos.x > x - SIZE / 2)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.re -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (julia->mouse_pos.y < SIZE / 2 - y)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im += (0.001 * julia->zoom);
		draw_julia(*julia);
	}
	if (julia->mouse_pos.x > SIZE / 2 - y)
	{
		mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
		julia->c.im -= (0.001 * julia->zoom);
		draw_julia(*julia);
	}
}
