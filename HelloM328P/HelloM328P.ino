// Hello MySensors

#define SN "Hello MySensors 328P"
#define SV "1.3"

/**
 * MySensors specific settings
 */
#define MY_SERIALDEVICE Serial
#define MY_NODE_ID (123)
// #define MY_TRANSPORT_WAIT_READY_MS (1000)

/**
 * Radio
 */
#define MY_RADIO_RFM69
#define MY_RFM69_NEW_DRIVER
// Network: 100=live, 99=test, 200=dev
//#define MY_RFM69_NETWORKID (200)
#define MY_IS_RFM69HW
// #define MY_RFM69_TX_POWER_DBM (20)
// #define MY_RFM69_CS_PIN (10)
// #define MY_RFM69_IRQ_PIN (2)
// #define MY_RFM69_IRQ_NUM (digitalPinToInterrupt(MY_RFM69_IRQ_PIN))

/**
 * Debug
 */
#define MY_DEBUG
// #define MY_SPECIAL_DEBUG
// #define MY_DEBUG_VERBOSE
// #define MY_DEBUG_VERBOSE_RFM69
// #define MY_DEBUG_VERBOSE_RFM69_REGISTERS

/**
 * Signing
 */

#define MY_SIGNING_ATSHA204
#define MY_SIGNING_REQUEST_SIGNATURES
#define MY_DEBUG_VERBOSE_SIGNING

#include <MySensors.h>


// sketch specific settings
const uint8_t PIN_LED_C = 8;
const uint8_t PIN_LED_A = 9;

enum CHILDS
{
  CHILD_SYSTEM, // not used
  CHILD_HELLO,  // node sends timestamps to this child
  CHILD_LED,    // controller sends LED on/off to this child
  CHILD_COUNT,
};

mysensors_sensor_t sensorTypes[CHILD_COUNT] =
{
  S_INFO,     // text
  S_INFO,     // timestamp
  S_BINARY,   // on/off
};

const char * sensorTitles[CHILD_COUNT] =
{
  "system",
  "timestamp",
  "led",
};

// used to send hello messages
MyMessage msg ( CHILD_HELLO, V_STATUS );
char msgBuffer[25];
  
void before ( )
{
  // LED connected to two arduino pins, saving wires
  pinMode ( PIN_LED_A, OUTPUT );
  pinMode ( PIN_LED_C, OUTPUT );
  pinMode ( MY_RFM69_CS_PIN, OUTPUT );
  pinMode ( MY_RFM69_IRQ_PIN, INPUT_PULLUP );

  digitalWrite ( PIN_LED_C, LOW );
  digitalWrite ( PIN_LED_A, HIGH ); // led on
};

void presentation()
{
  // Present sketch (name, version)
  sendSketchInfo(SN, SV);
  // Present childs
  
  for ( uint8_t i = 0; i < CHILD_COUNT; i++ )
  {
    present ( i, sensorTypes[i], sensorTitles[i] );
  };
  
};

// 
void receive(const MyMessage & message)
{
  if ( message.isAck ( ) )
  {
    MY_SERIALDEVICE.println ("Got ack from gateway");
    return;
  };
  
  message.getString ( msgBuffer );
  MY_SERIALDEVICE.print ( "received message for sensor " );
  MY_SERIALDEVICE.print ( message.sensor );
  MY_SERIALDEVICE.print ( ", type " );
  MY_SERIALDEVICE.print ( message.type );
  MY_SERIALDEVICE.print ( ", value " );
  MY_SERIALDEVICE.println ( msgBuffer );

  switch ( message.sensor )
  {
    case CHILD_LED:
      if ( message.type == V_STATUS )
        digitalWrite ( PIN_LED_A, message.getInt ( ) );
      break;
  };
};

void setup()
{
  Serial.begin ( 115200 );
  digitalWrite ( PIN_LED_A, LOW ); // led off
}

uint32_t timestampNextHello = 0;
const uint16_t HELLO_INTERVAL = 2000; // send hello message after 2 sec

void loop()
{
  if ( millis ( ) > timestampNextHello )
  {
    sprintf ( msgBuffer, "Hello %lu", millis ( ) );
    send ( msg.set ( msgBuffer ) );
    timestampNextHello = millis ( ) + HELLO_INTERVAL;
  };
};
