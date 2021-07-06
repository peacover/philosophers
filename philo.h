/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:14:06 by yer-raki          #+#    #+#             */
/*   Updated: 2021/07/05 17:41:00 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_infos
{
	int	nb_ph;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_t_eat;
	int	is_nb_t_eat;
}				t_infos;

size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
int		ft_atoi(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

# endif