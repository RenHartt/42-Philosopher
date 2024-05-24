/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:59:27 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/15 19:58:58 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_info	t;
	t_data	data;

	ph_args(&t, ac, av);
	ph_parsing(t);
	ph_init(t, &data);
	ph_loop(t, &data);
}
