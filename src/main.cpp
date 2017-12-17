#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ProcessScheduler.h>
#include "./tasks/OTAUpdateProcess.cpp"
#include "./tasks/TcpSocketProcess.cpp"

Scheduler sched;
void setup()
{
    // put your setup code here, to run once:
    static OTAUpdateProcess otaUpdate(sched, HIGH_PRIORITY, 250, "0819");
    static TcpSocketProcess tcpSocket(sched, HIGH_PRIORITY, 100);
    otaUpdate.add(true);
    tcpSocket.add(true);
    Serial.begin(9600);
    WiFi.begin("Andrewhous", "1234567891111");
    Serial.println("Connecting to wifi...");
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");

        delay(5000);
        ESP.restart();
    }
    Serial.println(WiFi.localIP());
}

void loop()
{
    sched.run();
    // put your main code here, to run repeatedly:
}