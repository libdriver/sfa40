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
 * @file      driver_sfa40.c
 * @brief     driver sfa40 source file
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

#include "driver_sfa40.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Sensirion SFA40"        /**< chip name */
#define MANUFACTURER_NAME         "Sensirion"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.62f                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.60f                    /**< chip max supply voltage */
#define MAX_CURRENT               2.00f                    /**< chip max current */
#define TEMPERATURE_MIN           0.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           50.0f                    /**< chip max operating temperature */
#define DRIVER_VERSION            1000                     /**< driver version */

/**
 * @brief chip address definition
 */
#define SFA40_ADDRESS             (0x5D << 1)              /**< chip iic address */

/**
 * @brief chip command definition
 */
#define SFA40_COMMAND_START_CONTINUOUS_MEASUREMENT      0x00ACU        /**< start continuous measurement command */
#define SFA40_COMMAND_READ_MEASUREMENT                  0xC0EBU        /**< read measurement command */
#define SFA40_COMMAND_STOP_CONTINUOUS_MEASUREMENT       0x50D2U        /**< stop continuous measurement command */
#define SFA40_COMMAND_READ_SERIAL_NUMBER                0x02CEU        /**< read serial number command */
#define SFA40_COMMAND_START_SELF_TEST                   0x060AU        /**< start self test command */
#define SFA40_COMMAND_READ_SELF_TEST_DATA               0xC0EBU        /**< read self test data command */
#define SFA40_COMMAND_PERFORM_SOFT_RESET                0x06           /**< perform soft reset command */

/**
 * @brief     generate the crc
 * @param[in] *data pointer to a data buffer
 * @param[in] count data length
 * @return    crc
 * @note      none
 */
static uint8_t a_sfa40_generate_crc(uint8_t* data, uint8_t count)
{
    uint8_t current_byte;
    uint8_t crc_bit;
    uint8_t crc = 0xFF;

    for (current_byte = 0; current_byte < count; ++current_byte)        /* calculate crc */
    {
        crc ^= (data[current_byte]);                                    /* xor data */
        for (crc_bit = 8; crc_bit > 0; --crc_bit)                       /* 8 bit */
        {
            if ((crc & 0x80) != 0)                                      /* if 7th bit is 1 */
            {
                crc = (crc << 1) ^ 0x31;                                /* xor */
            }
            else
            {
                crc = crc << 1;                                         /* left shift 1 */
            }
        }
    }

    return crc;                                                         /* return crc */
}

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to an sfa40 handle structure
 * @param[in]  addr iic device address
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @param[in]  delay_ms delay time in ms
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_sfa40_read(sfa40_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *data, uint16_t len, uint16_t delay_ms)
{
    uint8_t buf[2];

    buf[0] = (reg >> 8) & 0xFF;                                  /* set msb */
    buf[1] = (reg >> 0) & 0xFF;                                  /* set lsb */
    if (handle->iic_write_cmd(addr, (uint8_t *)buf, 2) != 0)     /* write data */
    {
        return 1;                                                /* return error */
    }
    handle->delay_ms(delay_ms);                                  /* delay ms */
    if (handle->iic_read_cmd(addr, (uint8_t *)data, len) != 0)   /* read data */
    {
        return 1;                                                /* return error */
    }

    return 0;                                                    /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to an sfa40 handle structure
 * @param[in] addr iic device address
 * @param[in] reg iic register address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @param[in] delay_ms delay time in ms
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_sfa40_write(sfa40_handle_t *handle, uint8_t addr, uint16_t reg, uint8_t *data, uint16_t len, uint16_t delay_ms)
{
    uint8_t buf[16];

    if (len > 14)                                                    /* check length */
    {
        return 1;                                                    /* return error */
    }
    
    buf[0] = (reg >> 8) & 0xFF;                                      /* set msb */
    buf[1] = (reg >> 0) & 0xFF;                                      /* set lsb */
    memcpy((uint8_t *)&buf[2], data, len);                           /* copy data */
    if (handle->iic_write_cmd(addr, (uint8_t *)buf, len + 2) != 0)   /* write data */
    {
        return 1;                                                    /* return error */
    }
    handle->delay_ms(delay_ms);                                      /* delay ms */

    return 0;                                                        /* success return 0 */
}

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
uint8_t sfa40_start_continuous_measurement(sfa40_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                                                                        /* check handle */
    {
        return 2;                                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                                   /* check handle initialization */
    {
        return 3;                                                                                              /* return error */
    }
    
    res = a_sfa40_write(handle, SFA40_ADDRESS, SFA40_COMMAND_START_CONTINUOUS_MEASUREMENT, NULL, 0, 1000);     /* start continuous measurement command */
    if (res != 0)                                                                                              /* check result */
    {
        handle->debug_print("sfa40: start continuous measurement failed.\n");                                  /* start continuous measurement failed */

        return 1;                                                                                              /* return error */
    }

    return 0;                                                                                                  /* success return 0 */
}

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
uint8_t sfa40_stop_continuous_measurement(sfa40_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                                                                       /* check handle */
    {
        return 2;                                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                                  /* check handle initialization */
    {
        return 3;                                                                                             /* return error */
    }

    res = a_sfa40_write(handle, SFA40_ADDRESS, SFA40_COMMAND_STOP_CONTINUOUS_MEASUREMENT, NULL, 0, 26);       /* stop continuous measurement command */
    if (res != 0)                                                                                             /* check result */
    {
        handle->debug_print("sfa40: stop continuous measurement failed.\n");                                  /* stop continuous measurement failed */

        return 1;                                                                                             /* return error */
    }

    return 0;                                                                                                 /* success return 0 */
}

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
uint8_t sfa40_get_serial_number(sfa40_handle_t *handle, uint8_t number[6])
{
    uint8_t res;
    uint8_t buf[9];

    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }

    res = a_sfa40_read(handle, SFA40_ADDRESS, SFA40_COMMAND_READ_SERIAL_NUMBER, buf, 9, 0);        /* read serial number command */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("sfa40: read serial number failed.\n");                                /* read serial number failed */

        return 1;                                                                                  /* return error */
    }
    if (a_sfa40_generate_crc(&buf[0], 2) != buf[2])                                                /* check crc */
    {
        handle->debug_print("sfa40: crc check error.\n");                                          /* crc check error */

        return 4;                                                                                  /* return error */
    }
    if (a_sfa40_generate_crc(&buf[3], 2) != buf[5])                                                /* check crc */
    {
        handle->debug_print("sfa40: crc check error.\n");                                          /* crc check error */

        return 4;                                                                                  /* return error */
    }
    if (a_sfa40_generate_crc(&buf[6], 2) != buf[8])                                                /* check crc */
    {
        handle->debug_print("sfa40: crc check error.\n");                                          /* crc check error */

        return 4;                                                                                  /* return error */
    }
    
    number[0] = buf[0];                                                                            /* set byte 0 */
    number[1] = buf[1];                                                                            /* set byte 1 */
    number[2] = buf[3];                                                                            /* set byte 2 */
    number[3] = buf[4];                                                                            /* set byte 3 */
    number[4] = buf[6];                                                                            /* set byte 4 */
    number[5] = buf[7];                                                                            /* set byte 5 */
    
    return 0;                                                                                      /* success return 0 */
}

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
uint8_t sfa40_start_self_test(sfa40_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }

    res = a_sfa40_write(handle, SFA40_ADDRESS, SFA40_COMMAND_START_SELF_TEST, NULL, 0, 0);        /* start self test command */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("sfa40: start self test failed.\n");                                  /* start self test failed */

        return 1;                                                                                 /* return error */
    }

    return 0;                                                                                     /* success return 0 */
}

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
uint8_t sfa40_get_self_test_data(sfa40_handle_t *handle, uint16_t *result)
{
    uint8_t res;
    uint8_t buf[3];

    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }

    res = a_sfa40_read(handle, SFA40_ADDRESS, SFA40_COMMAND_READ_SELF_TEST_DATA, buf, 3, 0);       /* read self test data  command */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("sfa40: read self test data failed.\n");                               /* read self test data failed */

        return 1;                                                                                  /* return error */
    }
    if (a_sfa40_generate_crc(&buf[0], 2) != buf[2])                                                /* check crc */
    {
        handle->debug_print("sfa40: crc check error.\n");                                          /* crc check error */

        return 4;                                                                                  /* return error */
    }
    
    *result = (uint16_t)((uint16_t)(buf[0]) << 8) | buf[1];                                        /* set the result */
    
    return 0;                                                                                      /* success return 0 */
}

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
uint8_t sfa40_perform_soft_reset(sfa40_handle_t *handle)
{
    uint8_t res;
    uint8_t cmd;

    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }

    cmd = SFA40_COMMAND_PERFORM_SOFT_RESET;                                /* set perform soft reset */
    res = handle->iic_write_cmd(0x00, &cmd, 1);                            /* perform soft reset command */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("sfa40: perform soft reset failed.\n");        /* perform soft reset failed */

        return 1;                                                          /* return error */
    }
    handle->delay_ms(26);                                                  /* delay 26ms */

    return 0;                                                              /* success return 0 */
}

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
uint8_t sfa40_read(sfa40_handle_t *handle, sfa40_data_t *data)
{
    uint8_t res;
    uint8_t i;
    uint8_t buf[12];

    if ((handle == NULL) || (data == NULL))                                                                  /* check handle */
    {
        return 2;                                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                                 /* check handle initialization */
    {
        return 3;                                                                                            /* return error */
    }
    
    res = a_sfa40_read(handle, SFA40_ADDRESS, SFA40_COMMAND_READ_MEASUREMENT, (uint8_t *)buf, 12, 0);        /*read measurement command */
    if (res != 0)                                                                                            /* check result */
    {
        handle->debug_print("sfa40: read measurement failed.\n");                                            /* read measurement failed */

        return 1;                                                                                            /* return error */
    }
    
    for (i = 0; i < 4; i++)                                                                                  /* check crc */
    {
        if (buf[i * 3 + 2] != a_sfa40_generate_crc((uint8_t *)&buf[i * 3], 2))                               /* check crc */
        {
            handle->debug_print("sfa40: crc is error.\n");                                                   /* crc is error */

            return 4;                                                                                        /* return error */
        }
    }
    
    data->formaldehyde_raw = (uint16_t)(((uint16_t)(buf[0]) << 8) | ((uint16_t)(buf[1]) << 0));              /* copy formaldehyde */
    data->humidity_raw = (uint16_t)(((uint16_t)(buf[3]) << 8) | ((uint16_t)(buf[4]) << 0));                  /* copy humidity */
    data->temperature_raw = (uint16_t)(((uint16_t)(buf[6]) << 8) | ((uint16_t)(buf[7]) << 0));               /* copy temperature*/
    data->status = buf[9];                                                                                   /* set sensor status */
    if ((data->status & 0x01) != 0)                                                                          /* check status */
    {
        handle->debug_print("sfa40: data is not ready.\n");                                                  /* data is not ready */

        return 5;                                                                                            /* return error */
    }
    
    data->formaldehyde = (float)(data->formaldehyde_raw) / 10.0f;                                            /* convert formaldehyde */
    data->humidity = (float)(data->humidity_raw) / 65535.0f * 125.0f - 6.0f;                                 /* convert humidity */
    if (data->humidity < 0.0f)                                                                               /* check range */
    {
        data->humidity = 0.0f;                                                                               /* set 0.0f */
    }
    if (data->humidity > 100.0f)                                                                             /* check range */
    {
        data->humidity = 100.0f;                                                                             /* set 100.0f */
    }
    data->temperature = (float)(data->temperature_raw) / 65535.0f * 175.0f - 45.0f;                          /* convert temperature*/

    return 0;                                                                                                /* success return 0 */
}

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
uint8_t sfa40_init(sfa40_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->iic_init == NULL)                                      /* check iic_init */
    {
        handle->debug_print("sfa40: iic_init is null.\n");             /* iic_init is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_deinit == NULL)                                    /* check iic_deinit */
    {
        handle->debug_print("sfa40: iic_deinit is null.\n");           /* iic_deinit is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                 /* check iic_write_cmd */
    {
        handle->debug_print("sfa40: iic_write_cmd is null.\n");        /* iic_write_cmd is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                  /* check iic_read_cmd */
    {
        handle->debug_print("sfa40: iic_read_cmd is null.\n");         /* iic_read_cmd is null */

        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("sfa40: delay_ms is null.\n");             /* delay_ms is null */

        return 3;                                                      /* return error */
    }
    
    if (handle->iic_init() != 0)                                       /* iic init */
    {
        handle->debug_print("sfa40: iic init failed.\n");              /* iic init failed */

        return 3;                                                      /* return error */
    }
    handle->inited = 1;                                                /* flag finish initialization */

    return 0;                                                          /* success return 0 */
}

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
uint8_t sfa40_deinit(sfa40_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = handle->iic_deinit();                                    /* iic deinit */
    if (res != 0)                                                  /* check result */
    {
        handle->debug_print("sfa40: iic deinit failed.\n");        /* iic deinit */

        return 1;                                                  /* return error */
    }

    handle->inited = 0;                                            /* flag close initialization */

    return 0;                                                      /* success return 0 */
}

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
uint8_t sfa40_set_reg(sfa40_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }

    if (a_sfa40_write(handle, SFA40_ADDRESS, reg, buf, len, 0) != 0)        /* write the data */
    {
        handle->debug_print("sfa40: write failed.\n");                      /* write failed */

        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t sfa40_get_reg(sfa40_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    if (a_sfa40_read(handle, SFA40_ADDRESS, reg, buf, len, 0) != 0)        /* read the data */
    {
        handle->debug_print("sfa40: read failed.\n");                      /* read failed */

        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief      get chip information
 * @param[out] *info pointer to an sfa40 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sfa40_info(sfa40_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(sfa40_info_t));                          /* initialize sfa40 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 16);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set maximum temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set minimal temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
