/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:45:02 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 16:22:58 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
	ft_status(1, philo);
	spend_time_interruptible(philo->sim->time_to_die, philo);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_eaten = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_status(2, philo);
	spend_time_interruptible(philo->sim->time_to_eat, philo);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
}

static void	ft_sleep(t_philo *philo)
{
	ft_status(4, philo);
	spend_time_interruptible(philo->sim->time_to_sleep, philo);
}

static void	ft_think(t_philo *philo)
{
	long long	think_time;
	long long	time_since_last_meal;
	long long	current_time;

	ft_status(3, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_eaten;
	think_time = (philo->sim->time_to_die - time_since_last_meal
			- philo->sim->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	else if (think_time > 50 && think_time < 100)
		think_time = 75;
	spend_time_interruptible(think_time, philo);
}

void	handle_routine(t_philo *philo)
{
	if (philo->sim->philo_count == 1)
	{
		ft_one_philo(philo);
		return ;
	}
	ft_even_wait(philo);
	while (!check_stop_flag(philo))
	{
		ft_take_fork(philo);
		if (check_stop_flag(philo))
		{
			ft_release_forks(philo);
			break ;
		}
		ft_eat(philo);
		if (check_stop_flag(philo))
			break ;
		ft_sleep(philo);
		if (check_stop_flag(philo))
			break ;
		ft_think(philo);
	}
}
