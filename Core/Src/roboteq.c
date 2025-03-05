#include "roboteq.h"
#include "stdio.h"
#include "string.h"

#define NODE_ID 1
#define ENCODER_CPR 16384  // 4096 PPR * 4 (Quadrature)

extern CAN_HandleTypeDef hcan;

// CAN Headers
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;

// ==================== INITIALIZATION ====================
void roboteq_init(void) {
    HAL_CAN_Start(&hcan);
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

// ==================== SDO COMMUNICATION ====================
void roboteq_sendSDO(uint16_t index, uint8_t subindex, uint32_t data, uint8_t size, uint8_t is_read) {
    TxHeader.StdId = 0x600 + NODE_ID;
    TxHeader.DLC = 8;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;

    memset(TxData, 0, sizeof(TxData));

    TxData[0] = is_read ? 0x40 : 0x23;  // Read (0x40) or Write (0x23)
    TxData[1] = index & 0xFF;
    TxData[2] = (index >> 8) & 0xFF;
    TxData[3] = subindex;

    if (!is_read) {
        memcpy(&TxData[4], &data, size);
    }

    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
        printf("[ERROR] Failed to send CAN SDO\n");
    }
}

// ==================== MOTOR CONTROL ====================
void roboteq_setMotorCommand(MotorChannel_t channel, int32_t speed) {
    if (speed < -1000 || speed > 1000) {
        printf("[ERROR] Speed out of range (-1000 to 1000)\n");
        return;
    }
    roboteq_sendSDO(OBJ_MOTOR_COMMAND, channel, speed, sizeof(int32_t), 0);
}

void roboteq_setMotorSpeed(MotorChannel_t channel, int32_t speed_rpm) {
    if (speed_rpm < -65535 || speed_rpm > 65535) {
        printf("[ERROR] Speed out of range (-65535 to 65535 RPM)\n");
        return;
    }
    roboteq_sendSDO(OBJ_MOTOR_SPEED, channel, speed_rpm, sizeof(int32_t), 0);
}

void roboteq_setMotorPosition(MotorChannel_t channel, int32_t position) {
    roboteq_sendSDO(OBJ_MOTOR_POSITION, channel, position, sizeof(int32_t), 0);
}

void roboteq_setMotorAngle(MotorChannel_t channel, int angle) {
    int32_t encoder_counts = (angle * ENCODER_CPR) / 360;  // Integer math
    printf("[ANGLE TO COUNT] Angle: %d° -> Counts: %d\n", angle, encoder_counts);
    roboteq_setMotorPosition(channel, encoder_counts);
}

// ==================== QUERIES ====================
void roboteq_queryVoltage(void) {
    roboteq_sendSDO(OBJ_VOLTAGE, 0x02, 0, 0, 1);
}

void roboteq_queryEncoderPosition(MotorChannel_t channel) {
    roboteq_sendSDO(OBJ_ENCODER_COUNT, channel, 0, 0, 1);
}

// ==================== CALLBACK HANDLING ====================
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
        printf("\n[CAN RX] StdID: 0x%lX DLC: %u | Data: ", (unsigned long)RxHeader.StdId, RxHeader.DLC);
        for (int i = 0; i < RxHeader.DLC; i++) {
            printf("0x%02X ", RxData[i]);
        }
        printf("\n");

        // Voltage Response
        if ((RxHeader.StdId & 0xFF0) == 0x580 && RxData[1] == 0x0D && RxData[2] == 0x21) {
            uint16_t voltage = (RxData[5] << 8) | RxData[4];
            printf("[VOLTAGE] %d V\n", voltage);
        }

        // Encoder Response
        if ((RxHeader.StdId & 0xFF0) == 0x580 && RxData[1] == 0x04 && RxData[2] == 0x21) {
            int32_t encoder_count;
            memcpy(&encoder_count, &RxData[4], sizeof(int32_t));
            printf("[ENCODER] Current Position: %d\n", encoder_count);
        }

        // SDO Acknowledgement
        if ((RxHeader.StdId & 0xFF0) == 0x580) {
            if (RxData[0] == 0x60) {
                printf("[ACK] SDO Command Acknowledged\n");
            } else if (RxData[0] == 0x80) {
                printf("[ERROR] SDO Transfer Failed!\n");
            }
        }
    }
}
