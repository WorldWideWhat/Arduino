#include "WifiHandler.h"

#ifdef ESP32
worldwidewhat::WifiHandler *worldwidewhat::WifiHandler::instance = nullptr;
bool worldwidewhat::WifiHandler::WIFI_STA_START = false;
#endif

worldwidewhat::WifiHandler::WifiHandler(const std::string SSID, const std::string PASSWD)
{
    ssid = SSID;
    password = PASSWD;
    allowReconnect = true;
#ifdef ESP32
    instance = this;
    WiFi.onEvent(onWifiEvent);
#else
    wifiDisconnectHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected & event){
       onWifiDisconnect(event);
    });

    wifiConnectHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP & event){
        onWifiConnect(event);
    });
#endif    
}

void worldwidewhat::WifiHandler::Connect()
{
    allowReconnect = true;
    wl_status_t ret = WiFi.begin(ssid.c_str(), password.c_str());
    Serial.printf("State %d, %s, %s\n", ret, ssid.c_str(), password.c_str());
}

void worldwidewhat::WifiHandler::Disconnect()
{
    allowReconnect = false;
    WiFi.disconnect();
}

bool worldwidewhat::WifiHandler::isConnected()
{
    return WiFi.isConnected();
}

void worldwidewhat::WifiHandler::AddCallbackListener(CallbackFunc callback)
{
    _callbackListeners.push_back(callback);
}

void worldwidewhat::WifiHandler::TransmitState(bool state)
{
    for(uint32_t i = 0; i < _callbackListeners.size(); i++)
    {
        //CallbackFunc func =*_callbackListeners[i];
        _callbackListeners[i](state);
        //func(state);
    }
}
#ifdef ESP32
void worldwidewhat::WifiHandler::onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
    static WiFiEvent_t lastEvent = ARDUINO_EVENT_WIFI_STA_DISCONNECTED;
    
    if(event == lastEvent) return;
    switch(event)
    {
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            if(!WIFI_STA_START) break;
            instance->ConnectionChanged(false);
            WIFI_STA_START = false;
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            if(!WIFI_STA_START) break;
            instance->ConnectionChanged(true);
            break;        
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            WIFI_STA_START = true;
            break;
    }
   lastEvent = event;
}

void worldwidewhat::WifiHandler::onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info)
{
    instance->ConnectionChanged(true);
}

void worldwidewhat::WifiHandler::onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info)
{
    instance->ConnectionChanged(false);
    
}

void worldwidewhat::WifiHandler::ConnectionChanged(bool state)
{
    TransmitState(state);
    if(!state) reconnectTimer.once(2, +[](WifiHandler* handler){handler->Connect();}, this);
}

#else
void worldwidewhat::WifiHandler::onWifiConnect(const WiFiEventStationModeGotIP& event)
{
    TransmitState(true);
}

void worldwidewhat::WifiHandler::onWifiDisconnect(const WiFiEventStationModeDisconnected& event) 
{
    TransmitState(false);
    reconnectTimer.once(2, +[](WifiHandler* handler){handler->Connect();}, this);
}
#endif