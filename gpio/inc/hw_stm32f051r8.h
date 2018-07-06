
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__


#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)


#define write_4_byte(addr, value)    *((unsigned int *)(addr)) = value
#define write_2_byte(addr, value)    *((unsigned short *)(addr)) = value
#define write_1_byte(addr, value)    *((unsigned char *)(addr)) = value

#define read_4_byte(addr, mask)      *((unsigned long int *)(addr)) & (mask)
#define read_2_byte(addr, mask)      *((unsigned long int *)(addr)) & (mask)
#define read_1_byte(addr, mask)      *((unsigned long int *)(addr)) & (mask)
/* RCC - clock */
#define BASE_ADDR_RCC		0x40021000u
#define RCC_AHBENR			(BASE_ADDR_RCC + 0x14)

#define CLK_AHB(port)		1<<(port + 17u)

#define PORTA		0u
#define PORTB		1u
#define PORTC		2u
#define PORTD		3u
#define PORTF		5u

/* GPIO */
#define BASE_ADDR_GPIO(port)		(0x48000000u + 0x400*(port))
#define GPIO_MODER(port)			(BASE_ADDR_GPIO(port) + 0x00u)
#define GPIO_OTYPER(port)			(BASE_ADDR_GPIO(port) + 0x04u)
#define GPIO_PUPDR(port)			(BASE_ADDR_GPIO(port) + 0x0Cu)
#define GPIO_IDR(port)				(BASE_ADDR_GPIO(port) + 0x10u)
#define GPIO_ODR(port)				(BASE_ADDR_GPIO(port) + 0x14u)
#define GPIO_BSRR(port)				(BASE_ADDR_GPIO(port) + 0x18u)

#define GPIO_MODER_INPUT		0x00u
#define GPIO_MODER_OUTPUT		0x01u
#define GPIO_MODER_ALT			0x02u
#define GPIO_MODER_ANALOG		0x03u

typedef unsigned int		u32_t;
typedef signed int			s32_t;

typedef unsigned short		u16_t;
typedef signed short		s16_t;

typedef unsigned char		u8_t;
typedef signed char			s8_t;


/* Led LD3 - PC9 */
#define LD3_PIN				9
#define LD4_PIN				8

/* end file */
#endif /* __HW_STM32F051R8_H__ */

