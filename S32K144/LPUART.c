#include "S32K144.h"
#include "LPUART.h"

void LPUART1_init(void){
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK; /* Ensure clk disabled for config */
	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b001) /* Clock Src= 1 (SOSCDIV2_CLK) */
							     | PCC_PCCn_CGC_MASK; /* Enable clock for LPUART1 regs */
	LPUART1->BAUD = 0x0F000034; /* Initialize for 9600 baud, 1 stop: */
	 /* SBR=52 (0x34): baud divisor = 8M/9600/16 = ~52 */
	/* OSR=15: Over sampling ratio = 15+1=16 */
	/* SBNS=0: One stop bit */
	/* BOTHEDGE=0: receiver samples only on rising edge */
	/* M10=0: Rx and Tx use 7 to 9 bit data characters */
	/* RESYNCDIS=0: Resync during rec'd data word supported */
	/* LBKDIE, RXEDGIE=0: interrupts disable */
	/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
	/* MAEN1, MAEN2, MATCFG=0: Match disabled */
	LPUART1->CTRL=0x000C0000;
}

void LPUART1_transmit_char(char send){
	while((LPUART1->STAT & LPUART_STAT_TDRE_MASK) >> LPUART_STAT_TDRE_SHIFT == 0);
	LPUART1->DATA = send;
}

void LPUART1_transmit_string(char data_string[]) {
 uint32_t i=0;
 while(data_string[i] != '\0') {
 LPUART1_transmit_char(data_string[i]);
 i++;
 }
}
char LPUART1_receive_char(void) {
 char receive;
 while((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT==0);
 receive= LPUART1->DATA;
 return receive;
}
void LPUART1_receive_and_echo_char(void) {
 char send = LPUART1_receive_char();
 LPUART1_transmit_char(send);
 LPUART1_transmit_char('\n');
}
