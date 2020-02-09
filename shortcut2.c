/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:54:46 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/09 15:54:48 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void mouse_move_j (t_julia *julia, int x, int y)
{
	if (julia->mouse_stop && julia->mouse_press)
	{
		if (julia->mouse_pos.x < x - SIZE / 2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.re -= (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > x - SIZE / 2)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.re += (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.y < SIZE / 2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.im += (0.01 * julia->zoom);
			draw_julia(*julia);
		}
		if (julia->mouse_pos.x > SIZE / 2 - y)
		{
			mlx_clear_window(julia->mlx_ptr, julia->win_ptr);
			julia->top_left.im -= (0.01 * julia->zoom);
			draw_julia(*julia);
		}
	}
}
