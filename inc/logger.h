/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:46:20 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 18:54:56 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

#include <stdio.h>

FILE	*logger;

void	init_logger(void);
void	quit_logger(void);

void	log_msg(const char *msg);

#endif
