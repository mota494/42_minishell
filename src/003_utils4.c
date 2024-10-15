/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   003_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:12:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/14 12:12:57 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_counters(t_count *counters)
{
	counters->d = 0;
	counters->i = 0;
	counters->j = 0;
	counters->p = 0;
}

char	*initalize_str(void)
{
	char	*newstr;

	newstr = malloc(1);
	newstr[0] = '\0';
	return (newstr);
}
