#include "automatic.h"
#include "stringparser.h"
#include "dac.h"
#include "config.h"
#include <Arduino.h>
#include <HardwareSerial.h>

bool forward, reverse, turf;
uint8_t accel;
unsigned long start_old_millis;

static void automatic_write_values(void){
  digitalWrite(TURF_PIN, turf);
  digitalWrite(REVERSE_PIN, reverse);
  digitalWrite(FORWARD_PIN, forward);

  //Whenever overflow happens reset
  //start old millis to zero to ensure
  //it does not get stuck at on
  //
  //May very rarely cause unwanted sudden stops!!!
  if(start_old_millis > millis() + 255)
    start_old_millis = 0;

  digitalWrite(START_PIN, start_old_millis > millis() ? HIGH : LOW);
  dac_write(accel);
}

static void automatic_handle_newline(void){
  int top, split;
  bool success = buffer_get_command_split_and_top(&top, &split);

  if(!success){
    Serial.println("err");
    return;
  }


  int value;

  if((value = buffer_get_val_from_split_index(split)) == -1){
    Serial.println("err");
    return;
  }

  bool is_read = value == -2;
  uint8_t byte_value = (uint8_t)value;

  if(buffer_check_matching_command(top, split, "FORWARD")){
    if(is_read){
      Serial.println(forward);
      Serial.println("ok");
    }
    else if(byte_value == 0){
      forward = 0;
      Serial.println("ok");
    }else if(byte_value == 1){
      forward = 1;
      Serial.println("ok");
    }else{
      Serial.println("err");
    }
  }else if(buffer_check_matching_command(top, split, "REVERSE")){
    if(is_read){
      Serial.println(reverse);
      Serial.println("ok");
    }
    else if(byte_value == 0){
      reverse = 0;
      Serial.println("ok");
    }else if(byte_value == 1){
      reverse = 1;
      Serial.println("ok");
    }else{
      Serial.println("err");
    }
  }else if(buffer_check_matching_command(top, split, "TURF")){
    if(is_read){
      Serial.println(turf);
      Serial.println("ok");
    }
    else if(byte_value == 0){
      turf = 0;
      Serial.println("ok");
    }else if(byte_value == 1){
      turf = 1;
      Serial.println("ok");
    }else{
      Serial.println("err");
    }
  }else if(buffer_check_matching_command(top, split, "ACCEL")){
    if(is_read){
      Serial.println(accel);
      Serial.println("ok");
    }
    else{
      accel = byte_value;
      Serial.println("ok");
    }
  }else if(buffer_check_matching_command(top, split, "START")){
    unsigned long current_millis = millis();
    if(is_read){
      Serial.println(start_old_millis - current_millis);
      Serial.println("ok");
    }
    else{
      start_old_millis = current_millis + byte_value;
      Serial.println("ok");
    }
  } else {
    Serial.println("err");
  }
}

void automatic_setup(int baud_rate){
  pinMode(TURF_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(START_PIN, OUTPUT);

  digitalWrite(TURF_PIN, LOW);
  digitalWrite(REVERSE_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(START_PIN, LOW);
  
  Serial.begin(baud_rate);
  dac_setup();
  buffer_zero();
  forward = false;
  reverse = false;
  turf = false;
  start_old_millis = 0;
  accel = 0;
    
}

void automatic_loop(void){
  if(Serial.available()){

    char input = Serial.read();

    buffer_write(input);

    if(input == '\n')
      automatic_handle_newline();

    }
  automatic_write_values();
}

void automatic_end(void){
  Serial.end();
  dac_end();
  buffer_zero();
  digitalWrite(TURF_PIN, LOW);
  digitalWrite(REVERSE_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(START_PIN, LOW);
}
