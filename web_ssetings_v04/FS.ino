// Поднимаем FTP-сервер для удобства отладки работы HTML (логин: root, пароль: root)
void FTP_init(){
  ftpSrv.begin(_ssidFTP,_passwordFTP); 
}

// Инициализация FFS
void FS_init(void) {
  SPIFFS.begin();

  // Это открытие файла json
  String pre_cfg = SPIFFS.open(F("/config.json"), "r").readString();
  Serial.println(String(F("\nCFG: ")) + pre_cfg);
  if (pre_cfg == "") pre_cfg = "{}";
  else deserializeJson(cfg, pre_cfg);
}



void cfgWrite(String key, String value) {
  if (cfg[key] != value) {
    cfg[key] = value;
    Serial.println("save: " + key + " = " + value);
    String pre_cfg;
    serializeJson(cfg, pre_cfg);
    SPIFFS.open(F("/config.json"), "w").print(pre_cfg);
    Serial.println("config saved");
  }
}

String cfgRead(String key) {
  return cfg[key];
}
// Запись всех данных указанных в скетче в файл config.json
void allCfgWrite(){
  cfgWrite("_ssidW", _ssidW);
  cfgWrite("_passwordW", _passwordW);
    
  cfgWrite("_ssid", _ssid);
  cfgWrite("_password", _password);
  
  cfgWrite("_ssidAP", _ssidAP);
  cfgWrite("_passwordAP", _passwordAP);

  cfgWrite("_ssdp", _ssdp);
  
  cfgWrite("_ssidFTP", _ssidFTP);
  cfgWrite("_passwordFTP", _passwordFTP);

  cfgWrite("_authB", _authB);
  cfgWrite("_serverB", _serverB);
  cfgWrite("_portB", _portB);
}

// Чтение всех данных из файла config.json используемых в скетче
void allCfgRead(){
  _ssidW = cfgRead("_ssidW");
  _passwordW = cfgRead("_passwordW");

  _ssid = cfgRead("_ssid");
  _password = cfgRead("_password");

  _ssidAP = cfgRead("_ssidAP");
  _passwordAP = cfgRead("_passwordAP");

  _ssdp = cfgRead("_ssdp");

  _ssidFTP = cfgRead("_ssidFTP");
  _passwordFTP = cfgRead("_passwordFTP");

  _authB = cfgRead("_authB");
  _serverB = cfgRead("_serverB");
  _portB = cfgRead("_portB");
}
