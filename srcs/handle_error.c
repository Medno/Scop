/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 10:42:32 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 17:07:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"

uint8_t	handle_gl_err(const char *fn)
{
	dprintf(2, "OpenGL Error in function %s\n", fn);
	return (0);
}

void	*print_error(const char *msg, const char *filename)
{
	if (filename)
		dprintf(2, "%s%s\n", msg, filename);
	else
		dprintf(2, "%s\n", msg);
	return (NULL);
}
