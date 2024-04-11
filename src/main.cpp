#define DEBUG 0

#define LED_PIN_1 22    // SUN
#define LED_PIN_2 21    // SOLAR
#define LED_PIN_3 23    // INVERTER
#define LED_PIN_4 33    // GENSET
#define LED_PIN_5 14    // ENERGY UP
#define LED_PIN_6 25    // ENERGY DOWN
#define LED_PIN_7 26    // LOAD
#define LED_PIN_8 32    // UTILITY/MAIN 

#define LED_COUNT_1 21    
#define LED_COUNT_2 20
#define LED_COUNT_3 40
#define LED_COUNT_4 34
#define LED_COUNT_5 43
#define LED_COUNT_6 65
#define LED_COUNT_7 56
#define LED_COUNT_8 29


#define SUNBOX      1
#define SOLARBOX    2
#define INVERTERBOX 3
#define GENSETBOX   4
#define TOTALBOX    5
#define ENERGYBOX   6
#define LOADBOX     7
#define MAINBOX     8

#define RED   255,0,0
#define GREEN 0,255,0
#define BLUE  0,0,255
#define WARM  255,70,0

#define BRIGHTNESS 255

#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_1_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_2_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_3_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_4_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_5_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_6_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_7_IN_us 90000
#define TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_8_IN_us 90000

#include <Arduino.h>
#include <cstdint>
#include "SparkFunDMX.h"
#include <Adafruit_NeoPixel.h>
#include "BluetoothSerial.h"

uint32_t current_led_number_1 = 0;
uint32_t current_led_number_2 = 0;
uint32_t current_led_number_3 = 0;
uint32_t current_led_number_4 = 0;
uint32_t current_led_number_5 = 0;
uint32_t current_led_number_6 = 0;
uint32_t current_led_number_7 = 0;
uint32_t current_led_number_8 = 0;

uint32_t last_updated_time_for_strip_1 = 0;
uint32_t last_updated_time_for_strip_2 = 0;
uint32_t last_updated_time_for_strip_3 = 0;
uint32_t last_updated_time_for_strip_4 = 0;
uint32_t last_updated_time_for_strip_5 = 0;
uint32_t last_updated_time_for_strip_6 = 0;
uint32_t last_updated_time_for_strip_7 = 0;
uint32_t last_updated_time_for_strip_8 = 0;

uint32_t brightness = 255;

BluetoothSerial SerialBT;
SparkFunDMX dmx;

Adafruit_NeoPixel strip_1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3(LED_COUNT_3, LED_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4(LED_COUNT_4, LED_PIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_5(LED_COUNT_5, LED_PIN_5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_6(LED_COUNT_6, LED_PIN_6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_7(LED_COUNT_7, LED_PIN_7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_8(LED_COUNT_8, LED_PIN_8, NEO_GRB + NEO_KHZ800);


void setmaxbrightness() {
//  brightness = BRIGHTNESS;
  strip_1.setBrightness(BRIGHTNESS);
  strip_2.setBrightness(BRIGHTNESS);
  strip_3.setBrightness(BRIGHTNESS);
  strip_4.setBrightness(BRIGHTNESS);
  strip_5.setBrightness(BRIGHTNESS);
  strip_6.setBrightness(BRIGHTNESS);
  strip_7.setBrightness(BRIGHTNESS);
  strip_8.setBrightness(BRIGHTNESS);
}


void strip_light_setup() {
  strip_1.begin();
  strip_2.begin();
  strip_3.begin();
  strip_4.begin();
  strip_5.begin();
  strip_6.begin();
  strip_7.begin();
  strip_8.begin();

  setmaxbrightness();
}

void all_dmx_off() {
  dmx.write(1, 0);
  dmx.write(2, 0);
  dmx.write(3, 0);
  dmx.write(4, 0);
  dmx.write(5, 0);
  dmx.write(6, 0);
  dmx.write(7, 0);
  dmx.write(8, 0);
  dmx.update();
}


void allstripClear() {
  strip_1.clear();
  strip_2.clear();
  strip_3.clear();
  strip_4.clear();
  strip_5.clear();
  strip_6.clear();
  strip_7.clear();
  strip_8.clear();

  strip_1.show();
  strip_2.show();
  strip_3.show();
  strip_4.show();
  strip_5.show();
  strip_6.show();
  strip_7.show();
  strip_8.show();
}

void sun_run_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_1 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_1_IN_us) {
    return;
  }
  
}



void process_data(String btdata) {

  if (DEBUG) {Serial.println(btdata);}
  if (btdata == "A1") { 
  }
  else if (btdata == "B1") {
  }
  else if (btdata == "C1") {
  }
  else if (btdata == "D1") {
  }
  else if (btdata == "A2") {
  }
  else if (btdata == "B2") {
  }
  else if (btdata == "C2") {
  }
  else if (btdata == "D2") {  
  }
}


void updateBrightness(uint16_t brightness) {
  // if (sun_status == 1) {
    strip_1.setBrightness(brightness);
    dmx.write(SUNBOX, brightness);
    dmx.update();
  // }
}
void process_bt_data(String recieved_data)
{
  uint8_t seperation_index = recieved_data.lastIndexOf("S");
  //  if (DEBUG){Serial.println("SI: " + String(seperation_index));}
  if (seperation_index == 255) {
    process_data(recieved_data);
  }
  else if (seperation_index == 0) {
    String required_data = recieved_data.substring(seperation_index + 1);
    brightness = required_data.toInt();
    updateBrightness(brightness);
    if (DEBUG) {Serial.println("BRIGHTNESS: " + String(brightness));}
  }
}

void read_bt_data()
{
  if (SerialBT.available()) {
    String recieved_data = SerialBT.readString();
    recieved_data.trim();
    process_bt_data(recieved_data);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  SerialBT.begin("JBros"); // Bluetooth device name
  SerialBT.setTimeout(1);
  delay(1000);

  dmx.initWrite(500);

  all_dmx_off();
  strip_light_setup();
  allstripClear();
}

void loop() {
  read_bt_data();

}