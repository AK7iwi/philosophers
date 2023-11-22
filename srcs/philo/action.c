/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:56:09 by mfeldman          #+#    #+#             */
/*   Updated: 2023/11/22 22:46:37 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_die(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->m_last_meal);
			if ((get_current_time() - data->start - philo[i].last_meal) >= data->time_to_die)
			{
				pthread_mutex_unlock(&data->m_last_meal);
				pthread_mutex_lock(&data->m_die);
				data->died = 1;
				pthread_mutex_unlock(&data->m_die);
				print(philo, DEAD);
				return ;
			}
			else
				pthread_mutex_unlock(&data->m_last_meal);
			i++;
		}	
	}
}

void	ft_sleep(t_philo *philo)
{
	print(philo, SLEEP);
	ft_usleep(philo, philo->ptr_data->time_to_sleep);
}

bool	eat(t_philo *philo)
{
	pthread_mutex_lock (&philo->ptr_data->fork[philo->id - 1]);
	print(philo, FORK);
	if(philo->ptr_data->nb_philo == 1)
		return (pthread_mutex_unlock (&philo->ptr_data->fork[philo->id - 1]), 1);
	pthread_mutex_lock (&philo->ptr_data->fork[philo->id]);
	print(philo, FORK);
	print(philo, EAT);
	pthread_mutex_lock(&philo->ptr_data->m_max_eat);
	philo->last_meal = get_current_time() - philo->ptr_data->start;
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->ptr_data->m_max_eat);
	pthread_mutex_unlock(&philo->ptr_data->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->ptr_data->fork[philo->id]);
	ft_usleep(philo, philo->ptr_data->time_to_eat);
	return(0);
}

void think(t_philo *philo, unsigned long time)
{
	print(philo, THINK);
	ft_usleep(philo, time);
}