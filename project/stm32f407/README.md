### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SFA40

#### 3.1 Command Instruction

1. Show sfa40 chip and driver information.

   ```shell
   sfa40 (-i | --information)
   ```

2. Show sfa40 help.

   ```shell
   sfa40 (-h | --help)
   ```

3. Show sfa40 pin connections of the current board.

   ```shell
   sfa40 (-p | --port)
   ```

4. Run sfa40 register test.

   ```shell
   sfa40 (-t reg | --test=reg)
   ```
   
5. Run sfa40 read test, num means the test times.

   ```shell
   sfa40 (-t read | --test=read) [--times=<num>]
   ```

6. Run sfa40 basic read function, num means the read times.

   ```shell
   sfa40 (-e read | --example=read) [--times=<num>]
   ```

7. Run sfa40 basic get sn function.

   ```shell
   sfa40 (-e sn | --example=sn)
   ```

#### 3.2 Command Example

```shell
sfa40 -i

sfa40: chip is Sensirion SFA40.
sfa40: manufacturer is Sensirion.
sfa40: interface is IIC.
sfa40: driver version is 1.0.
sfa40: min supply voltage is 1.6V.
sfa40: max supply voltage is 3.6V.
sfa40: max current is 2.00mA.
sfa40: max temperature is 50.0C.
sfa40: min temperature is 0.0C.
```

```shell
sfa40 -p

sfa40: IIC interface SCL connected to GPIOB PIN8.
sfa40: IIC interface SDA connected to GPIOB PIN9.
```

```shell
sfa40 -t reg

sfa40: chip is Sensirion SFA40.
sfa40: manufacturer is Sensirion.
sfa40: interface is IIC.
sfa40: driver version is 1.0.
sfa40: min supply voltage is 1.6V.
sfa40: max supply voltage is 3.6V.
sfa40: max current is 2.00mA.
sfa40: max temperature is 50.0C.
sfa40: min temperature is 0.0C.
sfa40: start register test.
sfa40: serial number is 0xEE 0xD2 0x6D 0x9E 0x14 0xE0.
sfa40: sfa40_start_self_test test.
sfa40: check self test ok.
sfa40: sfa40_get_self_test_data test.
sfa40: self test result is 0xFFFF.
sfa40: sfa40_perform_soft_reset test.
sfa40: check perform soft reset ok.
sfa40: finish register test.
```

```shell
sfa40 -t read --times=3

sfa40: chip is Sensirion SFA40.
sfa40: manufacturer is Sensirion.
sfa40: interface is IIC.
sfa40: driver version is 1.0.
sfa40: min supply voltage is 1.6V.
sfa40: max supply voltage is 3.6V.
sfa40: max current is 2.00mA.
sfa40: max temperature is 50.0C.
sfa40: min temperature is 0.0C.
sfa40: start read test.
sfa40: wait 65s.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.39%.
sfa40: temperature is 28.30C.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.39%.
sfa40: temperature is 28.30C.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.41%.
sfa40: temperature is 28.29C.
sfa40: finish read test.
```

```shell
sfa40 -e read --times=3

sfa40: wait 65s.
sfa40: 1/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.35%.
sfa40: temperature is 28.57C.
sfa40: 2/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.34%.
sfa40: temperature is 28.58C.
sfa40: 3/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 32.35%.
sfa40: temperature is 28.58C.
```

```shell
sfa40 -e sn

sfa40: serial number is 0xEE 0xD2 0x6D 0x9E 0x14 0xE0.
```

```shell
sfa40 -h

Usage:
  sfa40 (-i | --information)
  sfa40 (-h | --help)
  sfa40 (-p | --port)
  sfa40 (-t reg | --test=reg)
  sfa40 (-t read | --test=read) [--times=<num>]
  sfa40 (-e read | --example=read) [--times=<num>]
  sfa40 (-e sn | --example=sn)

Options:
  -e <read | sn>, --example=<read | sn>
                                          Run the driver example.
  -h, --help                              Show the help.
  -i, --information                       Show the chip information.
  -p, --port                              Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>    Run the driver test.
      --times=<num>                       Set the running times.([default: 3])
```

