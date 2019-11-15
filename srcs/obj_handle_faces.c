/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle_faces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:18:16 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 16:32:04 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	split_faces(t_parser_obj *parser, uint8_t offset, uint8_t len_data)
{
	int	i;

	i = 0;
	ft_lstaddlast(&parser->faces, ft_lstnew(&parser->garbage[0],
		sizeof(int) * len_data));
	while (i < offset * 2)
	{
		parser->garbage[i + offset] = parser->garbage[i + (2 * offset)];
		i++;
	}
	ft_lstaddlast(&parser->faces, ft_lstnew(&parser->garbage[0],
		sizeof(int) * len_data));
}

uint8_t	sscanf_full(t_parser_obj *parser, char *str)
{
	char	fmt[40];
	int		scanned;

	ft_strncpy(fmt, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 39);
	scanned = sscanf(str, fmt, &parser->garbage[0], &parser->garbage[1],
		&parser->garbage[2],
		&parser->garbage[3], &parser->garbage[4], &parser->garbage[5],
		&parser->garbage[6], &parser->garbage[7], &parser->garbage[8],
		&parser->garbage[9], &parser->garbage[10], &parser->garbage[11]);
	if (scanned == 9)
	{
		ft_lstaddlast(&parser->faces, ft_lstnew(&parser->garbage[0],
			sizeof(int) * 9));
		return (3);
	}
	else if (scanned == 12)
	{
		split_faces(parser, 3, 9);
		return (6);
	}
	return (print_parser_error(PARSING_NB_FACES));
}

uint8_t	sscanf_partial(t_parser_obj *parser, char *str, char *fmt)
{
	int		scanned;

	scanned = sscanf(str, fmt, &parser->garbage[0], &parser->garbage[1],
		&parser->garbage[2],
		&parser->garbage[3], &parser->garbage[4], &parser->garbage[5],
		&parser->garbage[6], &parser->garbage[7], &parser->garbage[8]);
	if (scanned == 6)
	{
		ft_lstaddlast(&parser->faces, ft_lstnew(&parser->garbage[0],
			sizeof(int) * 6));
		return (3);
	}
	else if (scanned == 8)
	{
		split_faces(parser, 2, 6);
		return (6);
	}
	return (print_parser_error(PARSING_NB_FACES));
}

uint8_t	sscanf_basic(t_parser_obj *parser, char *str, char *fmt)
{
	int		scanned;

	scanned = sscanf(str, fmt, &parser->garbage[0], &parser->garbage[1],
		&parser->garbage[2], &parser->garbage[3]);
	if (scanned == 3)
	{
		ft_lstaddlast(&parser->faces, ft_lstnew(&parser->garbage[0],
			sizeof(int) * 3));
		return (3);
	}
	else if (scanned == 4)
	{
		split_faces(parser, 1, 3);
		return (6);
	}
	return (print_parser_error(PARSING_NB_FACES));
}

uint8_t	handle_faces(t_parser_obj *parser, char *str)
{
	int	nb_faces;

	nb_faces = 0;
	if (parser->len_vertices && parser->len_normals
		&& parser->len_textures)
		nb_faces = (sscanf_full(parser, str));
	else if (parser->len_vertices && parser->len_normals)
		nb_faces = (sscanf_partial(parser, str,
			"f %d//%d %d//%d %d//%d %d//%d\n"));
	else if (parser->len_vertices && parser->len_textures)
		nb_faces = (sscanf_partial(parser, str, "f %d/%d %d/%d %d/%d %d/%d\n"));
	else if (parser->len_vertices)
		nb_faces = (sscanf_basic(parser, str, "f %d %d %d %d\n"));
	if (!nb_faces)
		return (0);
	parser->len_faces += nb_faces;
	return (1);
}
