

#include <Adafruit_MLX90614.h>
#include "U8glib.h"

  int a=0;
  int b=0;
   char temp_string[5]; //empty char array to hold the converted temp float 
   float hum_float;
   float new_temp=0.0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// display constructor for u8g library - this one depends on your type of display
  U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE);



void setup() {  
  mlx.begin();
  Serial.begin(9600);                     // start serial port 
 pinMode(2, INPUT);
pinMode(3, OUTPUT);
digitalWrite(3, LOW);
  // Select font =================================================================
   
  // u8g.setFont(u8g_font_unifont);
  // u8g.setFont(u8g_font_courB10);
  // u8g.setFont(u8g_font_7x14B);
  u8g.setFont(u8g_font_8x13B); 

  u8g.setColorIndex(1);                   // Instructs the display to draw with a pixel on. 
}

void loop() {  



  u8g.firstPage();
  do {   
    draw();
  } while( u8g.nextPage() );

 
}
  
void draw(){

//float tempC=0.00;
a=digitalRead(2);
    u8g.drawFrame(0,0,128,62);            // upper frame
    //u8g.drawFrame(0,33,128,62);           // lower frame
if(a==LOW){
   
float temp= mlx.readObjectTempC();
 new_temp=(0.55*temp)+18.98;
}

if(a==HIGH){
 new_temp=0.00;
}
 // convert floats into char u8g strings    
  u8g.drawStr( 15, 27, "Temperature");       // do this for temperature
  dtostrf(new_temp, 3, 1, temp_string);
  u8g.drawStr(33,41, temp_string);
  u8g.drawStr(70,41, "C"); 

  if(new_temp>=38.0){
  digitalWrite(3, HIGH);
  b=1;
}
while(b==1){
  u8g.drawStr( 15, 27, "Temperature");       // do this for temperature
  dtostrf(new_temp, 3, 1, temp_string);
  u8g.drawStr(33,41, temp_string);
  u8g.drawStr(70,41, "C"); 
  digitalWrite(3, LOW);
}
       
}
//}
