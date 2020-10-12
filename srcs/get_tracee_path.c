/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tracee_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 15:05:26 by pablo             #+#    #+#             */
/*   Updated: 2020/10/12 21:17:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ft_error.h>

char*         get_tracee_path(char* binary_name)
{
    char*       env = secure_getenv("PATH");
    char*       prev_path = NULL;
    char*       tracee_path = NULL;

    if (env)
    {
        if (!strncmp(binary_name, "./", 2) || !strncmp(binary_name, "/", 1))
        {
            if (asprintf(&tracee_path, "%s", binary_name) < 0)
                return (ptr_error_exit("Error: asprintf returned error"));
        }
        else
            while ((prev_path = strsep(&env, ":")))
            {
                dprintf(2, "PREV PATH IS %s\n", prev_path);
                dprintf(2, "DEBUG PATH %s\n", tracee_path);
                if (asprintf(&tracee_path, "%s%s%s", prev_path, "/", binary_name) < 0)
                    return (ptr_error_exit("Error: asprintf returned error"));
            }
        if (access(tracee_path, F_OK) < 0)
        {
            dprintf(2, "DEBUG PATH %s\n", tracee_path);
            free(tracee_path);
            return (NULL);
        }
    }
    dprintf(2, "DEBUG PATH %s\n", tracee_path);
    return (tracee_path);
}