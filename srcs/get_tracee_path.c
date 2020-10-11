/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tracee_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 15:05:26 by pablo             #+#    #+#             */
/*   Updated: 2020/10/11 15:23:21 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int8_t*         get_tracee_path(int8_t* binary_name)
{
    const int8_t*   env = secure_getenv("PATH");
    int8_t*         prev_path = NULL;
    int8_t*         tracee_path = NULL;

    if (env)
    {
        if (!strncmp(binary_name, "./", 2) || !strncmp(binary_name, "/", 1))
            if (asprintf(&tracee_path, "%s", binary_name) < 0)
                return (NULL); // error to handle
        else
            while (prev_path = strsep(&env, ":"))
                if (asprintf(&tracee_path, "%s%s", prev_path, binary_name))
                    return (NULL); // error to handle
        if (access(tracee_path, F_OK) < 0)
        {
            free(tracee_path);
            return (NULL);
        }
    }
    return (tracee_path);
}