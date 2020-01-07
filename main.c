/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:07:15 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 15:07:17 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	deal_key(int key, void *param)
{
	char *kek;

	kek = (char*) param;
	if (key == 53 || key == 65307)
	{
		exit(0);
	}
	return (0);
}

int	cls(void *param)
{
	char *kek;

	kek = (char*) param;
	exit(0);
}

int	main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_complex	c;
	t_complex   z;
	int			colour;

	z.re = -2;
	c = init_complex(0 - 0.74543, 0.11301);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fractol");
	mlx_pixel_put(mlx_ptr, win_ptr, 10, 10, 255);
	while (z.re <= 2)
	{
		z.im = -2;
		while (z.im <= 2)
		{
			colour = (check_if_julia(c, 200, z));
			mlx_pixel_put(mlx_ptr, win_ptr, z.re * 250 + 500, z.im * 250 + 500, colour * 20);
			z.im += 0.0005;
		}
		z.re += 0.0005;
	}
	mlx_hook(win_ptr, 2, 1L << 0, deal_key, (void*) mlx_ptr);
	mlx_hook(win_ptr, 17, 0L, cls, (void*) mlx_ptr);
	mlx_loop(mlx_ptr);
	return (0);

}
