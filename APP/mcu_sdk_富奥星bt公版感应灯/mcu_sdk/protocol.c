/****************************************Copyright (c)*************************
**                               版权所有 (C), 2015-2017, 涂鸦科技
**
**                                 http://www.tuya.com
**
**--------------文件信息-------------------------------------------------------
**文   件   名: protocol.c
**描        述: 下发/上报数据处理函数
**使 用 说 明 :

                  *******非常重要，一定要看哦！！！********

** 1、用户在此文件中实现数据下发/上报功能
** 2、DP的ID/TYPE及数据处理函数都需要用户按照实际定义实现
** 3、当开始某些宏定义后需要用户实现代码的函数内部有#err提示,完成函数后请删除该#err
**
**--------------当前版本修订---------------------------------------------------
** 版  本: v1.0
** 日　期: 2017年5月3日
** 描　述: 1:创建涂鸦bluetooth对接MCU_SDK
**
**-----------------------------------------------------------------------------
******************************************************************************/
#include "include.h"

#include "bluetooth.h"
  
  
extern TYPE_BUFFER_S FlashBuffer;

/******************************************************************************
                                移植须知:
1:MCU必须在while中直接调用mcu_api.c内的bt_uart_service()函数
2:程序正常初始化完成后,建议不进行关串口中断,如必须关中断,关中断时间必须短,关中断会引起串口数据包丢失
3:请勿在中断/定时器中断内调用上报函数
******************************************************************************/

         
/******************************************************************************
                              第一步:初始化
1:在需要使用到bt相关文件的文件中include "bt.h"
2:在MCU初始化中调用mcu_api.c文件中的bt_protocol_init()函数
3:将MCU串口单字节发送函数填入protocol.c文件中uart_transmit_output函数内,并删除#error
4:在MCU串口接收函数中调用mcu_api.c文件内的uart_receive_input函数,并将接收到的字节作为参数传入
5:单片机进入while循环后调用mcu_api.c文件内的bt_uart_service()函数
******************************************************************************/

/******************************************************************************
                        1:dp数据点序列类型对照表
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**         
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_SWITCH_LED, DP_TYPE_BOOL},
  {DPID_WORK_MODE, DP_TYPE_ENUM},
  {DPID_BRIGHT_VALUE, DP_TYPE_VALUE},
  {DPID_SCENE_DATA, DP_TYPE_STRING},
  {DPID_DEVICE_MODE, DP_TYPE_ENUM},
  {DPID_PIR_STATE, DP_TYPE_ENUM},
  {DPID_CDS, DP_TYPE_ENUM},
  {DPID_PIR_SENSITIVITY, DP_TYPE_ENUM},
  {DPID_PIR_DELAY, DP_TYPE_VALUE},
  {DPID_SWITCH_PIR, DP_TYPE_BOOL},
  {DPID_PIR_RESUME_COUNTDOWN, DP_TYPE_VALUE},
  {DPID_STANDBY_TIME, DP_TYPE_VALUE},
  {DPID_STANDBY_BRIGHT, DP_TYPE_VALUE},
};




/******************************************************************************
                           2:串口单字节发送函数
请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函数
******************************************************************************/

/*****************************************************************************
函数名称 : uart_transmit_output
功能描述 : 发数据处理
输入参数 : value:串口收到字节数据
返回参数 : 无
使用说明 : 请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函数
*****************************************************************************/
void uart_transmit_output(unsigned char value)
{
 #error "请将MCU串口发送函数填入该函数,并删除该行"
/*
  //示例:
  extern void Uart_PutChar(unsigned char value);
  Uart_PutChar(value);	                                //串口发送函数
*/  
}
/******************************************************************************
                           第二步:实现具体用户函数
1:APP下发数据处理
2:数据上报处理
******************************************************************************/

/******************************************************************************
                            1:所有数据上报处理
当前函数处理全部数据上报(包括可下发/可上报和只上报)
  需要用户按照实际情况实现:
  1:需要实现可下发/可上报数据点上报
  2:需要实现只上报数据点上报
此函数为MCU内部必须调用
用户也可调用此函数实现全部数据上报
******************************************************************************/

//自动化生成数据上报函数

/*****************************************************************************
函数名称 : all_data_update
功能描述 : 系统所有dp点信息上传,实现APP和muc数据同步
输入参数 : 无
返回参数 : 无
使用说明 : 此函数SDK内部需调用;
           MCU必须实现该函数内数据上报功能;包括只上报和可上报可下发型数据
*****************************************************************************/
void all_data_update(void)
{
  #error "请在此处理可下发可上报数据及只上报数据示例,处理完成后删除该行"
  //此代码为平台自动生成，请按照实际数据修改每个可下发可上报函数和只上报函数
    mcu_dp_bool_update(DPID_SWITCH_LED,当前开关); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_WORK_MODE,当前模式); //枚举型数据上报;
    mcu_dp_value_update(DPID_BRIGHT_VALUE,当前亮度值); //VALUE型数据上报;
    mcu_dp_string_update(DPID_SCENE_DATA,当前场景指针,当前场景数据长度); //STRING型数据上报;
    mcu_dp_enum_update(DPID_DEVICE_MODE,当前设备模式); //枚举型数据上报;
    mcu_dp_enum_update(DPID_PIR_STATE,当前感应状态); //枚举型数据上报;
    mcu_dp_enum_update(DPID_CDS,当前光敏参数); //枚举型数据上报;
    mcu_dp_enum_update(DPID_PIR_SENSITIVITY,当前灵敏度); //枚举型数据上报;
    mcu_dp_value_update(DPID_PIR_DELAY,当前感应延时); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_SWITCH_PIR,当前感应开关); //BOOL型数据上报;
    mcu_dp_value_update(DPID_PIR_RESUME_COUNTDOWN,当前感应恢复倒计时); //VALUE型数据上报;
    mcu_dp_value_update(DPID_STANDBY_TIME,当前伴亮延时); //VALUE型数据上报;
    mcu_dp_value_update(DPID_STANDBY_BRIGHT,当前伴亮亮度值); //VALUE型数据上报;



}


/******************************************************************************
                                WARNING!!!    
                            2:所有数据上报处理
自动化代码模板函数,具体请用户自行实现数据处理
******************************************************************************/

/*****************************************************************************
函数名称 : dp_download_switch_led_handle
功能描述 : 针对DPID_SWITCH_LED的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_led_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char switch_led;
    
    switch_led = mcu_get_dp_download_bool(value,length);
    if(switch_led == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_SWITCH_LED,switch_led);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_work_mode_handle
功能描述 : 针对DPID_WORK_MODE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_work_mode_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char work_mode;
    
    work_mode = mcu_get_dp_download_enum(value,length);
    switch(work_mode) {
        case 0:
        break;
        
        case 1:
        break;
        
        default:
    
        break;
    }
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_enum_update(DPID_WORK_MODE, work_mode);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_bright_value_handle
功能描述 : 针对DPID_BRIGHT_VALUE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_bright_value_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long bright_value;
    
    bright_value = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_BRIGHT_VALUE,bright_value);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_scene_data_handle
功能描述 : 针对DPID_SCENE_DATA的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_scene_data_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为STRING
    unsigned char ret;
    /*
    //STRING类型数据处理
    unsigned char string_data[8];
    
    string_data[0] = value[0];
    string_data[1] = value[1];
    string_data[2] = value[2];
    string_data[3] = value[3];
    string_data[4] = value[4];
    string_data[5] = value[5];
    string_data[6] = value[6];
    string_data[7] = value[7];
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_string_update(DPID_SCENE_DATA,value, length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_device_mode_handle
功能描述 : 针对DPID_DEVICE_MODE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_device_mode_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char device_mode;
    
    device_mode = mcu_get_dp_download_enum(value,length);
    switch(device_mode) {
        case 0:
        break;
        
        case 1:
        break;
        
        default:
    
        break;
    }
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_enum_update(DPID_DEVICE_MODE, device_mode);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_cds_handle
功能描述 : 针对DPID_CDS的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_cds_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char cds;
    
    cds = mcu_get_dp_download_enum(value,length);
    switch(cds) {
        case 0:
        break;
        
        case 1:
        break;
        
        case 2:
        break;
        
        case 3:
        break;
        
        case 4:
        break;
        
        case 5:
        break;
        
        default:
    
        break;
    }
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_enum_update(DPID_CDS, cds);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_pir_sensitivity_handle
功能描述 : 针对DPID_PIR_SENSITIVITY的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_pir_sensitivity_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char pir_sensitivity;
    
    pir_sensitivity = mcu_get_dp_download_enum(value,length);
    switch(pir_sensitivity) {
        case 0:
        break;
        
        case 1:
        break;
        
        case 2:
        break;
        
        default:
    
        break;
    }
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_enum_update(DPID_PIR_SENSITIVITY, pir_sensitivity);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_pir_delay_handle
功能描述 : 针对DPID_PIR_DELAY的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_pir_delay_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long pir_delay;
    
    pir_delay = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_PIR_DELAY,pir_delay);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_switch_pir_handle
功能描述 : 针对DPID_SWITCH_PIR的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_pir_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char switch_pir;
    
    switch_pir = mcu_get_dp_download_bool(value,length);
    if(switch_pir == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_SWITCH_PIR,switch_pir);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_standby_time_handle
功能描述 : 针对DPID_STANDBY_TIME的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_standby_time_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long standby_time;
    
    standby_time = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_STANDBY_TIME,standby_time);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_standby_bright_handle
功能描述 : 针对DPID_STANDBY_BRIGHT的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_standby_bright_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long standby_bright;
    
    standby_bright = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_STANDBY_BRIGHT,standby_bright);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}


/******************************************************************************
                                WARNING!!!                     
此代码为SDK内部调用,请按照实际dp数据实现函数内部数据
******************************************************************************/
#ifdef SUPPORT_MCU_FIRM_UPDATE
/*****************************************************************************
函数名称 : mcu_firm_update_handle
功能描述 : MCU进入固件升级模式
输入参数 : value:固件缓冲区
           position:当前数据包在于固件位置
           length:当前固件包长度(固件包长度为0时,表示固件包发送完成)
返回参数 : 无
使用说明 : MCU需要自行实现该功能
*****************************************************************************/
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
  #error "请自行完成MCU固件升级代码,完成后请删除该行"
  unsigned long addr;
 
  if(length == 0)
  {
#ifdef ENABLE_BOOT
    //固件数据发送完成
    FlashBuffer.magic_code = FIREWARE_UPDATE_FLAG;
    
    if(Earse_Flash(PARA_ADDR) == ERROR)
      return ERROR;
    
    //写入升级标志
    if(Write_Flash(PARA_ADDR,(unsigned char *)&FlashBuffer,sizeof(FlashBuffer)) == ERROR)
      return ERROR;
    
    Reset();
#endif
  }
  else
  {
    //固件数据处理
    addr = FIREWARE_ADDR_H;
     
    if(position % 1024 == 0)
    {
      if(Earse_Flash(addr + position) == ERROR)
        return ERROR;
    }
    
    if(Write_Flash(addr + position,(unsigned char *)value,length) == ERROR)
      return ERROR;
  }

  return SUCCESS;
}
#endif
/******************************************************************************
                                WARNING!!!                     
以下函数用户请勿修改!!
******************************************************************************/

/*****************************************************************************
函数名称 : dp_download_handle
功能描述 : dp下发处理函数
输入参数 : dpid:DP序号
           value:dp数据缓冲区地址
           length:dp数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERRO
使用说明 : 该函数用户不能修改
*****************************************************************************/
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length)
{
  /*********************************
  当前函数处理可下发/可上报数据调用                    
  具体函数内需要实现下发数据处理
  完成用需要将处理结果反馈至APP端,否则APP会认为下发失败
  ***********************************/
  unsigned char ret;
  switch(dpid)
  {
        case DPID_SWITCH_LED:
            //开关处理函数
            ret = dp_download_switch_led_handle(value,length);
        break;
        case DPID_WORK_MODE:
            //模式处理函数
            ret = dp_download_work_mode_handle(value,length);
        break;
        case DPID_BRIGHT_VALUE:
            //亮度值处理函数
            ret = dp_download_bright_value_handle(value,length);
        break;
        case DPID_SCENE_DATA:
            //场景处理函数
            ret = dp_download_scene_data_handle(value,length);
        break;
        case DPID_DEVICE_MODE:
            //设备模式处理函数
            ret = dp_download_device_mode_handle(value,length);
        break;
        case DPID_CDS:
            //光敏参数处理函数
            ret = dp_download_cds_handle(value,length);
        break;
        case DPID_PIR_SENSITIVITY:
            //灵敏度处理函数
            ret = dp_download_pir_sensitivity_handle(value,length);
        break;
        case DPID_PIR_DELAY:
            //感应延时处理函数
            ret = dp_download_pir_delay_handle(value,length);
        break;
        case DPID_SWITCH_PIR:
            //感应开关处理函数
            ret = dp_download_switch_pir_handle(value,length);
        break;
        case DPID_STANDBY_TIME:
            //伴亮延时处理函数
            ret = dp_download_standby_time_handle(value,length);
        break;
        case DPID_STANDBY_BRIGHT:
            //伴亮亮度值处理函数
            ret = dp_download_standby_bright_handle(value,length);
        break;


  default:
    break;
  }
  return ret;
}
/*****************************************************************************
函数名称 : get_download_cmd_total
功能描述 : 获取所有dp命令总和
输入参数 : 无
返回参数 : 下发命令总和
使用说明 : 该函数用户不能修改
*****************************************************************************/
unsigned char get_download_cmd_total(void)
{
  return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}
