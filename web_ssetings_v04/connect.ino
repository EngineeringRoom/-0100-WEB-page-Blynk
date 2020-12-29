void WIFIinit() {
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  WiFi.begin(_ssid.c_str(), _password.c_str());
  // Делаем проверку подключения до тех пор пока счетчик tries
  // не станет равен нулю или не получим подключение
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED){
    // Если не удалось подключиться запускаем в режиме AP
//    if(isFestConnectionBlynkWIFI){
//    // Если до этого еще не разу не подключались к WIFI
      Serial.println("");
      Serial.println("WiFi up AP");
      StartAPMode();
//    }
  }
  else {
    // Иначе удалось подключиться отправляем сообщение
    // о подключении и выводим адрес IP
    isFestConnectionBlynkWIFI=false; // к wifi уже подключались точку доступа AP поднимать не надо
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode()
{ // Отключаем WIFI
  WiFi.disconnect();
  // Меняем режим на режим точки доступа
  WiFi.mode(WIFI_AP);
  // Задаем настройки сети
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  // Включаем WIFI в режиме точки доступа с именем и паролем
  // хронящихся в переменных _ssidAP _passwordAP
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  return true;
}

void ConnectBlynk()
{
  timer.disable(IDt_reconnectBlynk);
  //*******************************************************
  // Запускаем WiFi
  if (WiFi.status() != WL_CONNECTED){// Если нет WiFi, то коннектимся
    WiFi.softAPdisconnect();
    WIFIinit();
  }  
  /*  Дисконект - для справки 
    WiFi.disconnect(); // отключаемся от сети
    Serial.println("Disconnect WiFi.");
  */
  
  //*******************************************************
  // Запускаем Blynk


  if (WiFi.status() == WL_CONNECTED){// Если нет WiFi, то не коннектимся
    Blynk.config(_authB.c_str(), _serverB.c_str(), _portB.toInt());
    Serial.println(Blynk.connect(5000));     
  }
  

  
  // До бесконечности будем оставаться в цикле while
  // пока не установим связь с сервером
  // while (Blynk.connect() == false) {}
  
  timer.enable(IDt_reconnectBlynk);
  timer.restartTimer(IDt_reconnectBlynk);  
}//ConnectBlynk()



// Реконектимся если обрыв связи
void reconnectBlynk() {
  if (!Blynk.connected()){
    Serial.println("Diconnect...");
    ConnectBlynk();
    if (Blynk.connected()){
        Serial.println("Reconnected");
     } 
    else{
        Blynk.disconnect();
        isFestConnectionBlynk=true;
        Serial.println("Not reconnected");
      if (WiFi.status() == WL_CONNECTED)  {
          Serial.println("not Server");
      } else {
          Serial.println("not WiFi");           
      }
    }
  }
  
}//reconnectBlynk()

void BLYNK_init(){
    
  IDt_reconnectBlynk=timer.setInterval(10*60*1000, reconnectBlynk);// Проверяем есть ли связь с сервером
 
// Вызываем функцию подключения к Blynk
  reconnectBlynk();
}
