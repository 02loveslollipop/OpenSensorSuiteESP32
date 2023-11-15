#include <Redis.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include "config.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.begin(config., WIFI_PASSWORD);
    Serial.print("Trying to connect to " + );
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    WiFiClient redisConn;
    if (!redisConn.connect(REDIS_ADDR, REDIS_PORT))
    {
        Serial.println("Failed to connect to the Redis server!");
        return;
    }

    Redis redis(redisConn);
    auto connRet = redis.authenticate(REDIS_PASSWORD);
    if (connRet == RedisSuccess)
    {
        Serial.println("Connected to the Redis server!");
    }
    else
    {
        Serial.printf("Failed to authenticate to the Redis server! Errno: %d\n", (int)connRet);
        return;
    }

    Serial.print("PUBLISH foo bar: ");
    Serial.println(redis.publish("foo", "bar"));

    redisConn.stop();
    Serial.print("Connection closed!");
}

void loop()
{
}
