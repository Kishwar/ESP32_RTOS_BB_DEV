


#include "interface.hpp"
#include "esp_task_wdt.h"
#include "soc/rtc_wdt.h"

extern "C" void app_main() {
  //stop wdt
  esp_task_wdt_init(portMAX_DELAY, pdFALSE);

}