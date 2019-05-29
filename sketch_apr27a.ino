//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cool-sina-97974.firebaseio.com"
#define FIREBASE_AUTH "AIWR9kGRJTYjCdHFy78Rj4xdOADP5gGcLDoa2fIA"

#define WIFI_SSID "Gaming Server"
#define WIFI_PASSWORD "Cinco12345"
#define greenled D1
#define redled D2
#define buzzer D3

int gas_sensor;
int flame_sensor = D0;
int flame_detected = 0;


void setup() {
  Serial.begin(9600);
  pinMode(flame_sensor, INPUT);
  pinMode(gas_sensor, INPUT);
  pinMode(greenled,OUTPUT);
  pinMode(redled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  // set value
  gas_sensor = analogRead(0);
  flame_detected = digitalRead(flame_sensor);
  Serial.println(flame_detected);
 Serial.println(gas_sensor);
  
  //digitalWrite(greenled, HIGH);
 //tone(buzzer,1000);

  if(gas_sensor > 400)
  {
    tone(buzzer, 1000);
    digitalWrite(greenled, HIGH);
  }
  /*else if
  {
    digitalWrite(greenled, LOW);
    noTone(buzzer);
  }*/
  else if (flame_detected == 0)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(redled, HIGH);
  }
  else
  {
    noTone(buzzer);
    digitalWrite(greenled,LOW);
    digitalWrite(redled, LOW);
  }
  
  delay(1000);
 
  Firebase.setFloat("gasleaklevel", gas_sensor);
  Firebase.setFloat("flame",flame_detected);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  
 

  
  // update value
  Firebase.setFloat("gasleaklevel",gas_sensor);
  Firebase.setFloat("flame",flame_detected);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);




  // get value 
  Serial.print("gasleaklevel: ");
  Serial.println(Firebase.getFloat("gasleaklevel"));
  delay(1000);

  // remove value
  //Firebase.remove("gasleaklevel");
   //Firebase.remove("flame");
  //delay(1000);

   




}
