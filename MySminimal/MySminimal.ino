// MySensors minimum node
#define USE_SIGNING
#define USE_NRF24_AND_NOT_RFM69

#define SN "MySensors minimum"
#define SV "0.1"
#define MY_TRANSPORT_WAIT_READY_MS (1000)
#ifdef USE_NRF24_AND_NOT_RFM69
  #define MY_RADIO_RF24
#else
  #define MY_RADIO_RFM69
  #define MY_RFM69_NEW_DRIVER
  //#define MY_RFM69_NETWORKID (200)
  #define MY_IS_RFM69HW
#endif
#define MY_DEBUG
#ifdef USE_SIGNING
  #define MY_SIGNING_ATSHA204_PIN 17
  #define MY_SIGNING_ATSHA204
  #define MY_SIGNING_REQUEST_SIGNATURES
  #define MY_DEBUG_VERBOSE_SIGNING
#endif
#include <MySensors.h>
void setup() { }
void loop() { }
