// Функция Авторизации (Что бы никто лишний нееизменил данные)
void auth() {
  if (!HTTP.authenticate(_ssidW.c_str(), _passwordW.c_str())) 
    return HTTP.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
}

void HTTP_init(void) {
  /*HTTP.on("/", []() {
    //auth();
    handleFileRead(HTTP.uri());                                      // Если функция handleFileRead (описана ниже) возвращает значение false в ответ на поиск файла в файловой системе     
  });
  */
  HTTP.on("/restart", handle_Restart); // Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
  
  HTTP.onNotFound([](){                                                 // Описываем действия при событии "Не найдено"
  auth();
  if(!handleFileRead(HTTP.uri()))                                       // Если функция handleFileRead (описана ниже) возвращает значение false в ответ на поиск файла в файловой системе
      HTTP.send(404, "text/plain", "Not Found");                        // возвращаем на запрос текстовое сообщение "File isn't found" с кодом 404 (не найдено)
  });

  HTTP.on("/ssdp", handle_Set_Ssdp);     // Установить имя SSDP устройства по запросу вида /ssdp?
  HTTP.on("/ssid", handle_Set_Ssid);     // Установить имя и пароль роутера(WiFi) по запросу вида /ssid?
  HTTP.on("/ssidap", handle_Set_Ssidap); // Установить имя и пароль для точки доступа(AP) по запросу вида /ssidap
  HTTP.on("/ssidblynk", handle_Set_SsidBlynk); // Установить Ключ Сервер и Порт(Blynk) по запросу вида /ssidblynk?authB=keyB&serverB=blynk-cloud.com&portB=8080
  HTTP.on("/ssidW", handle_Set_SsidW); // Установить имя и пароль для Авторизации по запросу вида /ssidW?ssidW=home1&passwordW=8765439
  HTTP.on("/ssidFTP", handle_Set_SsidWFTP); // Установить имя и пароль для FTP по запросу вида /ssidFTP?ssidFTP=home1&passwordFTP=8765439
  HTTP.on("/restart", handle_Restart);   // Перезагрузка модуля по запросу вида /restart?device=ok
  // Запускаем HTTP сервер
  HTTP.begin();
}

// Функции API-Set
// Установка SSDP имени по запросу вида http://192.168.0.101/ssdp?ssdp=proba
void handle_Set_Ssdp() {
  auth();
  _ssdp = HTTP.arg("ssdp"); // Получаем значение ssdp из запроса сохраняем в глобальной переменной
  cfgWrite("_ssdp", _ssdp);            // Сохраняем данные
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

// Установить имя и пароль роутера(WiFi) по запросу вида http://192.168.0.101/ssid?ssid=home2&password=12345678
void handle_Set_Ssid() {
  auth();
  _ssid = HTTP.arg("ssid");            // Получаем значение ssid из запроса сохраняем в глобальной переменной
  _password = HTTP.arg("password");    // Получаем значение password из запроса сохраняем в глобальной переменной
  cfgWrite("_ssid", _ssid);            // Сохраняем данные
  cfgWrite("_password", _password);            // Сохраняем данные
  HTTP.send(200, "text/plain", "OK");  // отправляем ответ о выполнении
}

//Установить имя и пароль для точки доступа(AP) по запросу вида http://192.168.1.101/ssidap?ssidAP=WiFi12345678&passwordAP=12345678
void handle_Set_Ssidap() {              
  auth();
  _ssidAP = HTTP.arg("ssidAP");         // Получаем значение ssidAP из запроса сохраняем в глобальной переменной
  _passwordAP = HTTP.arg("passwordAP"); // Получаем значение passwordAP из запроса сохраняем в глобальной переменной
  cfgWrite("_ssidAP", _ssidAP);
  cfgWrite("_passwordAP", _passwordAP);
  HTTP.send(200, "text/plain", "OK");   // отправляем ответ о выполнении
}

//Установить имя и пароль для Авторизации по запросу вида http://192.168.0.101/ssidW?ssidW=home1&passwordW=8765439
void handle_Set_SsidW() {              
  auth();
  _ssidW = HTTP.arg("ssidW");     // Получаем значение ssidAP из запроса сохраняем в глобальной переменной
  _passwordW = HTTP.arg("passwordW"); // Получаем значение passwordAP из запроса сохраняем в глобальной переменной
  cfgWrite("_ssidW", _ssidW);
  cfgWrite("_passwordW", _passwordW);
  HTTP.send(200, "text/plain", "OK");    // отправляем ответ о выполнении
}

//Установить имя и пароль для FTP по запросу вида http://192.168.0.101/ssidFTP?ssidFTP=home1&passwordFTP=8765439
void handle_Set_SsidWFTP() {              
  auth();
  _ssidFTP = HTTP.arg("ssidFTP");     // Получаем значение ssidAP из запроса сохраняем в глобальной переменной
  _passwordFTP = HTTP.arg("passwordFTP"); // Получаем значение passwordAP из запроса сохраняем в глобальной переменной
  cfgWrite("_ssidFTP", _ssidFTP);
  cfgWrite("_passwordFTP", _passwordFTP);
  HTTP.send(200, "text/plain", "OK");    // отправляем ответ о выполнении
}

//Установка параметров Blynk вида http://192.168.1.101/ssidblynk?authB=keyB&serverB=blynk-cloud.com&portB=5050
void handle_Set_SsidBlynk() {              
  auth();
  _authB = HTTP.arg("authB");         // Получаем значение authB из запроса сохраняем в глобальной переменной
  _serverB = HTTP.arg("serverB");     // Получаем значение serverB из запроса сохраняем в глобальной переменной
  _portB = HTTP.arg("portB");         // Получаем значение portB из запроса сохраняем в глобальной переменной
  cfgWrite("_authB", _authB);
  cfgWrite("_serverB", _serverB);
  cfgWrite("_portB", _portB);
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  auth();
  String restart = HTTP.arg("device");          // Получаем значение device из запроса
  if (restart == "ok") {                         // Если значение равно Ок
    HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
    ESP.restart();                                // перезагружаем модуль
  }
  else {                                        // иначе
    HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
  }
}

/*
String relay_switch() {                                                 // Функция переключения реле 
  byte state;
  if (digitalRead(relay))                                               // Если на пине реле высокий уровень   
    state = 0;                                                          //  то запоминаем, что его надо поменять на низкий
  else                                                                  // иначе
    state = 1;                                                          //  запоминаем, что надо поменять на высокий
  digitalWrite(relay, state);                                           // меняем значение на пине подключения реле
  Serial.println(state);
  return String(state);                                                 // возвращаем результат, преобразовав число в строку
}

String relay_status() {                                                 // Функция для определения текущего статуса реле 
  byte state;
  if (digitalRead(relay))                                               // Если на пине реле высокий уровень   
    state = 1;                                                          //  то запоминаем его как единицу
  else                                                                  // иначе
    state = 0;                                                          //  запоминаем его как ноль
  return String(state);                                                 // возвращаем результат, преобразовав число в строку
}
*/
// Здесь функции для работы с файловой системой
String getContentType(String filename) {
  if (HTTP.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){                                       // Функция работы с файловой системой
  if(path.endsWith("/")) path += "index.html";                          // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
  String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
  if(SPIFFS.exists(path)){                                              // Если в файловой системе существует файл по адресу обращения
    File file = SPIFFS.open(path, "r");                                 //  Открываем файл для чтения
    size_t sent = HTTP.streamFile(file, contentType);                   //  Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
    file.close();                                                       //  Закрываем файл
    return true;                                                        //  Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
  }
  return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
}
