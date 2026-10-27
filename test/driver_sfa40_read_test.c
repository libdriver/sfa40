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
 * @file      driver_sfa40_read_test.c
 * @brief     driver sfa40 read test source file
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

#include "driver_sfa40_read_test.h"

static sfa40_handle_t gs_handle;        /**< sfa40 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sfa40_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    sfa40_info_t info;
    sfa40_data_t data;
    
    /* link functions */
    DRIVER_SFA40_LINK_INIT(&gs_handle, sfa40_handle_t);
    DRIVER_SFA40_LINK_IIC_INIT(&gs_handle, sfa40_interface_iic_init);
    DRIVER_SFA40_LINK_IIC_DEINIT(&gs_handle, sfa40_interface_iic_deinit);
    DRIVER_SFA40_LINK_IIC_WRITE_COMMAND(&gs_handle, sfa40_interface_iic_write_cmd);
    DRIVER_SFA40_LINK_IIC_READ_COMMAND(&gs_handle, sfa40_interface_iic_read_cmd);
    DRIVER_SFA40_LINK_DELAY_MS(&gs_handle, sfa40_interface_delay_ms);
    DRIVER_SFA40_LINK_DEBUG_PRINT(&gs_handle, sfa40_interface_debug_print);
    
    /* get information */
    res = sfa40_info(&info);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        sfa40_interface_debug_print("sfa40: chip is %s.\n", info.chip_name);
        sfa40_interface_debug_print("sfa40: manufacturer is %s.\n", info.manufacturer_name);
        sfa40_interface_debug_print("sfa40: interface is %s.\n", info.interface);
        sfa40_interface_debug_print("sfa40: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sfa40_interface_debug_print("sfa40: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sfa40_interface_debug_print("sfa40: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sfa40_interface_debug_print("sfa40: max current is %0.2fmA.\n", info.max_current_ma);
        sfa40_interface_debug_print("sfa40: max temperature is %0.1fC.\n", info.temperature_max);
        sfa40_interface_debug_print("sfa40: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    sfa40_interface_debug_print("sfa40: start read test.\n");
    
    /* init the chip */
    res = sfa40_init(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: init failed.\n");
    
        return 1;
    }
    
    /* start continuous measurement */
    res = sfa40_start_continuous_measurement(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: start continuous measurement failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 65s*/
    sfa40_interface_debug_print("sfa40: wait 65s.\n");
    
    /* delay 65s */
    sfa40_interface_delay_ms(1000 * 65);
    
    for (i = 0; i < times; i++)
    {
        res = sfa40_read(&gs_handle, &data);
        if (res != 0)
        {
            sfa40_interface_debug_print("sfa40: read failed.\n");
            (void)sfa40_stop_continuous_measurement(&gs_handle);
            (void)sfa40_deinit(&gs_handle);
            
            return 1;
        }
        sfa40_interface_debug_print("sfa40: formaldehyde is %0.2fppb.\n", data.formaldehyde);
        sfa40_interface_debug_print("sfa40: humidity is %0.2f%%.\n", data.humidity);
        sfa40_interface_debug_print("sfa40: temperature is %0.2fC.\n", data.temperature);
        
        /* delay 2000 ms */
        sfa40_interface_delay_ms(2000);
    }
    
    /* stop continuous measurement */
    res = sfa40_stop_continuous_measurement(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: stop continuous measurement failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish read test */
    sfa40_interface_debug_print("sfa40: finish read test.\n");
    (void)sfa40_deinit(&gs_handle);
    
    return 0;
}
