/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:22:22 by pablo             #+#    #+#             */
/*   Updated: 2020/10/12 19:00:30 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool        error_exit(char *msg)
{
    dprintf(STDERR_FILENO, "%s\n", msg);
    exit(EXIT_FAILURE);
    return (false);
}

void        *ptr_error_exit(char *msg)
{
    dprintf(STDERR_FILENO, "%s\n", msg);
    exit(EXIT_FAILURE);
    return (NULL);
}