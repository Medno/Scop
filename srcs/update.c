/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:15:37 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 17:15:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

uint8_t	update_monitor(t_monitor monitor)
{
	SDL_Event	e;

	SDL_GL_SwapWindow(monitor.win);
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			return (1);
	return (0);
}
