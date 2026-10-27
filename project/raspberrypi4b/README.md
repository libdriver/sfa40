### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```
#### 2.2 Configuration

Enable serial port.

Disable serial console.

#### 2.3 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.4 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(sfa40 REQUIRED)
```

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
./sfa40 -i

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
./sfa40 -p

sfa40: IIC interface SCL connected to GPIO3(BCM).
sfa40: IIC interface SDA connected to GPIO2(BCM).
```

```shell
./sfa40 -t reg

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
./sfa40 -t read --times=3

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
sfa40: humidity is 28.03%.
sfa40: temperature is 32.01C.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 28.02%.
sfa40: temperature is 32.03C.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 28.00%.
sfa40: temperature is 32.02C.
sfa40: finish read test.
```

```shell
./sfa40 -e read --times=3

sfa40: wait 65s.
sfa40: 1/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 27.02%.
sfa40: temperature is 31.05C.
sfa40: 2/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 27.19%.
sfa40: temperature is 31.05C.
sfa40: 3/3.
sfa40: formaldehyde is 2.50ppb.
sfa40: humidity is 27.36%.
sfa40: temperature is 31.04C.
```

```shell
./sfa40 -e sn

sfa40: serial number is 0xEE 0xD2 0x6D 0x9E 0x14 0xE0.
```

```shell
./sfa40 -h

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

