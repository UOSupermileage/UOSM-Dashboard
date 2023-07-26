// STM headers
#include "stm32f7xx_hal.h"

#define DEBUG_UART              huart1

#define EXT_SPI_CAN             hspi2
#define SPI_CAN                 &hspi2
#define SPI_TIMEOUT             10
#define MCP2515_CS_HIGH()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
#define MCP2515_CS_LOW()        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
