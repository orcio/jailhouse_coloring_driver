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

#include <inmate.h>
#include <uart.h>

#define USART_ISR 		0x1C
#define USART_TDR		0x28
#define USART_ISR_TXE 	(1 << 7)


static void uart_stm32_init(struct uart_chip *chip)
{
}

static bool uart_stm32_is_busy(struct uart_chip *chip)
{
	return !( mmio_read32(chip->base + USART_ISR) & USART_ISR_TXE );
}

static void uart_stm32_write(struct uart_chip *chip, char c)
{
	mmio_write32(chip->base + USART_TDR, c);
}

DEFINE_UART(stm32, "STM32", JAILHOUSE_CON_TYPE_STM32);