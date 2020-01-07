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

int check_if_julia(t_complex c, int max_iter, t_complex z)
{
	float r;
	t_complex result;
	int i;

	r = (1.0 + sqrt(1 + 4 * c.abs))/2.0;
	i = 1;
	while (i <= max_iter)
	{
		result = comp_multiply(z, z);
		result = comp_sum(result, c);
		if (result.abs > r)
			return (i * 256);
		z = init_complex(result.re, result.im);
		i++;
	}
	return (0);
}
