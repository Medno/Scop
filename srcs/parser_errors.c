/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:22:17 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 16:22:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t			print_parser_error(t_error_parser error)
{
	char	buf[256];

	if (error == ARRAY_VERTICES)
		strcpy(buf, "Error: Cannot allocate memory for array of vertices");
	else if (error == ARRAY_VERTICES_NORMAL)
		strcpy(buf,
				"Error: Cannot allocate memory for array of normal vertices");
	else if (error == ARRAY_VERTICES_TEXTURE)
		strcpy(buf,
				"Error: Cannot allocate memory for array of texture vertices");
	else if (error == ARRAY_ALL_DATA)
		strcpy(buf,
			"Error: Cannot allocate memory for the array sent to OpenGL");
	else if (error == ARRAY_INDICES)
		strcpy(buf, "Error: Cannot allocate memory for the array of indices");
	else if (error == PARSING_NO_NEWLINE)
		strcpy(buf, "Error: Missing newline in obj file");
	else if (error == PARSING_NB_FACES)
		strcpy(buf, "Error: Parser: Invalid number of faces");
	else if (error == PARSING_WRONG_FORMAT)
		strcpy(buf, "Error: Parser: Wrong format");
	else if (error == PARSING_INDEX_OUT_OF_BOUND)
		strcpy(buf, "Error: Parser: Index out of bound");
	return ((uint8_t)print_error(buf, NULL));
}
