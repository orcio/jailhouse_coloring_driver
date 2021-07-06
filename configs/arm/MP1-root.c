#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[43];
	struct jailhouse_irqchip irqchips[2];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xF8000000,
			.size = 0x4000000,
		},

		.debug_console = { 
			.address = 0x40010000,
			.size = 0x1000,
			.type = JAILHOUSE_CON_TYPE_STM32,
			.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,

		},


		.platform_info = {
			.arm = {
				.gic_version = 2,
				.gicd_base = 0xA0021000,
				.gicc_base = 0xA0022000,
				.gich_base = 0xA0024000,
				.gicv_base = 0xA0026000,
				.maintenance_irq = 25,
			},

		},
		.root_cell = {
			.name = "STM32MP157A-EV1",
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.num_pci_devices = 0,
			.vpci_irq_base = 108,
		},
	},

	.cpus = {
		0x3,
	},


	.mem_regions = {
		/* 1. mcuram2 */
		{
			.phys_start = 0x10000000,
			.virt_start = 0x10000000,
			.size = 0x40000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
				
		},

		/* 2. vdev0vring0 */
		{
			.phys_start = 0x10040000,
			.virt_start = 0x10040000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,

		},

		/* 3. vdev0vring1 */
		{
			.phys_start = 0x10042000,
			.virt_start = 0x10042000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,

		},

		/* 4. vdev0buffer */
		{
			.phys_start = 0x10044000,
			.virt_start = 0x10044000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,

		},

		/* 5. SRAM Memory */
		{
			.phys_start = 0x10050000,
			.virt_start = 0x10050000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,

		},

		/* 6. mcuram */
		{
			.phys_start = 0x30000000,
			.virt_start = 0x30000000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,

		},

		/* 7. retram */
		{
			.phys_start = 0x38000000,
			.virt_start = 0x38000000,
			.size = 0x40000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,

		},

		/* 2. Timer 2 */
		{
			.phys_start = 0x40000000,
			.virt_start = 0x40000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* 2. Uart */
		{
			.phys_start = 0x40010000,
			.virt_start = 0x40010000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},

		/* 3. I2C2 */
		{
			.phys_start = 0x40013000,
			.virt_start = 0x40013000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* 4. DMA1 */
		{
			.phys_start = 0x48000000,
			.virt_start = 0x48000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 5. DMA MUX */
		{
			.phys_start = 0x48002000,
			.virt_start = 0x48002000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 6. USB-OTG */
		{
			.phys_start = 0x49000000,
			.virt_start = 0x49000000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 7. Hardware Spinlock */
		{
			.phys_start = 0x4C000000,
			.virt_start = 0x4C000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},

		/* 8. IPCC mailbox */
		{
			.phys_start = 0x4c001000,
			.virt_start = 0x4c001000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},

		/* 9. RCC */
		{
			.phys_start = 0x50000000,
			.virt_start = 0x50000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO | JAILHOUSE_MEM_IO_32,
		},

		/* 10. Power Control (PWR) */
		{
			.phys_start = 0x50001000,
			.virt_start = 0x50001000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 11. GPIO- A to M OK */
		{
			.phys_start = 0x50002000,
			.virt_start = 0x50002000,
			.size = 0xb000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 12. External Interrupts Controller Registers (EXTI) */
		{
			.phys_start = 0x5000d000,
			.virt_start = 0x5000d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 13. THM */
		{
			.phys_start = 0x50028000,
			.virt_start = 0x50028000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 14. Funnel */
		{
			.phys_start = 0x50091000,
			.virt_start = 0x50091000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 15. ETF */
		{
			.phys_start = 0x50092000,
			.virt_start = 0x50092000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 16. TPIU */
		{
			.phys_start = 0x50093000,
			.virt_start = 0x50093000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 17. stm32-base */
		{
			.phys_start = 0x500a0000,
			.virt_start = 0x500a0000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 18. ETM 1 */
		{
			.phys_start = 0x500dc000,
			.virt_start = 0x500dc000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 19. ETM 2 */
		{
			.phys_start = 0x500dd000,
			.virt_start = 0x500dd000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 20. RNG */
		{
			.phys_start = 0x54003000,
			.virt_start = 0x54003000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	
		/* 21. GPIO-Z */
		{
			.phys_start = 0x54004000,
			.virt_start = 0x54004000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 22. MDMA Controller  */
		{
			.phys_start = 0x58000000,
			.virt_start = 0x58000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 23. SDMMC Controller (SDMMC1) */
		{
			.phys_start = 0x58005000,
			.virt_start = 0x58005000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 24. Delay Block (DLYBSD1) */
		{
			.phys_start = 0x58006000,
			.virt_start = 0x58006000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 25. Gigabit media access control (GMAC) with DMA controller (ETH1)*/
		{
			.phys_start = 0x5800a000,
			.virt_start = 0x5800a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 26. usbh_ehci */
		{
			.phys_start = 0x5800d000,
			.virt_start = 0x5800d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 27. DSI */
		{
			.phys_start = 0x5a000000,
			.virt_start = 0x5a000000,
			.size = 0x800,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 28. Independent watchdog  (IWDG2) */
		{
			.phys_start = 0x5a002000,
			.virt_start = 0x5a002000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 29. Usb Phyc  */
		{
			.phys_start = 0x5a006000,
			.virt_start = 0x5a006000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 30. DDR performance monitor (DDRPERFM)  */
		{
			.phys_start = 0x5a007000,
			.virt_start = 0x5a007000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		
		/* 31. I2C4 ok*/
		{
			.phys_start = 0x5c002000,
			.virt_start = 0x5c002000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 32. RTC */
		{
			.phys_start = 0x5c004000,
			.virt_start = 0x5c004000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* 33. Boot and security and OTP control (BSEC) ok */
		{
			.phys_start = 0x5c005000,
			.virt_start = 0x5c005000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		



		/* 34. System RAM block 1*/
		{					
			.phys_start = 0xC0000000,
			.virt_start = 0xC0000000,
			.size = 0x2E000000, //0x17000000
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE ,
		},


		
				/* 34. System RAM block 1
		{					
			.phys_start = 0xEE000000,
			.virt_start = 0xEE000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO | JAILHOUSE_MEM_IO_32 ,
				
		},
		*/


				/* 59.  Inmate reserved*/
		{
			.phys_start = 0xEE000000,
			.virt_start = 0xEE000000,
			.size = 0x8000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE ,		
		},

				{
			.phys_start = 0xF6000000,
			.virt_start = 0xF6000000,
			.size = 0x2000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,		
		},

		

		
	},

	.irqchips = {
		/* GIC */
		{
			.address = 0xA0021000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			}
		}, 
		/* GIC */
		{
			.address = 0xA0021000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			}
		}	
	}, 
};
