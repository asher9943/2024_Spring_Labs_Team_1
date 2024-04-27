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

#define RED_ADDR broadcastAddr_D
#define GRN_ADDR broadcastAddr_A
#define BLU_ADDR broadcastAddr_S


// messaging structure (if changed,)
typedef struct esp_message {
  bool maze_obsticle; // maze obsticle
  bool dualFates_rdy; // dual fates direction ready
  bool dualFates_val; // 0 -> left; 1 -> right
  bool start;         // next robot in line goes
  bool rescue;        // red robot needs rescue
} esp_message;


// esp-now message buffers
extern esp_message espMessageDataTx;
extern esp_message espMessageDataRx;



/******************************************************************
 *                          Protoypes
 ******************************************************************
 */

/*
 * ESP-NOW initialization
 */
void heltec_espnow_Init(void);

/*
 * Data sent callback
 */
void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status);

/*
 * Data recieve callback
 */
void OnDataRecv_Callback(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif