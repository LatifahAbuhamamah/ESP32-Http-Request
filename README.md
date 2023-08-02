# ESP32-HTTP-Request
I have gained a deeper understanding of robot movements by using LEDs to simulate motor control for the robot while working with the ESP32 microcontroller via Wi-Fi. 
**Here are the steps I followed:**
### Step1 : Hardware Setup
- Gather the required components:
   - ESP32 Board
   - LEDs to simulate motor control
   - Wi-Fi connection
### Step2 : Software Setup
The provided Arduino code demonstrates how to use an ESP32 board to connect to Wi-Fi, fetch instructions from the specified URL, and control the robot's motors (represented by LEDs) accordingly. Here's a breakdown of the code:

1. Include necessary libraries:

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
```

The code includes the required libraries for Wi-Fi communication (`WiFi.h`) and HTTP requests (`HTTPClient.h`).

2. Set up Wi-Fi credentials and URL:

```cpp
const char* ssid = "xxxxxxxxxxx"; // My Wi-Fi network name
const char* password = "xxxxxxxxx"; // My Wi-Fi password
const String url = "http://192.168.1.112/g/f/get_direction.php"; // This is my address of PHP page
```

The `ssid`, `password`, and `url` variables are set up to hold the Wi-Fi network credentials and the address of the PHP page where the robot's movement instructions will be obtained. 

3. Initialize setup():

```cpp
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(21, OUTPUT); // Pin 21 for simulating motor control - forward direction
  pinMode(22, OUTPUT); // Pin 22 for simulating motor control - right direction

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

In the `setup()` function:
- Serial communication is initiated at a baud rate of 115200.
- The ESP32 connects to the specified Wi-Fi network using the provided credentials.
- Pins 21 and 22 are configured as outputs, representing the two motor control pins of the robot.

4. Loop through instructions:

```cpp
void loop() {
  HTTPClient http;
  http.begin(url); // Initialize the HTTPClient with the specified URL
  int httpResponseCode = http.GET(); // Send a GET request to the server and get the HTTP response code

  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString(); // Get the response payload from the server
    Serial.println();
    Serial.println(payload);

    // Depending on the received payload, simulate motor control for the robot
    if( payload == "forward" ){
      Serial.print("Moving forward");
      digitalWrite(21, HIGH); // Turn ON the forward LED
      digitalWrite(22, LOW); // Turn OFF the right LED
    }
    else if( payload == "right" ){
      Serial.print("Turning right");
      digitalWrite(22, HIGH); // Turn ON the right LED
      digitalWrite(21, LOW); // Turn OFF the forward LED
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
}
```
In the `loop()` function:
- A new instance of `HTTPClient` is created.
- The `http.begin(url)` initializes the HTTPClient with the specified URL.
- The ESP32 sends a GET request to the server, and the `httpResponseCode` stores the HTTP response code.
- If a valid HTTP response code is received, the payload from the server is obtained and stored in the `payload` variable.
- Based on the received payload, the code simulates motor control for the robot:
   - If the payload is "forward," the forward LED is turned ON, and the right LED is turned OFF, simulating the robot moving forward.
![image1](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/Control%20panel.png)

![image2](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/forward.png)

![image3](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/Serial%20monitor-%20forward.jpeg)

![image4](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/f.jpg)
   - If the payload is "right," the right LED is turned ON, and the forward LED is turned OFF, simulating the robot turning right.

![image1](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/right.png)
![image2](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/Serial%20monitor-%20right.jpeg)

![image3](https://github.com/LatifahAbuhamamah/ESP32-Http-Request/blob/main/images/r.jpg)


The code is not limited to only forward or right movement of the robot. It can work in any direction, including forward, backward, stop, left, or right.


