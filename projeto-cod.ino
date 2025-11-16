#include <Ticker.h>
#include <WiFi.h>
#include <MQTT.h>

//ID de rede e senha
const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";

const int ENTANL = 35;
const int BUZZER = 19;
const int BTITP = 18;
bool ALARME = false;
float CG = 0.0;
int TPRE = 0;

unsigned long lastMillis = 0;

Ticker temporizadorN;

//Criando objetos de rede, coenxao WIFI
WiFiClient net;
//Cria objeto pra protocolo MQTT, conexao de rede e link no topico
MQTTClient client;


//Classe que verifica conexao e estabelece protocolo mqtt
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("esp32dgt", "embarcadosdgt", "ijEl0Q2ulJqeC7oW")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

}

//Funcao de notificacao mobile
void enviarNotificacao() {
  TPRE = TPRE + 1;
  if (TPRE == 1) {
    
    String notificacao = "Altos niveis de gas detectados no ambiente!!!!!";
    client.publish("/noticel", notificacao);

    Serial.println("Notificacao enviada");
    Serial.println("Reenvio em 5 minutos");
  } else if (TPRE == 5) {
    TPRE = 0;
  }

}

//Ativa alarme e inicia contador para envio de notificacao via celular
void ativarAlarmeN() {
  ALARME = true;
  Serial.println("Altos niveis de gás (ppm) detectados!");
  tone(BUZZER, 400);
  temporizadorN.attach(5, enviarNotificacao);
  Serial.println("Contagem de 1 minuto iniciada para envio de notificacao");
}

//Cancela o alarme e o envio da notificacao via celular
void cancelarAlarmeN() {
  ALARME = false;
  noTone(BUZZER);
  temporizadorN.detach();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");

  WiFi.begin(ssid, pass);
  client.begin("embarcadosdgt.cloud.shiftr.io", net);

  connect();

  pinMode(ENTANL, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTITP, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTITP), cancelarAlarmeN, RISING);
}

void loop() {

  client.loop();
  CG = analogRead(ENTANL);
  Serial.print("Leitura: ");
  Serial.println(CG);

  if (CG > 2500 && !ALARME) {
    ativarAlarmeN();
  }

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    String message;
      message.concat(String(CG));
    client.publish("/projetodgt", message);
  }

  delay(1000);
}
//