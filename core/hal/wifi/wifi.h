/**
 * @file wifi.h
 *
 * @brief This is hal for wifi
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/03/2022
 *
 */

#ifndef _WIFI_H_
#define _WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

void wifi_connect(char *ssid, char *pass);

#ifdef __cplusplus
}
#endif

#endif // _WIFI_H_