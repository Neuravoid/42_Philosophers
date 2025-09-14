/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:43:57 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/12 18:39:53 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim	*simulation;

	simulation = NULL;
	simulation = init_simulation(ac, av, simulation);
	if (!simulation)
		return (1);
	start_simulation(simulation);
	return (0);
}
