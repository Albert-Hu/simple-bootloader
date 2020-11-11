#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "reg.h"
#include "config.h"

#define SET_THUMB_ADDRESS(x)  ((x) | 0x1)

typedef void (*app_func)(uint32_t config_addr);

extern uint32_t _app_entry;

struct version bootloader_version = { 0, 0, 1 };
char version_string[16];

void* memset(void *dest, int val, size_t len)
{
  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void load_app(struct boot_config *config)
{
	uint32_t config_addr = (_app_entry - sizeof(struct boot_config)) & (~3);
	uint32_t app_stack_top = config_addr - 4;
	app_func app_start = (app_func) SET_THUMB_ADDRESS(*(&_app_entry + 1));
	int len = sizeof(struct boot_config);
	char *dest = (char*) config_addr;
	const char *src = (const char*) config;

	/*
		Copy the config to the app's stack.
		NOTE: Don't use the memcpy that might cause the stack overlap.
	*/
	while (len-- > 0) {
		*dest++ = *src++;
	}

	/* Set the app's stack pointer. */
	__asm volatile ("MSR msp, %0" : : "r" (app_stack_top) : );

	/* Jump to the app entry. */
	app_start(config_addr);
}

void main(void)
{
	struct boot_config *config = NULL;
	unsigned char *begin = NULL, *end = NULL;

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

	/* Allocate the config memory. */
	config = (struct boot_config*) malloc(sizeof(struct boot_config));
	memset(config, 0, sizeof(struct boot_config));

	/* Initialize the config. */
	config->bootloader_version.major = bootloader_version.major;
	config->bootloader_version.minor = bootloader_version.minor;
	config->bootloader_version.build = bootloader_version.build;
	snprintf(config->message, 63, "This message from the bootloader.\r\n");

	/* Calculate the checksum of the config. */
	begin = (unsigned char*) config;
	end = (unsigned char*) &config->checksum;
	while (begin < end) {
		config->checksum = (config->checksum + *begin) % 100;
		begin++;
	}

  load_app(config);

	while (1);
}
