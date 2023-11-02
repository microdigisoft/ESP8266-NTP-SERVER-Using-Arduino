#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
const char *ssid     = "xxxxxxxxx";
const char *password = "xxxx";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
ESP8266WebServer server(80);
//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  // Initialize Serial Monitor

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
    Serial.begin(115200);
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(19800);
}

void loop() {
  
server.handleClient();
 timeClient.update();
 
  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);
   String currentDate = String(monthDay) + "-" + String(currentMonth)+ "-" + String(currentYear)  ;
Serial.print("today: ");
  Serial.println(currentDate);
 String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);    
 
 
  //Get a time structure
 
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

}

void handle_OnConnect() {  
 
 timeClient.update();
 
  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);
   String currentDate = String(monthDay) + "-" + String(currentMonth)+ "-" + String(currentYear)  ;
Serial.print("today: ");
  Serial.println(currentDate);
 String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);    
 
 
  //Get a time structure
 
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

  server.send(200, "text/html", SendHTML(currentDate,formattedTime,currentMonthName, weekDay)); 
  //Print complete date:
  
  
  //String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String currentDate, String formattedTime,  String currentMonthName, String weekDay){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 NTP Server</title>\n";

  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<center>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<center><h1> WELL-COME TO MICRODIGISOFT </h1></center>\n";
  ptr +="<h2>Current Date and Time with ESP8266-Wemos D1 Mini Module using NTP Server</h2>\n"; 
  
  ptr +="<p>Current Date: ";
  ptr +=(String)currentDate;
  ptr +="</p>";
  ptr +="<p>Time: ";
  ptr +=(String)formattedTime;
  ptr +="</p>";
   
   ptr +="<p>Month: ";
  ptr +=(String)currentMonthName;
  ptr +="</p>";
  
  ptr +="<p>Day: ";
  ptr +=(String)weekDay;
  ptr +="</p>";

   
  ptr +="</div>\n";
  ptr +="</center>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
