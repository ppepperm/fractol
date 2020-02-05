/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:18:27 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/05 15:18:29 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void free_mand(t_mandelbrot mand)
{
	mlx_destroy_image(mand.mlx_ptr, mand.img_ptr);
	mlx_destroy_window(mand.mlx_ptr, mand.win_ptr);
	free(mand.mlx_ptr);
}

void free_julia(t_julia mand)
{
	mlx_destroy_image(mand.mlx_ptr, mand.img_ptr);
	mlx_destroy_window(mand.mlx_ptr, mand.win_ptr);
	free(mand.mlx_ptr);
}

void free_ship(t_ship mand)
{
	mlx_destroy_image(mand.mlx_ptr, mand.img_ptr);
	mlx_destroy_window(mand.mlx_ptr, mand.win_ptr);
	free(mand.mlx_ptr);
}