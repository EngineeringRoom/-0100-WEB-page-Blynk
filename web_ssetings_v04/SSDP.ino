void SSDP_init(void) {
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(_ssdp);
  SSDP.setSerialNumber("0001");
  SSDP.setURL("/index.html");
  SSDP.setModelName(_ssdp + "sib.eng24");
  SSDP.setModelNumber("04.1");
  SSDP.setModelURL("https://www.youtube.com/channel/UCih0Gcl9IEdkR8deDJCiodg?view_as=subscriber");
  SSDP.setManufacturer("sib.eng24");
  SSDP.setManufacturerURL("https://www.youtube.com/channel/UCih0Gcl9IEdkR8deDJCiodg?view_as=subscriber");
  SSDP.begin();
}
