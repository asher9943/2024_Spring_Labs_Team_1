#ifndef HELTEC_ESPNOW_H_
#define HELTEC_ESPNOW_H_

#include <WiFi.h>
#include <esp_now.h>


/******************************************************************
 *                          Variables
 ******************************************************************
 */

extern esp_message espMessageDataTx;
extern esp_message espMessageDataRx;

extern uint8_t donaldAddr[];
extern uint8_t asherAddr[];
extern uint8_t stephenAddr[];



/******************************************************************
 *                          Protoypes
 ******************************************************************
 */

// initialize
void heltec_espnow_Init(void);

// something
void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status);

void OnDataRecv_Callback(const uint8_t * mac, const uint8_t *incomingData, int len);

#endif