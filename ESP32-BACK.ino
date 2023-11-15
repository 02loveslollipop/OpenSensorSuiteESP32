#include <Redis.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include "config.h"
#include <time.h>

double getData(){ //Change 128 to the size of your data (can't be a variable, will throw compilation error :/)
    //Change this to get data from your sensor it must return a char array change
    double random_seed = ((double)random(1024)) / 1024; //convert to float random between 0 and 1
    return random_seed*(104) - 100; //convert to random between -100 and 4
}

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup()
{
    
    unsigned long time;
    char char_time[10];
    char char_value[10];
    double float_value;
     //Change 128 to the size of your data (can't be a variable, will throw compilation error :/)

    Serial.begin(115200); //Setup serial connection for debugging at 115200 baud
    Serial.println();

    WiFi.mode(WIFI_STA); //Set WiFi mode to station (client)
    WiFi.begin(wifi_ssid, wifi_password); //Connect to the WiFi network
    Serial.print("Trying to connect to: ");
    Serial.println(wifi_ssid);

    while (WiFi.status() != WL_CONNECTED) //Wait for the WiFi connection to be established
    {
        delay(250);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); //Print the local IP address of the ESP32

    //set ntp server
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    WiFiClient redisConn; //Create a client to connect to Redis
    if (!redisConn.connect(redis_address, redis_port)) //Connect to Redis server
    {
        Serial.println("Failed to connect to the Redis server!");
        return;
    }

    Redis redis(redisConn);  //Create a Redis client to send commands to the Redis server
    auto connRet = redis.authenticate(redis_password); //Authenticate to the Redis server
    if (connRet == RedisSuccess) //Check if the authentication was successful
    {
        Serial.println("Connected to the Redis server!");
    }
    else //If authentication failed, print the reason
    {
        Serial.printf("Failed to authenticate to the Redis server! Errno: %d\n", (int)connRet); 
        return;
    }

    while(true){
        //current time in posix format
        time = getTime();
        sprintf(char_time, "%lu", time);
        Serial.print("current time: ");
        Serial.println(time);

        //get data from sensor
        float_value = getData();
        sprintf(char_value, "%lf", float_value);

        //push to redis
        Serial.print("Pushing value  to Redis:");
        Serial.println(redis.hset(redis_key,char_time,char_value));
        delay(1000);
    }
}

void loop(){
    return;
}