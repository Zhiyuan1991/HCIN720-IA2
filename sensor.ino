/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */

#include "application.h"
#include "neopixel/neopixel.h" // use for Build IDE
// #include "neopixel.h" // use for local build

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

//Declare functions
void meter(int data,int wait);
void GetData(const char *event, const char *data);

//Declare global varibles
//for publish
unsigned long lastTime = 0UL;
char publishString[40];
//Sensor
int sensorPin = A0;
int sensor_val=0;
//Neopixel
double scale = 1.0 / ((double) RAND_MAX + 1.0); //dumy data scale
int data_min=400;
int data_max=3200;
//subscrib
int sub_sensor_data=0;

void setup()
{
    //sensor
    pinMode(A0,INPUT);
    //neopixel
    strip.begin();
    strip.setBrightness(10);
    strip.show(); // Initialize all pixels to 'off'
    //subscribe
    Particle.subscribe("SensorData", GetData,"380025001347343338333633");
    //Particle.subscribe("https://api.spark.io/v1/devices/380025001347343338333633 /events/?access_token=8734299b639b819fcf341e4874fee78f80a03351/SensorData", GetData);
    
    Serial.begin(9600);
}

void loop()
{
    //get data and publish
    sensor_val = analogRead(sensorPin);
    unsigned long now = millis();
    if (now-lastTime>2000UL) {
        lastTime = now;
        sprintf(publishString, "%d", sensor_val);
        Spark.publish("SensorData",publishString);
    }
    
    //int rval = (int)(rand() * scale * (data_max - data_min + 1) + data_min);//generate dumy data
    meter(sub_sensor_data,200);
    //Serial.println(sub_sensor_data);

}


void GetData(const char *event, const char *data){
    sub_sensor_data=atoi(data);
}

void meter(int data,int wait)
{
    for(int i=0; i<16; i++){
        strip.setPixelColor(i, strip.Color(0,0,0));
    }
    
    int Pixel_nums=0;
    if (data<=data_min)
        data=data_min+1;
    if (data>=data_max)
        data=data_max-1;
    
    Pixel_nums=(data-data_min)*16/(data_max-data_min)+1;
    int R=(data-data_min)*254/(data_max-data_min)+1;
    int G=255-R;
    Serial.println(String(data)+","+String(R)+","+String(G));
    //Serial.println(G);
    if (Pixel_nums<14){
        for(int i=0; i<Pixel_nums; i++) {
            strip.setPixelColor(i, strip.Color(R,G,0));
        }
        strip.show();
        delay(wait);
    }
    else {
            for(int i=0; i<Pixel_nums; i++) {
                strip.setPixelColor(i, strip.Color(R,G,255));
                
            }
            strip.show();
            delay(wait/2);
            for(int i=0; i<Pixel_nums; i++) {
                strip.setPixelColor(i, strip.Color(255,0,0));
            }
            strip.show();
            delay(wait/2);
            
    }
}
