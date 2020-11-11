#include <stdint.h>
#include <stdio.h>
#include "reg.h"
#include "config.h"

struct version app_version = { 1, 0, 0 };
char version_string[16];

void main(struct boot_config *config)
{
	unsigned char *begin, *end;
	uint32_t checksum = 0;

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

	begin = (unsigned char*) config;
	end = (unsigned char*) &config->checksum;
	while (begin < end) {
		checksum = (checksum + *begin) % 100;
		begin++;
	}

	if (checksum != 0 && checksum == config->checksum) {
		printf("=== Bootloader Config ===\r\n");
		printf("Bootloader Version: %u.%u.%u\r\n"
			, config->bootloader_version.major
			, config->bootloader_version.minor
			, config->bootloader_version.build);
		printf("Message: %s\r\n", config->message);
	}

	snprintf(version_string, 15, "%u.%u.%u"
		, app_version.major
		, app_version.minor
		, app_version.build);

  printf("=== The App ===\r\n");
  printf("Version: %s\r\n", version_string);
	printf("app is running...\r\n");

	while (1);
}
