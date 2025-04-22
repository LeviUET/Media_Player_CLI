#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"
//#include "interrupt_manager.h"
#include "LPUART.h"
#include "ADC.h"
#include "stdint.h"

#define PCC_PORTD (*(volatile uint32_t *)(PCC_BASE + 0x130)) //Sử dụng con trỏ để truy xuất thanh ghi
#define PCC_PORTC (*(volatile uint32_t *)(PCC_BASE + 0x12C))

#define PORTD_PCR0 (*(volatile uint32_t *)(PORTD_BASE + 0x0))

#define GPIOD_BASE (0x400FF0C0)
#define GPIOD_PDDR (*(volatile uint32_t *)(GPIOD_BASE + 0x14))
#define GPIOD_PTOR (*(volatile uint32_t *)(GPIOD_BASE + 0xC))

#define PORTC_PCR12 (*(volatile uint32_t *)(PORTC_BASE + 0x30))
#define PORTC_ISFR (*(volatile uint32_t *)(PORTC_BASE + 0xA0))

#define GPIOC_BASE (0x400FF080)
#define GPIOC_PDDR (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

void PORT_init(void) {
	/* UART init */
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */
	PORTC->PCR[6] |= PORT_PCR_MUX(2); /* Port C6: MUX = ALT2,UART1 TX */
	PORTC->PCR[7] |= PORT_PCR_MUX(2); /* Port C7: MUX = ALT2,UART1 RX */

	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
}

void Interrupt_Init(void) {
	PORTC->PCR[12] |= (1 << 8);
	PORTC->PCR[12] |= (1 << 19) | (1 << 16);
	GPIOC_PDDR &= ~(1 << 12);

	PORTC->PCR[13] |= (1 << 8);
	PORTC->PCR[13] |= (1 << 19) | (1 << 16);
	GPIOC_PDDR &= ~(1 << 13);

	INT_SYS_EnableIRQ(61);
}

void PORTC_IRQHandler(void) {
	if (PORTC_ISFR & (1 << 12)) {
		PORTC_ISFR |= (1 << 12); // Clear interrupt flag
		LPUART1_transmit_string("P.");
	}

	if (PORTC_ISFR & (1 << 13)) {
		PORTC_ISFR |= (1 << 13); // Clear interrupt flag
		LPUART1_transmit_string("N.");
	}
}

void WDOG_disable(void) {
	WDOG->CNT = 0xD928C520; /* Unlock watchdog */
	WDOG->TOVAL = 0x0000FFFF; /* Maximum timeout value */
	WDOG->CS = 0x00002100; /* Disable watchdog */
}

void uint32_to_string(uint32_t value, char *str) {
	int i = 0;
	if (value == 0) {
		str[i++] = '0';
	} else {
		int start = 0;
		while (value > 0) {
			str[i++] = (value % 10) + '0';
			value /= 10;
		}
		// Đảo ngược chuỗi
		int end = i - 1;
		while (start < end) {
			char tmp = str[start];
			str[start++] = str[end];
			str[end--] = tmp;
		}
	}
	str[i] = '\0';
}

uint32_t adcResultInMv_pot = 0;
uint32_t lastAdcResult = -1;
uint32_t adcResultInMv_Vrefsh = 0;
char send_data[32];

int main(void) {
	/* Board Init */
	WDOG_disable(); /* Disable WDGO*/
	SOSC_init_8MHz(); /* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz(); /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); /* Init clocks: 80 MHz SPLL & core, 40 MHz bus, 20 MHz flash */

	PORT_init(); /* Configure ports */
	LPUART1_init();
	Interrupt_Init();
	ADC_init();

	for (;;) {
		// Bắt đầu chuyển đổi ADC
		convertAdcChan(12);
		while (adc_complete() == 0) {
		};

		adcResultInMv_pot = (read_adc_chx() * 128) / 5000;
		if (!(adcResultInMv_pot >= (lastAdcResult - 2)
				&& adcResultInMv_pot <= (lastAdcResult + 2))
				&& !(adcResultInMv_pot == 0 && lastAdcResult == 0)) {
			uint32_to_string(adcResultInMv_pot, send_data); // Chuyển sang chuỗi
			LPUART1_transmit_string(send_data);
			LPUART1_transmit_string(".");
			lastAdcResult = adcResultInMv_pot;
		}

		convertAdcChan(29); /* Convert chan 29, Vrefsh */
		while (adc_complete() == 0) {
		}; /* Wait for conversion complete flag */
		adcResultInMv_Vrefsh = read_adc_chx();
	}
}
