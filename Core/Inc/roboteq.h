#ifndef ROBOTEQ_H
#define ROBOTEQ_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

// ==================== ENUMS ====================
// Motor Channels
typedef enum {
    MOTOR_TURN = 1,   // Channel 1
    MOTOR_LIFT = 2    // Channel 2
} MotorChannel_t;

// CANOpen Object Dictionary (SDO Indices)
typedef enum {
    OBJ_VOLTAGE = 0x210D,        // Voltage reading (Confirm if subindex 0x02 is correct)
    OBJ_MOTOR_POSITION = 0x2001, // Closed-loop position mode
    OBJ_MOTOR_SPEED = 0x2002,    // Closed-loop speed mode
    OBJ_MOTOR_COMMAND = 0x2000,  // Open-loop motor control
    OBJ_ENCODER_COUNT = 0x2104   // Encoder count (Verify address)
} CANOpenObject_t;

// ==================== FUNCTION PROTOTYPES ====================
void roboteq_init(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

// SDO Communication
void roboteq_sendSDO(uint16_t index, uint8_t subindex, uint32_t data, uint8_t size, uint8_t is_read);

// Motor Control
void roboteq_setMotorCommand(MotorChannel_t channel, int32_t speed);
void roboteq_setMotorSpeed(MotorChannel_t channel, int32_t speed_rpm);
void roboteq_setMotorPosition(MotorChannel_t channel, int32_t position);
void roboteq_setMotorAngle(MotorChannel_t channel, int angle);

// Queries
void roboteq_queryVoltage(void);
void roboteq_queryEncoderPosition(MotorChannel_t channel);

#endif // ROBOTEQ_H
