/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_assert.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 08:18:00 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 08:18:08 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_assert.h"
#include <stdlib.h>

void
	mini_assert(ft_bool assertion)
{
	if (!assertion)
		exit(EXIT_FAILURE);
}
