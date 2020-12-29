/*
 *    Автор: Обушенков Алексей Андреевич 
 *    Группа в ВК https://vk.com/engineer24
 *    Канал на YouTube https://www.youtube.com/channel/UCih0Gcl9IEdkR8deDJCiodg
 *    Инженерка Engineering room
 */

#include "ArduinoJson.h"
#include <ESP8266WiFi.h>        

// Blynk библиотеки
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;       // Объявляем класс Таймер

#include <ESP8266WebServer.h>   
#include <ESP8266SSDP.h>        
#include <FS.h>                 
#include <ESP8266FtpServer.h>                                           // Библиотека для работы с SPIFFS по FTP

StaticJsonDocument<1024> cfg;

IPAddress apIP(192, 168, 4, 1);

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
FtpServer ftpSrv;                                                       // Определяем объект для работы с модулем по FTP (для отладки HTML)

#include "VARIABLES.h" // Переменные




void setup() {
  
  Serial.begin(115200);
  Serial.println("");
//Запускаем файловую систему 
  Serial.println("Start 1-FS");
  FS_init();

// Запись всех данных указанных в скетче в файл config.json
  //allCfgWrite();

// Чтение всех данных из файла config.json используемых в скетче
  allCfgRead();
  
//Запускаем WIFI и Blynk
  Serial.println("Start 2-WIFI and Blynk");
  BLYNK_init();
  //WIFIinit(); // Если ненужен Blynk
   
//Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
//Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 4-WebServer");
  HTTP_init();
  
//Настраиваем и запускаем FTP интерфейс  
  Serial.println("Start 5-FTP");
  FTP_init();

}

void loop() {
  HTTP.handleClient();
  ftpSrv.handleFTP();                                                // Обработчик FTP-соединений
  
  if (Blynk.connected()){ Blynk.run();} 
  timer.run();
  
  delay(1);
}
