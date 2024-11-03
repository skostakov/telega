#ifndef telega_H
#define telega_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino.h>

// Описание класса
class Telega{
	public:
	  Telega(String token, String chatid_str, const char* root_ca);
          bool tbot(String msg);
	private:
	  String _token;
	  String _chatid_str;
	  const char * _root_ca;
};

// Создаем экземпляр клаасса
Telega::Telega(String token, String chatid_str, const char* root_ca){
	_token = token;
	_chatid_str = chatid_str;
	_root_ca = root_ca;
}

// Создаем функцию tbot для отправки сообщений
bool Telega::tbot(String msg){
  //WiFiClientSecure _client;
  HTTPClient _https;
  bool _result = false;

  if (_https.begin("https://api.telegram.org/bot"+_token+"/sendMessage?chat_id="+_chatid_str+"&text="+msg+"&parse_mode=html", _root_ca)) {
    int _httpCode = _https.GET();
    if (_httpCode > 0) {
      if (_httpCode == HTTP_CODE_OK || _httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = _https.getString();
        //term(payload);
        bool _result = true;
      }
    }
    _https.end();
  }
  return _result;
}

#endif
