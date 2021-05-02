// Arduino_2 Coding

#include <SPI.h> // for SPI communication

#include <nRF24L01.h>

#include <RF24.h>

#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  

float lat,lon;                          // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(2,3);         //tx,rx
TinyGPS gps;                            // create gps object

RF24 radio(4,5); // CE, CSN

const uint64_t rAddress1 = {0x7878787878LL};
const uint64_t rAddress2 = {0xB3B4B5B6CDLL};  
const uint64_t rAddress3 = {0xB3B4B5B6F1LL}; 

char lati[10],longi[10];
char loca[25];
char text2[100];
char text3[100];

String textt1,textt2,textt3,textt4;

void setup() {
Serial.begin(9600);

analogWrite(A0,255);

lcd.init();                            // initialize the lcd     
lcd.backlight();                     // Print a message to the LCD.
   
gpsSerial.begin(9600);             // connect gps sensor

radio.begin();

radio.openWritingPipe(rAddress2);
radio.openReadingPipe(0,rAddress1);
radio.openReadingPipe(1,rAddress3);
radio.setPALevel(RF24_PA_MIN);

radio.stopListening();

}

void loop() {

char text1[] = "Arduino2"; // you can customize this text to your wish

 while (gpsSerial.available())
    {                                         // check for gps data
       if(gps.encode(gpsSerial.read()))          // encode gps data
       { 
         gps.f_get_position(&lat,&lon);            // get latitude and longitude
         String latitude = String(lat,6);
         String longitude = String(lon,6);
         latitude.toCharArray(lati,10);
         longitude.toCharArray(longi,10);
         strcpy(loca,lati);
         strcat(loca,";");
         strcat(loca,longi);
         Serial.println(loca); 
         radio.write(&loca, sizeof(loca));
         delay(5);  
       }
    } 
    
byte pipenum;
radio.startListening();
if (radio.available(&pipenum) || !radio.available()) { // if nrf has any incoming data
if (pipenum == 0)
{
   
   radio.read(&text2, sizeof(text2));
   delay(5);
   Serial.println(pipenum);
   Serial.println(text2);
   delay(5);
}
else 
{
  
  radio.read(&text3, sizeof(text3));
  delay(5);
  Serial.println(pipenum);
  Serial.println(text3);
  delay(5);
}
radio.stopListening();
}
textt1 = String(loca);
textt2 = String(text1);
textt3 = String(text2);
textt4 = String(text3);

Display(textt1,textt2,textt3,textt4);
}

void Display(String texts1,String texts2,String texts3, String texts4)
{ 
  String space = "                     ";
  String msg1,msg2,msg3,msg4;
  
  if (texts1.length() <= 20)
  {
    lcd.setCursor(0,0);
    lcd.print(texts1);
    msg1 = "null";
  }
  else
  {
    msg1 = space + texts1 + space;
  }
  
  if (texts2.length() <= 20)
  {
    lcd.setCursor(0,1);
    lcd.print(texts2);
    msg2 = "null";
  }
  else
  {
    msg2 = space + texts2 + space;
  }

  if (texts3.length() <= 20)
  {
    lcd.setCursor(0,2);
    lcd.print(texts3);
    msg3 = "null";
  }
   else
  {
    msg3 = space + texts3 + space;
  }

  if (texts4.length() <= 20)
  {
    lcd.setCursor(0,3);
    lcd.print(texts4);
    msg4 = "null";
  }
   else
  {
    msg4 = space + texts4 + space;
  }

  int maxi = max(max(msg1.length(),msg2.length()),max(msg3.length(),msg4.length()));
   
  for(int i = 20;i < maxi;i++)
  { 
    if (msg1 != "null")
    {
    String msgs1 = msg1.substring(i-20,i);   
    lcd.setCursor(0,0);
    lcd.print(msgs1);
    delay(250);
    }

    if (msg2 != "null")
    {
    String msgs2 = msg2.substring(i-20,i);   
    lcd.setCursor(0,1);
    lcd.print(msgs2);
    delay(250);
    }

    if (msg3 != "null")
    {
    String msgs3 = msg3.substring(i-20,i);   
    lcd.setCursor(0,2);
    lcd.print(msgs3);
    delay(250);
    }

    if (msg4 != "null")
    {
    String msgs4 = msg4.substring(i-20,i);   
    lcd.setCursor(0,3);
    lcd.print(msgs4);
    delay(250);
    }
  }
}
