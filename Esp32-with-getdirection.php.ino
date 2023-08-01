#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxx";
const String url = "http://192.168.1.112/g/f/get_direction.php";
String payload = "";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");


}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
    if( payload == "forward" ){
      Serial.print("forward1");
      digitalWrite(21, HIGH);
      digitalWrite(22, LOW);

    }else if( payload == "right" ){
      digitalWrite(22, HIGH);
      digitalWrite(21, LOW);
    }
    
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  
}
