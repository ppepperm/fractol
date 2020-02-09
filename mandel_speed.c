/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:40:40 by ppepperm          #+#    #+#             */
/*   Updated: 2020/02/02 15:40:42 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"
#include <fcntl.h>
#include <unistd.h>
#include <OpenCL/opencl.h>
#include <math.h>

static void	init_short(t_opencl *o)
{
	o->platform_id = NULL;
	o->device_id = NULL;
	o->ret = clGetPlatformIDs(1, &o->platform_id, &o->ret_num_platforms);
	o->ret = clGetDeviceIDs(o->platform_id, CL_DEVICE_TYPE_CPU, 1,\
	&o->device_id, &o->ret_num_devices);
	o->context = clCreateContext(NULL, 1, &o->device_id, NULL, NULL, &o->ret);
	o->command_queue = clCreateCommandQueue(o->context, o->device_id, 0,\
	&o->ret);
	o->a_mem_obj = clCreateBuffer(o->context, CL_MEM_READ_ONLY,\
	o->array_size * sizeof(cl_double), NULL, &o->ret);
	o->c_mem_obj = clCreateBuffer(o->context, CL_MEM_READ_WRITE,\
	SIZE * SIZE * sizeof(cl_int), NULL, &o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->a_mem_obj, CL_TRUE, 0,\
	o->array_size * sizeof(cl_double), o->data_array, 0, NULL, NULL);
	o->program = clCreateProgramWithSource(o->context, 1,\
	(const char **)&o->source, (const size_t *)&o->f_size, &o->ret);
	o->ret = clBuildProgram(o->program, 1, &o->device_id, NULL, NULL, NULL);
	o->kernel = clCreateKernel(o->program, "calc_mand", &o->ret);
	o->ret = clSetKernelArg(o->kernel, 0, sizeof(cl_mem),\
	(void *)&o->a_mem_obj);
	o->ret = clSetKernelArg(o->kernel, 1, sizeof(cl_mem),\
	(void *)&o->c_mem_obj);
	o->global_item_size = SIZE;
	o->local_item_size = SIZE / 10;
}

static void	free_seq(t_opencl o)
{
	o.ret = clFlush(o.command_queue);
	o.ret = clFinish(o.command_queue);
	o.ret = clReleaseKernel(o.kernel);
	o.ret = clReleaseProgram(o.program);
	o.ret = clReleaseMemObject(o.a_mem_obj);
	o.ret = clReleaseMemObject(o.c_mem_obj);
	o.ret = clReleaseCommandQueue(o.command_queue);
	o.ret = clReleaseContext(o.context);
	free(o.data_array);
	free(o.source);
}

int			get_mand_image(t_mandelbrot mand, int *image)
{
	t_opencl o;

	o.source = (char *)malloc(sizeof(char) * 4096);
	o.fd = open("mand_speed.cl", O_RDWR);
	o.f_size = read(o.fd, o.source, 4096);
	close(o.fd);
	o.array_size = 4;
	o.data_array = (cl_double*)malloc(sizeof(cl_double) * o.array_size);
	o.data_array[0] = 4.0 * mand.zoom / SIZE;
	o.data_array[1] = mand.acc;
	o.data_array[2] = mand.top_left.re;
	o.data_array[3] = mand.top_left.im;
	init_short(&o);
	o.ret = clEnqueueNDRangeKernel(o.command_queue, o.kernel, 1, NULL,\
	&o.global_item_size, &o.local_item_size, 0, NULL, NULL);
	o.ret = clEnqueueReadBuffer(o.command_queue, o.c_mem_obj, CL_TRUE, 0,\
	SIZE * SIZE * sizeof(cl_int), image, 0, NULL, NULL);
	free_seq(o);
	return (0);
}

int		deal_unclick_m(int button, int x, int y, void *param)
{
	t_mandelbrot *mand;

	mand = (t_mandelbrot*)param;
	if (button == 2)
	{
		mand->mouse_press = 0;
	}
	mand->mouse_pos.x = x - SIZE / 2;
	mand->mouse_pos.y = SIZE / 2 - y;
	return (0);
}

int		cls_m(void *param)
{
	t_mandelbrot *kek;

	kek = (t_mandelbrot*)param;
	free_mand(*kek);
	exit(0);
}