/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:02:49 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 16:04:27 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char curr, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (curr == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*toret;
	int		i;
	int		strl;

	i = 0;
	while (isset(s1[i], set))
		s1++;
	strl = ft_strlen(s1);
	while (isset(s1[strl - 1], set))
		strl--;
	toret = ft_substr(s1, 0, strl);
	return (toret);
}
// int main(void)
// {
// 	char *string1 = "   \t  \n\n \t\t HELLO \n\n\n;
// 	char *set = " \n\t";
// 	char *temp;
// 	temp = ft_strtrim(string1, set);
// 	printf("%s\n", temp);
// 	free(temp);
// 	return (0);
// }
