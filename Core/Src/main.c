/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "roboteq.h"
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
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
	 int DataIdx;
	 for (DataIdx = 0; DataIdx < len; DataIdx++){
		 ITM_SendChar(*ptr++);
	 }
	 return len;
 }

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
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  HAL_CAN_Start(&hcan);
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
//	  roboteq_queryVoltage(1);  // Query voltage from node ID 1
//	  HAL_Delay(2000);

//	  roboteq_setMotorCommand(1, 2, 500);  // Control Motor Channel 2 with 50% speed
//	  HAL_Delay(2000);
//	  roboteq_setMotorCommand(1, 2, -500); // Reverse direction with 50% speed
//	  HAL_Delay(2000);

//	  roboteq_setMotorSpeed(1, 2, 3000);  // Set motor channel 2 to 3000 RPM
//	  HAL_Delay(20000);
//	  roboteq_setMotorSpeed(1, 2, -3000); // Reverse direction at 3000 RPM
//	  HAL_Delay(20000);

//	 //POSITION MODE CLOSED
//	  roboteq_setMotorPosition(1, 2, 4096);  // Move motor channel 2 to position 10000
//	  HAL_Delay(5000);
////	  roboteq_queryEncoderPosition(1, 2);  // Query Encoder Position
////	  HAL_Delay(1000);
//
//	  roboteq_setMotorPosition(1, 2, -4096);  // Move motor channel 2 to position -5000
//	  HAL_Delay(5000);
//	  roboteq_queryEncoderPosition(1, 2);  // Query Encoder Position
//	  HAL_Delay(1000);

//	  roboteq_setMotorAngle(1, 2, 90);  // Move to 90 degrees
//	  HAL_Delay(3000);
//	  roboteq_queryEncoderPosition(1, 2);  // Query Encoder Position
//	  HAL_Delay(1000);
//
////	  roboteq_setMotorAngle(1, 2, 180);  // Move to 180 degrees
////	  HAL_Delay(3000);
////	  roboteq_queryEncoderPosition(1, 2);
//	  HAL_Delay(1000);
//
//	  roboteq_setMotorAngle(1, 2, -90);  // Move to -90 degrees
//	  HAL_Delay(3000);
//	  roboteq_queryEncoderPosition(1, 2);
//	  HAL_Delay(1000);

//	  roboteq_setMotorAngle(1, 2, 360);  // Move to 360 degrees (full rotation)
//	  HAL_Delay(3000);
//	  roboteq_queryEncoderPosition(1, 2);
//	  HAL_Delay(1000);

	  // ==== QUERY VOLTAGE ====
//	   roboteq_queryVoltage();
//	   HAL_Delay(2000);

	  // ==== OPEN-LOOP MOTOR CONTROL (PWM DUTY CYCLE) ====
//	   roboteq_setMotorCommand(MOTOR_LIFT, 500);  // 50% forward
//	   HAL_Delay(3000);
//	   roboteq_setMotorCommand(MOTOR_LIFT, -500); // 50% reverse
//	   HAL_Delay(3000);
//	   roboteq_setMotorCommand(MOTOR_LIFT, 0);    // Stop motor
//	   HAL_Delay(2000);

	  // ==== CLOSED-LOOP SPEED MODE ====
//	   roboteq_setMotorSpeed(MOTOR_LIFT, 500);   // Set speed to 3000 RPM
//	   HAL_Delay(10000);
//	   roboteq_setMotorSpeed(MOTOR_LIFT, -500);  // Reverse direction at 3000 RPM
//	   HAL_Delay(10000);
//	   roboteq_setMotorSpeed(MOTOR_LIFT, 0);      // Stop motor
//	   HAL_Delay(10000);

	  // ==== CLOSED-LOOP POSITION MODE (ABSOLUTE ENCODER POSITION) ====
//	   roboteq_setMotorPosition(MOTOR_LIFT, 5000);   // Move to encoder count 5000
//	   HAL_Delay(3000);
//	   roboteq_setMotorPosition(MOTOR_LIFT, -5000);  // Move to encoder count -5000
//	   HAL_Delay(3000);

	  // ==== CLOSED-LOOP POSITION MODE USING ANGLES ====
//	   roboteq_setMotorAngle(MOTOR_LIFT, 90);   // Move to 90 degrees
//	   HAL_Delay(3000);
//	   roboteq_setMotorAngle(MOTOR_LIFT, 180);  // Move to -90 degrees
//	   HAL_Delay(3000);
//	   roboteq_setMotorAngle(MOTOR_LIFT, -90);  // Move to 180 degrees
//	   HAL_Delay(3000);
//	   roboteq_setMotorAngle(MOTOR_LIFT, 360);  // Full rotation
//	   HAL_Delay(3000);

	  // ==== ENCODER POSITION QUERY ====
	   roboteq_queryEncoderPosition(MOTOR_LIFT);
	   HAL_Delay(2000);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 16;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_16TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = ENABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;

  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  CAN_FilterTypeDef canFilterConfig;
  canFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  canFilterConfig.FilterBank = 0;
  canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  canFilterConfig.FilterIdHigh = 0x0000;
  canFilterConfig.FilterIdLow = 0x0000;
  canFilterConfig.FilterMaskIdHigh = 0x0000;
  canFilterConfig.FilterMaskIdLow = 0x0000;
  canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

  HAL_CAN_ConfigFilter(&hcan, &canFilterConfig);


  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
