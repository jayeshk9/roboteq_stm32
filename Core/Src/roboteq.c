#include "roboteq.h"
#include "stdio.h"
#include "string.h"

#define ENCODER_CPR 16384  // 4096 PPR * 4 (Quadrature)

extern CAN_HandleTypeDef hcan;



// CAN Tx & Rx Headers
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;

//// Callback to handle received messages
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
//    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
//        printf("\n[CAN RX] StdID: 0x%lX DLC: %u\n", (unsigned long)RxHeader.StdId, RxHeader.DLC);
//
//        if ((RxHeader.StdId & 0xFF0) == 0x580 && RxHeader.DLC == 8) {
//            uint16_t voltage_raw = (uint16_t)((RxData[5] << 8) | RxData[4]);
//            printf("[Voltage] Raw: 0x%04X (%u)\n", voltage_raw, voltage_raw);
//        }
//    }
//}
//
//// Send an SDO message
//void roboteq_sendSDO(uint8_t node_id, uint16_t index, uint8_t subindex, uint32_t data, uint8_t size, uint8_t is_read) {
//    TxHeader.StdId = 0x600 + node_id;
//    TxHeader.DLC = 8;
//    TxHeader.IDE = CAN_ID_STD;
//    TxHeader.RTR = CAN_RTR_DATA;
//
//    memset(TxData, 0, sizeof(TxData));
//
//    TxData[0] = is_read ? 0x40 : 0x23;  // Read (0x40) or Write (0x23)
//    TxData[1] = index & 0xFF;
//    TxData[2] = (index >> 8) & 0xFF;
//    TxData[3] = subindex;
//
//    if (!is_read) {
//        memcpy(&TxData[4], &data, size);
//    }
//
//    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
//        printf("[CAN TX] SDO Sent: Index 0x%04X, Subindex 0x%02X, NodeID: %d\n", index, subindex, node_id);
//    } else {
//        printf("[ERROR] Failed to send CAN message\n");
//    }
//}

// Query Voltage
void roboteq_queryVoltage(uint8_t node_id) {
    roboteq_sendSDO(node_id, 0x210D, 0x02, 0, 0, 1);
}


// Callback to handle received messages (Acknowledgement & Debug)
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
//    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
//        // Print raw message
//        printf("\n[CAN RX] StdID: 0x%lX DLC: %u | Data: ", (unsigned long)RxHeader.StdId, RxHeader.DLC);
//        for (int i = 0; i < RxHeader.DLC; i++) {
//            printf("0x%02X ", RxData[i]);
//        }
//        printf("\n");
//
//        // Check for SDO Acknowledgement (0x580 + Node ID)
//        if ((RxHeader.StdId & 0xFF0) == 0x580) {
//            if (RxData[0] == 0x60) {
//                printf("[ACK] SDO Command Acknowledged by Node %d\n", RxHeader.StdId - 0x580);
//            } else if (RxData[0] == 0x80) {
//                printf("[ERROR] SDO Transfer Failed!\n");
//            }
//        }
//    }
//}
//
//// Function to send motor command in Open Loop Mode
//void roboteq_setMotorCommand(uint8_t node_id, uint8_t channel, int32_t speed) {
//    if (speed < -1000 || speed > 1000) {
//        printf("[ERROR] Speed out of range! Must be between -1000 and 1000.\n");
//        return;
//    }
//
//    TxHeader.StdId = 0x600 + node_id;  // SDO Request
//    TxHeader.DLC = 8;
//    TxHeader.IDE = CAN_ID_STD;
//    TxHeader.RTR = CAN_RTR_DATA;
//
//    memset(TxData, 0, sizeof(TxData));
//
//    TxData[0] = 0x23;  // Write Command
//    TxData[1] = 0x00;  // Index LSB (0x2000 for CG)
//    TxData[2] = 0x20;  // Index MSB
//    TxData[3] = channel;  // Motor Channel (1 or 2)
//
//    memcpy(&TxData[4], &speed, sizeof(int32_t));  // Copy speed value
//
//    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
//        printf("[CAN TX] Sent Motor Command - Channel: %d, Speed: %d\n", channel, speed);
//    } else {
//        printf("[ERROR] Failed to send Motor Command\n");
//    }
//}

// CLOSED LOOP SPEED
// Callback to handle received messages (Acknowledgement & Debug)
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
//    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
//        // Print raw message
//        printf("\n[CAN RX] StdID: 0x%lX DLC: %u | Data: ", (unsigned long)RxHeader.StdId, RxHeader.DLC);
//        for (int i = 0; i < RxHeader.DLC; i++) {
//            printf("0x%02X ", RxData[i]);
//        }
//        printf("\n");
//
//        // Check for SDO Acknowledgement (0x580 + Node ID)
//        if ((RxHeader.StdId & 0xFF0) == 0x580) {
//            if (RxData[0] == 0x60) {
//                printf("[ACK] SDO Command Acknowledged by Node %d\n", RxHeader.StdId - 0x580);
//            } else if (RxData[0] == 0x80) {
//                printf("[ERROR] SDO Transfer Failed!\n");
//            }
//        }
//    }
//}
//
//// Function to set motor speed in Closed-Loop Speed Mode
//void roboteq_setMotorSpeed(uint8_t node_id, uint8_t channel, int32_t speed_rpm) {
//    if (speed_rpm < -65535 || speed_rpm > 65535) {
//        printf("[ERROR] Speed out of range! Must be between -65535 and 65535 RPM.\n");
//        return;
//    }
//
//    TxHeader.StdId = 0x600 + node_id;  // SDO Request
//    TxHeader.DLC = 8;
//    TxHeader.IDE = CAN_ID_STD;
//    TxHeader.RTR = CAN_RTR_DATA;
//
//    memset(TxData, 0, sizeof(TxData));
//
//    TxData[0] = 0x23;  // Write Command
//    TxData[1] = 0x02;  // Index LSB (0x2002 for MOTVEL)
//    TxData[2] = 0x20;  // Index MSB
//    TxData[3] = channel;  // Motor Channel (1 or 2)
//
//    memcpy(&TxData[4], &speed_rpm, sizeof(int32_t));  // Copy speed value
//
//    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
//        printf("[CAN TX] Set Motor Speed - Channel: %d, Speed: %d RPM\n", channel, speed_rpm);
//    } else {
//        printf("[ERROR] Failed to send Motor Speed Command\n");
//    }
//}


//CLOSED LOOP POSITION
// Callback to handle received messages (Acknowledgement & Debug)
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
        // Print raw message
        printf("\n[CAN RX] StdID: 0x%lX DLC: %u | Data: ", (unsigned long)RxHeader.StdId, RxHeader.DLC);
        for (int i = 0; i < RxHeader.DLC; i++) {
            printf("0x%02X ", RxData[i]);
        }
        printf("\n");

        // Check for Encoder Response (Index 0x6064 -> SDO Response 0x580 + Node ID)
        if ((RxHeader.StdId & 0xFF0) == 0x580 && RxHeader.DLC == 8 && RxData[1] == 0x04 && RxData[2] == 0x21) {
            int32_t encoder_count;
            memcpy(&encoder_count, &RxData[4], sizeof(int32_t));
            printf("[ENCODER] Current Position: %d\n", encoder_count);
        }

        // Check for SDO Acknowledgement (0x580 + Node ID)
        if ((RxHeader.StdId & 0xFF0) == 0x580) {
            if (RxData[0] == 0x60) {
                printf("[ACK] SDO Command Acknowledged by Node %d\n", RxHeader.StdId - 0x580);
            } else if (RxData[0] == 0x80) {
                printf("[ERROR] SDO Transfer Failed!\n");
            }
        }
    }
}


//Function to set motor absolute position in Closed-Loop Count Position Mode
void roboteq_setMotorPosition(uint8_t node_id, uint8_t channel, int32_t position) {
    if (position < -2147483648 || position > 2147483647) {
        printf("[ERROR] Position out of range! Must be between -2147483648 and 2147483647.\n");
        return;
    }

    TxHeader.StdId = 0x600 + node_id;  // SDO Request
    TxHeader.DLC = 8;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;

    memset(TxData, 0, sizeof(TxData));

    TxData[0] = 0x23;  // Write Command
    TxData[1] = 0x01;  // Index LSB (0x2001 for MOTPOS)
    TxData[2] = 0x20;  // Index MSB
    TxData[3] = channel;  // Motor Channel (1 or 2)

    memcpy(&TxData[4], &position, sizeof(int32_t));  // Copy position value

    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
        printf("[CAN TX] Set Motor Position - Channel: %d, Position: %d\n", channel, position);
    } else {
        printf("[ERROR] Failed to send Motor Position Command\n");
    }
}

// Function to query encoder position
void roboteq_queryEncoderPosition(uint8_t node_id, uint8_t channel) {
    TxHeader.StdId = 0x600 + node_id;  // SDO Request
    TxHeader.DLC = 8;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;

    memset(TxData, 0, sizeof(TxData));

    TxData[0] = 0x40;  // Read Command
    TxData[1] = 0x04;  // Index LSB (0x2104 for Encoder Count)
    TxData[2] = 0x21;  // Index MSB
    TxData[3] = channel;  // Motor Channel (1 or 2)
    TxData[4] = 0x00;
    TxData[5] = 0x00;
    TxData[6] = 0x00;
    TxData[7] = 0x00;

    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
        printf("[CAN TX] Encoder Query Sent for Channel: %d\n", channel);
    }
}


