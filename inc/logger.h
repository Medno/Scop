/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:14:47 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:16:23 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include <stdio.h>

FILE	*g_logger;

void	init_logger(void);
void	quit_logger(void);

void	log_msg(const char *msg);

#endif
