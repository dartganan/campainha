# Campainha Wi-Fi usando ESP8266

Projeito feito para demonstrar a integração do flutter com IoT. Simples exemplo feito parar palestra do DevFest do Cerrado de 2019.

Aproveitei um problema que tenho no meu cotidiano, diversas vezes o correio me comunica que não tinha ninguém em casa, mas tinha. Crio um registro para ter certeza se foi ou não tocado a campainha e sou notificado quando isso acontecer. 


# O projeto inclui:

- Esquemático da placa;
- Programa que conecta no Firebase usando o ESP8266;
- Aplicativo feito em flutter que recebe notificações via push e mostra o histórico de chamadas.


## Como configurar o programa da placa

Setar as variáveis:

#define  WIFI_SSID  "Nome da sua rede"
#define  WIFI_PASSWORD  "Senha do seu wifi"
#define  FIREBASE_HOST  "Endreco do seu firebase terminando em.firebaseio.com"
#define  FIREBASE_AUTH  "Token de autenticação"
#define  FIREBASE_FCM_SERVER_KEY  "Token para envio de push do FCM"

## Como configurar o aplicativo flutter

Instalar o **google-services.json** obtido no seu Firebase no diretório **android/app/**

# Pronto! Viu como é fácil? 

Use como desejar, faça uma campainha na sua casa também ou quem sabe inicie um novo negócio baseado nesta funcionalidade. Boa sorte!
