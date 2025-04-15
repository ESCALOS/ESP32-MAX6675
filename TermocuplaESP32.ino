#include <WiFi.h>
#include <HTTPClient.h>
#include <max6675.h>

// Pines para el MAX6675
int thermoDO = 19;   // MISO
int thermoCS = 5;    // CS
int thermoCLK = 18;  // CLK

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

    String serverUrl = "http://SERVER_IP:4000/api/temperature";
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Cuerpo JSON con el valor de la temperatura
    String jsonData = "{\"value\": " + String(temperatura, 2) + "}";

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.printf("✅ Código de respuesta: %d\n", httpResponseCode);
      String respuesta = http.getString();
      Serial.println("📨 Respuesta del servidor:");
      Serial.println(respuesta);
    } else {
      Serial.printf("❌ Error en la solicitud: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println("⚠️ WiFi no conectado");
  }

  delay(1000); // Esperar 1 segundo antes del próximo envío
}
