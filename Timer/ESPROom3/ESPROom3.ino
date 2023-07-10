#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif


const char* ssid     = "SHAW-FD2A7D";
const char* password = "0N36X8XKDT22";

const char* resource = "/trigger/SessionReading/with/key/dec_MfvuJNp9Rd7XBZZsOz";
int sessionCount = 0;
int breakCount = 0;
const char* server = "maker.ifttt.com";
int sessionPin = 2;
int breakPin = 0;

unsigned long currentMillis = 0;
unsigned long startMillis;
const unsigned long period = 1000;

void setup() {
  Serial.begin(115200); 
  initWifi();
  pinMode(sessionPin,INPUT);
  pinMode(breakPin,INPUT);  
  startMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  
    startMillis  = currentMillis;
    if(digitalRead(sessionPin) == HIGH)
    {
      makeIFTTTRequest();
    }
  
}

void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

void makeIFTTTRequest() {
  
    sessionCount++;
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
 

  String jsonObject = String("{\"value1\":\"") + "Session Ended" + "\",\"value2\":\"" + sessionCount + "\",\"value3\":\""  + "\"}";
  
      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
  Serial.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}