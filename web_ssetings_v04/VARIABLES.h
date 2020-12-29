/////////////////////////////////////////
//               База GPIO             //

  
  

/////////////////////////////////////////
//      База Виртуальных PIN -ов       //

  


/////////////////////////////////////////
//      База глобальных переменных     //



// Первое ли это подключение к Серверу Blynk
  bool isFestConnectionBlynk=true;
  bool isFestConnectionBlynkWIFI=true;

// ID для таймеров Blynk
  int IDt_reconnectBlynk;

/////////////////////////////////////////
//   База переменных для подключения   //

// Логин и пароль от Авторизации
String _ssidW = "admin"; //const char*
String _passwordW = "esp8266"; //const char*
// Позволяет вам установить область аутентификации. По умолчанию: "Требуется вход в систему"
const char* www_realm = "Custom Auth Realm";
// Содержимое HTML-ответа в случае несанкционированного доступа По умолчанию: пусто
String authFailResponse = "Authentication Failed";

// Определяем переменные wifi
String _ssid     = "SSIDwifi"; // Для хранения SSID
String _password = "12345678"; // Для хранения пароля сети

String _ssidAP = "WiFi_sib.eng24";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа

String _ssdp="ESP8266"; // Имя SSDP

String _ssidFTP = "root";   // SSID AP точки доступа
String _passwordFTP = "root"; // пароль точки доступа

String _authB = "11112222333344445555666677778888"; // AUTH токен Blynk
String _serverB = "blynk-cloud.com";           // Сервер Blynk
String _portB = "8080";                        // Порт сервера Blynk
