#define MAX_SERIAL_PRINT_LENGTH 128

#ifdef STM

#include "stm32f7xx_hal.h"

#define DEBUG_UART              huart1
#define MAX_SERIAL_PRINT_LENGTH 128

#define EXT_SPI_CAN             hspi2
#define SPI_CAN                 &hspi2
#define SPI_TIMEOUT             10
#define MCP2515_CS_HIGH()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
#define MCP2515_CS_LOW()        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)

#define MCP2515_SPI_TRANSMIT(BUFFER, SIZE)    HAL_SPI_Transmit(SPI_CAN, BUFFER, SIZE, SPI_TIMEOUT);
#define MCP2515_SPI_RECEIVE(BUFFER, SIZE)     HAL_SPI_Receive(SPI_CAN, BUFFER, SIZE, SPI_TIMEOUT);
#define MCP2515_SPI_READY                     HAL_SPI_GetState(SPI_CAN) == HAL_SPI_STATE_READY

#else

#ifdef __cplusplus
extern "C" {
#endif

void ExternalSerialPrint(const char* message, ...);
void ExternalSerialPrintln(const char* message, ...);

#ifdef __cplusplus
}
#endif

#endif