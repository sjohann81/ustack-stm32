/* file:          slip_netif.c
 * description:   Serial Line IP interface
 * date:          07/2021
 * author:        Sergio Johann Filho <sergio.johann@acad.pucrs.br>
 */

#include "ustack.h"
#include <hal.h>
#include <usart.h>

int32_t if_setup()
{
	uart_init(USART_PORT, USART_BAUD, 0);
	
	return 0;
}
 
uint16_t netif_send(uint8_t *packet, uint16_t len)
{
	uint16_t i;

	uart_tx(USART_PORT, SLIP_END);
	for (i = 0; i < len; i++) {
		if (packet[i] == SLIP_END) {
			uart_tx(USART_PORT, SLIP_ESC);
			uart_tx(USART_PORT, SLIP_ESC_END);
		} else {
			if (packet[i] == SLIP_ESC) {
				uart_tx(USART_PORT, SLIP_ESC);
				uart_tx(USART_PORT, SLIP_ESC_ESC);
			} else {
				uart_tx(USART_PORT, packet[i]);
			}
		}
	}
	uart_tx(USART_PORT, SLIP_END);
	
	return len;
}

uint16_t netif_recv(uint8_t *packet)
{
	uint16_t len = 0;
	int16_t r;

	while (1) {
		r = uart_rx(USART_PORT);
		if (r == SLIP_END) {
			if (len > 0) {
				return len;
			}
		} else {
			if (r == SLIP_ESC) {
				r = uart_rx(USART_PORT);
				if (r == SLIP_ESC_END) {
					r = SLIP_END;
				} else {
					if (r == SLIP_ESC_ESC) {
						r = SLIP_ESC;
					}
				}
			}
			packet[len++] = r;
			if (len > FRAME_SIZE)
				len = 0;
		}
	}
}
