/*
 * rplidar_driver.cpp
 *
 *  Created on: 17 Jun 2022
 *      Author: tmass
 */

#include "rplidar_driver.h"

#include "fsl_debug_console.h" //PRINTF

RPLidarDriver::RPLidarDriver()
: m_drv(*sl::createLidarDriver())
{
}

bool RPLidarDriver::Init()
{
    sl_result     op_result;

	if (!m_drv) {
	   PRINTF("Lidar driver instance could not be created\n");
	   return false;
	}

    sl_lidar_response_device_info_t devinfo;

    op_result = m_drv->getDeviceInfo(devinfo);

    if (!SL_IS_OK(op_result)) {
 	   PRINTF("Unable to get device info\n");
 	   return false;
 	}

    // print out the device serial number, firmware and hardware version number..
    PRINTF("SLAMTEC LIDAR S/N: ");
    for (int pos = 0; pos < 16 ;++pos) {
    	PRINTF("%02X", devinfo.serialnum[pos]);
    }

    PRINTF("\n"
            "Firmware Ver: %d.%02d\n"
            "Hardware Rev: %d\n"
            , devinfo.firmware_version>>8
            , devinfo.firmware_version & 0xFF
            , (int)devinfo.hardware_version);

    // check health...
	if (!checkSLAMTECLIDARHealth()) {
	 	   PRINTF("Lidar device health not OK\n");
	 	   return false;
	}

	return true;
}

bool RPLidarDriver::StartScan()
{
    sl_result     op_result;

    // set motor speed...
    op_result = m_drv->setMotorSpeed();

    if (!SL_IS_OK(op_result)) {
 	   PRINTF("Unable to set motor speed\n");
 	   return false;
 	}

    // start scan...
    op_result = m_drv->startScan(0,1);

    if (!SL_IS_OK(op_result)) {
 	   PRINTF("Unable to start scan\n");
 	   return false;
 	}

    return true;
}

bool RPLidarDriver::checkSLAMTECLIDARHealth()
{
    sl_result     op_result;
    sl_lidar_response_device_health_t healthinfo;

    op_result = m_drv->getHealth(healthinfo);
    if (SL_IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
    	PRINTF("SLAMTEC Lidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == SL_LIDAR_STATUS_ERROR) {
        	PRINTF("Error, slamtec lidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want slamtec lidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
    	PRINTF("Error, cannot retrieve the lidar health code: %lx\n", op_result);
        return false;
    }
}
