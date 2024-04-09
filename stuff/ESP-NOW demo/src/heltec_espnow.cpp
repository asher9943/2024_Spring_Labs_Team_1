#include "heltec_espnow.hpp"


/******************************************************************
 *                          Variables
 ******************************************************************
 */

// robot using the code
#define USER_DONALD
// #define USER_ASHER
// #define USER_STEPHEN


// messaging structure
typedef struct esp_message {
  char a[32];
  int b;
  float c;
  bool d;
} esp_message;

esp_message espMessageData;


// peer info
uint8_t donaldAddr[]  = {0x30,0xC6,0xF7,0x14,0x33,0xBC};
uint8_t asherAddr[]   = {0x78,0x21,0x84,0x9E,0xFA,0xF4};
uint8_t stephenAddr[] = {0x78,0x21,0x84,0x99,0x63,0x24};

esp_now_peer_info_t peerInfo;



/******************************************************************
 *                          Functions
 ******************************************************************
 */

void heltec_espnow_Init(void) {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  
  esp_now_register_send_cb(OnDataSent_Callback);


  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  #ifndef USER_DONALD
  memcpy(peerInfo.peer_addr, donaldAddr, 6);    
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  #endif

  #ifndef USER_ASHER
  memcpy(peerInfo.peer_addr, asherAddr, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  #endif

  #ifndef USER_STEPHEN
  memcpy(peerInfo.peer_addr, stephenAddr, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  #endif

}

void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
