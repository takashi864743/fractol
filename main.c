/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/05 14:39:55 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_fractol_type(char *arg)
{
	if (!ft_strcmp(arg, "mandelbrot"))
		return (1);
	if (!ft_strcmp(arg, "julia"))
		return (2);
	if (!ft_strcmp(arg, "burning_ship"))
		return (3);
	return (0);
}

static void	setup_hooks(t_fractol *f)
{
	mlx_hook(f->win, KEY_PRESS, KEY_PRESS_MASK, handle_key, f);
	mlx_hook(f->win, BUTTON_PRESS, BUTTON_PRESS_MASK, handle_mouse, f);
	mlx_hook(f->win, MOTION_NOTIFY, POINTER_MOTION_MASK, handle_mouse_move, f);
	mlx_hook(f->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, close_window, f);
}

/*
** main:
**   Program entry point.
*/
int	main(int argc, char **argv)
{
	t_fractol	f;
	int			type;

	if (argc != 2)
	{
		print_usage();
		return (1);
	}
	type = get_fractol_type(argv[1]);
	if (!type)
	{
		print_usage();
		return (1);
	}
	init_fractol(&f, type);
	setup_hooks(&f);
	render_fractol(&f);
	mlx_loop(f.mlx);
	return (0);
}
