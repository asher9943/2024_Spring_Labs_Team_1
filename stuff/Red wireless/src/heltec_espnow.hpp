#ifndef HELTEC_ESPNOW_H_
#define HELTEC_ESPNOW_H_

#include <WiFi.h>
#include <esp_now.h>


/******************************************************************
 *                          Variables
 ******************************************************************
 */

// broadcast address
extern const uint8_t broadcastAddr_D[];
extern const uint8_t broadcastAddr_A[];
extern const uint8_t broadcastAddr_S[];

// messaging structure
typedef struct esp_message {
  bool obsticle;
  bool dualFates_ready;
  bool dualFates_val;
} esp_message;

// esp-now message buffers
extern esp_message espMessageDataTx;
extern esp_message espMessageDataRx;



/******************************************************************
 *                          Protoypes
 ******************************************************************
 */

/*
 * ESP-NOW initialization, put in setup() before wifi_init()
 */
void heltec_espnow_Init(void);

/*
 * Data sent callback
 */
void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status);

/*
 * Data recieve callback
 */// turn left
void OnDataRecv_Callback(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif