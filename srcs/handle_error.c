/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 10:42:32 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 15:47:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"

uint8_t	handle_gl_err(const char *fn)
{
//	GLenum			err_code;
//
//	if ((err_code = glGetError()) != GL_NO_ERROR)
//	{
		dprintf(2, "OpenGL Error in function %s\n", fn);
//		return (1);
//	}
	return (0);
}
