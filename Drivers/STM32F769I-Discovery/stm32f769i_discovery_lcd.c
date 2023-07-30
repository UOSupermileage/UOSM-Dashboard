/**
  ******************************************************************************
  * @file    stm32f769i_discovery_lcd.c
  * @author  MCD Application Team
  * @brief   This file includes the driver for Liquid Crystal Display (LCD) module
  *          mounted on STM32F769I-DISCOVERY board.
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

/* File Info: ------------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive directly in video mode a LCD TFT using the DSI interface.
     The following IPs are implied : DSI Host IP block working
     in conjunction to the LTDC controller.
   - This driver is linked by construction to LCD KoD mounted on board MB1166.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the LCD using the BSP_LCD_Init() function.
     o Select the LCD layer to be used using the BSP_LCD_SelectLayer() function.
     o Enable the LCD display using the BSP_LCD_DisplayOn() function.

  + Options
     o Configure and enable the color keying functionality using the
       BSP_LCD_SetColorKeying() function.
     o Modify in the fly the transparency and/or the frame buffer address
       using the following functions:
       - BSP_LCD_SetTransparency()
       - BSP_LCD_SetLayerAddress()

  + Display on LCD
     o Clear the whole LCD using BSP_LCD_Clear() function or only one specified string
       line using the BSP_LCD_ClearStringLine() function.
     o Display a character on the specified line and column using the BSP_LCD_DisplayChar()
       function or a complete string line using the BSP_LCD_DisplayStringAtLine() function.
     o Display a string line on the specified position (x,y in pixel) and align mode
       using the BSP_LCD_DisplayStringAtLine() function.
     o Draw and fill a basic shapes (dot, line, rectangle, circle, ellipse, .. bitmap)
       on LCD using the available set of functions.

------------------------------------------------------------------------------*/

/* Dependencies
- stm32f769i_discovery.c
- stm32f769i_discovery_sdram.c
- stm32f7xx_hal_dsi.c
- stm32f7xx_hal_ltdc.c
- stm32f7xx_hal_ltdc_ex.c
- stm32f7xx_hal_dma2d.c
- stm32f7xx_hal_rcc_ex.c
- stm32f7xx_hal_gpio.c
- stm32f7xx_hal_cortex.c
- otm8009a.c
- adv7533.c
EndDependencies */

/* Includes ------------------------------------------------------------------*/
#include "stm32f769i_discovery_lcd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F769I_DISCOVERY
  * @{
  */

/** @defgroup STM32F769I_DISCOVERY_LCD STM32F769I_DISCOVERY LCD
  * @{
  */

/** @defgroup STM32F769I_DISCOVERY_LCD_Private_Defines LCD Private Defines
  * @{
  */
#if defined(USE_LCD_HDMI)
#define HDMI_ASPECT_RATIO_16_9  ADV7533_ASPECT_RATIO_16_9
#define HDMI_ASPECT_RATIO_4_3   ADV7533_ASPECT_RATIO_4_3
#endif /* USE_LCD_HDMI */
#define LCD_DSI_ID              0x11
#define LCD_DSI_ID_REG          0xA8

static DSI_VidCfgTypeDef hdsivideo_handle;
/**
  * @}
  */

/** @defgroup STM32F769I_DISCOVERY_LCD_Private_TypesDefinitions LCD Private TypesDefinitions
  * @{
  */
#if defined(USE_LCD_HDMI)
/**
  * @brief  DSI timming params used for different HDMI adpater
  */
typedef struct 
{
  uint16_t      HACT;
  uint16_t      HSYNC;
  uint16_t      HBP;
  uint16_t      HFP;
  uint16_t      VACT;
  uint16_t      VSYNC;
  uint16_t      VBP;
  uint16_t      VFP;
  uint8_t       ASPECT_RATIO;
  uint8_t       RGB_CODING;
} HDMI_FormatTypeDef;

/**
  * @brief  DSI packet params used for different HDMI adpater
  */
typedef struct 
{
  uint16_t      NullPacketSize;
  uint16_t      NumberOfChunks;
  uint16_t      PacketSize;
} HDMI_DSIPacketTypeDef;

/**
  * @brief  LTDC PLL params used for different HDMI adpater
  */
typedef struct
{
  uint16_t      PLLSAIN;
  uint16_t      PLLSAIR;
  uint32_t      PCLK;
  uint16_t      IDF;
  uint16_t      NDIV;
  uint16_t      ODF;
  uint16_t      LaneByteClock;
  uint16_t      TXEscapeCkdiv;
} HDMI_PLLConfigTypeDef;
#endif /* USE_LCD_HDMI */
/**
  * @}
  */



/** @defgroup STM32F769I_DISCOVERY_LCD_Private_Macros LCD Private Macros
  * @{
  */
#define ABS(X)                 ((X) > 0 ? (X) : -(X))

#define POLY_X(Z)              ((int32_t)((Points + (Z))->X))
#define POLY_Y(Z)              ((int32_t)((Points + (Z))->Y))
/**
  * @}
  */

/** @defgroup STM32F769I_DISCOVERY_LCD_Exported_Variables STM32F769I DISCOVERY LCD Exported Variables
  * @{
  */
DMA2D_HandleTypeDef hdma2d_discovery;
LTDC_HandleTypeDef hltdc_discovery;
DSI_HandleTypeDef hdsi_discovery;
uint32_t lcd_x_size = OTM8009A_800X480_WIDTH;
uint32_t lcd_y_size = OTM8009A_800X480_HEIGHT;
/**
  * @}
  */


/** @defgroup STM32F769I_DISCOVERY_LCD_Private_Variables LCD Private Variables
  * @{
  */
#if defined(USE_LCD_HDMI)
/**
  * @brief  DSI timming used for different HDMI resolution (720x480 and 720x576)
  */
HDMI_FormatTypeDef HDMI_Format[2] =
{
/* HA   HS  HB  HF  VA   VS VB  VF  ASPECT                BPP */
  {720, 62, 60, 30, 480, 6, 19, 9, HDMI_ASPECT_RATIO_4_3, LCD_DSI_PIXEL_DATA_FMT_RBG888},
  {720, 64, 68, 12, 576, 5, 39, 5, HDMI_ASPECT_RATIO_16_9, LCD_DSI_PIXEL_DATA_FMT_RBG888}

};

/**
  * @brief  DSI packet size used for different HDMI resolution (720x480 and 720x576)
  */
HDMI_DSIPacketTypeDef HDMI_DSIPacket[2] =
{
  /* NP NC VP */
  {0, 1, 720},
  {0, 1, 720}
};

/**
  * @brief  LTDC PLL settings used for different HDMI resolution (720x480 and 720x576)
  */
HDMI_PLLConfigTypeDef HDMI_PLLConfig[4] =
{
/* N   DIV Pclk   IDF              NDIV ODF               LBClk TXEscapeCkdiv*/
  {325, 6, 27083, DSI_PLL_IN_DIV5, 65, DSI_PLL_OUT_DIV1, 40625, 3},
  {325, 6, 27083, DSI_PLL_IN_DIV5, 65, DSI_PLL_OUT_DIV1, 40625, 3}

};
#endif /* USE_LCD_HDMI */
/**
  * @brief  Default Active LTDC Layer in which drawing is made is LTDC Layer Background
  */
static uint32_t ActiveLayer = LTDC_ACTIVE_LAYER_BACKGROUND;

/** @defgroup STM32F769I_DISCOVERY_LCD_Private_FunctionPrototypes LCD Private FunctionPrototypes
  * @{
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t* c);
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
static void
LL_FillBuffer(uint32_t LayerIndex, void* pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex);
static void LL_ConvertLineToARGB8888(void* pSrc, void* pDst, uint32_t xSize, uint32_t ColorMode);
static uint16_t LCD_IO_GetID(void);
/**
  * @}
  */

/** @defgroup STM32F769I_DISCOVERY_LCD_Exported_Functions LCD Exported Functions
  * @{
  */

/**
  * @brief  Initializes the DSI LCD.
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void) {
    return (BSP_LCD_InitEx(LCD_ORIENTATION_LANDSCAPE));
}

/**
  * @brief  Initializes the DSI LCD. 
  * The ititialization is done as below:
  *     - DSI PLL ititialization
  *     - DSI ititialization
  *     - LTDC ititialization
  *     - OTM8009A LCD Display IC Driver ititialization
  * @param  orientation: LCD orientation, can be LCD_ORIENTATION_PORTRAIT or LCD_ORIENTATION_LANDSCAPE
  * @retval LCD state
  */
uint8_t BSP_LCD_InitEx(LCD_OrientationTypeDef orientation) {
    DSI_PLLInitTypeDef dsiPllInit;
    static RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    uint32_t LcdClock = 27429; /*!< LcdClk = 27429 kHz */
    uint16_t read_id = 0;

    uint32_t laneByteClk_kHz = 0;
    uint32_t VSA; /*!< Vertical start active time in units of lines */
    uint32_t VBP; /*!< Vertical Back Porch time in units of lines */
    uint32_t VFP; /*!< Vertical Front Porch time in units of lines */
    uint32_t VACT; /*!< Vertical Active time in units of lines = imageSize Y in pixels to display */
    uint32_t HSA; /*!< Horizontal start active time in units of lcdClk */
    uint32_t HBP; /*!< Horizontal Back Porch time in units of lcdClk */
    uint32_t HFP; /*!< Horizontal Front Porch time in units of lcdClk */
    uint32_t HACT; /*!< Horizontal Active time in units of lcdClk = imageSize X in pixels to display */

    /* Toggle Hardware Reset of the DSI LCD using
    * its XRES signal (active low) */
    BSP_LCD_Reset();

    /* Check the connected monitor */
    read_id = LCD_IO_GetID();

#if defined(USE_LCD_HDMI)
    if(read_id == ADV7533_ID)
    {
      return BSP_LCD_HDMIInitEx(HDMI_FORMAT_720_576);
    }
    else if(read_id != LCD_DSI_ID)
    {
      return LCD_ERROR;
    }
#else
    if (read_id != LCD_DSI_ID) {
        return LCD_ERROR;
    }
#endif /* USE_LCD_HDMI */

    /* Call first MSP Initialize only in case of first initialization
    * This will set IP blocks LTDC, DSI and DMA2D
    * - out of reset
    * - clocked
    * - NVIC IRQ related to IP blocks enabled
    */
    BSP_LCD_MspInit();

/*************************DSI Initialization***********************************/

    /* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
    hdsi_discovery.Instance = DSI;

    HAL_DSI_DeInit(&(hdsi_discovery));

    dsiPllInit.PLLNDIV = 100;
    dsiPllInit.PLLIDF = DSI_PLL_IN_DIV5;
    dsiPllInit.PLLODF = DSI_PLL_OUT_DIV1;
    laneByteClk_kHz = 62500; /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */

    /* Set number of Lanes */
    hdsi_discovery.Init.NumberOfLanes = DSI_TWO_DATA_LANES;

    /* TXEscapeCkdiv = f(LaneByteClk)/15.62 = 4 */
    hdsi_discovery.Init.TXEscapeCkdiv = laneByteClk_kHz / 15620;

    HAL_DSI_Init(&(hdsi_discovery), &(dsiPllInit));

    /* Timing parameters for all Video modes
    * Set Timing parameters of LTDC depending on its chosen orientation
    */
    if (orientation == LCD_ORIENTATION_PORTRAIT) {
        lcd_x_size = OTM8009A_480X800_WIDTH;  /* 480 */
        lcd_y_size = OTM8009A_480X800_HEIGHT; /* 800 */
    } else {
        /* lcd_orientation == LCD_ORIENTATION_LANDSCAPE */
        lcd_x_size = OTM8009A_800X480_WIDTH;  /* 800 */
        lcd_y_size = OTM8009A_800X480_HEIGHT; /* 480 */
    }

    HACT = lcd_x_size;
    VACT = lcd_y_size;

    /* The following values are same for portrait and landscape orientations */
    VSA = OTM8009A_480X800_VSYNC;        /* 12  */
    VBP = OTM8009A_480X800_VBP;          /* 12  */
    VFP = OTM8009A_480X800_VFP;          /* 12  */
    HSA = OTM8009A_480X800_HSYNC;        /* 63  */
    HBP = OTM8009A_480X800_HBP;          /* 120 */
    HFP = OTM8009A_480X800_HFP;          /* 120 */

    hdsivideo_handle.VirtualChannelID = LCD_OTM8009A_ID;
    hdsivideo_handle.ColorCoding = LCD_DSI_PIXEL_DATA_FMT_RBG888;
    hdsivideo_handle.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
    hdsivideo_handle.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
    hdsivideo_handle.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
    hdsivideo_handle.Mode = DSI_VID_MODE_BURST; /* Mode Video burst ie : one LgP per line */
    hdsivideo_handle.NullPacketSize = 0xFFF;
    hdsivideo_handle.NumberOfChunks = 0;
    hdsivideo_handle.PacketSize = HACT; /* Value depending on display orientation choice portrait/landscape */
    hdsivideo_handle.HorizontalSyncActive = (HSA * laneByteClk_kHz) / LcdClock;
    hdsivideo_handle.HorizontalBackPorch = (HBP * laneByteClk_kHz) / LcdClock;
    hdsivideo_handle.HorizontalLine = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz) /
                                      LcdClock; /* Value depending on display orientation choice portrait/landscape */
    hdsivideo_handle.VerticalSyncActive = VSA;
    hdsivideo_handle.VerticalBackPorch = VBP;
    hdsivideo_handle.VerticalFrontPorch = VFP;
    hdsivideo_handle.VerticalActive = VACT; /* Value depending on display orientation choice portrait/landscape */

    /* Enable or disable sending LP command while streaming is active in video mode */
    hdsivideo_handle.LPCommandEnable = DSI_LP_COMMAND_ENABLE; /* Enable sending commands in mode LP (Low Power) */

    /* Largest packet size possible to transmit in LP mode in VSA, VBP, VFP regions */
    /* Only useful when sending LP packets is allowed while streaming is active in video mode */
    hdsivideo_handle.LPLargestPacketSize = 16;

    /* Largest packet size possible to transmit in LP mode in HFP region during VACT period */
    /* Only useful when sending LP packets is allowed while streaming is active in video mode */
    hdsivideo_handle.LPVACTLargestPacketSize = 0;

    /* Specify for each region of the video frame, if the transmission of command in LP mode is allowed in this region */
    /* while streaming is active in video mode                                                                         */
    hdsivideo_handle.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;   /* Allow sending LP commands during HFP period */
    hdsivideo_handle.LPHorizontalBackPorchEnable = DSI_LP_HBP_ENABLE;   /* Allow sending LP commands during HBP period */
    hdsivideo_handle.LPVerticalActiveEnable = DSI_LP_VACT_ENABLE;  /* Allow sending LP commands during VACT period */
    hdsivideo_handle.LPVerticalFrontPorchEnable = DSI_LP_VFP_ENABLE;   /* Allow sending LP commands during VFP period */
    hdsivideo_handle.LPVerticalBackPorchEnable = DSI_LP_VBP_ENABLE;   /* Allow sending LP commands during VBP period */
    hdsivideo_handle.LPVerticalSyncActiveEnable = DSI_LP_VSYNC_ENABLE; /* Allow sending LP commands during VSync = VSA period */

    /* Configure DSI Video mode timings with settings set above */
    HAL_DSI_ConfigVideoMode(&(hdsi_discovery), &(hdsivideo_handle));

/*************************End DSI Initialization*******************************/


/************************LTDC Initialization***********************************/

    /* Timing Configuration */
    hltdc_discovery.Init.HorizontalSync = (HSA - 1);
    hltdc_discovery.Init.AccumulatedHBP = (HSA + HBP - 1);
    hltdc_discovery.Init.AccumulatedActiveW = (lcd_x_size + HSA + HBP - 1);
    hltdc_discovery.Init.TotalWidth = (lcd_x_size + HSA + HBP + HFP - 1);

    /* Initialize the LCD pixel width and pixel height */
    hltdc_discovery.LayerCfg->ImageWidth = lcd_x_size;
    hltdc_discovery.LayerCfg->ImageHeight = lcd_y_size;

    /** LCD clock configuration
      * Note: The following values should not be changed as the PLLSAI is also used
      *      to clock the USB FS
      * PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
      * PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 384 Mhz
      * PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 384 MHz / 7 = 54.85 MHz
      * LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_2 = 54.85 MHz / 2 = 27.429 MHz
      */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    /* Background value */
    hltdc_discovery.Init.Backcolor.Blue = 0;
    hltdc_discovery.Init.Backcolor.Green = 0;
    hltdc_discovery.Init.Backcolor.Red = 0;
    hltdc_discovery.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc_discovery.Instance = LTDC;

    /* Get LTDC Configuration from DSI Configuration */
    HAL_LTDC_StructInitFromVideoConfig(&(hltdc_discovery), &(hdsivideo_handle));

    /* Initialize the LTDC */
    HAL_LTDC_Init(&hltdc_discovery);

    /* Enable the DSI host and wrapper after the LTDC initialization
       To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
    HAL_DSI_Start(&hdsi_discovery);

#if !defined(DATA_IN_ExtSDRAM)
    /* Initialize the SDRAM */
    BSP_SDRAM_Init();
#endif /* DATA_IN_ExtSDRAM */

/************************End LTDC Initialization*******************************/


/***********************OTM8009A Initialization********************************/

    /* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver)
    *  depending on configuration set in 'hdsivideo_handle'.
    */
    OTM8009A_Init(OTM8009A_FORMAT_RGB888, orientation);

/***********************End OTM8009A Initialization****************************/

    return LCD_OK;
}

#if defined(USE_LCD_HDMI)
/**
  * @brief  Initializes the DSI for HDMI monitor. 
  * The ititialization is done as below:
  *     - DSI PLL ititialization
  *     - DSI ititialization
  *     - LTDC ititialization
  *     - DSI-HDMI ADV7533 adapter device ititialization
  * @param  format : HDMI format could be HDMI_FORMAT_720_480 or HDMI_FORMAT_720_576
  * @retval LCD state
  */
uint8_t BSP_LCD_HDMIInitEx(uint8_t format)
{ 
  /************************ADV7533 Initialization********************************/  

  /* Initialize the ADV7533 HDMI Bridge
  *  depending on configuration set in 'hdsivideo_handle'.
  */
  adv7533ConfigTypeDef adv7533_config;

  adv7533_config.DSI_LANES = 2;
  adv7533_config.HACT = HDMI_Format[format].HACT;
  adv7533_config.HSYNC = HDMI_Format[format].HSYNC;
  adv7533_config.HBP = HDMI_Format[format].HBP;
  adv7533_config.HFP = HDMI_Format[format].HFP;
  adv7533_config.VACT = HDMI_Format[format].VACT;
  adv7533_config.VSYNC = HDMI_Format[format].VSYNC;
  adv7533_config.VBP = HDMI_Format[format].VBP;
  adv7533_config.VFP = HDMI_Format[format].VFP;  

  ADV7533_Init();  
  ADV7533_Configure(&adv7533_config);
  ADV7533_PowerOn();

/************************ Update hdmi_x_size and hdmi_y_size *****************/
  lcd_x_size = HDMI_Format[format].HACT;
  lcd_y_size = HDMI_Format[format].VACT;

/***********************End ADV7533 Initialization****************************/  
  DSI_PLLInitTypeDef dsiPllInit;
  DSI_PHY_TimerTypeDef dsiPhyInit;
  static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

  /* Call first MSP Initialize only in case of first initialization
  * This will set IP blocks LTDC and DSI
  * - out of reset
  * - clocked
  * - NVIC IRQ related to IP blocks enabled
  */
  BSP_LCD_MspInit();

/*************************DSI Initialization***********************************/  

  /* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
  hdsi_discovery.Instance = DSI;

  HAL_DSI_DeInit(&(hdsi_discovery));

  /* Configure the DSI PLL */
  dsiPllInit.PLLNDIV    = HDMI_PLLConfig[format].NDIV;
  dsiPllInit.PLLIDF     = HDMI_PLLConfig[format].IDF;
  dsiPllInit.PLLODF     = HDMI_PLLConfig[format].ODF;

  /* Set number of Lanes */
  hdsi_discovery.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
  /* Set the TX escape clock division ratio */
  hdsi_discovery.Init.TXEscapeCkdiv = HDMI_PLLConfig[format].TXEscapeCkdiv;
  /* Disable the automatic clock lane control (the ADV7533 must be clocked) */
  hdsi_discovery.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;

  /* Init the DSI */
  HAL_DSI_Init(&hdsi_discovery, &dsiPllInit);

  /* Configure the D-PHY Timings */
  dsiPhyInit.ClockLaneHS2LPTime = 0x14;
  dsiPhyInit.ClockLaneLP2HSTime = 0x14;
  dsiPhyInit.DataLaneHS2LPTime = 0x0A;
  dsiPhyInit.DataLaneLP2HSTime = 0x0A;
  dsiPhyInit.DataLaneMaxReadTime = 0x00;
  dsiPhyInit.StopWaitTime = 0x0;
  HAL_DSI_ConfigPhyTimer(&hdsi_discovery, &dsiPhyInit);

  /* Virutal channel used by the ADV7533 */
  hdsivideo_handle.VirtualChannelID     = HDMI_ADV7533_ID;

  /* Timing parameters for Video modes
     Set Timing parameters of DSI depending on its chosen format */
  hdsivideo_handle.ColorCoding          = HDMI_Format[format].RGB_CODING;
  hdsivideo_handle.LooselyPacked        = DSI_LOOSELY_PACKED_DISABLE;
  hdsivideo_handle.VSPolarity           = DSI_VSYNC_ACTIVE_LOW;
  hdsivideo_handle.HSPolarity           = DSI_HSYNC_ACTIVE_LOW;
  hdsivideo_handle.DEPolarity           = DSI_DATA_ENABLE_ACTIVE_HIGH;  
  hdsivideo_handle.Mode                 = DSI_VID_MODE_NB_PULSES;
  hdsivideo_handle.NullPacketSize       = HDMI_DSIPacket[format].NullPacketSize;
  hdsivideo_handle.NumberOfChunks       = HDMI_DSIPacket[format].NumberOfChunks;
  hdsivideo_handle.PacketSize           = HDMI_DSIPacket[format].PacketSize; 
  hdsivideo_handle.HorizontalSyncActive = HDMI_Format[format].HSYNC*HDMI_PLLConfig[format].LaneByteClock/HDMI_PLLConfig[format].PCLK;
  hdsivideo_handle.HorizontalBackPorch  = HDMI_Format[format].HBP*HDMI_PLLConfig[format].LaneByteClock/HDMI_PLLConfig[format].PCLK;
  hdsivideo_handle.HorizontalLine       = (HDMI_Format[format].HACT + HDMI_Format[format].HSYNC + HDMI_Format[format].HBP + HDMI_Format[format].HFP)*HDMI_PLLConfig[format].LaneByteClock/HDMI_PLLConfig[format].PCLK;
  hdsivideo_handle.VerticalSyncActive   = HDMI_Format[format].VSYNC;
  hdsivideo_handle.VerticalBackPorch    = HDMI_Format[format].VBP;
  hdsivideo_handle.VerticalFrontPorch   = HDMI_Format[format].VFP;
  hdsivideo_handle.VerticalActive       = HDMI_Format[format].VACT;

  /* Enable or disable sending LP command while streaming is active in video mode */
  hdsivideo_handle.LPCommandEnable      = DSI_LP_COMMAND_DISABLE; /* Enable sending commands in mode LP (Low Power) */

  /* Largest packet size possible to transmit in LP mode in VSA, VBP, VFP regions */
  /* Only useful when sending LP packets is allowed while streaming is active in video mode */
  hdsivideo_handle.LPLargestPacketSize          = 4;

  /* Largest packet size possible to transmit in LP mode in HFP region during VACT period */
  /* Only useful when sending LP packets is allowed while streaming is active in video mode */
  hdsivideo_handle.LPVACTLargestPacketSize      = 4;

  /* Specify for each region, if the going in LP mode is allowed */
  /* while streaming is active in video mode                     */
  hdsivideo_handle.LPHorizontalFrontPorchEnable = DSI_LP_HFP_DISABLE;
  hdsivideo_handle.LPHorizontalBackPorchEnable  = DSI_LP_HBP_DISABLE;
  hdsivideo_handle.LPVerticalActiveEnable       = DSI_LP_VACT_DISABLE;
  hdsivideo_handle.LPVerticalFrontPorchEnable   = DSI_LP_VFP_DISABLE;
  hdsivideo_handle.LPVerticalBackPorchEnable    = DSI_LP_VBP_DISABLE;
  hdsivideo_handle.LPVerticalSyncActiveEnable   = DSI_LP_VSYNC_DISABLE;

  /* No acknoledge at the end of a frame */
  hdsivideo_handle.FrameBTAAcknowledgeEnable    = DSI_FBTAA_DISABLE;

  /* Configure DSI Video mode timings with settings set above */
  HAL_DSI_ConfigVideoMode(&hdsi_discovery, &hdsivideo_handle);

  /* Enable the DSI host and wrapper : but LTDC is not started yet at this stage */
  HAL_DSI_Start(&hdsi_discovery);

/*************************End DSI Initialization*******************************/ 
  
  
/************************LTDC Initialization***********************************/ 

  /* LTDC clock configuration */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = HDMI_PLLConfig[format].PLLSAIN;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = HDMI_PLLConfig[format].PLLSAIR;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct); 

  /* Base address of LTDC registers to be set before calling De-Init */
  hltdc_discovery.Instance = LTDC;

  HAL_LTDC_DeInit(&(hltdc_discovery));

  /* Timing Configuration */    
  hltdc_discovery.Init.HorizontalSync = (HDMI_Format[format].HSYNC - 1);
  hltdc_discovery.Init.AccumulatedHBP = (HDMI_Format[format].HSYNC + HDMI_Format[format].HBP - 1);
  hltdc_discovery.Init.AccumulatedActiveW = (HDMI_Format[format].HACT + HDMI_Format[format].HSYNC + HDMI_Format[format].HBP - 1);
  hltdc_discovery.Init.TotalWidth = (HDMI_Format[format].HACT + HDMI_Format[format].HSYNC + HDMI_Format[format].HBP + HDMI_Format[format].HFP - 1);
  hltdc_discovery.Init.VerticalSync = (HDMI_Format[format].VSYNC - 1);
  hltdc_discovery.Init.AccumulatedVBP = (HDMI_Format[format].VSYNC + HDMI_Format[format].VBP - 1);
  hltdc_discovery.Init.AccumulatedActiveH = (HDMI_Format[format].VACT + HDMI_Format[format].VSYNC + HDMI_Format[format].VBP - 1);
  hltdc_discovery.Init.TotalHeigh = (HDMI_Format[format].VACT + HDMI_Format[format].VSYNC + HDMI_Format[format].VBP + HDMI_Format[format].VFP - 1);

  /* background value */
  hltdc_discovery.Init.Backcolor.Blue = 0x00;
  hltdc_discovery.Init.Backcolor.Green = 0xFF;
  hltdc_discovery.Init.Backcolor.Red = 0xFF;

  /* Polarity */
  hltdc_discovery.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc_discovery.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc_discovery.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc_discovery.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

  /* Initialize & Start the LTDC */  
  HAL_LTDC_Init(&hltdc_discovery);     

#if !defined(DATA_IN_ExtSDRAM)
  /* Initialize the SDRAM */
  BSP_SDRAM_Init();
#endif /* DATA_IN_ExtSDRAM */

  /* Initialize the font */
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
/************************End LTDC Initialization*******************************/

    return LCD_OK; 
}
#endif /* USE_LCD_HDMI */

/**
  * @brief  BSP LCD Reset
  *         Hw reset the LCD DSI activating its XRES signal (active low for some time)
  *         and desactivating it later.
  */
void BSP_LCD_Reset(void) {
    GPIO_InitTypeDef gpio_init_structure;

    __HAL_RCC_GPIOJ_CLK_ENABLE();

    /* Configure the GPIO on PJ15 */
    gpio_init_structure.Pin = GPIO_PIN_15;
    gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOJ, &gpio_init_structure);

    /* Activate XRES active low */
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_15, GPIO_PIN_RESET);

    HAL_Delay(20); /* wait 20 ms */

    /* Desactivate XRES */
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_15, GPIO_PIN_SET);

    /* Wait for 10ms after releasing XRES before sending commands */
    HAL_Delay(10);
}

/**
  * @brief  Gets the LCD X size.
  * @retval Used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void) {
    return (lcd_x_size);
}

/**
  * @brief  Gets the LCD Y size.
  * @retval Used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void) {
    return (lcd_y_size);
}

/**
  * @brief  DCS or Generic short/long write command
  * @param  NbrParams: Number of parameters. It indicates the write command mode:
  *                 If inferior to 2, a long write command is performed else short.
  * @param  pParams: Pointer to parameter values table.
  * @retval HAL status
  */
void DSI_IO_WriteCmd(uint32_t NbrParams, uint8_t* pParams) {
    if (NbrParams <= 1) {
        HAL_DSI_ShortWrite(&hdsi_discovery, LCD_OTM8009A_ID, DSI_DCS_SHORT_PKT_WRITE_P1, pParams[0], pParams[1]);
    } else {
        HAL_DSI_LongWrite(&hdsi_discovery, LCD_OTM8009A_ID, DSI_DCS_LONG_PKT_WRITE, NbrParams, pParams[NbrParams],
                          pParams);
    }
}

/**
  * @brief  Returns the ID of connected screen by checking the HDMI
  *        (adv7533 component) ID or LCD DSI (via TS ID) ID.
  * @retval LCD ID
  */
static uint16_t LCD_IO_GetID(void) {
#if defined(USE_LCD_HDMI)
    HDMI_IO_Init();

    HDMI_IO_Delay(120);

    if(ADV7533_ID == adv7533_drv.ReadID(ADV7533_CEC_DSI_I2C_ADDR))
    {
      return ADV7533_ID;
    }
    else if(((HDMI_IO_Read(LCD_DSI_ADDRESS, LCD_DSI_ID_REG) == LCD_DSI_ID)) || \
             (HDMI_IO_Read(LCD_DSI_ADDRESS_A02, LCD_DSI_ID_REG) == LCD_DSI_ID))
    {
      return LCD_DSI_ID;
    }
    else
    {
      return 0;
    }
#else
    return LCD_DSI_ID;
#endif /* USE_LCD_HDMI */
}

/*******************************************************************************
                       LTDC, DMA2D and DSI BSP Routines
*******************************************************************************/
/**
  * @brief  De-Initializes the BSP LCD Msp
  * Application can surcharge if needed this function implementation.
  */
__weak void BSP_LCD_MspDeInit(void) {
    /** @brief Disable IRQ of LTDC IP */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);

    /** @brief Disable IRQ of DMA2D IP */
    HAL_NVIC_DisableIRQ(DMA2D_IRQn);

    /** @brief Disable IRQ of DSI IP */
    HAL_NVIC_DisableIRQ(DSI_IRQn);

    /** @brief Force and let in reset state LTDC, DMA2D and DSI Host + Wrapper IPs */
    __HAL_RCC_LTDC_FORCE_RESET();
    __HAL_RCC_DMA2D_FORCE_RESET();
    __HAL_RCC_DSI_FORCE_RESET();

    /** @brief Disable the LTDC, DMA2D and DSI Host and Wrapper clocks */
    __HAL_RCC_LTDC_CLK_DISABLE();
    __HAL_RCC_DMA2D_CLK_DISABLE();
    __HAL_RCC_DSI_CLK_DISABLE();
}

/**
  * @brief  Initialize the BSP LCD Msp.
  * Application can surcharge if needed this function implementation
  */
__weak void BSP_LCD_MspInit(void) {
    /** @brief Enable the LTDC clock */
    __HAL_RCC_LTDC_CLK_ENABLE();

    /** @brief Toggle Sw reset of LTDC IP */
    __HAL_RCC_LTDC_FORCE_RESET();
    __HAL_RCC_LTDC_RELEASE_RESET();

    /** @brief Enable the DMA2D clock */
    __HAL_RCC_DMA2D_CLK_ENABLE();

    /** @brief Toggle Sw reset of DMA2D IP */
    __HAL_RCC_DMA2D_FORCE_RESET();
    __HAL_RCC_DMA2D_RELEASE_RESET();

    /** @brief Enable DSI Host and wrapper clocks */
    __HAL_RCC_DSI_CLK_ENABLE();

    /** @brief Soft Reset the DSI Host and wrapper */
    __HAL_RCC_DSI_FORCE_RESET();
    __HAL_RCC_DSI_RELEASE_RESET();

    /** @brief NVIC configuration for LTDC interrupt that is now enabled */
    HAL_NVIC_SetPriority(LTDC_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);

    /** @brief NVIC configuration for DMA2D interrupt that is now enabled */
    HAL_NVIC_SetPriority(DMA2D_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA2D_IRQn);

    /** @brief NVIC configuration for DSI interrupt that is now enabled */
    HAL_NVIC_SetPriority(DSI_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DSI_IRQn);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
