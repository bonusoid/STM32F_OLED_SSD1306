/* USER CODE BEGIN Header */
/**
 * 2022-05-22
 * Created by : bonusoid
 * OLED SSD1306 (128x64) Demo
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "periph_stm32f.h"
#include "main.h"
#include "oled_ssd1306.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned char dsine[10] = {0x18,0x06,0x01,0x01,0x06,0x18,0x60,0x80,0x80,0x60}; //Sinewave pattern
unsigned char dtri[14] = {0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x40,0x20,0x10}; //Trianglewave pattern
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
void drawInt(unsigned char olednum);	//Draw Integer demo
void drawAlphanum(unsigned char olednum); //Draw Letter & Number demo
void drawPunct(unsigned char olednum); //Draw Punctuation demo
void drawFrame(unsigned char olednum); //Draw Frame demo
void drawArrow(unsigned char olednum); //Draw Arrow demo
void drawBytes(unsigned char olednum); //Draw Pattern demo

void drawLoadingBar(unsigned char olednum); //Draw Loading Bar animation
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  //Up to 2 OLED. If only 1 OLED is connected, use one of : OLED1 or OLED2
  ssd1306_init(OLED1);
  ssd1306_init(OLED2);
  /* USER CODE BEGIN 2 */
  OLED_clear(OLED1);
  OLED_clear(OLED2);

  drawLoadingBar(OLED1);
  drawLoadingBar(OLED2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  	    drawBytes(OLED1);
	  		HAL_Delay(1000);
	        OLED_clearblock(OLED1,3,5,114); //Finish column = 5 + 11*10 - 1
	     	HAL_Delay(500);
	  		OLED_clearblock(OLED1,5,3,114); //Finish column = 3 + 8*14 - 1
	     	HAL_Delay(500);

	  		drawInt(OLED2);
	  		HAL_Delay(1000);
	  		OLED_clear(OLED2);

	  		drawAlphanum(OLED1);
	  		HAL_Delay(1000);
	  		OLED_reverse(OLED1);
	  		HAL_Delay(1000);
	  		OLED_clear(OLED1);
	  		OLED_normal(OLED1);

	  		drawPunct(OLED2);
	  		HAL_Delay(1000);
	  		OLED_reverse(OLED2);
	  		HAL_Delay(1000);
	  		OLED_clear(OLED2);
	  		OLED_normal(OLED2);

	  		drawFrame(OLED1);
	  		HAL_Delay(700);
	  		OLED_clearblock(OLED1,3,36,43); //Finish column = 36 + 8 - 1
	  		HAL_Delay(700);
	  		OLED_clear(OLED1);

	  		drawArrow(OLED2);
	  		HAL_Delay(700);
	  		OLED_clearblock(OLED2,3,36,43); //Finish column = 36 + 8 - 1
	  		HAL_Delay(700);
	  		OLED_clear(OLED2);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void drawInt(unsigned char olednum)
{
	OLED_drawint(olednum, 64, 0, 8); //Decimal
	OLED_drawint(olednum, 064, 0, 48); //Octal displayed as Decimal
	OLED_drawint(olednum, 0x64, 0, 88); //Hexadecimal displayed as Decimal

	OLED_drawint(olednum, -64, 1, 8); //Negative number is not supported
				 	 	 	 	 	  //Its 2's complement will be displayed

	OLED_drawint(olednum, 4294967295, 3, 8); //Max. is 4294967295

	OLED_drawint(olednum, 100, 5, 8);
	OLED_drawchar(olednum, SYM_DEGREE, 5, 32);
	OLED_drawchar(olednum, 'C', 5, 40);

	OLED_drawtext(olednum, " OLED TEST : INT",7,0);
}

void drawAlphanum(unsigned char olednum)
{
	OLED_drawtext(olednum, "ABCDEFGHIJKLM",0,0);
	OLED_drawtext(olednum, "NOPQRSTUVWXYZ",1,0);

	OLED_drawtext(olednum, "abcdefghijklm",3,0);
	OLED_drawtext(olednum, "nopqrstuvwxyz",4,0);

	OLED_drawtext(olednum, "0123456789",6,0);

	OLED_drawtext(olednum, "OLED TEST : CHAR",7,0);
}

void drawPunct(unsigned char olednum)
{
	OLED_drawtext(olednum, "<{([+_-=])}>",0,0);
	OLED_drawtext(olednum, "!@#$%^&*`|~?",2,0);
	OLED_drawtext(olednum, ".,\"\'\\/ :;",4,0);

	OLED_drawtext(olednum, "OLED TEST : CHAR",7,0);
}

void drawFrame(unsigned char olednum)
{
	unsigned char startcol=20;

	OLED_drawchar(olednum, FRAME_TOP_LEFT,1,startcol);
	OLED_drawchar(olednum, FRAME_LINE_HOR,1,startcol+8);
	OLED_drawchar(olednum, FRAME_TOP,1,startcol+16);
	OLED_drawchar(olednum, FRAME_LINE_HOR,1,startcol+24);
	OLED_drawchar(olednum, FRAME_TOP_RIGHT,1,startcol+32);

	OLED_drawchar(olednum, FRAME_LINE_VER,2,startcol);
	OLED_drawchar(olednum, FRAME_LINE_VER,2,startcol+16);
	OLED_drawchar(olednum, FRAME_LINE_VER,2,startcol+32);

	OLED_drawchar(olednum, FRAME_MID_LEFT,3,startcol);
	OLED_drawchar(olednum, FRAME_LINE_HOR,3,startcol+8);
	OLED_drawchar(olednum, FRAME_CENTER,3,startcol+16);
	OLED_drawchar(olednum, FRAME_LINE_HOR,3,startcol+24);
	OLED_drawchar(olednum, FRAME_MID_RIGHT,3,startcol+32);

	OLED_drawchar(olednum, FRAME_LINE_VER,4,startcol);
	OLED_drawchar(olednum, FRAME_LINE_VER,4,startcol+16);
	OLED_drawchar(olednum, FRAME_LINE_VER,4,startcol+32);

	OLED_drawchar(olednum, FRAME_BOT_LEFT,5,startcol);
	OLED_drawchar(olednum, FRAME_LINE_HOR,5,startcol+8);
	OLED_drawchar(olednum, FRAME_BOT,5,startcol+16);
	OLED_drawchar(olednum, FRAME_LINE_HOR,5,startcol+24);
	OLED_drawchar(olednum, FRAME_BOT_RIGHT,5,startcol+32);

	OLED_drawtext(olednum, " OLED TEST : SYM",7,0);
}
void drawArrow(unsigned char olednum)
{
	unsigned char startcol=20;

	OLED_drawchar(olednum, ARROW_UP_LEFT,1,startcol);
	OLED_drawchar(olednum, ARROW_UP,1,startcol+16);
	OLED_drawchar(olednum, ARROW_UP_RIGHT,1,startcol+32);

	OLED_drawchar(olednum, ARROW_LEFT,3,startcol);
	OLED_drawchar(olednum, ARROW_POINT,3,startcol+16);
	OLED_drawchar(olednum, ARROW_RIGHT,3,startcol+32);

	OLED_drawchar(olednum, ARROW_DOWN_LEFT,5,startcol);
	OLED_drawchar(olednum, ARROW_DOWN,5,startcol+16);
	OLED_drawchar(olednum, ARROW_DOWN_RIGHT,5,startcol+32);

	OLED_drawtext(olednum, " OLED TEST : SYM",7,0);
}

void drawBytes(unsigned char olednum)
{
	unsigned char Ts,ds;

	OLED_setpos(olednum,3,5);
	for(Ts=0;Ts<11;Ts++) //Draw pattern 11 times
	{
		for(ds=0;ds<10;ds++)
		{
			OLED_drawbyte(olednum, dsine[ds]);
		}
	}

	OLED_setpos(olednum,5,3);
	for(Ts=0;Ts<8;Ts++) //Draw pattern 8 times
	{
		for(ds=0;ds<14;ds++)
		{
			OLED_drawbyte(olednum, dtri[ds]);
		}
	}

	OLED_drawtext(olednum, "  DRAW PATTERN  ",7,0);
}

void drawLoadingBar(unsigned char olednum)
{
	unsigned char lb;

	OLED_setpos(olednum, 4,5);

	for(lb=5;lb<123;lb++)
	{
		OLED_drawbyte(olednum, 0xFF);
		HAL_Delay(10);
	}
	HAL_Delay(1000);
	OLED_clearblock(olednum,4,5,122); //Start & finish column = start & finish lb
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

