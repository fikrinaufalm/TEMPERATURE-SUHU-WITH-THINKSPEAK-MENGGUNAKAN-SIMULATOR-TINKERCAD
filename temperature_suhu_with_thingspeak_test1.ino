String ssid     = "Simulator Wifi";
String password = ""; 
String host     = "api.thingspeak.com";
const int httpPort   = 80;
String uri     = "/update?api_key=3X796GRZI6C3MYBY&field1=";

int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  // Connect to 123D Circuits Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void enviaTemperaturaESP8266(void) {
  
  int temp = map(analogRead(A0),20,358,-40,125);
  
  // Construct our HTTP call
  String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
  
  
}


void setup() {
  
  setupESP8266();
               
}

void loop() {
  
  enviaTemperaturaESP8266();
  
  delay(10000);
}