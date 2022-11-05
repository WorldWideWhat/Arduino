#ifndef __WIFI_HANDLER_H__
#define __WIFI_HANDLER_H__
#include <Arduino.h>
#ifdef ESP32
#include <Wifi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Ticker.h>
#include <string>
#include <functional>
#include <vector>
#include <List.h>

namespace worldwidewhat
{
    class WifiHandler
    {
        public:
        typedef void (*CallbackFunc)(bool state);
        private:
#ifdef ESP32
        static WifiHandler *instance;
        static bool WIFI_STA_START;
#else
        /**
         * @brief Wifi disconnect event handler
         */
        WiFiEventHandler wifiConnectHandler;
        /**
         * @brief Wifi connected event handler
         */
        WiFiEventHandler wifiDisconnectHandler;
#endif        
        /**
         * @brief Reconnect timer
         */
        Ticker reconnectTimer;
        /**
         * @brief Wifi SSID
         */
        std::string ssid;
        /**
         * @brief Wifi passphrase
         */
        std::string password;
        std::vector<CallbackFunc> _callbackListeners;
        /**
         * @brief Allow reconnect to wifi
         */
        bool allowReconnect;

        public:
        WifiHandler(const std::string SSID, const std::string PASSWD);
        void AddCallbackListener(CallbackFunc callback);

        void Connect();

        void Disconnect();

        /**
         * @brief Wifi connection state
         * 
         * @return true 
         * @return false 
         */
        bool isConnected();

        private:
#ifdef ESP32
        static void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info);
        static void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info);
        static void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
        void ConnectionChanged(bool state);
#else        
        /**
         * @brief Wifi connected event internal callback
         * 
         * @param event Callback event
         */
        void onWifiConnect(const WiFiEventStationModeGotIP& event);
        /**
         * @brief Wifi disconnected event internal callback
         * 
         * @param event Callback event
         */
        void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
#endif
        private:
        void TransmitState(bool state);
    };
}

#endif // __WIFI_HANDLER_H__