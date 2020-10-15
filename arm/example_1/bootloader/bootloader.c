#include <stdint.h>
#include <stdio.h>
#include "reg.h"

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */
#define USART_FLAG_TXE	((uint16_t) 0x0080)

extern uint32_t _app_rom;

static char version[] = "0.0.1";

void load_app(uint32_t sp, uint32_t pc)
{
  __asm("msr msp, r0");
  __asm("bx r1");
}

void main(void)
{
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;

  printf("Simple Bootloader\r\n");
  printf("Version: %s\r\n", version);
	printf("load app...\r\n\r\n");

  load_app(_app_rom, *(&_app_rom + 1));

	while (1);
}
