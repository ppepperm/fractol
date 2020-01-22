/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    Robert_E_O_Speedwagon.cl                           :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+             */
/*   Created: 2020/01/22 14:31:32 by ppepperm          #+#    #+#               */
/*    Updated: 2020/01/22 14:31:35 by ppepperm         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

int check(float z_im, float z_re, float c_im, float c_re, float r, int max_iter)
{
	float res_re;
	float res_im;
	float abs;
	int i;

	i = 1;
	while (i <= max_iter)
	{
		res_re = z_re * z_re - z_im * z_im;
		res_im = z_re * z_im + z_re * z_im;
		res_re += c_re;
		res_im += c_im;
		abs = sqrt(res_re * res_re + res_im * res_im);
		if (abs > r)
		{
			return ((i + 20) * 256 * 256  + 10* 256 * 256);
		}
		z_re = res_re;
		z_im = res_im;
		i++;
	}
	return (0);
}

__kernel void calc_julia(__global const float *data, __global int *image)
{
	// Get the index of the current element to be processed
	//Robert E. O. Speedwagon is the greatest hero of our time
	int i = get_global_id(0);
	int k = 0;
	int max_iter;
	float z_re;
	float z_im;
	float c_im;
	float c_re;
	float inc;
	float r;


	inc = data[0];
	c_re = data[1];
	c_im = data[2];
	max_iter = data[3];
	r = data[4];
	z_re = -2;
	z_im = -2 + i * inc;
	while (k < 800)
	{
		image[k + i * 800] = check(z_im, z_re, c_im, c_re, r, max_iter);
		k++;
		z_re += inc;
	}
}

/*__kernel void calc_julia(__global const float *data, __global int *image)
{

	// Get the index of the current element to be processed
	int i = get_global_id(0);
	int k = 0;
	int j = 0;
	int max_iter;
	float abs;
	float z_re;
	float z_im;
	float res_re;
	float res_im;
	float c_re;
	float c_im;
	float inc;
	float r;


	inc = data[0];
	c_re = data[1];
	c_im = data[2];
	max_iter = data[3];
	r = data[4];
	z_re = -2;
	z_im = -2 + i * inc;
	res_re = z_re;
	res_im = z_im;
	while (k < 800)
	{
		z_re += k * inc;
		res_re = z_re;
		res_im = z_im;
		j = 1;
		while (j < max_iter)
		{
			res_re = res_re * res_re - res_re * res_im + c_re;
			res_im = res_re * res_im + res_re * res_im + c_re;
			abs = sqrt(res_re * res_re + res_im * res_im);
			if (abs > r)
			{
				image[k + i * 800] = 100;
				break ;
			}
			j++;
		}
		j = 0;
		image[k + i * 800] = 100;
		k++;
	}
}*/