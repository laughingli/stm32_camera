/**
 ******************************************************************************
 * @file    task_frame_buffer.c
 * @author  PSEE Applications Team
 * @brief	Frame buffer specific Functions
 *
 ******************************************************************************
 * @attention
 * Copyright (c) Prophesee S.A.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "task_frame_buffer.h"

/* Private Defines */
#define DISPLAY_RESOLUTION (320*272)

/* 3 Display Frame Buffers */
static uint8_t frame_buffer_l1_one[DISPLAY_RESOLUTION] __attribute__((section("L1_Frame_Buffers"))) __attribute__((aligned(4)));
static uint8_t frame_buffer_l1_two[DISPLAY_RESOLUTION] __attribute__((section("L1_Frame_Buffers"))) __attribute__((aligned(4)));
static uint8_t frame_buffer_l1_three[DISPLAY_RESOLUTION] __attribute__((section("L1_Frame_Buffers"))) __attribute__((aligned(4)));

uint8_t* volatile fb_cpi = frame_buffer_l1_three;

/* This semaphore is used to notify the application that the new
 * frame buffer is displayed, a new one can be prepared...
 */
static SemaphoreHandle_t xSemphFbUpdtHdl = NULL;

/**
 * @brief Color look-up table for Events streaming mode
 */
static const uint32_t clut_event[] = {
		((30UL << 16) | (37UL << 8) | (52UL)), 		// Background
		((216UL << 16) | (223UL << 8) | (236UL)), 	// ON event
		((64UL << 16) | (126UL << 8) | (201UL)) 	// OFF event
};

/**
 * @brief Function to enable the LCD layer
 * @param hltdc Pointer to a LTDC_HandleTypeDef structure
 * @param layer LTDC Layer index
 * @param address Pointer to the address of the frame buffer
 */
static void enable_layer(LTDC_HandleTypeDef *hltdc, unsigned int layer, void *address) {

	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	pLayerCfg.WindowX0 = 160;
	pLayerCfg.WindowX1 = 480;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = 272;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_L8; //LTDC_PIXEL_FORMAT_RGB565;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = (uint32_t)address;
	pLayerCfg.ImageWidth = 320;
	pLayerCfg.ImageHeight = 272;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	HAL_LTDC_ConfigLayer(hltdc, &pLayerCfg, layer);
	HAL_LTDC_ConfigCLUT(hltdc, (uint32_t *)clut_event, sizeof(clut_event)/sizeof(uint32_t), layer);
	HAL_LTDC_EnableCLUT(hltdc, layer);
}

/**
 * @brief Function to Reset the frame buffer. It must be done before scheduling starts.
 * It can not be done by DMA.
 */
void reset_frame_buffers() {

	memset(frame_buffer_l1_one, 0 , sizeof(frame_buffer_l1_one));
	memset(frame_buffer_l1_two, 0 , sizeof(frame_buffer_l1_two));
	memset(frame_buffer_l1_three, 0 , sizeof(frame_buffer_l1_three));

}

/**
 * @brief Function implementing the Update frame buffer task.
 */
extern SemaphoreHandle_t tskCtlUpdateFbHandle;
void task_update_fb(const args_update_fb_t *args) {

	uint8_t* fb_display = frame_buffer_l1_one;
	uint8_t* fb_reset = frame_buffer_l1_two;
	uint8_t* old_fb_cpi;
	DrvDmaHandle_t drv_dma = *(args->drv_dma);
	BaseType_t status;
	StaticSemaphore_t xSemaphoreBuffer;

	xSemphFbUpdtHdl = xSemaphoreCreateBinaryStatic( &xSemaphoreBuffer );
	assert(xSemphFbUpdtHdl);

	enable_layer(args->hltdc, 1, fb_display);

	/* Infinite loop */
	for(;;)
	{
		/* This semaphore is used to suspend the task. */
		status = xSemaphoreTake(tskCtlUpdateFbHandle, portMAX_DELAY  );
		assert(status == pdTRUE);

		/* Swap CPI Buffer, Reset Buffer and display buffer */
		old_fb_cpi = fb_cpi;
		fb_cpi = fb_reset;

		fb_reset = fb_display;
		fb_display = old_fb_cpi;

		/* Wait for register reload interrupt ( Generated when shadow register reload is performed ) */
		HAL_LTDC_Reload(args->hltdc, LTDC_RELOAD_VERTICAL_BLANKING);

		/* Notify the display and change fb address */
		LTDC_LAYER(args->hltdc, 1)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
		LTDC_LAYER(args->hltdc, 1)->CFBAR = (uint32_t)(fb_display);

		status = xSemaphoreTake( xSemphFbUpdtHdl, 50 / portTICK_PERIOD_MS );
		assert(status == pdTRUE);

		status = xSemaphoreGive(tskCtlUpdateFbHandle);
		assert(status == pdTRUE);

		/* Start Reset */
		ucDrvDmaMemsetTo0(drv_dma, fb_reset, sizeof(frame_buffer_l1_one));

		vTaskDelay( 12 / portTICK_PERIOD_MS);
	}

}

/**
 * @brief Call back function for register reload
 */
void update_fb_callback()
{
	BaseType_t xHigherPriorityTaskWoken_RR = pdFALSE;
	xSemaphoreGiveFromISR( xSemphFbUpdtHdl, &xHigherPriorityTaskWoken_RR);

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken_RR );
}


