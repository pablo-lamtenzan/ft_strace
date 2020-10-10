/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_db.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:04:08 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/10 21:59:30 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALL_DB_H
# define SYSCALL_DB_H

#include <stdint.h>

typedef enum			e_args_type
{
	NONE,
	INT,
	UINT,
	PTR,
	STR,
	STRUCT
}						t_args_type;

typedef struct			s_sys_data
{
	int8_t const*const		index;
	int8_t					nb_args;
	t_args_type				args[6];
}						sys_data_t;

const sys_data_t      syscall_db(int64_t *index);

#endif