/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_printf.h"
#include "canmd_controller.h"
#include "stm32f4_easy_can.h"
#include "ps3.h"
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
static uint8_t uart2_buf[8];
int motor_printf[4]={-2000,-2000,-2000,-2000};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void canmd_status_set_data(int canmd_num,int motor_select,unsigned int DutyOrPid,int p_value,int i_value,int d_value);

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
  MX_TIM7_Init();
  MX_USART1_UART_Init();
  MX_CAN_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
  ps3_init();
  stm32_printf_init(&huart1);
  HAL_UART_Receive_IT(&huart2,uart2_buf,8);

  canmd_controller_init();

  stm32f4_easy_can_init(&hcan,0,0b11111);
  canmd_controller_clear_all_encoder_count();

  //// PID値設定送信
  HAL_Delay(500);
  canmd_status_set_data(1,0,0,30,30,45);
  canmd_status_set_data(1,1,0,30,30,45);
  canmd_status_set_data(2,0,0,30,30,45);
  canmd_status_set_data(2,1,0,30,30,45);
  canmd_status_set_data(3,0,0,30,30,45);
  canmd_status_set_data(3,1,0,30,30,45);
  canmd_status_set_data(4,0,0,30,30,45);
  canmd_status_set_data(4,1,0,30,30,45);

  //HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start_IT(&htim16);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

 int i;
 //Ps3 ps3_data;
  while (1)
  {



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	 /* ps3_get_data(&ps3_data);
	  stm32_printf("====================================================================================================\n\r");
	  stm32_printf("L1=%d\n\r",ps3_data.L1);
	  stm32_printf("L2=%d\n\r",ps3_data.L2);
	  stm32_printf("R1=%d\n\r",ps3_data.R1);
	  stm32_printf("R2=%d\n\r",ps3_data.R2);
	  stm32_printf("batsu=%d\n\r",ps3_data.batsu);
	  stm32_printf("maru=%d\n\r",ps3_data.maru);
	  stm32_printf("shikaku=%d\n\r",ps3_data.shikaku);
	  stm32_printf("sankaku=%d\n\r",ps3_data.sankaku);
	  stm32_printf("up=%d\n\r",ps3_data.up);
	  stm32_printf("down=%d\n\r",ps3_data.down);
	  stm32_printf("right=%d\n\r",ps3_data.right);
	  stm32_printf("left=%d\n\r",ps3_data.left);
	  stm32_printf("left_analog_updown=%d\n\r",ps3_data.left_analog_updown);
	  stm32_printf("left_analog_rightleft=%d\n\r",ps3_data.left_analog_rightleft);

	  //debug printf
	  for(i=0;i<4;i++){
		  stm32_printf("motor_printf[%d]=%d\n\r",i,motor_printf[i]);
	  }*/
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM16){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		int motor_output[CANMD_MD_NUM + 1][2] = {};
		int id=1;
		/*制御文*/

		Ps3 ps3_data;
		 ps3_get_data(&ps3_data);


		 stm32_printf("Hello,World!\n\r");
		 stm32_printf("L1=%d\n\r",ps3_data.L1);
		 stm32_printf("L2=%d\n\r",ps3_data.L2);
		 stm32_printf("R1=%d\n\r",ps3_data.R1);
		 stm32_printf("R2=%d\n\r",ps3_data.R2);
		 stm32_printf("batsu=%d\n\r",ps3_data.batsu);
		 stm32_printf("maru=%d\n\r",ps3_data.maru);
		 stm32_printf("shikaku=%d\n\r",ps3_data.shikaku);
		 stm32_printf("sankaku=%d\n\r",ps3_data.sankaku);
		 stm32_printf("up=%d\n\r",ps3_data.up);
		 stm32_printf("down=%d\n\r",ps3_data.down);
		 stm32_printf("right=%d\n\r",ps3_data.right);
		 stm32_printf("left=%d\n\r",ps3_data.left);
		 stm32_printf("left_analog_updown=%d\n\r",ps3_data.left_analog_updown);
		 stm32_printf("left_analog_rightleft=%d\n\r",ps3_data.left_analog_rightleft);




/*制御文終了*/

		for(id = 1;id < (CANMD_MD_NUM + 1);id++)
		{
			canmd_controller_set_motor_control_data(id, motor_output[id][0],motor_output[id][1]);
		}
	}
	//end TIM7

	if(htim->Instance == TIM7) {
		int id = 1;
		int dlc = 3;
		unsigned char data[8];


		// 送信データ生成
		canmd_controller_get_can_transmit_data(&id, &dlc, data);

		// CANデータ送信
		stm32f4_easy_can_transmit_message(id, dlc, data);
	}
}

//*********************************************************
//    CAN割り込み関数
//*********************************************************
void stm32f4_easy_can_interrupt_handler(void)
{
	int id;
	int dlc;
	unsigned char data[8];

	// 受信データ取得
	stm32f4_easy_can_get_receive_message(&id, &dlc, data);
	// canmdモジュールに受信データを渡す
	canmd_controller_set_can_receive_data(id, dlc, data);

}

//*********************************************************
//    UART割り込み関数
//*********************************************************
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart2.Instance) {
        ps3_uart_interrupt_routine(uart2_buf, 8);
        HAL_UART_Receive_IT(&huart2, uart2_buf, 8);
    }
}


//*********************************************************
//    PID値セット関数
//*********************************************************

void canmd_status_set_data(int canmd_num,int motor_select,unsigned int DutyOrPid,int p_value,int i_value,int d_value)
{
	int id;
	int dlc = 4;
	unsigned char data[8];

	id = canmd_num;

    data[0] = ((motor_select << 6) & 0b11000000 ) | DutyOrPid;
    data[1] = p_value & 0XFF;
    data[2] = i_value & 0XFF;
    data[3] = d_value & 0XFF;

	// CANデータ送信
    HAL_Delay(100);

	stm32f4_easy_can_transmit_message(id, dlc, data);
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
