#include <WiFi.h>

const char* ssid = "ATACON-2.4G";
const char* password = "05270902";

WiFiServer server(80);

int readPinSensor;  //Variável para leitura da porta analógica
float volts, volts2; //Armazenar o cálculo

void setup() {
  Serial.begin(115200);
  pinMode(33, INPUT);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo Cliente.");

    while (client.connected()) {
      readPinSensor = analogRead(33);
      volts = ((readPinSensor * 0.00123) * 3.6);
      volts = volts + volts*0.06;
      
      String request = client.readStringUntil('\r');
      Serial.println(request);
      client.flush();
      client.println("<html>");
      client.println();
      client.println("<h1><center>ARDUINO OMEGA</center></h1>");
      client.print("<center><font size='5'>Valor da Tensao: " + String(volts) + "</center>");
      client.println();
      client.println("</html>");
      delay(1);
    }
  }
  client.stop();
  //Serial.println("Client Disconnected.");
  delay(1);
}
