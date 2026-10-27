[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SFA40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/sfa40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SFA40是一种甲醛（HCHO）传感器，由于对乙醇或二氧化氮等常见室内气体的交叉敏感性极低，在现场具有出色的精度。SFA40专为空气净化器、空调和室内空气质量监测仪而开发，即使在其他挥发性有机化合物的背景下，也具有微型尺寸、低功耗和可靠输出的特点。该传感器适用于检测低于世界卫生组织、WELL Building Standard™和中国国家标准GB/T 18883-2022规定限值的低甲醛浓度。由于其先进的防干燥技术，这种电化学传感器具有超长的使用寿命。每个SFA40都经过工厂校准，可以通过手动或自动焊接轻松集成到最终设备中。这使得SFA40成为一种可靠、易于使用和高质量的甲醛传感解决方案，使紧凑型设备具有较长的电池寿命和最佳性能。

LibDriver SFA40是LibDriver推出的SFA40的全功能驱动，该驱动提供甲醛浓度读取、温度读取、湿度读取和SN读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver SFA40的源文件。

/interface目录包含了LibDriver SFA40与平台无关的IIC总线模板。

/test目录包含了LibDriver SFA40驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver SFA40编程范例。

/doc目录包含了LibDriver SFA40离线文档。

/datasheet目录包含了SFA40数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_sfa40_basic.h"

uint8_t res;
uint32_t i;

/* init */
res = sfa40_basic_init();
if (res != 0)
{
    return 1;
}

/* start */
res = sfa40_basic_start();
if (res != 0)
{
    (void)sfa40_basic_deinit();

    return 1;
}

/* wait 65s*/
sfa40_interface_debug_print("sfa40: wait 65s.\n");

/* delay 65s */
sfa40_interface_delay_ms(1000 * 65);

/* loop */
for (i = 0; i < 3; i++)
{
    sfa40_data_t data;

    /* read data */
    res = sfa40_basic_read(&data);
    if (res != 0)
    {
        (void)sfa40_basic_stop();
        (void)sfa40_basic_deinit();

        return 1;
    }

    /* print */
    sfa40_interface_debug_print("sfa40: %d/%d.\n", i + 1, 3);
    sfa40_interface_debug_print("sfa40: formaldehyde is %0.2fppb.\n", data.formaldehyde);
    sfa40_interface_debug_print("sfa40: humidity is %0.2f%%.\n", data.humidity);
    sfa40_interface_debug_print("sfa40: temperature is %0.2fC.\n", data.temperature);

    /* delay 2000 ms */
    sfa40_interface_delay_ms(2000);
}

/* deinit */
(void)sfa40_basic_stop();
(void)sfa40_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/sfa40/index.html](https://www.libdriver.com/docs/sfa40/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。