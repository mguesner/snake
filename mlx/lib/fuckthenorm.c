/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuckthenorm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguezell <nguezell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 17:14:44 by nguezell          #+#    #+#             */
/*   Updated: 2015/01/21 17:15:24 by nguezell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "easylibx.h"

int		mouse_motion(int x, int y, void *e)
{
	mouse_event(x, y, e);
	return (1);
}
