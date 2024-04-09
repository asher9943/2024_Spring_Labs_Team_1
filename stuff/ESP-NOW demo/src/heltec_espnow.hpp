#ifndef HELTEC_ESPNOW_H_
#define HELTEC_ESPNOW_H_

#include <WiFi.h>
#include <esp_now.h>


/******************************************************************
 *                          Variables
 ******************************************************************
 */

extern esp_message espMessageData;

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

#endif