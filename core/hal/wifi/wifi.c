/**
 * @file wifi.c
 *
 * @brief This is hal for wifi
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */

#include "wifi.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include <string.h>

static bool _isConnected = false;

static void _callback_wifi_event(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
  // TODO update information in kernel queue
  if (event_base != WIFI_EVENT) return;
  switch(event_id)
  {
    case WIFI_EVENT_STA_START:
      esp_wifi_connect();
      break;
    case WIFI_EVENT_STA_CONNECTED:
      _isConnected = true;
      break;
    case WIFI_EVENT_STA_DISCONNECTED:
      _isConnected = true;
      break;
    default:
      break;
  }
}

void wifi_connect(char *ssid, char *pass)
{
  wifi_config_t sta_config;
  esp_err_t ret = nvs_flash_init();

  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    nvs_flash_erase();
    nvs_flash_init();
  }

  esp_netif_init();
  esp_event_loop_create_default();
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);

  esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, _callback_wifi_event, NULL);

  esp_wifi_set_mode(WIFI_MODE_STA);

  memset(&sta_config, 0, sizeof(sta_config));
  memcpy(sta_config.sta.ssid, ssid, strlen(ssid));
  memcpy(sta_config.sta.password, pass, strlen(pass));

  esp_wifi_set_config(WIFI_IF_STA, &sta_config);
  esp_wifi_start();
}
