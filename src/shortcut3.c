/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:37:02 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/09 16:37:04 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	mouse_move_sh(t_ship *ship, int x, int y)
{
	if (ship->mouse_pos.x < x - SIZE / 2)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (ship->mouse_pos.x > x - SIZE / 2)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (ship->mouse_pos.y < SIZE / 2 - y)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (ship->mouse_pos.x > SIZE / 2 - y)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
}

void	mouse_press_sh(t_ship *ship, int button, int x, int y)
{
	if (button == 1)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re += (x - SIZE / 2) * (4 * ship->zoom / SIZE);
		ship->top_left.im -= (SIZE / 2 - y) * (4 * ship->zoom / SIZE);
		draw_ship(*ship);
	}
	if (button == 2)
		ship->mouse_press = 1;
}

void	zoom_sh(t_ship *ship, int key)
{
	if (key == 15)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->zoom *= 0.95;
		ship->top_left.re += (4 * ship->zoom / 0.95 - 4 * ship->zoom) / 2;
		ship->top_left.im += (4 * ship->zoom / 0.95 - 4 * ship->zoom) / 2;
		draw_ship(*ship);
	}
	if (key == 3)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->zoom /= 0.95;
		ship->top_left.re += (4 * ship->zoom * 0.95 - 4 * ship->zoom) / 2;
		ship->top_left.im += (4 * ship->zoom * 0.95 - 4 * ship->zoom) / 2;
		draw_ship(*ship);
	}
	if (key == 24)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->acc += 5;
		draw_ship(*ship);
	}
}

void	move_sh(t_ship *ship, int key)
{
	if (key == 13)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 1)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.im -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 0)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re += (0.01 * ship->zoom);
		draw_ship(*ship);
	}
	if (key == 2)
	{
		mlx_clear_window(ship->mlx_ptr, ship->win_ptr);
		ship->top_left.re -= (0.01 * ship->zoom);
		draw_ship(*ship);
	}
}
