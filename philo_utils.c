/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:26:08 by yer-raki          #+#    #+#             */
/*   Updated: 2021/07/05 17:31:38 by yer-raki         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	while (len > i && s[i] != '\0')
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		l;
	char	*d;

	i = 0;
	l = ft_strlen(s1);
	d = (char *)malloc(sizeof(char) * (l + 1));
	if (!d)
		return (NULL);
	while (l > i)
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
