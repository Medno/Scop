/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:48:20 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 14:28:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

void	init_logger(void)
{
	if (!(g_logger = fopen("./.log", "w")))
		return ;
}

void	quit_logger(void)
{
	fclose(g_logger);
}

void	log_msg(const char *msg)
{
	fprintf(g_logger, "%s", msg);
}


