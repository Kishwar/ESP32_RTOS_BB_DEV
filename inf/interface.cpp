/**
 * @file interface.cpp
 *
 * @brief This is interface layer between App and Core
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */


#include "interface.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <map>

#include "core.hpp"

static std::map<uint32_t, QueueHandle_t> infQ;

void inf_start(void)
{
  core_powerup();
}

int32_t inf_create(inf &pmsg, uint32_t size, uint32_t id)
{
  pmsg.buf = std::malloc(size);
  pmsg.identifier = id;
  return 0;
}

void inf_destroy(inf &pmsg)
{
  if(pmsg.buf != NULL)
    free(pmsg.buf);
  pmsg.buf = NULL;
  pmsg.identifier = -1;
}

void *inf_getbuffer(inf &pmsg)
{
  return pmsg.buf;
}

int32_t inf_create_task(inf_task task, std::string &&tname, const uint32_t stack, const uint32_t prio)
{
  if(xTaskCreate(task, tname.c_str(), stack, NULL, prio, NULL) != pdPASS)
  {
    return -1;
  }
  return 0;
}

int32_t inf_create_queue(const uint32_t id, const uint32_t size, const uint32_t items)
{
  QueueHandle_t hdlQ;
  if((hdlQ = xQueueCreate(size, items)) == NULL)
  {
    return -1;
  }
  infQ[id] = hdlQ;
  return 0;
}

int32_t inf_receive_queue(const uint32_t id, inf &recv, const uint32_t timeout)
{
  int32_t ret = 0;
  ret = xQueueReceive(infQ[id], &recv, timeout == -1 ? portMAX_DELAY : timeout) == pdPASS ? 0 : -1;
  return ret;
}