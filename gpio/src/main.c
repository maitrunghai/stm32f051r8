
#include "hw_stm32f051r8.h"


/*************************************************************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}
/*************************************************************************************************/

void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}

void enabled_clock(void)
{
	unsigned int tempreg;
	/* set mode led ld3 */
	tempreg = read_reg(RCC_AHBENR, ~CLK_AHB(PORTC));
	tempreg = tempreg | CLK_AHB(PORTC);
	write_reg(RCC_AHBENR, tempreg);
}


void main(void)
{
	enabled_clock();
  set_mode_pin(PORTC,LD3_PIN,GPIO_MODER_OUTPUT);
  set_mode_pin(PORTC,LD4_PIN,GPIO_MODER_OUTPUT);
	while(1)
	{
    write_pin(PORTC,LD3_PIN,1);
    write_pin(PORTC,LD4_PIN,0);
		delay(0xf);
    write_pin(PORTC,LD3_PIN,0);
    write_pin(PORTC,LD4_PIN,1);
		delay(0xf);
	}
}

/*************************************************************************************************/
/* Function     :   set_mode_pin
 * Brief        :   The function is called to setup mode of pin
 * Parameter    :
 *                  [IN] port : port number which will be set up
 *                  [IN] pin : pin number which will be set up
 *                  [IN] mode_option : contain setting options include: 0x0XYZ
 *                                  - alternate mode Z  + input   00
 *                                                      + output  01
 *                                                      + alternate 10
 *                                                      + analog  11
 *                                  - output type  Y    + pushpull    0
 *                                                      + open drain  1
 *                                  - pull up/down   X  + pullup:     01
 *                                                      + pull down   10
 *                                                      + nopull    00
 * Return       :   None
/*************************************************************************************************/
void set_mode_pin(u8_t port, u8_t pin, u32_t mode_option)
{
  u32_t temp,tmpreg;
  temp = mode_option & 0xF;                           //Z
  tmpreg=read_reg(GPIO_MODER(port),~(0x03<<(2*pin)));
  tmpreg |= (temp<<(2*pin));
  write_reg(GPIO_MODER(port),tmpreg);
  
  if(temp == 0x01){
    temp = mode_option & 0xF0;                         //Y
    tmpreg=read_reg(GPIO_OTYPER(port),~(1<<pin));
    if (temp == 0x10){
      tmpreg |= (1<<pin);
      write_reg(GPIO_OTYPER(port),tmpreg);
    }
    else{
      write_reg(GPIO_OTYPER(port),tmpreg);
      temp=mode_option & 0xF00;                         //X
      tmpreg=read_reg(GPIO_PUPDR(port),~(0x03<<(2*pin)));
      if(temp == 0x00)
        write_reg(GPIO_PUPDR(port),tmpreg);
      else if (temp = 0x100){
        tmpreg |= (1<<(2*pin));
        write_reg(GPIO_PUPDR(port),tmpreg);
      }
      else if (temp = 0x200){
        tmpreg |= (2<<(2*pin));
        write_reg(GPIO_PUPDR(port),tmpreg);
      }
    }  
  }
}

/*************************************************************************************************/
/* Function     :   write_pin
 * Brief        :   The function is called to write new data to a pin
 * Parameter    :
 *                  [IN] port : port number which will be set up
 *                  [IN] pin : pin number which will be set up
 *                  [IN] value : 0 - low loggic; 1 - high loggic
 * Return       :   None
/*************************************************************************************************/
void write_pin(u8_t port, u8_t pin, u8_t value)
{
  if(value == 1){
    write_reg(GPIO_BSRR(port),(1<<pin));
  }
  else {
    write_reg(GPIO_BSRR(port),(1<<(pin+16)));
  }
}

/*************************************************************************************************/
/* Function     :   read_pin
 * Brief        :   The function is called to read data of a pin
 * Parameter    :
 *                  [IN] port : port number which will be set up
 *                  [IN] pin : pin number which will be set up
 * Return       :   0 - low loggic; 1 - high loggic
/*************************************************************************************************/
u8_t read_pin(u8_t port, u8_t pin)
{
  u32_t temp;
  temp=read_reg(GPIO_IDR(port),(1<<pin));
  if (temp == (1<<pin))
    return 1;
  else 
    return 0;
}

/*************************************************************************************************/
/* Function     :   toggle_pin
 * Brief        :   The function is called to inverse value of a pin
 * Parameter    :
 *                  [IN] port : port number which will be set up
 *                  [IN] pin : pin number which will be set up
 * Return       :   Return value which is set to pin
/*************************************************************************************************/
u8_t toggle_pin(u8_t port, u8_t pin)
{
  u32_t tmpreg;
  tmpreg = read_reg(GPIO_ODR(port),(1<<pin));
  if(tmpreg == 1<<pin){
    write_reg(GPIO_BSRR(port),(1<<pin));
    tmpreg=0;
  }
  else {
    write_reg(GPIO_BSRR(port),(1<<(pin+16)));
    tmpreg=1;
  }
  return tmpreg;
}