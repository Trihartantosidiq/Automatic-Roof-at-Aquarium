#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>


#define SensorLDR A0
#define DHTTYPE DHT11
#define ONE_WIRE_BUS 2
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define In1 0
#define In2 16
#define Lampu 3     //inp3
#define Peltier 14  //inp4


char auth[] = "8B-jaUnq7KaqGY3_cKXE8GIFE7gqD62R";
char ssid[] = "SERENITY_plus";
char pass[] = "babykenya";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorSuhu(&oneWire);
DHT dht(5, DHTTYPE);

float suhuSekarang;
int cahaya;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200);
  dht.begin();
  sensorSuhu.begin();
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(Lampu, OUTPUT);
  pinMode(Peltier, OUTPUT);
  digitalWrite(Lampu, LOW);
  digitalWrite(Peltier, LOW);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  Blynk.begin(auth, ssid, pass);
}



float ambilSuhu()
{
   sensorSuhu.requestTemperatures();
   float suhu = sensorSuhu.getTempCByIndex(0);
   return suhu;   
}

void maju(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

}

void mundur(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

}

void berhenti(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);

}
void loop() {

  //intensitas();
  cahaya = analogRead(SensorLDR);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  suhuSekarang = ambilSuhu();
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, suhuSekarang);
  display.clearDisplay();
  display.setCursor(8,0);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("MONITORING AKUARIUM");
  display.setCursor(0,20);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Temp Udara :");
  display.print(t);
  display.print((char)247);
  display.print("C");
  display.setCursor(0,30);
  display.setTextSize(1);
  display.print("Kelembapan :");
  display.print(h);
  display.print(" %");
  display.setCursor(0,40);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Temp Air   :");
  display.print(suhuSekarang);
  display.print((char)247);
  display.print("C");
  display.setCursor(0,50);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Int. Cahaya:");
  display.display();
 
  if(suhuSekarang <=24){
    Blynk.notify("Temperatur Air Sedang Dingin");
  }
  if(suhuSekarang >= 32){
    Blynk.notify("Temperatur Air Sedang Panas");
  }
  if (t >=32 && suhuSekarang >=30){
    digitalWrite(Peltier, HIGH);
    Blynk.notify("TEMPERATUR LINGKUNGAN DAN AIR SEDANG PANAS !");
    if(cahaya <=699){
      maju();
      digitalWrite(Lampu, LOW);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Terang");
      display.display();
    }
    if (cahaya >=700 && cahaya <=899){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Mendung");
      display.display();
    }
    if (cahaya >=900){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Gelap");
      display.display();
    }
  }
  if (suhuSekarang >= 30){
     digitalWrite(Peltier, HIGH);
     if(cahaya <=699){
      mundur();
      digitalWrite(Lampu, LOW);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Terang");
      display.display();
    }
    if (cahaya >=700 && cahaya <=899){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Mendung");
      display.display();
    }
    if (cahaya >=900){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Gelap");
      display.display();
    }
  }
  if (suhuSekarang <= 26){
    digitalWrite(Peltier, LOW);
     if(cahaya <=699){
      mundur();
      digitalWrite(Lampu, LOW);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Terang");
      display.display();
    }
    if (cahaya >=700 && cahaya <=899){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Mendung");
      display.display();
    }
    if (cahaya >=900){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Gelap");
      display.display();
    }
  }
  if (t <=28 && suhuSekarang <=26){
    Blynk.notify("TEMPERATUR LINGKUNGAN DAN AIR SEDANG DINGIN !");
    digitalWrite(Peltier, LOW);
     if(cahaya <=699){
      maju();
      digitalWrite(Lampu, LOW);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Terang");
      display.display();
    }
     if (cahaya >=700 && cahaya <=899){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Mendung");
      display.display();
    }
    if (cahaya >=900){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Gelap");
      display.display();
    }
  }
  else{
    if(cahaya <=699){
      mundur();
      digitalWrite(Lampu, LOW);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Terang");
      display.display();
    }
     if (cahaya >=700 && cahaya <=899){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Mendung");
      display.display();
    }
    if (cahaya >=900){
      maju();
      digitalWrite(Lampu, HIGH);
      display.setCursor(75,50);  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("Gelap");
      display.display();
    }
    
  }
  delay(500);
}
