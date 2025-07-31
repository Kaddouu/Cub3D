/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/06/16 17:43:59 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	game_loop(t_game *game)
{
	move_player(game);
	ft_raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_struct(&game);
	if (argc != 2 || !argv[1] || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4,
			".cub", 4) != 0)
		error_exit(&game, "Usage: ./cube3d <map.cub>");
	if (open(argv[1], O_RDONLY) < 0)
		error_exit(&game, "Can't open map file");
	if (parse_map(&game, argv[1]) != 0)
		error_exit(&game, "Parsing map");
	if (validate_map(&game.map) != 0)
		error_exit(&game, "Invalid map");
	if (init_mlx(&game) != 0)
		error_exit(&game, "Initializing MLX");
	if (init_textures(&game) != 0)
		error_exit(&game, "Loading textures");
	init_mouse(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
