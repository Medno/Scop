/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:32 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/05 11:37:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "vec3.h"
# include "read_file.h"
# include "errno.h"
# include <string.h>

enum	e_face_type
{
	V_1,
	V_2,
	V_3
};

typedef struct	s_parse_obj
{
	t_vec3				*vertices;
	t_vec3				*vertices_normal;
	t_vec3				*vertices_texture;
	int					*indices;
	enum e_face_type	face_type;
	size_t				len_vertices;
	size_t				len_vertices_normal;
	size_t				len_vertices_texture;
	size_t				len_faces;
	size_t				index_vertices;
	size_t				index_vertices_normal;
	size_t				index_vertices_texture;
	long				obj_size;
}				t_parse_obj;

enum	e_token_obj
{
	VERTEX,
	TEXTURE,
	N_VERTEX,
	FACES,
	NAME,
	GROUP,
	MATERIAL,
	COMMENT
};

enum	e_error_parser
{
	ARRAY_VERTICES,
	ARRAY_VERTICES_NORMAL,
	ARRAY_VERTICES_TEXTURE,
	ARRAY_ALL_DATA,
	ARRAY_INDICES,
	PARSING_NO_NEWLINE,
	PARSING_NB_FACES,
	PARSING_MISSING_SPACE
};

uint8_t	check_float(const char *str, float *fl);

void	init_parse_obj(t_parse_obj *parser);
uint8_t	create_vertices_arrays(t_parse_obj *parse);
uint8_t	print_parser_error(e_error_parser error);

void	print_parser_data(t_parse_obj *parser);

#endif
