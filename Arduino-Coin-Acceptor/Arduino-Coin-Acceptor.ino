//https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/
/**@author Adri1G
 * @brief receive a value from coin acceptor (RS232 link), convert the value in € ( 1€ = 100 in this program)
 * and send impulse to arcade cabinet
   Pin map:
   2 (D2) Arduino on coin acceptor Signal


   Switch configuration coin acceptor :
   OFF: SW1, SW2, SW4
   ON: SW3
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

#define RATIO_CURRENCY_COIN_ACCEPTOR_SIGNAL 5 // ratio to convert value from coin acceptor in €
#define SENDING_INTERVAL 250                  //send a signal each intervale
#define GAME_PRICE 10                         // ratio: € x 100, exemple: one game at 0,05€ is GAME_PRICE = 10
#define LED_PIN 13

SoftwareSerial mySerial(2, 3); // RX, TX

volatile int coin_value = 0; //1€ = 100 int, to avoid double imprecision by design https://stackoverflow.com/questions/23137719/incorrect-rounding-of-currency-double-values
unsigned long previous_Millis = 0;
unsigned long current_Millis;
bool high_state_sending = false;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Coin Acceptor Ready!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);

  pinMode(4, OUTPUT); //use to send credit to arcade cabinet
  digitalWrite(4, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  //TODO pass receveid value coin function to interrup

  // any input coming from coin acceptor?
  if (mySerial.available())
  {
    volatile int input_value = mySerial.read();
    // read input, which is a 1 byte integer
    // coin acceptor send two value, whose one is worth 170, if to check this
    if (input_value < 170)
    {
      coin_value = (int)input_value * RATIO_CURRENCY_COIN_ACCEPTOR_SIGNAL; //ratio to adapt the value send by the coin acceptor
      Serial.print("Monnaie reçue ");
      Serial.println(coin_value);
    }
  }

  if (coin_value > 0)
  {
    current_Millis = millis();
    //if there is some money  and state is low, send a rising edge
    if (current_Millis - previous_Millis >= SENDING_INTERVAL)
    {
      if (!high_state_sending)
      {
        coin_value -= GAME_PRICE;
        digitalWrite(4, HIGH);
        digitalWrite(LED_PIN, HIGH);
        high_state_sending = true;
        previous_Millis = current_Millis;
      }
      //else send a falling edge
      else
      {
        digitalWrite(4, LOW);
        digitalWrite(LED_PIN, LOW);
        high_state_sending = false;
        previous_Millis = current_Millis;
      }
    }
  }
}
