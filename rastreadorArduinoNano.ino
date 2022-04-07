#include <TinyGPS++.h>      //Gps
#include <BareBoneSim800.h> //Gsm

String latitud = "";
String longitud = "";

#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device     
SoftwareSerial ss(RXPin, TXPin);

BareBoneSim800 sim800("internet.comcel.com.co",NULL,NULL);  //to declare the library with an APN


// Connecting to the Internet and Acting as an HTTP Web Client
 //const char resource[] = "192.168.1.4";
 static String serverIP="www.yourwebpage.com/rastreador/open-layers/";
 String url = "";

 const int port = 80;

void setup() {
  
  ss.begin(GPSBaud);
  
  Serial.begin(9600);
   
  sim800.begin();

  delay(2000);

  
  while(!Serial);

  Serial.println("Testing GSM module For GPRS Connectivity");
  delay(8000); // this delay is necessary, it helps the device to be ready and connect to a network

  Serial.println("Should be ready by now");
    bool deviceAttached = sim800.isAttached();
  if (deviceAttached)
    Serial.println("Device is Attached");
  else
    Serial.println("Not Attached");

// Connecting the the GPRS APN Network
 Serial.println(" Connecting to APN");
 bool netConnect = sim800.gprsConnect();
 if(netConnect)
  
  Serial.println("Connected to Network");
 
 else
  Serial.println("An Error Occured");
 
  
  if(netConnect)   {      
   
    url += serverIP;
    url += "guardar.php?lati=";
    url += latitud;
    url += "&longi=";
    url += longitud;
  
  String result = sim800.sendHTTPData(url.c_str());

    Serial.println("Making HTTP Get Request");
    Serial.println(url);
    //String result = sim800.sendHTTPData(resource);
    Serial.println("Received Info: ");
    Serial.println(result);
  
  }
    
    sim800.closeHTTP(); // disconnect from server
    sim800.gprsDisconnect();
 
}

void obtener_coordenadas(){
   while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      //Serial.print("Latitude= "); 
      //Serial.print(gps.location.lat(), 6);
      latitud = gps.location.lat();
      //Serial.print(" Longitude= "); 
      //Serial.println(gps.location.lng(), 6);
      longitud = gps.location.lng();
    }
  }
}
void loop() {
   obtener_coordenadas();
  
  }



