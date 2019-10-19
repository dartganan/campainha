

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <_Sound_Drive.h>

class_Sound sound; //Sound drive

#define WIFI_SSID "Nome da sua rede"
#define WIFI_PASSWORD "Senha da sua rede"
#define FIREBASE_HOST "Seu endereco do firebase terminando em .firebaseio.com"
#define FIREBASE_AUTH "Token de acesso ao firebase"
#define FIREBASE_FCM_SERVER_KEY "Token de acesso ao serviço do FCM"

FirebaseData firebaseData;

// CONTA A QUANTIDADE DE VEZES QUE FOI ENVIADO O PUSH
int count = 0;

int const BUTTON_BELL = 12;
#define _SOUND_PIN 15
#define _LED_PIN 13
int32_t tempo;

// FORWARDS
void sendMessage();
void somCampainha();
void reset();

void setup()
{

    pinMode(_LED_PIN, OUTPUT);

    // SOM QUANDO LIGA PARA TER UM RETORNO QUE FOI LIGADO
    sound.playTone(1200, 150);
    digitalWrite(_LED_PIN, LOW); // LED FICA LIGADO AO ENVIAR O PUSH

    // INICIA SERIAL
    Serial.begin(115200);

    // INICIA WIFI
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando no Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Conecitado no IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // CONFIGURA REAL TIME DATA BASE
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    // CONFIGURACAO DO FCM PARA ENVIO DO PUSH
    firebaseData.fcm.begin(FIREBASE_FCM_SERVER_KEY);
    firebaseData.fcm.setPriority("high");
    firebaseData.fcm.setTopic("campainha");
    firebaseData.fcm.setTimeToLive(1000);

    // ENVIA MENSAGEM LOGO APOS CONEXAO PARA TESTAR
    sendMessage();
    tempo = millis();
}

void loop()
{

    // LEIO O BOTAO DA CAMPAINHA

    if (digitalRead(BUTTON_BELL) == LOW)
    {
        Serial.println("Toca campainha");
        digitalWrite(_LED_PIN, LOW); // LED FICA LIGADO AO ENVIAR O PUSH
        somCampainha();
        //ENVIA PUSH DE NOTIFICACAO
        sendMessage();
        do
        {
        } while (digitalRead(BUTTON_BELL) == LOW);
    }

    // PISCA LED
    if ((millis() - tempo) > 250)
    {
        tempo = millis();
        digitalWrite(_LED_PIN, !digitalRead(_LED_PIN));
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        reset();
    }
}

void reset()
{
    for (;;)
        ;
}

void somCampainha()
{
    tone(_SOUND_PIN, 1000);
    delay(500);
    tone(_SOUND_PIN, 880);
    delay(1000);
    noTone(_SOUND_PIN);
}

void sendMessage()
{

    Serial.println("------------------------------------");
    Serial.println("Envia para o Firebase Cloud Messaging...");

    // CONFIGURA QUAL MENSAGEM SERA ENVIADO AO TOCAR A CAMPAINHA
    firebaseData.fcm.setNotifyMessage("Campainha Wi-Fi", "Alguém tocou a campainha. " + String(count));
    //firebaseData.fcm.setDataMessage("{\"myData\":" + String(count) + "}");

    //if (Firebase.broadcastMessage(firebaseData))
    // ENVIO A MENSAGEM PARA UM TOPICO CAMPAINHA
    if (Firebase.sendTopic(firebaseData))
    //if (Firebase.sendMessage(firebaseData1, 0))//send message to recipient index 0
    {

        Serial.println("ENVIADO");
        Serial.println(firebaseData.fcm.getSendResult());
        Serial.println("------------------------------------");
        Serial.println();

        String path = "/campainha";

        // ENVIA PARA O FIREBASE
        if (Firebase.pushTimestamp(firebaseData, path + "/principal/"))
        {
            Serial.println("SALVO NO DATABASE");
            //Timestamp saved in millisecond, get its seconds from intData()
            Serial.print("TIMESTAMP (Seconds): ");
            Serial.println(firebaseData.doubleData());
            Serial.println(firebaseData.intData());
        }
        else
        {
            Serial.println("FALHOU AO SALVAR O DADO");
            Serial.println("ERROR: " + firebaseData.errorReason());
            Serial.println("------------------------------------");
            Serial.println();
        }
    }
    else
    {
        Serial.println("FALOU O ENVIO");
        Serial.println("ERRO: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
    }

    // CONTATAS VEZES JA FOI ENVIADO O PUSH.
    count++;
}