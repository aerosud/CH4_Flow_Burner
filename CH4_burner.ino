#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int fire_start = 2;
int blower_on = 3;
int blower_feedback = 4;
int pneumatic_valve = 5;
int valve_feedback = 6;
int pneumatic_valve2 = 7;
int ch4_sensor = 8; 
int ignition_coil = 9;
int fire_sensor = 10;
int alaram = 11; 
int auto_stop = 13; 
int reset = 12;
int temp_sensor = A1;
int temp;
int i = 0;
//int temp = 0;
//int temp_value; // variable for reading the sensor status
 LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{ 
 lcd.init();
 lcd.backlight();
 Serial.begin(9600);
pinMode(ch4_sensor, INPUT); 
pinMode(fire_sensor, INPUT);
pinMode(fire_start, INPUT);
pinMode(temp_sensor, INPUT);
pinMode(ignition_coil,OUTPUT);
pinMode(pneumatic_valve,OUTPUT);
pinMode(pneumatic_valve2,OUTPUT);
pinMode(blower_on,OUTPUT);
pinMode(blower_feedback,INPUT);
pinMode(valve_feedback,INPUT);
pinMode(alaram,OUTPUT); 
pinMode(auto_stop,OUTPUT); 
pinMode(reset, INPUT);

lcd.print(" Green Energy ");
 lcd.setCursor(2,1);
 lcd.print(" Projects ");
 delay(3000);
 Serial.println("GREEN ENERGY PROJECTS");
 lcd.clear();

lcd.setCursor(0,0);
lcd.print(" Methane (CH4)");
lcd.setCursor(0,1);
lcd.print("Fire Controller");
delay(3000);
lcd.clear();
}

void loop()
{
temp = analogRead(temp_sensor);
temp = temp * 0.5;
lcd.clear(); 
lcd.setCursor(9,1);
lcd.print("T=");
 lcd.print(temp); // display temperature value
 lcd.print(" C"); 
 
if (!digitalRead (fire_start))
 {
  digitalWrite(pneumatic_valve, LOW);
  digitalWrite(pneumatic_valve2, LOW); 
  digitalWrite(ignition_coil, LOW);
  digitalWrite(blower_on, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Fire Cmd STOP ");
  delay(1000); 
 }
 
if (digitalRead (fire_start))
{  
  lcd.setCursor(0, 0);
  lcd.print("Fire Cmd Start");
  digitalWrite(blower_on, HIGH);
  delay(1000);
  if (digitalRead (blower_feedback))
   {
   digitalWrite(pneumatic_valve, HIGH);
   lcd.setCursor(0, 1);
   lcd.print("Fan ON"); 
   digitalWrite(alaram, LOW);
   delay(1000);
   }
  else 
   {
   digitalWrite(pneumatic_valve, LOW);
   digitalWrite(alaram, HIGH);
   lcd.setCursor(0, 1);
   lcd.print("Fan Trip");
   delay(3000);
   }

  if (digitalRead (valve_feedback)) 
   {
   digitalWrite(pneumatic_valve2, HIGH); 
   digitalWrite(ignition_coil, HIGH);
   digitalWrite(alaram, LOW);
   }
 else
 {
   digitalWrite(pneumatic_valve2, LOW); 
   digitalWrite(ignition_coil, LOW);
   digitalWrite(alaram, HIGH);
   lcd.setCursor(0, 1);
   lcd.print("V-1 Fail");
   delay(3000);
 }
  delay(1000);
  if (digitalRead (ch4_sensor))
   {
   lcd.setCursor(0, 1);
   lcd.print("Gas ON"); 
   digitalWrite(alaram, LOW);
   delay(1000);
   }
  else
   {
   lcd.setCursor(0, 1);
   lcd.print("Gas-Off ");
   digitalWrite(alaram, HIGH);
   delay(1000);
   }
  if (digitalRead (fire_sensor))
   {
   lcd.setCursor(0,1);
   lcd.print("Fire ON");
   digitalWrite(alaram, LOW);
   delay(1000);
   }
else  
   {
   lcd.setCursor(0,1);
   lcd.print("Fire OFF");
   i = i + 1;
   digitalWrite(alaram, HIGH);
   delay(1000);
   } 
}
if(i == 5){
  digitalWrite(auto_stop, HIGH);  // Fire Command Stopped.
  lcd.setCursor(0,1);
  lcd.print("Auto OFF");
  delay(3000);
  }
 
 if(digitalRead (reset))
  {
  digitalWrite(auto_stop, LOW);  //Fir commend Start through this realy 'NC'
  i=0;
  delay(1000);
  }
}
