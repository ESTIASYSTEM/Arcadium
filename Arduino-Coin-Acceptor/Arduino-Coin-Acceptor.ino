//
//
//
#include <Arduino.h>

#define COIN_PIN XXX
#define LED_PIN XXX
#define INHIBIT_PIN XXX
//TODO
enum coin_mode
{
  acceptCoins = 0,
  refuseCoins = 1
};

// variable

volatile coin_mode;

bool acceptCoin = false;
char PCOrder;

unsigned int coins_stored;

void setup()
{

  Serial.begin(9600);

  // Depart
  coin_mode = refuse_coins;

}

void loop()
{

  if(Serial.available)
    PC_order = Serial.read();

  if(PC_order != "")
  {
    PCOrder = tolower(PCOrder);

    if(PCOrder == 'r') // mode refus
    {
      coin_mode = refuse_coins;
    }
  }

  switch(coin_mode)
  {
    case(acceptCoins):


    break;

    case(refuseCoins):

    break;

    default:

    break;
  }

  delay(500);



}
