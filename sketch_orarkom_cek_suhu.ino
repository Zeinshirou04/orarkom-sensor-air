// Blynk Config
#define BLYNK_TEMPLATE_ID "TMPLEefkEANU"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "p6by6yxE-2koM2BWN9F67gJJoU7nGO6D"

// Import Library OneWire, Chat Bot dan Blynk
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define Jalur data yang dipilih
#define ONE_WIRE_BUS 15

// Komen baris dibawah ini jika tidak ingin mencetak tulisan
#define BLYNK_PRINT Serial

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature Sensors(&oneWire);

// Authentikasi
char auth[] = BLYNK_AUTH_TOKEN;

// Configurasi Jaringan
// Isi "" Jika tidak memiliki password
char ssid[] = "Kantor_Pusat"; 
char pass[] = "Farras123";

// Timer untuk Blynk
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  // if(param.asInt() == 1) {
  //   digitalWrite(ONE_WIRE_BUS, HIGH);
  //   Blynk.virtualWrite(V7, "Sensor Online!");
  // } else if(param.asInt() == 0) {
  //   digitalWrite(ONE_WIRE_BUS, LOW);
  //   Blynk.virtualWrite(V7, "Sensor Offline!");
  // }

  // Update state
  Blynk.virtualWrite(V1, param.asInt());
}

// Fungsi dibawah akan dipanggil setiap IoT terhubung ke Blynk 
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Sensors.begin();
  // pinMode(ONE_WIRE_BUS, OUTPUT);

  // Set Timer
  timer.setInterval(1000L, myTimerEvent);
}

void loop() { 
  Blynk.run();
  timer.run();
  Sensors.requestTemperatures();
  int suhu = Sensors.getTempCByIndex(0);

  // Kondisi Membeku
  if ((suhu < 20) && (suhu > 0)) {
    // Mengirimkan data ke Blynk
    Blynk.virtualWrite(V4, suhu);
    Blynk.virtualWrite(V5, "Kondisi membeku"); 
  } else if ((suhu >= 20) && (suhu < 30)) {
    // Mengirimkan data ke Blynk
    Blynk.virtualWrite(V4, suhu);
    Blynk.virtualWrite(V5, "Kondisi normal");
  } else if ((suhu >= 30) && (suhu <= 40)) {
    // Mengirimkan data ke Blynk
    Blynk.virtualWrite(V4, suhu);
    Blynk.virtualWrite(V5, "Kondisi mendidih");
  } else {
    // Mengirimkan data ke Blynk
    Blynk.virtualWrite(V4, suhu);
    Blynk.virtualWrite(V5, "SUHU DILUAR JANGKAUAN!");
  }
  delay(2000);
}
