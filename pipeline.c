/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:19:31 by yannis            #+#    #+#             */
/*   Updated: 2025/04/23 13:20:26 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// mettre le wait ici car sinon les commandes attendes les autres pour travailler
// il faut le mettre dans la focntion générale pipe pour permettre l'execution parallèle 
// waitpid(pid, NULL, 0);