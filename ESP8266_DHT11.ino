#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<DHT.h>
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
ESP8266WebServer server(80);
const char*ssid="**********";
const char*password="**********";
String SendHTML(float temp,float humid);
void handle_OnConnect();
void handle_NotFound();
void handle_retake();
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
dht.begin();
WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.println(".");
  delay(650);
}
Serial.println("CONNECTED");
Serial.println("USE THIS IP TO CONNECT");
Serial.println(WiFi.localIP());
server.on("/" ,handle_OnConnect);
server.on("/RESET",handle_retake);
server.onNotFound(handle_NotFound);
server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
void handle_OnConnect()
{
  float temp=dht.readTemperature();
  delay(1000);
  float humid=dht.readHumidity();
  delay(1000);
  server.send(200, "text/html",SendHTML(temp,humid));
}
void handle_retake()
{
  handle_OnConnect();
}
void handle_NotFound()
{
  server.send(404,"text/plain","NOT FOUND");
}
String SendHTML(float temp,float humid){
  String ptr="<!DOCTYPE html>\n";
ptr+="<html lang=\"en\">\n";
ptr+="<head>\n";
ptr+="    <meta charset=\"UTF-8\">\n";
ptr+="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
ptr+="    <title>Document</title>\n";
ptr+="    <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css\" integrity=\"sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2\" crossorigin=\"anonymous\">\n";
ptr+="    <script src=\"https://code.jquery.com/jquery-3.5.1.slim.min.js\" integrity=\"sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj\" crossorigin=\"anonymous\"></script>\n";
ptr+="<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ho+j7jyWK8fNQe+A12Hb8AhRq26LrZ/JpcUGGOn+Y7RsweNrtN/tE3MoK7ZeZDyx\" crossorigin=\"anonymous\"></script>\n";
ptr+="<style>\n";
ptr+="    textarea{\n";
ptr+="        border-radius: 20px;\n";
ptr+="    }\n";
ptr+="    body{\n";
ptr+="        background-color:#e0ece4;\n";
ptr+="    }\n";
ptr+="    button{\n";
ptr+="        background: #3D94F6;\n";
ptr+="    background-image: -webkit-linear-gradient(top, #3D94F6, #1E62D0);\n";
ptr+="    background-image: -moz-linear-gradient(top, #3D94F6, #1E62D0);\n";
ptr+="    background-image: -ms-linear-gradient(top, #3D94F6, #1E62D0);\n";
ptr+="    background-image: -o-linear-gradient(top, #3D94F6, #1E62D0);\n";
ptr+="    background-image: -webkit-gradient(to bottom, #3D94F6, #1E62D0);\n";
ptr+="    -webkit-border-radius: 20px;\n";
ptr+="    -moz-border-radius: 20px;\n";
ptr+="    border-radius: 20px;\n";
ptr+="    color: #FFFFFF;\n";
ptr+="    font-family: Open Sans;\n";
ptr+="    font-size: 40px;\n";
ptr+="    font-weight: 100;\n";
ptr+="    padding: 40px;\n";
ptr+="    -webkit-box-shadow: 1px 1px 20px 0 #000000;\n";
ptr+="    -moz-box-shadow: 1px 1px 20px 0 #000000;\n";
ptr+="    box-shadow: 1px 1px 20px 0 #000000;\n";
ptr+="    text-shadow: 1px 1px 20px #000000;\n";
ptr+="    border: solid #337FED 1px;\n";
ptr+="    text-decoration: none;\n";
ptr+="    display: inline-block;\n";
ptr+="    cursor: pointer;\n";
ptr+="    text-align: center;\n";
ptr+=" }\n";
ptr+=" \n";
ptr+=" button:hover {\n";
ptr+="    border: solid #337FED 1px;\n";
ptr+="    background: #1E62D0;\n";
ptr+="    background-image: -webkit-linear-gradient(top, #1E62D0, #3D94F6);\n";
ptr+="    background-image: -moz-linear-gradient(top, #1E62D0, #3D94F6);\n";
ptr+="    background-image: -ms-linear-gradient(top, #1E62D0, #3D94F6);\n";
ptr+="    background-image: -o-linear-gradient(top, #1E62D0, #3D94F6);\n";
ptr+="    background-image: -webkit-gradient(to bottom, #1E62D0, #3D94F6);\n";
ptr+="    -webkit-border-radius: 20px;\n";
ptr+="    -moz-border-radius: 20px;\n";
ptr+="    border-radius: 20px;\n";
ptr+="    text-decoration: none;\n";
ptr+=" }\n";
ptr+="    }\n";
ptr+="</style>\n";
ptr+="</head>\n";
ptr+="<body>\n";
ptr+="<h1><u>Temperature and Humidity via ESP8266</u></h1>\n";
ptr+="<br>\n";
ptr+="<br>\n";
ptr+="<table class=\"table table-dark\">\n";
ptr+="    <thead>\n";
ptr+="      <tr>\n";
ptr+="        <th scope=\"col\">TEMPERATURE</th>\n";
ptr+="        <th scope=\"col\">HUMIDITY</th>\n";
ptr+="      </tr>\n";
ptr+="    </thead>\n";
ptr+="    <tbody>\n";
ptr+="      <tr>\n";
ptr+="        <td>\n";
ptr+="            <textarea placeholder=\"0\">\n";
ptr+=float(temp);
ptr+="</textarea>\n";
ptr+="        </td>\n";
ptr+="        <td>\n";
ptr+="            <textarea placeholder=\"0\">\n";
ptr+=float(humid);
ptr+="</textarea>\n";
ptr+="        </td>\n";
ptr+="      </tr>\n";
ptr+="    </tbody>\n";
ptr+="  </table>\n";
ptr+="  <hr>\n";
ptr+="<a href=\"/RESET\"><button class=\"BUTTON_XAD\">Getvalues</button></a>";
ptr+="</body>\n";
ptr+="</html>";
   
return ptr;
}
