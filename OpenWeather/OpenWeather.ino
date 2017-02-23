
#include <SoftwareSerial.h>



//String json= "+IPD,449:{\"coord\":{\"lon\":-58.54,\"lat\":-34.64},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"cielo claro\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temp\":35,\"pressure\":1009,\"humidity\":41,\"temp_min\":35,\"temp_max\":35},\"visibility\":10000,\"wind\":{\"speed\":5.1,\"deg\":30,\"gust\":12.9},\"clouds\":{\"all\":0},\"dt\":1485806400,\"sys\":{\"type\":1,\"id\":4699,\"message\":0.2674,\"country\":\"AR\",\"sunrise\":1485767610,\"sunset\":1485817276},\"id\":3435376,\"name\":\"Ciudadela\",\"cod\":200}CLOSED";
String json="";
const String GET= "GET /data/2.5/weather?lat=-34.63&lon=-58.54&units=metric&lang=es&APPID=";
const String APPID = "";//Completar con el APPID de OpenWeather
char clima[20];
float temp;
int hum;
int presion;
float t_min;
float t_max;
int vis;
float wind_speed;
int dir_wind;
int nubosidad;

SoftwareSerial mySerial(10,11); //ESP con AT

void setup() {
  GET=GET+APPID;
  mySerial.begin(115200);
  //mySerial.println("AT+RST");
  mySerial.println("ATE0");
    delay(200);
   mySerial.println("AT+CIPMUX=0");

  delay(200);
   mySerial.println("AT+CWDHCP=1,1");
  delay(200);
  mySerial.println("AT+CIOBAUD=9600");
delay(200);  
  mySerial.setTimeout(2500);
delay(200);
mySerial.end();
mySerial.begin(9600);
Serial.begin(9600);


}

void loop() {
 
enviar_request();

leer_incoming();
delay(1000);
parsearjson();
delay(30000);
}


void enviar_request() 
{

    
Serial.print("AT+CIPSTART=\"TCP\",\"");
Serial.print("api.openweathermap.org");
Serial.println("\",80");

    mySerial.print("AT+CIPSTART=\"TCP\",\"");
mySerial.print("api.openweathermap.org");
mySerial.println("\",80");

delay(1000);


mySerial.print("AT+CIPSEND=");
mySerial.println(GET.length()+2);

Serial.print("AT+CIPSEND=");
Serial.println((GET.length()+2));

delay(500);
mySerial.println(GET);

Serial.println(GET);

//mySerial.print("  ");

//Serial.print("  ");

delay(100);

}


 void leer_incoming()
  {

    while (mySerial.available()>0)
    {
      json=mySerial.readString();
    
      }
      if (mySerial.available()==0)
      { mySerial.println("AT+CIPCLOSE");}
   

  }


void parsearjson()
  {


json.substring(json.lastIndexOf("iption\":")+9,json.indexOf("\",\"icon\"")).toCharArray(clima,20);
temp=json.substring(json.lastIndexOf("\"temp\":")+7,json.indexOf(",\"press")).toFloat();
hum=json.substring(json.lastIndexOf("idity\":")+7,json.indexOf(",\"temp_min")).toInt();
presion=json.substring(json.lastIndexOf("ssure\":")+7,json.indexOf(",\"humi")).toInt();
t_min=json.substring(json.lastIndexOf("mp_min\":")+8,json.indexOf(",\"temp_max")).toFloat();
t_max=json.substring(json.lastIndexOf("mp_max\":")+8,json.indexOf("},\"visib")).toFloat();
vis=json.substring(json.lastIndexOf("lity\":")+6,json.indexOf(",\"wind")).toInt();
wind_speed=json.substring(json.lastIndexOf("speed\":")+7,json.indexOf(",\"deg")).toFloat();
dir_wind=json.substring(json.lastIndexOf(",\"deg\":")+7,json.lastIndexOf(",\"deg\":")+10).toInt();
nubosidad=json.substring(json.lastIndexOf("{\"all\":")+7,json.indexOf("},\"dt")).toInt();

Serial.println(json);
Serial.print("clima: ");
Serial.println(clima);
Serial.print("Temp: ");
Serial.println(temp);
Serial.print("Hum.: ");
Serial.println(hum);
Serial.print("Presion: ");
Serial.println(presion);
Serial.print("T min: ");
Serial.println(t_min);
Serial.print("T max: ");
Serial.println(t_max);
Serial.print("Visibilidad: ");
Serial.println(vis);
Serial.print("Vel. viento(m/s):");
Serial.println(wind_speed);
Serial.print("Dir. viento(deg):");
Serial.println(dir_wind);
Serial.print("Nubosidad: ");
Serial.println(nubosidad);
json="";
    }

