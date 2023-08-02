# ESP32-HTTP-Request
I have gained a deeper understanding of robot movements by using LEDs to simulate motor control for the robot while working with the ESP32 microcontroller via Wi-Fi. Here are the steps I followed:
## 1. Hardware Setup
- Gather the required components:
-- ESP32 board 
LEDs (for simulating motor direction control)
Resistors (220-470 ohms) for current-limiting the LEDs (optional, but recommended)
Breadboard and jumper wires
Connect the LEDs to the ESP32 board:

Connect one leg of the first LED to GPIO pin 21 on the ESP32 (you've already defined it as pinMode(21, OUTPUT); in your code).
Connect the other leg of the first LED to a current-limiting resistor, then connect the resistor to the GND (ground) pin on the ESP32.
Repeat the same process for the second LED, connecting it to GPIO pin 22


## Code Explanation:
The provided Arduino code demonstrates how to use an ESP32 board to connect to Wi-Fi, fetch instructions from the specified URL, and control the robot's motors (represented by LEDs) accordingly. Here's a breakdown of the code:

1. Include necessary libraries:
```cpp
#include <WiFi.h>
#include <HTTPClient.h>
```
The code includes the required libraries for Wi-Fi communication and HTTP requests.

2. Set up Wi-Fi credentials and URL:
```cpp
const char* ssid = "xxxxxxxxxxx"; // This is my Wi-Fi network name
const char* password = "xxxxxxxxx"; // This is my Wi-Fi password
const String url = "http://192.168.1.112/g/f/get_direction.php";
```
Enter your Wi-Fi network name and password in the corresponding variables. The `url` variable contains the address of the web server where the robot's movement instructions are obtained.

3. Initialize setup():
```cpp
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
```
In the setup() function:
- The Serial communication is initiated at a baud rate of 115200.
- The ESP32 connects to the specified Wi-Fi network using the provided credentials.
- Pins 21 and 22 are configured as outputs, representing the two motor control pins of the robot.
- The connection to Wi-Fi is checked, and the local IP address is printed on the Serial monitor.

4. Loop through instructions:
```cpp
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
```
In the loop() function:
- An instance of the HTTPClient is created.
- A GET request is sent to the specified URL to fetch the robot's movement instruction.
- If the HTTP response is successful (httpResponseCode > 0), the received payload is extracted.
- Depending on the payload value ("forward" or "right"), the corresponding motor control pins are set, simulating the robot's movement.

