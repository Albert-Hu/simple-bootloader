#include <stdint.h>
#include <stdio.h>
#include "reg.h"

struct version {
	unsigned int major;
	unsigned int minor;
	unsigned int build;
};

extern uint32_t _app_entry;

struct version bootloader_version = { 0, 0, 1 };
char version_string[16];

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

	snprintf(version_string, 15, "%u.%u.%u"
		, bootloader_version.major
		, bootloader_version.minor
		, bootloader_version.build);

  printf("=== Simple Bootloader ===\r\n");
  printf("Version: %s\r\n", version_string);
	printf("load app...\r\n\r\n");

  load_app(_app_entry, *(&_app_entry + 1));

	while (1);
}
