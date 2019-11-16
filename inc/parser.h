/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:32 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 15:51:05 by pchadeni         ###   ########.fr       */
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
	t_vec3	*vertices;
	size_t	len_vertices;
	size_t	index_vertices;
	t_vec3	*normals;
	size_t	len_normals;
	size_t	index_normals;
	t_vec3	*textures;
	size_t	len_textures;
	size_t	index_textures;
	t_list	*faces;
	size_t	len_faces;
	size_t	index_indices;
	long	obj_size;
	uint8_t	offset_data;
	uint8_t	offset_data_normal;
	size_t	data_size;
	float	*data;
	int		garbage[12];
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
	PARSING_WRONG_FORMAT,
	PARSING_INDEX_OUT_OF_BOUND
}				t_error_parser;

t_parser_obj	*parse_obj_file(const char *obj_name);

uint8_t			check_float(const char *str, float *fl);

t_parser_obj	*init_parser_obj(void);
uint8_t			create_vertices_arrays(t_parser_obj *parse);
uint8_t			destroy_parser_obj(t_parser_obj **parse, uint8_t all);
void			clean_parser(t_parser_obj *parser);

uint8_t			add_faces_into_data(t_parser_obj *parser);
uint8_t			handle_faces(t_parser_obj *parser, char *str);

uint8_t			get_vertices_values(char *data, t_parser_obj *parse);

void			center_vertices(t_vec3 *vertices, size_t len);

void			print_parser_data(t_parser_obj *parser);
uint8_t			print_parser_error(t_error_parser error);

#endif
