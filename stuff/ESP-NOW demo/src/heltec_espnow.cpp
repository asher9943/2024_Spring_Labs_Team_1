#include "heltec_espnow.hpp"


#define USER_DONALD
// #define USER_ASHER
// #define USER_STEPHEN


/******************************************************************
 *                          Variables
 ******************************************************************
 */

// broadcast MAC address
const uint8_t broadcastAddr_D[] = {0x30,0xC6,0xF7,0x14,0x33,0xBC}; //Donald
const uint8_t broadcastAddr_A[] = {0x78,0x21,0x84,0x9E,0xFA,0xF4}; //Asher
const uint8_t broadcastAddr_S[] = {0x78,0x21,0x84,0x99,0x63,0x24}; //Stephen

// peer info
esp_now_peer_info_t peerInfo;

// message buffers
esp_message espMessageDataTx;
esp_message espMessageDataRx;



/******************************************************************
 *                          Functions
 ******************************************************************
 */

// initialize esp-now
void heltec_espnow_Init(void) {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  esp_now_register_send_cb(OnDataSent_Callback);
  esp_now_register_recv_cb(OnDataRecv_Callback);


  #ifndef USER_DONALD
    memcpy(peerInfo.peer_addr, broadcastAddr_D, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
    }
  #endif
  #ifndef USER_ASHER
    memcpy(peerInfo.peer_addr, broadcastAddr_A, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
    }
  #endif
  #ifndef USER_STEPHEN
    memcpy(peerInfo.peer_addr, broadcastAddr_S, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
    }
  #endif
}

// data sent callback
void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// data recieve callback
void OnDataRecv_Callback(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espMessageDataRx, incomingData, sizeof(espMessageDataRx));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(espMessageDataRx.a);
  Serial.print("Int: ");
  Serial.println(espMessageDataRx.b);
  Serial.print("Float: ");
  Serial.println(espMessageDataRx.c);
  Serial.print("Bool: ");
  Serial.println(espMessageDataRx.d);
  Serial.println();
}
