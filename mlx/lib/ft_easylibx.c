/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_easylibx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguesner <mguesner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 17:12:05 by nguezell          #+#    #+#             */
/*   Updated: 2015/03/05 17:57:21 by mguesner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "easylibx.h"

int		expose_hook(void *e)
{
	expose_event(e);
	return (1);
}

int		redraw(void *e)
{
	redraw_event(e);
	return (1);
}

int		key_hook(int keycode, void *e)
{
	keyboard_event(keycode, e);
	return (1);
}

int		mouse_press(int code, int x, int y, void *e)
{
	click_event(code, x, y, e);
	return (1);
}

void	ft_handle_loop(void *win, void *mlx, void *param, int full)
{
	mlx_hook(win, 2, (1L << 0), key_hook, param);
	if (full)
	{
		mlx_hook(win, 4, (1L << 2), mouse_press, param);
		mlx_hook(win, 6, (1L << 6), mouse_motion, param);
	}
	mlx_loop_hook(mlx, redraw, param);
	mlx_expose_hook(win, expose_hook, param);
}
