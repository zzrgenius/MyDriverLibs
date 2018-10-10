# <center>按键驱动V1.0使用说明 
<br>
## 1、功能说明
>　　按键驱动模块包括按键的获取(硬件模糊层)、按键信息产生(驱动层)、按键信息处理(应用层)。可用于获取独立按键、芯片按键等，对单键、组合键的处理。支持自定义按键名称、按键状态（不同长按状态），方便不同项目使用。同时支持独立按键检测、按键卡住剔除检测功能。
## 2、文件说明
* ####`KeyDriverConfig.c/KeyDriverConfig.h`
    按键驱动配置文件，用于用户自定义按键名称、按键状态(不同长按时间)。对应不同需求更改，改动较小。

* ####`KeyDriverHardware.c`
    按键硬件处理转换文件，用于获取不用的硬件按键。讲硬件按键转换成能用于按键标准助理的数据，将硬件模糊，方便移植。对于不同项目需要修改。

* ####`KeyDriver.c/KeyDriver.h`
    按键处理驱动核心文件，用于将硬件获取的按键处理后输出标准按键输出结果。为固定文件，正常不需要更改。

* ####`KeyDeal.c/KeyDeal.h`
    按键应用处理文件文件，根据每种时间按键功能进行相应功能处理。

## 3、移植说明
* 根据按键数量、名称等修改`KeyDriverConfig.h`中的单键和组合键，同时可以自定义不同的按键状态。如果自定义按键状态，将新增的按键状态及对应的时间填入到`KeyDriverConfig.c`的`Tab_KeySelfState`中。**注意可以自定义5种状态，也可扩展枚举`KEY_STATE`，用于定义更多**。
>     #define KEY_SIGLE_POWER 0x00000001//电源键
>       
>     #define KEY_PRESS_1S KEY_STATE_1 //自定义长按状态1S
>     #define KEY_PRESS_1S_TM 100//*10ms

* 根据不同硬件按键信息，修改按键`KeyDriverHardware.c`的获取转换函数`f_GetKeys`。
* 根据功能需求，在`KeyDeal.c`编写不同的按键和状态的处理函数(详见Demo中`f_KeyDeal`,实际根据功能可拆分函数，最终在`f_KeyDeal`处理)。
* 移植完成后，包含`KeyDeal.h`，初始化调用一次`f_KeyDealInit`，在10ms时基中调用`f_KeyDriverDeal`。
* 在`f_KeyDeal`使用状态去执行用户代码时，建议同一个按键既带长按又带短按功能，短按功能用`KEY_RELEASE`状态去判断。同时如果如果按键已处理(调用了`f_SetKeyDealDone()`),则该按键会等待释放，不会产生其他有用的状态。故关于长按定时累加，可用户自行定时处理，且不要调用`f_SetKeyDealDone()`,该状态会一直存在，直到释放。
* **注意**：`KeyDriverConfig.h`中的`KEY_DONE_OVER`【默认关闭】宏用于控制是否在用户处理了按键状态后继续产生新的其他按键状态（如`KEY_PRESSED`处理完后，会继续产生但是`KEY_PRESS_1S`,`KEY_RELEASE`除外）


## 4、API接口说明
###`f_KeyDealInit`
>**功能描述：**按键初始化函数，初始化调用一次<br>
>**输入参数：**无<br>
>**输出参数：**无<br>
>**调用：**初始化调用一次<br>

<br>

###`f_KeyDriverDeal`
>**功能描述：**按键初始化函数，初始化调用一次<br>
>**输入参数：**pKeyDriver 按键驱动结构体指针<br>
>**输出参数：**无<br>
>**调用：**定时10ms调用一次<br>

<br>

###`f_GetKeys`
>**功能描述：**按键硬件数据获取，用于将硬件信息转换为驱动可处理信息<br>
>**输入参数：**pKeyDriver 按键驱动结构体指针<br>
>**输出参数：**无<br>
>**调用：**硬件驱动已注册，需要完善转换即可<br>

## 5、依赖文件
* 公用小函数文件`SubFunction.c`
* 公用类型定义`DataType.h`
* 公用系统时间定义`TimeFlag.h`