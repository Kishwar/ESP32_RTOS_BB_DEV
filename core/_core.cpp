/**
 * @file core.cpp
 *
 * @brief This is core module handling hal
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */

#include "_core.hpp"
#include "interface.hpp"
#include "inf_message.h"
#include "wifi.h"

static int8_t _kernel_request_handle_wifi_connect(inf &v);
static int8_t _kernel_request_handle_wifi_disconnect(inf &v);

typedef int8_t (&hndl) (inf &);
static const uint8_t RECEIVE_CORE_QUEUE_LENGTH = 10;
struct core_hdl
{
  reqE req;
  rspE rsp;
  hndl hdl;
} core_hdl [] {
    KERNEL_REQUEST_CONNECT_TO_WIFI_REQ,
    INF_RESPONSE_CONNECT_TO_WIFI_RSP,
    _kernel_request_handle_wifi_connect,

    KERNEL_REQUEST_DISCONNECT_WIFI_REQ,
    INF_RESPONSE_DISCONNECT_WIFI_RSP,
    _kernel_request_handle_wifi_disconnect,

    //write more handlers here..
};

//-------------------------------------------------------------------------//
static void _handle_recv(inf &recv)
{
  int len = sizeof(core_hdl) / sizeof(core_hdl[0]);
  int i = 0;
  while(i < len) {
    if(core_hdl[i].req == recv.identifier) {
      //handle the case here
      core_hdl[i].hdl(recv);
      break;
    }
    i += abs(static_cast<int>(recv.identifier - core_hdl[i].req));
  }
}

//-------------------------------------------------------------------------//
static void _thread_received(void *ptr)
{
  inf recv;
  (void)ptr;
  while(true)
  {
    if(inf_receive_queue(RECEIVE_QUEUE_CORE, recv, -1) == 0)
    {
      //handle recv
      _handle_recv(recv);

      //clear memory
      if(recv.buf != NULL) free(recv.buf);
    }
  }
}

//-------------------------------------------------------------------------//
void core_powerup(void)
{
  inf_create_queue(RECEIVE_QUEUE_CORE, RECEIVE_CORE_QUEUE_LENGTH, sizeof(inf));
  inf_create_task(_thread_received, "CORE_RECV", 2048, 20);
}

//-------------------------------------------------------------------------//
//-------------------------------------------------------------------------//
//-------------------------------------------------------------------------//
int8_t _kernel_request_handle_wifi_connect(inf &v)
{
  wifi_con_req *req = (wifi_con_req *)inf_getbuffer(v);
  if(req != NULL)
  {
    wifi_connect(&req->ssid[0], &req->pass[0]);
  }
  return 0;
}

//-------------------------------------------------------------------------//
int8_t _kernel_request_handle_wifi_disconnect(inf &v)
{
  //TODO
  return 0;
}