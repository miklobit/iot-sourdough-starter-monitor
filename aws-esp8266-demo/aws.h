#pragma once

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

class AwsIot
{
public:
    AwsIot();
    void loadCertificatesFromSPIFFS(void);
    void setHost(const char* name);
    void connect();
    void loop();
    bool connected();
    void publishMessage();
private:
    WiFiClientSecure *net;
    PubSubClient *client;

    void pubSubErr(int8_t MQTTErr);
};