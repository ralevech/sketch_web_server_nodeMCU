#pragma once
#include "Includes.h"

void printWifiInfo(wl_status_t status, IPAddress ip) {
  if (status == WL_CONNECTED) {
    Serial.println(Msg::WIFI_OK);
    Serial.print(Msg::IP_LABEL);
    Serial.println(ip);
  } else {
    Serial.println(Msg::WIFI_ERR);
  }
}

void printFSInfo() {
  FSInfo fs_info;
  if (LittleFS.info(fs_info)) {
    Serial.print("Всего: ");
    Serial.print(fs_info.totalBytes);
    Serial.print(" байт, Использовано: ");
    Serial.println(fs_info.usedBytes);
    
    if (fs_info.totalBytes - fs_info.usedBytes < 10000) {
      Serial.println(Msg::FS_WARN);
    }
  }
}