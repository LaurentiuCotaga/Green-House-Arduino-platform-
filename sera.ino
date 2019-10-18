#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"


#define DHTPIN 2 // 
LiquidCrystal_I2C lcd(0x27,20,4); // 0x27 adresa,20 caracteri linii,4 cite lini(4 rinduri)

#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE);
//  creare constante
int relay1 = 4;  // pompa de apă
int relay2 = 5;  // cooler
int bec = 7;
int Sol_sensor; // analog
int umid;       // analog
//int button1 = 6;
//boolean button1_state = LOW; 
//boolean relay1_on = false;

void setup() {
  Serial.begin(9600);   //viteza de transmitere a datelor bit pe sec. 
  dht.begin();  // initializare DHT22
  lcd.begin();   // initializare ecranului lcd.init();
  lcd.backlight();  // initializare luminare LDC
  pinMode(relay1, OUTPUT);  // OUTPUT pin de esire
  pinMode(relay2,OUTPUT);
  pinMode(bec, OUTPUT);
  //pinMode(button1, INPUT);
}
void loop() {
  // asteapta 2 secunde, DTH22 lucreaza doar dupa 2 secunde dupa pornire
  delay(2000);

  //Secreaza 2 variabile in care se vor pastra datele de la citirea sensorului DTH22
  float hum = dht.readHumidity(); // tip de date
  float temp = dht.readTemperature();
  //Variabila pentru pastrarea valorii trimise de sensorul de umiditate
  int Sol_sensor = analogRead(A0);

  //controleaza daca vin datele de la sensorul DTH22
  if (isnan(hum) || isnan(temp)) {
    lcd.setCursor(1, 3);
    lcd.print("DTH22 Lipseste!");
    return;
  }
  //controleaza daca vin datele de la sensorul DTH22
  if (isnan(Sol_sensor)) {
    lcd.setCursor(1, 3);
    lcd.print("UmidS Lipseste!");
    return;
  }
  
  //Secventa pentru bec
  digitalWrite(bec,HIGH);
  
  /*if ((digitalRead(relay1) == HIGH) && (button1_state == LOW))
  {
    relay1_on = !relay1_on;
    button1_state = HIGH;
  }
  else
  {
    button1_state = digitalRead(relay1);
  }
  digitalWrite(relay1, relay1_on);*/
  

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temp, hum, false); // sa citesca in *C
  
  //Afisarea pe LCD ecran a umiditatii si temperaturii trimise de la sensorul DTH22
  lcd.setCursor(1,0);
  lcd.print("Umid: ");
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(1,1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" *C ");
  lcd.setCursor(1,2);
  lcd.print("Usol: ");
  //Secventa pentru Sensorul de umiditate a solului, valorile trimise de sensor se transofrma in procente
  if ((Sol_sensor>= 0) and (Sol_sensor <= 51)) {
    umid = 100;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 52) and (Sol_sensor <= 103)) {
    umid = 95;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 104) and (Sol_sensor <= 155)) {
    umid = 90;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 156) and (Sol_sensor <= 208)) {
    umid = 85;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 209) and (Sol_sensor <= 262)) {
    umid = 80;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 263) and (Sol_sensor <= 313)) {
    umid = 75;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 314) and (Sol_sensor <= 367)) {
    umid = 70;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 368) and (Sol_sensor <= 417)) {
    umid = 65;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 418) and (Sol_sensor <= 471)) {
    umid = 60;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 472) and (Sol_sensor <= 521)) {
    umid = 55;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 522) and (Sol_sensor <= 575)) {
    umid = 50;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 576) and (Sol_sensor <= 625)) {
    umid = 45;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 626) and (Sol_sensor <= 679)) {
    umid = 40;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 680) and (Sol_sensor <= 729)) {
    umid = 35;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 730) and (Sol_sensor <= 783)) {
    umid = 30;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 784) and (Sol_sensor <= 833)) {
    umid = 25;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 834) and (Sol_sensor <= 887)) {
    umid = 20;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 888) and (Sol_sensor <= 937)) {
    umid = 15;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 938) and (Sol_sensor <= 991)) {
    umid = 10;
    lcd.print(umid);
  }
  if ((Sol_sensor >= 992) and (Sol_sensor <= 1023)) {
    umid = 5;
    lcd.print(umid);
  }
  lcd.print("%");

  //Conditia pentru aprinderea coolerului
  if (temp <= 24){
    digitalWrite(relay2,HIGH);
  }
  if (temp >= 24){
    digitalWrite(relay2,LOW);
  }

  //Conditia pentru aprinderea pompei
  if (Sol_sensor <= 680){
    digitalWrite(relay1,HIGH);
  }
  if (Sol_sensor >= 680){
    digitalWrite(relay1,LOW);
  }
}
