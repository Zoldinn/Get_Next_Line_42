/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:38:06 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/26 17:13:35 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- liste chainee ?
- var static : pour savoir ou a fini la ligne : si '\n' est au milieu du buffer read
--> strjoin pour joindre le morceau de buffer precedent avec le debut de la nouvelle ligne
- malloc a la taille du BUFFER donner a la compil
- retourne : la ligne lue (premiere ou suivante), \n compris (ou \0), ligne = ce qu'il y a entre debut, \n et EOF
- si erreur ou plus rien a lire -> retourne NULL
- doit pouvoir lire autant sur un fichier que sur l'entree standard (fd 0)
- doit compiler avec -D BUFFER_SIZE=n
*/

char	*get_next_line(int fd)
{

}

/*--- TESTS ---*/

#include <stdio.h>

int	main(void)
{
	return (0);
}