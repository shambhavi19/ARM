/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
			
int main(void)
{
	spi_master_init();
	while(1)
	{
		for(int i=0; i<8; i++ )
		{
			spi_transmit(-10);
			delay(2000);
		}

	}

}

void spi_master_init()
{

	RCC->APB2ENR|=(RCC_APB2ENR_SPI1EN)|(RCC_APB2ENR_AFIOEN)|(RCC_APB2ENR_IOPAEN); ///SCK ALTER PUSH PULL, MOSI, MISO FLOATING PULLUP
	GPIOA->CRL|=(GPIO_CRL_MODE5_0)|(GPIO_CRL_MODE5_1)|(GPIO_CRL_MODE7_0)|(GPIO_CRL_MODE7_1)|(GPIO_CRL_CNF5_1)|(GPIO_CRL_CNF7_1); //A5-SCK,6-MISO,7-MOSI
	GPIOA->CRL&=~(GPIO_CRL_CNF5_0);
	GPIOA->CRL&=~(GPIO_CRL_CNF7_0);
	GPIOA->CRL&=~(GPIO_CRL_MODE6_0);
	GPIOA->CRL&=~(GPIO_CRL_MODE6_1);
	GPIOA->CRL&=~(GPIO_CRL_CNF6_1);
	GPIOA->CRL|=(GPIO_CRL_CNF6_0);


	SPI1->CR1&=~(SPI_CR1_BIDIMODE); //FULL DUPLEX
	SPI1->CR1&=~(SPI_CR1_DFF); //8 BIT DATA
	SPI1->CR1&=~(SPI_CR1_RXONLY); //FULL DUPLEX
	SPI1->CR1|=(SPI_CR1_SSM); //SOFTWARE SLAVE MANAGEMENT
	SPI1->CR1|=(SPI_CR1_SSI); //NSS PIN HIGH(CHIP SELECT FOR MASTER)
	SPI1->CR1&=~(SPI_CR1_LSBFIRST);//MSB TRANSMITTED FIRST
	SPI1->CR1&=~(SPI_CR1_BR_0); //FCLK/2 baud 8/2=4Mhz
	SPI1->CR1&=~(SPI_CR1_BR_1); //FCLK/2
	SPI1->CR1&=~(SPI_CR1_BR_2); //FCLK/2
	SPI1->CR1|=(SPI_CR1_MSTR); //MASTER MODE
	SPI1->CR1&=~(SPI_CR1_CPOL); //CLOCK 0 IN IDLE STATE
	SPI1->CR1&=~(SPI_CR1_CPHA); //DATA TRANSFER ON 1ST CLOCK TRANSITION
	SPI1->CR1|=(SPI_CR1_SPE); //SPI ENABLE

	//SPI1->CR2|=(SPI_CR2_SSOE); //IF 0 MULTIMASTER MODE

}

void spi_transmit(int tdata)
{
	SPI1->DR=tdata;
	while(!(SPI1->SR & SPI_SR_TXE));
}


void delay(long int time)
{
	int m,n=0;
	for (m=0; m<time; m++)
	{
		n++;
	}
}



