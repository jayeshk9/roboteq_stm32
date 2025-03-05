#ifndef ROBOTEQ_H
#define ROBOTEQ_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

// Function prototypes
void roboteq_sendSDO(uint8_t node_id, uint16_t index, uint8_t subindex, uint32_t data, uint8_t size, uint8_t is_read);
void roboteq_queryVoltage(uint8_t node_id);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

void roboteq_setMotorCommand(uint8_t node_id, uint8_t channel, int32_t speed);
void roboteq_setMotorSpeed(uint8_t node_id, uint8_t channel, int32_t speed_rpm);
void roboteq_setMotorPosition(uint8_t node_id, uint8_t channel, int32_t position);
void roboteq_queryEncoderPosition(uint8_t node_id, uint8_t channel);
void roboteq_setMotorAngle(uint8_t node_id, uint8_t channel, int angle);

#endif // ROBOTEQ_H
