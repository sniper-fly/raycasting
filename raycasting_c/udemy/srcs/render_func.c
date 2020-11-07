/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:48:22 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/07 12:44:02 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"

void	render_player(t_game *game)
{
	t_rect_info	rect;
	
	rect = init_rect_info(g_player.x, g_player.y, 10, 10);
	draw_player_rect(game, &rect, 0x00ff00);
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, TWO_PI);
	if (ray_angle < 0)
	{
		ray_angle = TWO_PI + ray_angle;
	}
	return (ray_angle);
}

void	cast_ray(t_game *game, float ray_angle, int strip_id)
{
	t_cast_ray_var	hrz;
	t_cast_ray_var	vrt;

	ray_angle = normalize_angle(ray_angle);
	hrz.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	hrz.is_ray_facing_up = !hrz.is_ray_facing_down;
	hrz.is_ray_facing_right = ray_angle < 0.5 * PI && ray_angle > 1.5 * PI;
	hrz.is_ray_facing_left = !hrz.is_ray_facing_right;

    // Find the y-coordinate of the closest horizontal grid intersection
    hrz.yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
    hrz.yintercept += hrz.is_ray_facing_down ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (mapHasWallAt(xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
}

void	render_rays(t_game *game)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		cast_ray(game, ray_angle, strip_id);
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