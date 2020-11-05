/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:48:22 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/05 16:03:46 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"

void	render_player(t_game *game)
{
	t_rect_info	rect;
	
	rect = init_rect_info(g_player.x, g_player.y, 10, 10);
	draw_player_rect(game, &rect, 0x00ff00);
}

void	render_rays(t_game *game)
{
	t_line_info line;

	line = init_line_info(
		g_player.x,
		g_player.y,
		g_player.x + cos(g_player.rotation_angle) * 30,
		g_player.y + sin(g_player.rotation_angle) * 30);
	draw_ray(game, &line);

	t_rect_info rect;
	rect = init_rect_info(line.x2, line.y2, 3, 3);
	draw_player_rect(game, &rect, 0x00ff000);
}

void	render_map(t_game *game)
{
	draw_rectangles(game);
	draw_lines(game);
}

void	render(t_game *game)
{
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}