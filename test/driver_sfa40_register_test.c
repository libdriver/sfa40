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
 * @file      driver_sfa40_register_test.c
 * @brief     driver sfa40 register test source file
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

#include "driver_sfa40_register_test.h"

static sfa40_handle_t gs_handle;        /**< sfa40 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t sfa40_register_test(void)
{
    uint8_t res;
    uint16_t result;
    sfa40_info_t info;
    uint8_t number[6];
    
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
    
    /* start register test */
    sfa40_interface_debug_print("sfa40: start register test.\n");
    
    /* init the chip */
    res = sfa40_init(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: init failed.\n");
    
        return 1;
    }
    
    /* get serial number */
    res = sfa40_get_serial_number(&gs_handle, number);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: get serial number failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sfa40_interface_debug_print("sfa40: serial number is 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n", 
                                number[0], number[1], number[2], number[3], number[4], number[5]);
    
    /* sfa40_start_self_test test */
    sfa40_interface_debug_print("sfa40: sfa40_start_self_test test.\n");
    
    /* start self test */
    res = sfa40_start_self_test(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: start self test failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sfa40_interface_debug_print("sfa40: check self test %s.\n", (res == 0) ? "ok" : "error");
    
    /* delay 2000 ms */
    sfa40_interface_delay_ms(2000);
    
    /* sfa40_get_self_test_data test */
    sfa40_interface_debug_print("sfa40: sfa40_get_self_test_data test.\n");
    
    /* get self test data */
    res = sfa40_get_self_test_data(&gs_handle, &result);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: get self test data failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sfa40_interface_debug_print("sfa40: self test result is 0x%04X.\n", result);
    
    /* sfa40_perform_soft_reset test */
    sfa40_interface_debug_print("sfa40: sfa40_perform_soft_reset test.\n");
    
    /* perform soft reset */
    res = sfa40_perform_soft_reset(&gs_handle);
    if (res != 0)
    {
        sfa40_interface_debug_print("sfa40: perform soft reset failed.\n");
        (void)sfa40_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sfa40_interface_debug_print("sfa40: check perform soft reset %s.\n", (res == 0) ? "ok" : "error");
    
    /* finish register test */
    sfa40_interface_debug_print("sfa40: finish register test.\n");
    (void)sfa40_deinit(&gs_handle);
    
    return 0;
}
