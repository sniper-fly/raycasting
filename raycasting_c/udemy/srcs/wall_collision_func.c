/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:12:30 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/06 13:39:06 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"

int		has_wall_at(float x, float y)
{
	int	map_grid_idx_x;
	int	map_grid_idx_y;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (TRUE);
	map_grid_idx_x = floor(x / TILE_SIZE);
	map_grid_idx_y = floor(y / TILE_SIZE);
	return (g_map[map_grid_idx_y][map_grid_idx_x] == 1);
}
