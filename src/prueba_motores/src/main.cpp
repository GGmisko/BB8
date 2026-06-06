#include <Arduino.h>
#include <WiFi.h>

// ================= WIFI =================
const char* ssid = "Familia Robayo";
const char* password = "Esteban1";

WiFiServer server(8888);

// ================= MOTORES =================
const int leftmotor_A1 = 32;
const int leftmotor_A2 = 33;

const int rightmotor_B1 = 25;
const int rightmotor_B2 = 26;

void adelante() {
  digitalWrite(leftmotor_A1, HIGH);
  digitalWrite(leftmotor_A2, LOW);

  digitalWrite(rightmotor_B1, HIGH);
  digitalWrite(rightmotor_B2, LOW);
}

void atras() {
  digitalWrite(leftmotor_A1, LOW);
  digitalWrite(leftmotor_A2, HIGH);

  digitalWrite(rightmotor_B1, LOW);
  digitalWrite(rightmotor_B2, HIGH);
}

void izquierda() {
  digitalWrite(leftmotor_A1, LOW);
  digitalWrite(leftmotor_A2, HIGH);

  digitalWrite(rightmotor_B1, HIGH);
  digitalWrite(rightmotor_B2, LOW);
}

void derecha() {
  digitalWrite(leftmotor_A1, HIGH);
  digitalWrite(leftmotor_A2, LOW);

  digitalWrite(rightmotor_B1, LOW);
  digitalWrite(rightmotor_B2, HIGH);
}

void parar() {
  digitalWrite(leftmotor_A1, LOW);
  digitalWrite(leftmotor_A2, LOW);

  digitalWrite(rightmotor_B1, LOW);
  digitalWrite(rightmotor_B2, LOW);
}

void setup() {

  Serial.begin(115200);

  pinMode(leftmotor_A1, OUTPUT);
  pinMode(leftmotor_A2, OUTPUT);

  pinMode(rightmotor_B1, OUTPUT);
  pinMode(rightmotor_B2, OUTPUT);

  parar();

  Serial.println("Conectando WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Servidor TCP iniciado");
}

void loop() {

  WiFiClient client = server.available();

  if (client) {

    Serial.println("Cliente conectado");

    while (client.connected()) {

      if (client.available()) {

        char cmd = client.read();

        Serial.print("Comando: ");
        Serial.println(cmd);

        switch (cmd) {

          case 'w':
            adelante();
            break;

          case 's':
            atras();
            break;

          case 'a':
            izquierda();
            break;

          case 'd':
            derecha();
            break;

          case 'x':
            parar();
            break;
        }
      }

      delay(10);
    }

    client.stop();

    Serial.println("Cliente desconectado");
  }
}