#include <Arduino.h>
#include <FastLED.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid = "Bbox-42B040ED";
const char* password = "wWggY7LcF9jrwCMkGA";

#define pinLed 2
int valeurDelay =0;

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:

  //---------------------------------------serial
  Serial.begin(115200);
  Serial.println("\n");

  //---------------------------------------GPIO
  pinMode(pinLed,OUTPUT);
  digitalWrite(pinLed,HIGH);

  //---------------------------------------SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("Erreur SPIFFS...");
    return;
  }
  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("File : ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }


  //---------------------------------------WIFI
  WiFi.begin(ssid, password);
	Serial.print("Tentative de connexion test...");
	
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.localIP());


  //---------------------------------------SERVER
  //pages de bases
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/index.html","text/html");
  });
  server.on("/index.html",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/index.html","text/html");
  });
  server.on("/w3.css",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/w3.css","text/css");
  });
  server.on("/script.js",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/script.js","text/javascript");
  });
  server.on("/jquery-3.5.1.min.js.js",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/jquery-3.5.1.min.js.js","text/javascript");
  });
  //page de modes
  server.on("/solid.html",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/solid.html","text/html");
  });
  server.on("/strombo.html",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/strombo.html","text/html");
  });
  server.on("/wave.html",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/wave.html","text/html");
  });

  //variables
  server.on("/on",HTTP_GET,[](AsyncWebServerRequest *request){
    digitalWrite(pinLed, HIGH);
    Serial.println("led on");
    request->send(204);
  });
  server.on("/off",HTTP_GET,[](AsyncWebServerRequest *request){
    digitalWrite(pinLed, LOW);
    Serial.println("led off");
    request->send(204);
  });

  server.on("/delayed",HTTP_POST,[](AsyncWebServerRequest *request){
    String message;
    if (request->hasParam("valeurDelayLed",true))
    {
      message = request->getParam("valeurDelayLed",true)->value();
    }
    Serial.println(message);
    request->send(204);
  });


  server.begin();
  Serial.println("serveur actif !!!");


}

void loop() {
  // put your main code here, to run repeatedly:
}