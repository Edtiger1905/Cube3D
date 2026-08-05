/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:21:19 by epandele          #+#    #+#             */
/*   Updated: 2025/09/26 10:34:32 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
static char	*read_buffer(int fd, char *buffer)
{
	char	*s1; 
	ssize_t	bytes_read;

	s1 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s1)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, s1, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(s1);
            free(buffer);
			return (NULL);
		}
		s1[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, s1);
	}
	free(s1);
	return (buffer);
}
/*
 * read_buffer: legge dal file descriptor fino a trovare '\n' o EOF
 * Righe 5-7: Dichiarazione variabili
 *   - s1: pointer al buffer che contiene i dati letti dal file (fd)
 *   - tempp: puntatore temporaneo per gestire la concatenazione delle stringhe
 *   - bytes_read: numero di byte letti dalla chiamata read()
 * Righe 9-13: Alloca BUFFER_SIZE
	+ 1 per includere il '\0' e controlla successo allocazione
 * Riga 14: Inizializza bytes_read a 1 per entrare nel ciclo
 * Riga 15: Il ciclo continua finché non trova '\n' in buffer e bytes_read > 0
 * Riga 17: Legge BUFFER_SIZE byte dal file descriptor
 * Righe 18-22: Se read() ritorna minore di 0 (errore), libera memoria e ritorna NULL
 * Riga 23: Aggiunge null terminator dopo ogni lettura
 * Righe 24-25: Se buffer è NULL, lo inizializza con stringa vuota
 * Riga 26: Salva puntatore attuale di buffer
 * Riga 27: Concatena buffer esistente con nuovi dati letti
 * Riga 28: Libera la vecchia stringa buffer (ora in tempp)
 * Righe 30-31: Libera buffer temporaneo s1 e ritorna la stringa accumulata
 */

static char	*get_line(char *buffer)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	if (buffer[len] == '\n')
		line[len] = buffer[len];
	else
		line[len] = '\0';
	line[len + 1] = '\0';
	return (line);
}
/*
 * get_line: estrae una singola riga (incluso '\n' se presente) da buffer
 * Righe 36-37: Dichiarazione variabili
 *   - line: puntatore alla riga che viene estratta
 *   - len: lunghezza della riga da estrarre
 * Riga 39: Inizializza len a 0
 * Righe 40-41: Se il primo carattere di buffer è '\0' ritorna NULL
 * Righe 42-43: Primo ciclo
	- conta i caratteri fino al primo '\n' o fine stringa
 * Riga 44: Alloca len + 2 caratteri (len + possibile '\n' + terminatore '\0')
 * Riga 45: Resetta len a 0 per il secondo ciclo
 * Righe 46-50: Secondo ciclo - copia caratteri da buffer a line,
	si ferma a '\n'
 * Righe 51-54: Se trova '\n' lo include nella riga, altrimenti mette '\0'
 * Riga 55: Aggiunge sempre '\0' finale per terminare la stringa
 * Riga 56: Ritorna la riga estratta
 */

static char	*get_new_buffer(char *buffer)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buff = (char *)malloc(sizeof(char) * (ft_strlen(&buffer[i++]) + 1));
	while (buffer[i])
	{
		new_buff[j] = buffer[i];
		j++;
		i++;
	}
	new_buff[j] = '\0';
	free(buffer);
	return (new_buff);
}
/*
 * get_new_buffer: crea un nuovo buffer contenente tutto dopo il primo '\n'
 * Righe 61-63: Dichiarazione variabili
 *   - new_buff: puntatore al nuovo buffer da creare
 *   - i: indice per scorrere il buffer originale
 *   - j: indice per scrivere nel nuovo buffer
 * Righe 65-66: Inizializzazione degli indici a 0
 * Righe 67-68: Trova la posizione del primo '\n' nel buffer
 * Righe 69-73: Se non trova '\n' (fine file), libera buffer e ritorna NULL
 * Riga 74: Calcola lunghezza della parte dopo '\n' e alloca memoria
 *   (i++ fa avanzare oltre il '\n' durante il calcolo della lunghezza)
 * Righe 75-80: Copia tutti i caratteri dopo '\n' nel nuovo buffer
 * Riga 81: Termina la stringa con '\0'
 * Riga 82: Libera il vecchio buffer
 * Riga 83: Ritorna il nuovo buffer
 */

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	buffer = read_buffer(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = get_line(buffer);
	buffer = get_new_buffer(buffer);
	return (line);
}
/*
 * get_next_line: funzione principale che ritorna una riga alla volta
 * Righe 88-89: Dichiarazione variabili
 *   - buffer: variabile statica che mantiene i dati tra le chiamate
 *   - line: riga estratta da ritornare
 * Righe 91-94: Controlla validità del file descriptor e BUFFER_SIZE
 * Riga 95: Legge dati dal file e li accumula in buffer
 * Righe 96-100: Se buffer è vuoto dopo la lettura, libera e ritorna NULL
 * Riga 101: Estrae una riga dal buffer
 * Riga 102: Aggiorna buffer con il contenuto rimanente dopo la riga estratta
 * Riga 103: Ritorna la riga letta
 */