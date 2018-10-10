# <center>自带过零功率控制驱动V1.0使用说明 
<br>
## 1、功能说明
>　　该驱动用于含过零光耦的可控硅控制(如MOC3063M)输出功率,可按一个半波精度控制。
## 2、文件说明
* ####`PowerControl.c/PowerControl.h`
    功率控制实现文件，用于实现功率百分比转换、功率均衡输出等功能。

* ####`PowerControlHardware.c/PowerControlHardware.h`
    功率硬件输出控制。

## 3、移植说明
* 根据输出修改`PowerControlHardware.c`中的输出函数（可自己重新按注册格式写）。
* 在`main.cpp`中定义功率驱动（根据不用硬件个数分别定义），初始化将对应硬件输出函数注册到驱动中。

## 4、API接口说明
###`f_PowerCtrlOut`
>**功能描述：**用于功率控制输出<br>
>**输入参数：**pPowerCtrl 功率控制驱动结构体指针<br>
>**输出参数：**无<br>
>**调用：**100us中断调用<br>

<br>

###`f_PowerCtrlCalc`
>**功能描述：**功率计算<br>
>**输入参数：**pPowerCtrl 功率控制驱动结构体指针；percent 输出功率百分比<br>
>**输出参数：**无<br>
>**调用：**需要时调用<br>

<br>

###`f_PowerCtrlInit`
>**功能描述：**功率控制初始化<br>
>**输入参数：**pPowerCtrl 功率控制驱动结构体指针；pFunc 硬件输出函数指针<br>
>**输出参数：**无<br>
>**调用：**初始化调用一次<br>

## 5、依赖文件
* 公用类型定义`DataType.h`
* 公用小函数文件`SubFunction.c`