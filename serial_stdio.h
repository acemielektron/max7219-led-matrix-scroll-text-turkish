/*
 *  (c) 2021 Acemi Elektronikçi
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef SERIAL_STDIO_H
#define SERIAL_STDIO_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>

#define serial0_tx_ready (UCSR0A & (1 << UDRE0))
#define serial0_rx_ready (UCSR0A & (1 << RXC0))

extern bool serial0_echo;

int serial0_putch(char ch);
int serial0_getch();
int serial0_fputch(char ch, FILE *stream);
int serial0_fgetch(FILE *stream);
void serial0_init_stdinout();
void serial0_init(uint32_t baud);

#ifdef __cplusplus
}
#endif

#endif //SERIAL_STDIO_H
