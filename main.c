/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:30:33 by mgould            #+#    #+#             */
/*   Updated: 2017/04/25 19:50:42 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>
#include <stdio.h>
//remove stdio.h

static void	pathsandroutes(t_game *game)
{
	int		i;
	t_path	*ptmp;

	i = 0;
	while (game->path)
	{
		ptmp = (game->path)->nx;
		free((game->path)->path);
		free((game->path));
		game->path = ptmp;
	}
	if (!(game->routes))
		return ;
	while ((game->routes)[i])
	{
		while ((game->routes)[i])
		{
			ptmp = ((game->routes)[i])->nx;
			free(((game->routes)[i])->path);
			free((game->routes)[i]);
			(game->routes)[i] = ptmp;
		}
		i++;
	}
	free(game->routes);
}

static void	mapandedges(t_game *game, int len)
{
	int i;

	i = 0;
	if (game->map)
	{
		while ((game->map)[i])
		{
			free((game->map)[i]);
			i++;
		}
		free(game->map);
	}
	if (game->edge)
	{
		i = 0;
		while (i <= len)
		{
			free((game->edge)[i]);
			i++;
		}
		free(game->edge);
	}
}

static void	rmsandlsts(t_game *game)
{
	t_lnk	*ltmp;
	t_room	*rtmp;

	while (game->lnlst)
	{
		ltmp = (game->lnlst)->nx;
		free((game->lnlst)->a);
		free((game->lnlst)->b);
		free(game->lnlst);
		game->lnlst = ltmp;
	}
	while (game->rmlst)
	{
		rtmp = (game->rmlst)->nx;
		free((game->rmlst)->nm);
		free((game->rmlst));
		game->rmlst = rtmp;
	}
	if (game->lnlst)
		free(game->lnlst);
	if (game->rmlst)
		free(game->rmlst);
}

static int	freethemalloc(t_game **gamepointer)
{
	int		len;
	t_game	*game;

	len = 0;
	game = *gamepointer;
	if (!(game->rmlst))
	{
		free(game);
		return (0);
	}
	len = (game->rmlst)->id;
	if (!(game->start) || !(game->end))
	{
		rmsandlsts(game);
		free(game);
		return (0);
	}
	rmsandlsts(game);
	mapandedges(game, len);
	pathsandroutes(game);
	if (game->ant)
		antsandcap(game);
	free(game);
	return (0);
}

int			main(void)
{
	t_game	*game;

	game = makegame();
	if (!parseinput(game))
	{
		return (freethemalloc(&game));
	}
	game->map = makemap(game);
	game->edge = makeedge(game);
	if (!routefinder(game))
	{
		ft_putstr("Error\nThere are no valid routes!\n");
		return (freethemalloc(&game));
	}
	routecount(game);
	routecap(game);
	antmarch(game);
	return (freethemalloc(&game));
}
