/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easylibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguesner <mguesner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 08:30:27 by nguezell          #+#    #+#             */
/*   Updated: 2015/03/02 16:57:43 by mguesner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_handle_loop(void *win, void* mlx, void *param, int full);
void	mouse_event(int x, int y, void *e);
void	expose_event(void *e);
void	redraw_event(void *e);
void	keyboard_event(int keycode, void *e);
void	click_event(int code, int x, int y, void *e);
int		mouse_motion(int x, int y, void *e);



#endif
