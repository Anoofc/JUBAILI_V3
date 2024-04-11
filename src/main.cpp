#define DEBUG 0

#define BTDEVICE_NAME "JBros"
#define BAUDRATE      115200

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
#define UTILITYBOX  8

#define RED   255,0,0
#define GREEN 0,255,0
#define BLUE  0,0,255
#define WARM  255,70,0

#define CLEAR_TIME 10000

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

uint32_t strip_1_clear_time = 0;
uint32_t strip_2_clear_time = 0;
uint32_t strip_3_clear_time = 0;
uint32_t strip_4_clear_time = 0;
uint32_t strip_5_clear_time = 0;
uint32_t strip_6_clear_time = 0;
uint32_t strip_7_clear_time = 0;
uint32_t strip_8_clear_time = 0;

uint16_t brightness = 255;

uint8_t sun_status = 0;
uint8_t solar_status = 0;
uint8_t inverter_status = 0;
uint8_t genset_status = 0;
uint8_t energyup_status = 0;
uint8_t energydown_status = 0;
uint8_t load_status = 0;
uint8_t utility_status = 0;

uint8_t sunbox_status = 0;
uint8_t solarbox_status = 0;
uint8_t inverterbox_status = 0;
uint8_t gensetbox_status = 0;
uint8_t totalbox_status = 0;
uint8_t energybox_status = 0;
uint8_t loadbox_status = 0;
uint8_t utilitybox_status = 0;


uint8_t sun_button_status = 0;
uint8_t genset_button_status = 0;
uint8_t utility_button_status = 0;
uint8_t energy_button_status = 0;


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

void reset_values(){
  sun_status = 0;
  solar_status = 0;
  inverter_status = 0;
  genset_status = 0;
  energyup_status = 0;
  energydown_status = 0;
  load_status = 0;
  utility_status = 0;

  sunbox_status = 0;
  solarbox_status = 0;
  inverterbox_status = 0;
  gensetbox_status = 0;
  totalbox_status = 0;
  energybox_status = 0;
  loadbox_status = 0;
  utilitybox_status = 0;
}


void reset_values_for_strip()
{
  current_led_number_1 = 0;
  current_led_number_2 = 0;
  current_led_number_3 = 0;
  current_led_number_4 = 0;
  current_led_number_5 = 0;
  current_led_number_6 = 0;
  current_led_number_7 = 0;
  current_led_number_8 = 0;
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


void sun_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_1 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_1_IN_us) {
    return;
  }
  if (current_led_number_1<LED_COUNT_1){
    strip_1.setPixelColor(current_led_number_1,strip_1.Color(r,g,b));
    strip_1.show();
    if (DEBUG){ Serial.println("LED 1 COUNT: " + String (current_led_number_1)); }
    current_led_number_1++;
    if (current_led_number_1 == LED_COUNT_1 && solarbox_status == 0 ) {dmx.write(SOLARBOX, 1); dmx.update(); solarbox_status = 1; solar_status=1;}
    strip_1_clear_time = millis();
  } 
  last_updated_time_for_strip_1 = micros();
}
void solar_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_2 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_2_IN_us) {
    return;
  }
  if (current_led_number_2<LED_COUNT_2){
    strip_2.setPixelColor(current_led_number_2,strip_2.Color(r,g,b));
    strip_2.show();
    if (DEBUG){ Serial.println("LED 2 COUNT: " + String (current_led_number_2)); }
    current_led_number_2++;
    if (current_led_number_2 == LED_COUNT_2 && inverterbox_status == 0 ) {dmx.write(INVERTERBOX, 1); dmx.update(); inverterbox_status = 1; inverter_status=1;}
    strip_2_clear_time = millis();
  } 
  last_updated_time_for_strip_2 = micros();
}

void inverter_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_3 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_3_IN_us) {
    return;
  }
  if (current_led_number_3<LED_COUNT_3){
    strip_3.setPixelColor(current_led_number_3,strip_3.Color(r,g,b));
    strip_3.show();
    if (DEBUG){ Serial.println("LED 3 COUNT: " + String (current_led_number_3)); }
    current_led_number_3++;
    strip_3_clear_time = millis();
  } 
  last_updated_time_for_strip_3 = micros();
}

void genset_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_4 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_4_IN_us) {
    return;
  }
  if (current_led_number_4<LED_COUNT_4){
    strip_4.setPixelColor(current_led_number_4,strip_4.Color(r,g,b));
    strip_4.show();
    if (DEBUG){ Serial.println("LED 4 COUNT: " + String (current_led_number_4)); }
    current_led_number_4++;
    if (current_led_number_4 == LED_COUNT_4 && totalbox_status == 0 ) {dmx.write(TOTALBOX, 1); dmx.update(); totalbox_status = 1; load_status = 1; energyup_status = 1;}
    strip_4_clear_time = millis();
  } 
  last_updated_time_for_strip_4 = micros();
}

void energyup_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_5 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_5_IN_us) {
    return;
  }
  if (current_led_number_5<LED_COUNT_5){
    strip_5.setPixelColor(current_led_number_5,strip_5.Color(r,g,b));
    strip_5.show();
    if (DEBUG){ Serial.println("LED 5 COUNT: " + String (current_led_number_5)); }
    current_led_number_5++;
    if (current_led_number_5 == LED_COUNT_5 && energybox_status == 0 ) {dmx.write(ENERGYBOX, 1); dmx.update(); energybox_status = 1; }
    strip_5_clear_time = millis();
  } 
  last_updated_time_for_strip_5 = micros();
}

void energydown_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_6 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_6_IN_us) {
    return;
  }
  if (current_led_number_6<LED_COUNT_6){
    strip_6.setPixelColor(current_led_number_6,strip_6.Color(r,g,b));
    strip_6.show();
    if (DEBUG){ Serial.println("LED 6 COUNT: " + String (current_led_number_6)); }
    current_led_number_6++;
    if (current_led_number_6 == LED_COUNT_6 && loadbox_status == 0 ) {dmx.write(LOADBOX, 1); dmx.update(); loadbox_status = 1; load_status = 1;}
    strip_6_clear_time = millis();
  } 
  last_updated_time_for_strip_6 = micros();
}

void load_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_7 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_7_IN_us) {
    return;
  }
  if (current_led_number_7<LED_COUNT_7){
    strip_7.setPixelColor(current_led_number_7,strip_7.Color(r,g,b));
    strip_7.show();
    if (DEBUG){ Serial.println("LED 7 COUNT: " + String (current_led_number_7)); }
    current_led_number_7++;
    if (current_led_number_7 == LED_COUNT_7 && loadbox_status == 0 ) {dmx.write(LOADBOX, 1); dmx.update(); loadbox_status = 1; }
    strip_7_clear_time = millis();
  } 
  last_updated_time_for_strip_7 = micros();
}

void utility_led(uint8_t r, uint8_t g, uint8_t b)
{
  if (micros() - last_updated_time_for_strip_8 < TIME_DELAY_FOR_RUNNING_SPEED_FOR_STRIP_8_IN_us) {
    return;
  }
  if (current_led_number_8<LED_COUNT_8){
    strip_8.setPixelColor(current_led_number_8,strip_8.Color(r,g,b));
    strip_8.show();
    if (DEBUG){ Serial.println("LED 8 COUNT: " + String (current_led_number_8)); }
    current_led_number_8++;
    if (current_led_number_8 == LED_COUNT_8 && totalbox_status == 0 ) {dmx.write(TOTALBOX, 1); dmx.update(); totalbox_status = 1; load_status = 1; energyup_status = 1;}
    strip_8_clear_time = millis();
  } 
  last_updated_time_for_strip_8 = micros();
}

void clear_sun(){
  if (millis() - strip_1_clear_time > CLEAR_TIME) {
    current_led_number_1 = 0;
    strip_1.clear();
    strip_1.show();
    if (DEBUG){ Serial.println("Strip 1 Cleared!"); }
    strip_1_clear_time = millis();
  }
}
void clear_solar(){
  if (millis() - strip_2_clear_time > CLEAR_TIME) {
    current_led_number_2 = 0;
    strip_2.clear();
    strip_2.show();
    if (DEBUG){ Serial.println("Strip 2 Cleared!"); }
    strip_2_clear_time = millis();
  }
}

void clear_inverter(){
  if (millis() - strip_3_clear_time > CLEAR_TIME) {
    current_led_number_3 = 0;
    strip_3.clear();
    strip_3.show();
    if (DEBUG){ Serial.println("Strip 3 Cleared!"); }
    strip_3_clear_time = millis();
  }
}

void clear_genset(){
  if (millis() - strip_4_clear_time > CLEAR_TIME) {
    current_led_number_4 = 0;
    strip_4.clear();
    strip_4.show();
    if (DEBUG){ Serial.println("Strip 4 Cleared!"); }
    strip_4_clear_time = millis();
  }
}

void clear_energyup(){
  if (millis() - strip_5_clear_time > CLEAR_TIME) {
    current_led_number_5 = 0;
    strip_5.clear();
    strip_5.show();
    if (DEBUG){ Serial.println("Strip 5 Cleared!"); }
    strip_5_clear_time = millis();
  }
}

void clear_energydown(){
  if (millis() - strip_6_clear_time > CLEAR_TIME) {
    current_led_number_6 = 0;
    strip_6.clear();
    strip_6.show();
    if (DEBUG){ Serial.println("Strip 6 Cleared!"); }
    strip_6_clear_time = millis();
  }
}

void clear_load(){
  if (millis() - strip_7_clear_time > CLEAR_TIME) {
    current_led_number_7 = 0;
    strip_7.clear();
    strip_7.show();
    if (DEBUG){ Serial.println("Strip 7 Cleared!"); }
    strip_7_clear_time = millis();
  }
}

void clear_utility(){
  if (millis() - strip_8_clear_time > CLEAR_TIME) {
    current_led_number_8 = 0;
    strip_8.clear();
    strip_8.show();
    if (DEBUG){ Serial.println("Strip 8 Cleared!"); }
    strip_8_clear_time = millis();
  }
}

void clear_strips(){
  clear_sun();
  clear_solar();
  clear_inverter();
  clear_genset();
  clear_energyup();
  clear_energydown();
  clear_load();
  clear_utility();
}

void sunRunning (){
  if (sun_button_status == 1 ){
    if (sunbox_status==0){dmx.write(SUNBOX, 1); dmx.update(); sunbox_status = 1; sun_status = 1;}
    if (sun_status==1){sun_led(WARM);}
    if (solar_status){solar_led(BLUE);}
    if (inverter_status){inverter_led(BLUE);}
  }
}

void gensetRunning (){
  if (genset_button_status == 1 ){
    if (gensetbox_status==0){dmx.write(GENSETBOX, 1); dmx.update(); gensetbox_status = 1; genset_status = 1;}
    if (genset_status==1){genset_led(BLUE);}
    if (load_status==1){load_led(BLUE);}
    if (energyup_status==1){energyup_led(GREEN);}
  }
}

void utilityRunning (){
  if (utility_button_status == 1 ){
    if (utilitybox_status==0){dmx.write(UTILITYBOX, 1); dmx.update(); utilitybox_status = 1; utility_status = 1;}
    if (utility_status==1){utility_led(BLUE);}
    if (load_status==1){load_led(BLUE);}
    if (energyup_status==1){energyup_led(GREEN);}
  }
}

void energyRunning (){
  if (energy_button_status == 1 ){
    if (energybox_status==0){dmx.write(ENERGYBOX, 1); dmx.update(); energybox_status = 1; energydown_status = 1;}
    if (energydown_status==1){energydown_led(RED);}
    if (load_status==1){load_led(BLUE);}
  }
}

void clear_all(){
  clear_sun();
  clear_solar();
  clear_inverter();
  clear_genset();
  clear_energyup();
  clear_energydown();
  clear_load();
  clear_utility();
}

void process_data(String btdata)
{

  if (DEBUG){Serial.println(btdata);}
  // UTILITY BUTTON ON
  if (btdata == "A1"){
    utility_button_status = 1;
  }
  // GENSET BUTTON ON
  else if (btdata == "B1"){ 
    genset_button_status = 1;
  }
  // ENERGY BUTTON ON
  else if (btdata == "C1"){
    energy_button_status = 1;
  }
  // SUN BUTTON ON
  else if (btdata == "D1"){
    sun_button_status = 1;
  }
  // UTILITY BUTTON OFF
  else if (btdata == "A2"){
    utility_button_status = 0;
    utility_status = 0;
    utilitybox_status = 0;
    strip_8.clear(); strip_8.show();
    current_led_number_8 = 0;
    dmx.write(UTILITYBOX, 0); dmx.update();

    if (energy_button_status==1 && sun_button_status==0){ energyup_status=0; current_led_number_5 = 0; strip_5.clear(); strip_5.show(); }
    if (genset_button_status==0 && energy_button_status==0){ sun_button_status==0; allstripClear(); all_dmx_off(); reset_values(); reset_values_for_strip();}

  }
  // GENSET BUTTON OFF
  else if (btdata == "B2"){
    genset_button_status = 0;
    genset_status = 0;
    gensetbox_status = 0;
    strip_4.clear(); strip_4.show();
    current_led_number_4 = 0;
    dmx.write(GENSETBOX, 0); dmx.update();

    if (energy_button_status==1 && sun_button_status==0){ energyup_status=0; current_led_number_5 = 0; strip_5.clear(); strip_5.show(); }
    if (utility_button_status==0 && energy_button_status==0){ sun_button_status==0; allstripClear(); all_dmx_off(); reset_values(); reset_values_for_strip();}
  }
  // ENERGY BUTTON OFF
  else if (btdata == "C2"){ 
    energy_button_status = 0;
    energydown_status = 0;
    strip_6.clear(); strip_6.show();
    current_led_number_6 = 0;

    if (utility_button_status==1 || genset_button_status==1){ return;}
    if (sun_button_status==0 && genset_button_status==0){ sun_button_status=0; allstripClear(); all_dmx_off(); reset_values(); reset_values_for_strip();}

  }
  // SUN BUTTON OFF
  else if (btdata == "D2"){ 
    sun_button_status = 0;
    sun_status = 0;
    solar_status = 0;
    inverter_status = 0;
    sunbox_status = 0;
    solarbox_status = 0;
    inverterbox_status = 0;

    current_led_number_1 = 0;
    current_led_number_2 = 0;
    current_led_number_3 = 0;

    strip_1.clear(); strip_1.show();
    strip_2.clear(); strip_2.show();
    strip_3.clear(); strip_3.show();    

    dmx.write(SUNBOX, 0); 
    dmx.write(SOLARBOX, 0);
    dmx.write(INVERTERBOX, 0);
    dmx.update();


    if (utility_button_status==1 || genset_button_status==1){ return;}
    if (energy_button_status==1){ energyup_status=0; current_led_number_5 = 0; strip_5.clear(); strip_5.show(); }
    if (energy_button_status==0 && genset_button_status==0 && utility_button_status==0){  allstripClear(); all_dmx_off(); reset_values(); reset_values_for_strip();}

  }
  // ALL BUTTON OFF
  else if (btdata == "Z"){ 
    sun_button_status = 0;
    genset_button_status = 0;
    utility_button_status = 0;
    energy_button_status = 0;
    allstripClear();
    all_dmx_off();
    reset_values();
    reset_values_for_strip();
  }
}

void updateBrightness(uint16_t brightness) {
   if (sun_button_status == 1) {
    strip_1.setBrightness(brightness);
    dmx.write(SUNBOX, brightness);
    dmx.update();
   }
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
  Serial.begin(BAUDRATE);
  Serial.setTimeout(1);
  SerialBT.begin(BTDEVICE_NAME); // Bluetooth device name
  SerialBT.setTimeout(1);
  delay(1000);

  dmx.initWrite(500);

  all_dmx_off();
  strip_light_setup();
  allstripClear();
}

void loop() {
  read_bt_data();
  clear_strips();
  sunRunning();
  gensetRunning();
  utilityRunning();
  energyRunning();
}