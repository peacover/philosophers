/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:08 by yer-raki          #+#    #+#             */
/*   Updated: 2021/09/14 15:09:29 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (s2[i]);
	else if (!s2)
		return (s1[i]);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_atoi(const char *s)
{
	int		i;
	int		x;
	long	nb;

	i = 0;
	x = 1;
	nb = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
		x = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i++] - '0');
		if (nb > 9223372036854775807 / 10)
		{
			if (x == -1)
				return (0);
			else
				return (-1 * x);
		}
	}
	return (nb * x);
}

int	len_int(int n)
{
	int				l;
	unsigned int	nb;

	l = 1;
	if (n < 0)
	{
		l++;
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)n;
	while (nb > 9)
	{
		nb /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int				l;
	char			*s;
	unsigned int	nb;

	l = len_int(n);
	s = (char *)malloc(sizeof(char) * (l + 1));
	if (!s)
		return (NULL);
	s[l] = '\0';
	l--;
	if (n >= 0)
		nb = (unsigned int)n;
	else
		nb = (unsigned int)(-n);
	while (l >= 0)
	{
		s[l] = (nb % 10) + '0';
		nb /= 10;
		l--;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
