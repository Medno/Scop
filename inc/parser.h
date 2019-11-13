/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:32 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 13:03:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "libft.h"
# include "vec3.h"
# include "read_file.h"
# include "handle_error.h"
# include <errno.h>
# include <string.h>

typedef struct	s_parser_obj
{
	t_vec3				*vertices;
	t_vec3				*vertices_normal;
	t_vec3				*vertices_texture;
	int					*indices;
	size_t				len_vertices;
	size_t				len_vertices_normal;
	size_t				len_vertices_texture;
	size_t				len_faces;
	size_t				index_vertices;
	size_t				index_vertices_normal;
	size_t				index_vertices_texture;
	size_t				index_indices;
	long				obj_size;
	uint8_t				offset_all_data;
	uint8_t				offset_all_data_normal;
	size_t				all_data_size;
	float				*all_data;
}				t_parser_obj;

typedef enum	e_token_obj
{
	VERTEX,
	TEXTURE,
	NORMAL,
	FACES,
	NAME,
	GROUP,
	MATERIAL,
	COMMENT
}				t_token_obj;

typedef enum	e_error_parser
{
	ARRAY_VERTICES,
	ARRAY_VERTICES_NORMAL,
	ARRAY_VERTICES_TEXTURE,
	ARRAY_ALL_DATA,
	ARRAY_INDICES,
	PARSING_NO_NEWLINE,
	PARSING_NB_FACES,
	PARSING_MISSING_SPACE,
	PARSING_INDEX_OUT_OF_BOUND
}				t_error_parser;

t_parser_obj	*parse_obj_file(const char *obj_name);

uint8_t			check_float(const char *str, float *fl);

t_parser_obj	*init_parser_obj(void);
uint8_t			create_vertices_arrays(t_parser_obj *parse);
uint8_t			destroy_parser_obj(t_parser_obj *parse, uint8_t all);
void			clean_parser(t_parser_obj *parser);
uint8_t			print_parser_error(t_error_parser error);

uint8_t			get_length_arrays_obj(char *data, t_parser_obj *parse);
uint8_t			get_vertices_values(char *data, t_parser_obj *parse);

uint8_t			count_faces(char *str);

uint8_t			init_indices_triplet
(t_parser_obj *parse, char *data, int len, int split);
void			center_vertices(t_parser_obj *parser);

void			print_parser_data(t_parser_obj *parser);

#endif
