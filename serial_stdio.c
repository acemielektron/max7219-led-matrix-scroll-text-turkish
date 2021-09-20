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
#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>

bool serial0_echo=true;

int serial0_putch(char ch)
{
  while ((UCSR0A & (1<<UDRE0)) == 0);  /* Wait for empty transmit buffer */
  UDR0 = ch ;
  return 0; //should return EOF on error
}

int serial0_getch()
{
  while ((UCSR0A & (1 << RXC0)) == 0);/* Wait till data is received */
  return(UDR0);    /* Return the byte */  
}

int serial0_fputch(char ch, FILE *stream)
{
  int res;
  if (ch == '\n') res = serial0_putch('\r');
  res = serial0_putch(ch);
  return res;
}

int serial0_fgetch(FILE *stream)
{
  int res = serial0_getch();
  if (serial0_echo) serial0_putch(res);
  return res;
}

void serial0_init_stdinout()
{  
  static FILE serial0_stdinout = FDEV_SETUP_STREAM(serial0_fputch, serial0_fgetch, _FDEV_SETUP_RW);
  stdout=stdin=stderr=&serial0_stdinout;
}

void serial0_init(uint32_t baud)
{
  uint16_t baudrate;
  
  if (baud == 115200)
  {
    UCSR0A = (1<<U2X0);  //Enable 2x speed
    baudrate = (F_CPU/8)/baud - 1;
  }
  else baudrate = (F_CPU/16)/baud -1;
  UBRR0 = baudrate;
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0); //enable receiver and transmitter
  serial0_init_stdinout();
}
