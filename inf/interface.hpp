/**
 * @file interface.hpp
 *
 * @brief This is interface layer between App and Core
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdint.h>
#include <string>
#include <esp_log.h>

#define LOG_INFO(tag, format, ...) \
  ESP_LOGI(tag, "%06d %s: " format, __LINE__, __func__, ##__VA_ARGS__); \

typedef void (*inf_task)(void *);

typedef struct inf
{
  uint32_t identifier;
  void *buf;
} inf;

typedef enum rcvQ {
  RECEVIE_QUEUE_INVALID = 0,
  RECEIVE_QUEUE_CORE,
  RECEIVE_QUEUE_MAX = 0xFF
} rcvQ;

typedef enum reqE {
  INF_REQUEST_INVALID_VALUE_MIN = 0,

  //wifi
  KERNEL_REQUEST_CONNECT_TO_WIFI_REQ,
  KERNEL_REQUEST_DISCONNECT_WIFI_REQ,
  KERNEL_REQUEST_GET_WIFI_IP_REQ,

  //max value (last enum value)
  INF_REQUEST_INVALID_VALUE_MAX
} reqE;

typedef enum rspE {
  INF_RESPONSE_INVALID_VALUE_MIN = 0,

  //wifi
  INF_RESPONSE_CONNECT_TO_WIFI_RSP,
  INF_RESPONSE_DISCONNECT_WIFI_RSP,
  INF_RESPONSE_GET_WIFI_IP_RSP,

  //max value (last enum value)
  INF_RESPONSE_INVALID_VALUE_MAX
} rspE;

void inf_start(void);

int32_t inf_create(inf &, uint32_t, uint32_t);

void inf_destroy(inf &);

void *inf_getbuffer(inf &pmsg);

int32_t inf_create_task(inf_task task, std::string &&tname, const uint32_t stack, const uint32_t prio);

int32_t inf_create_queue(const uint32_t id, const uint32_t size, const uint32_t items);

int32_t inf_receive_queue(const uint32_t id, inf &recv, const uint32_t timeout);

#endif // _INTERFACE_H_