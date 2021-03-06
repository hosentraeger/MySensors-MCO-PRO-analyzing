// Hello MySensors
#define USE_SIGNING
#define USE_NRF24_AND_NOT_RFM69
#define NO_PERIODIC_TASKS

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
#ifdef USE_NRF24_AND_NOT_RFM69
  #define MY_RADIO_RF24
#else
  #define MY_RADIO_RFM69
  #define MY_RFM69_NEW_DRIVER
  // Network: 100=live, 42=live(new driver), 99=test, 200=dev
  #define MY_RFM69_NETWORKID (200)
  #define MY_IS_RFM69HW
  #define MY_RFM69_TX_POWER_DBM (20)
  #define MY_RFM69_CS_PIN (10)
  #define MY_RFM69_IRQ_PIN (2)
  #define MY_RFM69_IRQ_NUM (digitalPinToInterrupt(MY_RFM69_IRQ_PIN))
#endif
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

#ifdef USE_SIGNING
  #define MY_SIGNING_ATSHA204_PIN 17
  #define MY_SIGNING_ATSHA204
  #define MY_SIGNING_REQUEST_SIGNATURES
  #define MY_DEBUG_VERBOSE_SIGNING
#endif

#include <MySensors.h>


// sketch specific settings
const uint8_t PIN_LED_C = 14;
const uint8_t PIN_LED_A = 15;

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

void printConfig ( )
{
  MY_SERIALDEVICE.println ( F ( "***********************************************" ) );
  MY_SERIALDEVICE.println ( SN );
  MY_SERIALDEVICE.print ( "Version " );
  MY_SERIALDEVICE.println ( SV );
  MY_SERIALDEVICE.print ( F ( "Radio type: " ) );
#ifdef USE_NRF24_AND_NOT_RFM69
    MY_SERIALDEVICE.println ( F ( "NRF24" ) );
#else
    MY_SERIALDEVICE.println ( F (  "RFM69" ) );
    MY_SERIALDEVICE.print ( F ( "network id: " ) );
    MY_SERIALDEVICE.println ( MY_RFM69_NETWORKID );
#ifdef MY_RFM69_NEW_DRIVER
    MY_SERIALDEVICE.println ( F ( "driver: new" ) );
#else
    MY_SERIALDEVICE.println ( F ( "driver: old" ) );
#endif
#endif
  MY_SERIALDEVICE.print ( F ( "signing: " ) );
#ifdef USE_SIGNING
    MY_SERIALDEVICE.println ( "yes" );
#else
    MY_SERIALDEVICE.println ( "no" );
#endif
}
  
void before ( )
{
  MY_SERIALDEVICE.begin ( 115200 );
  printConfig ( );
  // LED connected to two arduino pins, saving wires
  pinMode ( PIN_LED_A, OUTPUT );
  pinMode ( PIN_LED_C, OUTPUT );
#ifdef USE_NRF24_AND_NOT_RFM69
#else
  pinMode ( MY_RFM69_CS_PIN, OUTPUT );
  pinMode ( MY_RFM69_IRQ_PIN, INPUT_PULLUP );
#endif
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
  
//  message.getString ( msgBuffer );

  strcpy(msgBuffer, message.getString());        // copy it in
  MY_SERIALDEVICE.print ( msgBuffer[0] );
  MY_SERIALDEVICE.println ( );
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
  digitalWrite ( PIN_LED_A, LOW ); // led off
}

uint32_t timestampNextHello = 0;
const uint16_t HELLO_INTERVAL = 2000; // send hello message after 2 sec

void loop()
{
#ifndef NO_PERIODIC_TASKS
  if ( millis ( ) > timestampNextHello )
  {
    sprintf ( msgBuffer, "Hello %lu", millis ( ) );
    send ( msg.set ( msgBuffer ) );
    timestampNextHello = millis ( ) + HELLO_INTERVAL;
  };
#endif
};
