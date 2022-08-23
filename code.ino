#include <LiquidCrystal.h>

#define uls 12
#define buzzer 7
#define wheel 13
#define brakeled 11
#define alertled 10
#define led 9
#define ldr A0
#define tmp A1
#define acm 8
#define gas A2

LiquidCrystal lcd(6,5,4,3,2,1);

int lightvalue = 0;
int val = 0;
int gasValue = 0;

void setup() 
{
  lcd.begin(16,2);
  pinMode(ldr,INPUT);
  pinMode(tmp,INPUT);
  pinMode(gas,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(wheel,OUTPUT);
  pinMode(brakeled,OUTPUT);
  pinMode(alertled,OUTPUT);
}

void loop() 
{
  long duration, distance;
  int tempadc, tempc;
  int gasValue;
  pinMode(uls, OUTPUT);
  digitalWrite(uls, HIGH);
  pinMode(uls, INPUT);
  duration = pulseIn(uls, HIGH);
  distance = duration/58;
  digitalWrite(wheel, HIGH);
  digitalWrite(brakeled, LOW);
  digitalWrite(alertled, LOW);
  pinMode(gas, OUTPUT);
  digitalWrite(gas, HIGH);
  pinMode(gas, INPUT);
  
  if (distance>=70 && distance<90)
  {
    digitalWrite(alertled,HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("OBSTACLE IN     ");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.println(" CM GO SLOW!   ");
    delay(1000);
    lcd.clear();
  }
  else if (distance>=50 && distance<70)
  {
    tone(buzzer,HIGH);
    digitalWrite(alertled,HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("OBSTACLE IN     ");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.println(" CM SLOW DOWN!  ");
    delay(1000);
    noTone(buzzer);
    lcd.clear();
  }
  else if (distance<50)
  {
    tone(buzzer,HIGH);   
    digitalWrite(wheel,LOW);
    digitalWrite(brakeled,HIGH);
    digitalWrite(alertled,HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("AUTOMATIC       ");
    lcd.setCursor(0,1);
    lcd.print ("BRAKES ENGAGED  ");
    delay(1000);
    noTone(buzzer);
    lcd.clear();
  }
  else
  {
    noTone(buzzer);
  }
  
  lightvalue = analogRead(ldr);
  lightvalue = map(lightvalue,6,679,255,0);
  val= lightvalue;  
  analogWrite(led,val);
  
  tempadc = analogRead(tmp);
  tempc = int(((tempadc*4.88)/10)-50);
  
  if(tempc>27)
  {
    digitalWrite(acm, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("TEMPERATURE IS  ");
    lcd.setCursor(0,1);
    lcd.print(tempc);
    lcd.print (" C AC ON        ");
    delay(1000);
    lcd.clear();
  }
  else 
  {
    digitalWrite(acm, LOW);
  }
  
  gasValue=analogRead(gas);
  if(gasValue>100)
  {
    digitalWrite(alertled,HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("POLLUTION IS    ");
    lcd.setCursor(0,1);
    lcd.print(gasValue);
    lcd.println(" PPM HIGH       ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("VISIT CAR       ");
    lcd.setCursor(0,1);
    lcd.println("SERVICE         ");
    delay(1000);
    lcd.clear();
  }
  else
  {
    delay(10);
  }
}        
