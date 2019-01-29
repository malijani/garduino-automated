#include <dht.h>
#include <LiquidCrystal.h>
#include <util/atomic.h>
dht DHT;
#define DHT11_PIN 2
#define RELAY_PIN 3
#define FAN_PIN 10
extern volatile unsigned long timer0_millis;
unsigned long new_value=0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// another relay module needed to control humidity tool
void setup(){
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(FAN_PIN,OUTPUT);
  lcd.begin(16, 2);
}


void loop()
{  
    
//  int lightsOffDuration=21600000;
//  int lightsOnDuration=21600000+7200000;
  millis();
  //light off
  if (millis() <= 7200000){
  digitalWrite(RELAY_PIN,HIGH); // Turns relay off
  delay(15000);
  lcd.clear();
  lcd.setCursor(13,0);
  lcd.print("OFF");
  lcd.setCursor(0, 0);
  int chk = DHT.read11(DHT11_PIN);
  lcd.print("TEMP:");
  lcd.print((int)DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("HUM:");
  lcd.print((int)DHT.humidity);
  lcd.print("%");
  if((int)DHT.temperature >= 24){
    digitalWrite(FAN_PIN,HIGH);
    lcd.setCursor(9,1);
    lcd.print("fan");
  } else{
    digitalWrite(FAN_PIN,LOW);
    lcd.setCursor(9,1);
    lcd.print("   ");
  }
  if((int)DHT.temperature > 30 || (int)DHT.temperature < 20 && (int)DHT.humidity < 50){ // bad situation for flower
    lcd.setCursor(11,0);
    lcd.print("1"); // error code
  } else{
    lcd.setCursor(11,0);
    lcd.print("0");
  }
  int hours   = (int) (millis() / 60000);
  lcd.setCursor(13,1);
  lcd.print(hours);
  }
  // light on
  if(millis() > 7200000 && millis() <= 21600000+7200000){
  digitalWrite(RELAY_PIN,LOW); // Turns relay on
  delay(15000);
  lcd.clear();
  lcd.setCursor(13,0);
  lcd.print("ON ");
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.print((int)DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("HUM:");
  lcd.print((int)DHT.humidity);
  lcd.print("%");
  if((int)DHT.temperature >= 30){
    digitalWrite(FAN_PIN,HIGH);
    lcd.setCursor(9,1);
    lcd.print("fan");
  } else{
    digitalWrite(FAN_PIN,LOW);
    lcd.setCursor(9,1);
    lcd.print("   ");
  }
  if((int)DHT.temperature > 26 || (int)DHT.temperature < 18 && (int)DHT.humidity < 50){ // bad situation for flower
    lcd.setCursor(11,0);
    lcd.print("1"); // error code
  }  else{
    lcd.setCursor(11,0);
    lcd.print("0"); 
  }
  int hours   = (int) (millis() / 60000 - 120);
  lcd.setCursor(13,1);
  lcd.print(hours);
  }
  if(millis()>21600000+7200000){
  setMillis(new_value);
  }
}

void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}






