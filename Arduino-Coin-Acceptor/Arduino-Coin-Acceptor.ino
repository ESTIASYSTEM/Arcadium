//https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/
/**@author Adri1G
 * @brief receive a value from coin acceptor (RS232 link), convert the value in € ( 1€ = 100 integer in this program,
 *  and send impulse to arcade cabinet.
 * Currency in integer to avoid double imprecision by design, cf
 * https://stackoverflow.com/questions/23137719/incorrect-rounding-of-currency-double-values.
 * 
 * Currency
 * Each coin is associated with a value in coin acceptor
 * C1 : 2€       Value coin acceptor    40
 * C2 : 1€       Value coin acceptor    20
 * C3 : 0,50€    Value coin acceptor    10
 * C4 : 0,20€    Value coin acceptor    4
 * C5 : 0,10€    Value coin acceptor    2
 * C6 : 0,05€    Value coin acceptor    1
 * 
 * To avoid problem with software serial (no hardware buffer), the port use is RX to receive data from coin acceptor
 * 
 * Pin map on Arduino Nano:
 * RX: SIGNAL (coin acceptor)                   /!\KEEP MIND TO UNPLUG BEFORE TÉLÉVERSER
 * Vin: 12v
 * Gnd: with coin acceptor and generator
 * 
 * Pin map coin acceptor
 * GND
 * SIGNAL (to Arduino)
 * DC12V
 * PIN_PC: 2 to connect with the PC via button
 * 
 * Coin acceptor Switch configuration :
 * SW1: OFF
 * SW2: OFF
 * SW3: ON
 * SW4: OFF
 * 
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

#define GAME_PRICE 10                         // ratio: € x 100, exemple: one game (impluse) at 0,1€ is GAME_PRICE 10
#define RATIO_CURRENCY_COIN_ACCEPTOR_SIGNAL 5 // ratio to convert value from coin acceptor in €
#define SENDING_INTERVAL 250                  //send a signal each intervale
#define LED_PIN 13
#define PIN_PC  2

unsigned int coin_value = 0; //1€ = 100 integer
unsigned long previous_Millis = 0;
unsigned long current_Millis;
bool high_state_sending = false;


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
  Serial.println("Coin Acceptor Ready!");

  pinMode(PIN_PC, OUTPUT); //use to send credit to arcade cabinet
  digitalWrite(PIN_PC, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{

  //TODO pass receveid value coin function to interrup

  // any input coming from coin acceptor?
  if (Serial.available())
  {
    unsigned int input_value = Serial.read();
    // read input, which is a 1 byte integer
    // coin acceptor send two value, whose one is allways 170
    if (input_value < 170)
    {
      coin_value += (int)input_value * RATIO_CURRENCY_COIN_ACCEPTOR_SIGNAL; //ratio to adapt the value send by the coin acceptor
      Serial.print("Monnaie reçue ");
      Serial.println(coin_value);
    }
  }

  if (coin_value > 0)
  {
    current_Millis = millis();

    if (abs(current_Millis - previous_Millis) >= SENDING_INTERVAL)
    {
      Serial.println(high_state_sending);   //to count impulse send
      //if there is some money and state is high, send a falling edge

      if (high_state_sending)
      {
        coin_value -= GAME_PRICE;
        digitalWrite(PIN_PC, LOW);
        digitalWrite(LED_PIN, LOW);
        high_state_sending = false;
        previous_Millis = current_Millis;
      }
      //else send a rising edge
      else
      {
        digitalWrite(PIN_PC, HIGH);
        digitalWrite(LED_PIN, HIGH);
        high_state_sending = true;
        previous_Millis = current_Millis;
      }
    }
  }
}
