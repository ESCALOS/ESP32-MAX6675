#include <WiFi.h>
#include <HTTPClient.h>
#include <max6675.h>

// Pines para el MAX6675
int thermoDO = 19;    // MISO
int thermoCS = 5;    // CS
int thermoCLK = 18;   // CLK

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// WiFi
const char* ssid = "SSID";
const char* password = "PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);
  
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Conectado a WiFi");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());

  delay(500); // Esperar a que el sensor se estabilice
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperatura = thermocouple.readCelsius();
    Serial.printf("🌡 Temperatura: %.2f°C\n", temperatura);

    HTTPClient http;

    // Construir la URL con la temperatura real
    String url = "http://puerto:8080/temperatura?valor=" + String(temperatura, 2);
    Serial.println("🔁 Enviando solicitud a: " + url);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("✅ Código de respuesta: %d\n", httpCode);
      String respuesta = http.getString();
      Serial.println("📨 Respuesta del servidor:");
      Serial.println(respuesta);
    } else {
      Serial.printf("❌ Error en la solicitud: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("⚠️ WiFi no conectado");
  }

  delay(1000); // Al menos 250ms, pero tú quieres cada 1s
}
