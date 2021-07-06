/*
 * Jailhouse, a Linux-based partitioning hypervisor
 * 
 * Driver for STM32 family UART
 * 
 * Copyright (c) Aras Ashraf Gandomi, 2020
 *
 * Authors:
 *  Aras Ashraf Gandomi <aras.gandomi@gmail.com>
 */

#include <jailhouse/mmio.h>
#include <asm/processor.h>
#include <jailhouse/uart.h>

#define USART_ISR 		0x1C
#define USART_TDR		0x28
#define USART_ISR_TXE 	(1 << 7)


static void uart_init(struct uart_chip *chip)
{
	return;
}

static bool uart_is_busy(struct uart_chip *chip)
{
	return !( mmio_read32(chip->virt_base + USART_ISR) & USART_ISR_TXE );
}

static void uart_write_char(struct uart_chip *chip, char c)
{
	mmio_write32(chip->virt_base + USART_TDR, c);
}

struct uart_chip uart_stm32_ops = {
	.init = uart_init,
	.is_busy = uart_is_busy,
	.write_char = uart_write_char,
};
