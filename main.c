/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/01 17:09:07 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** init_fractal:
**   Initializes the fractal context with default values.
*/
void	init_fractal(t_fractal *f, int type)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		exit(1);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
	{
		free(f->mlx);
		exit(1);
	}
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
	{
		mlx_destroy_window(f->mlx, f->win);
		free(f->mlx);
		exit(1);
	}
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->max_iter = MAX_ITER;
	f->color_shift = 0;
	f->fractal_type = type;
	f->julia_c.re = -0.4;
	f->julia_c.im = 0.6;
	f->mouse_x = 0;
	f->mouse_y = 0;
}

static int	get_fractal_type(char *arg)
{
	if (!ft_strcmp(arg, "mandelbrot"))
		return (1);
	if (!ft_strcmp(arg, "julia"))
		return (2);
	if (!ft_strcmp(arg, "burning_ship"))
		return (3);
	return (0);
}

static void	setup_hooks(t_fractal *f)
{
	mlx_hook(f->win, KEY_PRESS, KEY_PRESS_MASK, handle_key, f);
	mlx_hook(f->win, BUTTON_PRESS, BUTTON_PRESS_MASK, handle_mouse, f);
	mlx_hook(f->win, MOTION_NOTIFY, POINTER_MOTION_MASK, handle_mouse_move, f);
	mlx_hook(f->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, close_window, f);
}

void	print_usage(void)
{
	write(1, "Usage: ./fractol <fractal_type>\n", 32);
	write(1, "Available fractals:\n", 20);
	write(1, "  mandelbrot\n", 13);
	write(1, "  julia\n", 8);
	write(1, "  burning_ship\n", 15);
	write(1, "\nControls:\n", 11);
	write(1, "  ESC: Exit\n", 12);
	write(1, "  Arrow keys: Move\n", 19);
	write(1, "  Mouse wheel: Zoom\n", 19);
	write(1, "  R: Shift colors\n", 18);
	write(1, "  Mouse move: Change Julia\n", 27);
}

/*
** main:
**   Program entry point.
*/
int	main(int argc, char **argv)
{
	t_fractal	f;
	int			type;

	if (argc != 2)
	{
		print_usage();
		return (1);
	}
	type = get_fractal_type(argv[1]);
	if (!type)
	{
		print_usage();
		return (1);
	}
	init_fractal(&f, type);
	setup_hooks(&f);
	render_fractal(&f);
	mlx_loop(f.mlx);
	return (0);
}
