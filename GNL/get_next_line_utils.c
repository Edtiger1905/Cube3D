/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:21:28 by epandele          #+#    #+#             */
/*   Updated: 2025/08/27 15:32:51 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return(0);
	while (s[i] != '\0')
		i++;
	return (i);
}
/*
 * ft_strlen: calcola la lunghezza di una stringa
 * Riga 6: Dichiarazione variabile i (contatore caratteri)
 * Riga 8: Inizializzazione del contatore a 0
 * Righe 9-10: Scorre la stringa fino al null terminator '\0'
 * Riga 11: Ritorna il numero totale di caratteri (escluso '\0')
 */

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(s1);
	return (str);
}
/*
 * ft_strjoin: concatena due stringhe in una nuova stringa
 * Righe 18-20: Dichiarazione variabili
 *   - str: puntatore alla nuova stringa risultante
 *   - i: indice per scorrere le stringhe sorgente
 *   - j: indice per scrivere nella stringa destinazione
 * Riga 22: Alloca memoria per lunghezza totale delle due stringhe + 1 per '\0'
 * Righe 23-26: Controlla se allocazione è riuscita, altrimenti ritorna NULL
 * Righe 27-28: Inizializza gli indici a 0
 * Righe 29-33: Primo ciclo - copia tutti i caratteri di s1 in str
 * Riga 34: Resetta i a 0 per la seconda stringa
 * Righe 35-39: Secondo ciclo - copia tutti i caratteri di s2 in str
 * Riga 40: Aggiunge il null terminator alla fine
 * Riga 41: Ritorna la stringa concatenata
 */

char	*ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	if(!s)
		return(NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
/*
 * ft_strchr: cerca un carattere in una stringa
 * Riga 47: Dichiarazione variabile i (indice per scorrere la stringa)
 * Riga 49: Inizializza l'indice a 0
 * Riga 50: Scorre la stringa fino al null terminator
 * Righe 52-55: Se trova il carattere c, ritorna puntatore alla sua posizione
 * Riga 56: Incrementa l'indice per continuare la ricerca
 * Riga 58: Se non trova il carattere, ritorna NULL
 */

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	i;

	if (!src)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
 * ft_strdup: duplica una stringa allocando nuova memoria
 * Righe 65-66: Dichiarazione variabili
 *   - dup: puntatore alla stringa duplicata
 *   - i: indice per scorrere i caratteri
 * Righe 68-69: Se src è NULL, ritorna immediatamente NULL
 * Riga 70: Alloca memoria della dimensione di char (1 byte) per lunghezza src
	+ 1
 *   (il +1 serve per il null terminator)
 * Righe 71-72: Controllo sull'allocazione della memoria
 * Riga 73: Inizializza l'indice a 0
 * Righe 74-78: Copia dei caratteri uno per uno dalla stringa sorgente
 * Riga 79: Aggiunge il null terminator alla fine
 * Riga 80: Ritorna la nuova stringa duplicata
 */