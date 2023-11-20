/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:00:08 by mfeldman          #+#    #+#             */
/*   Updated: 2023/11/20 22:08:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo*)arg;
	pthread_mutex_lock(&philo->ptr->fork[0]); //test
	philo->ptr->test++;
	pthread_mutex_unlock(&philo->ptr->fork[0]);
	return (NULL);
}

int	main(int argc, char **argv)
{
	// test les retours d'erreur
	t_data	data;
	t_philo *philo;
	t_error	error;

	ft_bzero(&data, sizeof(t_data));
	philo = NULL;
	ft_bzero(&error, sizeof(t_error));
	data.error = &error;
	parsing(argc, argv, data.error);
	if(data.error->error_g)
		return (0);
	init_struct(&data,argv);
	if(init_mutex(&data))
		return (ft_destroy(&data), free(philo), 0);
	if(init_philo(&data, &philo))
		return (ft_destroy(&data), free(philo), 0);
	if(init_thread(&data, philo))
		return (ft_destroy(&data), free(philo), 0);
	return (ft_destroy(&data), free(philo), 0);
}
