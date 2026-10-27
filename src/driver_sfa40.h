/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sfa40.h
 * @brief     driver sfa40 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-08-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/08/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_SFA40_H
#define DRIVER_SFA40_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sfa40_driver sfa40 driver function
 * @brief    sfa40 driver modules
 * @{
 */

/**
 * @addtogroup sfa40_basic_driver
 * @{
 */

/**
 * @brief sfa40 status enumeration definition
 */
typedef enum
{
    SFA40_STATUS_NOT_YET_WITHIN_SPECIFICATIONS = (1 << 1),        /**< not yet within specifications */
    SFA40_STATUS_NOT_READY                     = (1 << 0),        /**< not ready */
} sfa40_status_t;

/**
 * @brief sfa40 data structure definition
 */
typedef struct sfa40_data_s
{
    uint8_t status;                  /**< status */
    uint16_t formaldehyde_raw;       /**< formaldehyde raw */
    uint16_t humidity_raw;           /**< humidity raw */
    uint16_t temperature_raw;        /**< temperature raw */
    float formaldehyde;              /**< formaldehyde in ppb */
    float humidity;                  /**< humidity in % */
    float temperature;               /**< temperature in C */
} sfa40_data_t;

/**
 * @brief sfa40 handle structure definition
 */
typedef struct sfa40_handle_s
{
    uint8_t (*iic_init)(void);                                                /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                              /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);       /**< point to an iic_write_cmd function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_read_cmd function address */
    void (*delay_ms)(uint32_t ms);                                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                          /**< point to a debug_print function address */
    uint8_t inited;                                                           /**< inited flag */
} sfa40_handle_t;

/**
 * @brief sfa40 information structure definition
 */
typedef struct sfa40_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[16];                /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} sfa40_info_t;

/**
 * @}
 */

/**
 * @defgroup sfa40_link_driver sfa40 link driver function
 * @brief    sfa40 link driver modules
 * @ingroup  sfa40_driver
 * @{
 */

/**
 * @brief     initialize sfa40_handle_t structure
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] STRUCTURE sfa40_handle_t
 * @note      none
 */
#define DRIVER_SFA40_LINK_INIT(HANDLE, STRUCTURE)              memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_IIC_INIT(HANDLE, FUC)               (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_IIC_DEINIT(HANDLE, FUC)             (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)      (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_IIC_READ_COMMAND(HANDLE, FUC)       (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_DELAY_MS(HANDLE, FUC)               (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an sfa40 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_SFA40_LINK_DEBUG_PRINT(HANDLE, FUC)            (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup sfa40_basic_driver sfa40 basic driver function
 * @brief    sfa40 basic driver modules
 * @ingroup  sfa40_driver
 * @{
 */

/**
 * @brief      get chip information
 * @param[out] *info pointer to an sfa40 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sfa40_info(sfa40_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t sfa40_init(sfa40_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_deinit(sfa40_handle_t *handle);

/**
 * @brief      read the result
 * @param[in]  *handle pointer to an sfa40 handle structure
 * @param[out] *data pointer to an sfa40_data_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check error
 *             - 5 data is not ready
 * @note       none
 */
uint8_t sfa40_read(sfa40_handle_t *handle, sfa40_data_t *data);

/**
 * @brief     start continuous measurement
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous measurement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_start_continuous_measurement(sfa40_handle_t *handle);

/**
 * @brief     stop continuous measurement
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous measurement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_stop_continuous_measurement(sfa40_handle_t *handle);

/**
 * @brief      get serial number
 * @param[in]  *handle pointer to an sfa40 handle structure
 * @param[out] *number pointer to a number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check error
 * @note       none
 */
uint8_t sfa40_get_serial_number(sfa40_handle_t *handle, uint8_t number[6]);

/**
 * @brief     start self test
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start self test failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_start_self_test(sfa40_handle_t *handle);

/**
 * @brief      get self test data
 * @param[in]  *handle pointer to an sfa40 handle structure
 * @param[out] *result pointer to a result buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check error
 * @note       result
 *             0xFFFFU is running
 *             0x0000U is passed
 *             the others is failed
 */
uint8_t sfa40_get_self_test_data(sfa40_handle_t *handle, uint16_t *result);

/**
 * @brief     perform soft reset
 * @param[in] *handle pointer to an sfa40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 perform soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_perform_soft_reset(sfa40_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup sfa40_extern_driver sfa40 extern driver function
 * @brief    sfa40 extern driver modules
 * @ingroup  sfa40_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an sfa40 handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sfa40_set_reg(sfa40_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to an sfa40 handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sfa40_get_reg(sfa40_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
