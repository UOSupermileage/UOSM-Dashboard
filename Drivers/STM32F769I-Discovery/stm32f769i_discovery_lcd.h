/**
  ******************************************************************************
  * @file    stm32f769i_discovery_lcd.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_discovery_lcd.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F769I_DISCOVERY_LCD_H
#define __STM32F769I_DISCOVERY_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Include LCD component Driver */

/* Include OTM8009A LCD Driver IC driver code */
#include "../Components/otm8009a/otm8009a.h"
/* Include ADV7533 HDMI Driver IC driver code */
#include "../Components/adv7533/adv7533.h"

/* Include SDRAM Driver */
#include "stm32f769i_discovery_sdram.h"
#include "stm32f769i_discovery.h"

#include <string.h> /* use of memset() */

#define BSP_LCD_DMA2D_IRQHandler        DMA2D_IRQHandler
#define BSP_LCD_DSI_IRQHandler          DSI_IRQHandler
#define BSP_LCD_LTDC_IRQHandler         LTDC_IRQHandler
#define BSP_LCD_LTDC_ER_IRQHandler      LTDC_ER_IRQHandler

#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef
/** 
  * @brief  LCD FB_StartAddress  
  */
#define LCD_FB_START_ADDRESS       ((uint32_t)0xC0000000)

/** @brief Maximum number of LTDC layers
 */
#define LTDC_MAX_LAYER_NUMBER             ((uint32_t) 2)

/** @brief LTDC Background layer index
 */
#define LTDC_ACTIVE_LAYER_BACKGROUND      ((uint32_t) 0)

/** @brief LTDC Foreground layer index
 */
#define LTDC_ACTIVE_LAYER_FOREGROUND      ((uint32_t) 1)

/** @brief Number of LTDC layers
 */
#define LTDC_NB_OF_LAYERS                 ((uint32_t) 2)

/** @brief LTDC Default used layer index
 */
#define LTDC_DEFAULT_ACTIVE_LAYER         LTDC_ACTIVE_LAYER_FOREGROUND

/** 
  * @brief  LCD status structure definition  
  */
#define   LCD_OK         0x00
#define   LCD_ERROR      0x01
#define   LCD_TIMEOUT    0x02

/** 
  * @brief  LCD Display OTM8009A DSI Virtual Channel  ID 
  */
#define LCD_OTM8009A_ID  ((uint32_t) 0)

/** 
  * @brief  HDMI ADV7533 DSI Virtual Channel  ID  
  */
#define HDMI_ADV7533_ID  ((uint32_t) 0)

/** 
  * @brief  HDMI Foramt   
  */
#define HDMI_FORMAT_720_480   ((uint8_t) 0x00) /*720_480 format choice of HDMI display */
#define HDMI_FORMAT_720_576   ((uint8_t) 0x01) /*720_576 format choice of HDMI display*/

/**
  * @brief LCD default font
  */
#define LCD_DEFAULT_FONT        Font24

/**
 *  @brief  Possible values of
 *  pixel data format (ie color coding) transmitted on DSI Data lane in DSI packets
 */

#define   LCD_DSI_PIXEL_DATA_FMT_RBG888  DSI_RGB888 /*!< DSI packet pixel format chosen is RGB888 : 24 bpp */
#define   LCD_DSI_PIXEL_DATA_FMT_RBG565  DSI_RGB565 /*!< DSI packet pixel format chosen is RGB565 : 16 bpp */


/**
 *  @brief LCD_OrientationTypeDef
 *  Possible values of Display Orientation
 */
typedef enum {
    LCD_ORIENTATION_PORTRAIT = 0x00, /*!< Portrait orientation choice of LCD screen  */
    LCD_ORIENTATION_LANDSCAPE = 0x01, /*!< Landscape orientation choice of LCD screen */
    LCD_ORIENTATION_INVALID = 0x02  /*!< Invalid orientation choice of LCD screen   */
} LCD_OrientationTypeDef;

uint8_t BSP_LCD_Init(void);
uint8_t BSP_LCD_InitEx(LCD_OrientationTypeDef orientation);
uint8_t BSP_LCD_HDMIInitEx(uint8_t format);

void BSP_LCD_MspDeInit(void);
void BSP_LCD_MspInit(void);
void BSP_LCD_Reset(void);

uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);

/* DMA2D handle variable */
extern DMA2D_HandleTypeDef hdma2d_discovery;

#ifdef __cplusplus
}
#endif

#endif /* __STM32F769I_DISCOVERY_LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
