/*
 * rplidar_driver.h
 *
 *  Created on: 17 Jun 2022
 *      Author: tmass
 */

#ifndef RPLIDAR_DRIVER_H_
#define RPLIDAR_DRIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "sl_lidar.h"
#include "sl_lidar_driver.h"

class RPLidarDriver
{
public:
	RPLidarDriver();
	bool Init();
	bool StartScan();

private:
	sl::ILidarDriver* m_drv;
	bool m_connectSuccess = false;

	bool checkSLAMTECLIDARHealth();
};


#endif /* RPLIDAR_DRIVER_H_ */
