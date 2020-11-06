/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:48:22 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/06 13:35:09 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"

void	render_player(t_game *game)
{
	t_rect_info	rect;
	
	rect = init_rect_info(g_player.x, g_player.y, 10, 10);
	draw_player_rect(game, &rect, 0x00ff00);
}

void	cast_ray(game, strip_id)
{

}

void	render_rays(t_game *game)
{
	int		strip_id;
	int		ray_angle;

	strip_id = 0;
	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		cast_ray(game, strip_id);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
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