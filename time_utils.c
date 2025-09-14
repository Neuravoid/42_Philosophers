/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:00:00 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 14:36:11 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	spend_time(long long ms)
{
	long long	start;
	long long	target;

	start = get_time();
	target = start + ms;

	while (get_time() < target)
	{
		if (target - get_time() > 1)
			usleep(100);
	}
}
void	spend_time_interruptible(long long ms, t_philo *philo)
{
	long long	start;
	long long	target;

	start = get_time();
	target = start + ms;
	
	while (get_time() < target)
	{
		if (check_stop_flag(philo))
			break ;
		
		if (target - get_time() > 1)
			usleep(50); 
	}
}
