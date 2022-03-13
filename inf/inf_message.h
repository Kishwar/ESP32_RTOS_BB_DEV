/**
 * @file interface.h
 *
 * @brief Defines difference interface req/rsp
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

#define SSID_MAX_SSID_BUFFER_SIZE    50
#define SSID_MAX_PASS_BUFFER_SIZE    50

typedef struct wifi_connect {
  char ssid[SSID_MAX_SSID_BUFFER_SIZE];  //< SSID
  char pass[SSID_MAX_PASS_BUFFER_SIZE];  //< PASSWORD
} wifi_con_req;


#ifdef __cplusplus
}
#endif