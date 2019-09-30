/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:48:20 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 18:53:48 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

void	init_logger(void)
{
	if (!(logger = fopen("./.log", "w")))
		return;
}

void	quit_logger(void)
{
	fclose(logger);
}

void	log_msg(const char *msg)
{
	fprintf(logger, "%s", msg);
}
