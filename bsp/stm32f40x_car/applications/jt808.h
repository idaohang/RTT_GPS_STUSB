#ifndef _H_JT808_H_
#define _H_JT808_H_

#include <stm32f4xx.h>

#define   MsgQ_Timeout            3




/*字节顺序的定义网络顺序*/
typedef struct
{
	uint32_t latitude; 		/*纬度 1/10000分 */
	uint32_t longitude; 	/*经度 1/10000分 */
	uint16_t altitude;		/*高程 m*/
	uint16_t speed;			/*速度 1/10KMH*/
	uint8_t direction;		/*方向 0-178 刻度为2度*/
	uint8_t datetime[6];	/*YY-MM-DD hh-mm-ss BCD编码*/
}T_GPSINFO;


//------- 文本信息 --------
typedef struct _TEXT_INFO
{
  uint8_t  TEXT_FLAG;          //  文本标志
  uint8_t  TEXT_SD_FLAG;       // 发送标志位  
  uint8_t  TEXT_Content[100];  // 文本内容
}TEXT_INFO;


//----- 信息 ----
typedef struct _MSG_TEXT
{
  uint8_t   TEXT_mOld;     //  最新的一条信息  写为1代表是最新的一条信息
  uint8_t   TEXT_TYPE;     //  信息类型   1-8  中第几条
  uint8_t   TEXT_LEN;      //  信息长度    
  uint8_t   TEXT_STR[150]; //  信息内容
}MSG_TEXT;

//-----  提问 ------
typedef struct _CENTER_ASK
{
  uint8_t  ASK_SdFlag; //  标志位           发给 TTS  1  ；   TTS 回来  2
  uint16_t ASK_floatID; // 提问流水号
  uint8_t  ASK_infolen;// 信息长度  
  uint8_t  ASK_answerID;    // 回复ID
  uint8_t  ASK_info[30];//  信息内容
  uint8_t  ASK_answer[30];  // 候选答案  
}CENTRE_ASK;

//------ 事件  -------
typedef struct _EVENT               //  name: event
{
  uint8_t Event_ID;   //  事件ID
  uint8_t Event_Len;  //  事件长度
  uint8_t Event_Effective; //  事件是否有效，   1 为要显示  0     
  uint8_t Event_Str[20];  //  事件内容
}EVENT; 


//----- 信息 ----
typedef struct _MSG_BROADCAST    // name: msg_broadcast
{
  uint8_t   INFO_TYPE;     //  信息类型
  uint16_t  INFO_LEN;      //  信息长度
  uint8_t   INFO_PlyCancel; // 点播/取消标志      0 取消  1  点播
  uint8_t   INFO_SDFlag;    //  发送标志位
  uint8_t   INFO_Effective; //  显示是否有效   1 显示有效    0  显示无效     
  uint8_t   INFO_STR[30];  //  信息内容
}MSG_BRODCAST;

//------ 电话本 -----
typedef struct _PHONE_BOOK            // name: phonebook
{
  uint8_t CALL_TYPE ;    // 呼入类型  1 呼入 2 呼出 3 呼入/呼出
  uint8_t NumLen;        // 号码长度   
  uint8_t UserLen;       // 联系人长度
  uint8_t Effective_Flag;// 有效标志位   无效 0 ，有效  1
  uint8_t NumberStr[20]; // 电话号码
  uint8_t UserStr[10];   // 联系人名称  GBK 编码
}PHONE_BOOK;


typedef struct _MULTIMEDIA
{
  u32  Media_ID;           //   多媒体数据ID
  u8   Media_Type;         //   0:   图像    1 : 音频    2:  视频 
  u8   Media_CodeType;     //   编码格式  0 : JPEG  1:TIF  2:MP3  3:WAV  4: WMV
  u8   Event_Code;         //   事件编码  0: 平台下发指令  1: 定时动作  2 : 抢劫报警触发 3: 碰撞侧翻报警触发 其他保留
  u8   Media_Channel;      //   通道ID
  //----------------------
  u8   SD_Eventstate;          // 发送事件信息上传状态    0 表示空闲   1  表示处于发送状态        
  u8   SD_media_Flag;     // 发送没提事件信息标志位
  u8   SD_Data_Flag;      // 发送数据标志位
  u8   SD_timer;          // 发送定时器
  u8   MaxSd_counter;   // 最大发送次数  
  u8   Media_transmittingFlag;  // 多媒体传输数据状态  1: 多媒体传输前发送1包定位信息    2 :多媒体数据传输中  0:  未进行多媒体数据传输
  u16  Media_totalPacketNum;    // 多媒体总包数 
  u16  Media_currentPacketNum;  // 多媒体当前报数 
  //----------------------
  u8   RSD_State;     //  重传状态   0 : 重传没有启用   1 :  重传开始    2  : 表示顺序传完但是还没收到中心的重传命令
  u8   RSD_Timer;     //  传状态下的计数器   
  u8   RSD_Reader;    //  重传计数器当前数值 
  u8   RSD_total;     //  重传选项数目  
  
   
  u8	Media_ReSdList[10]; //  多媒体重传消息列表 
}MULTIMEDIA;   




void gps_rx(uint8_t *pinfo,uint16_t length);
void gprs_rx(uint8_t *pinfo,uint16_t length);


//--------------每分钟的平均速度 
typedef  struct AvrgMintSpeed
{
  uint8_t datetime[6]; //current
  uint8_t datetime_Bak[6];//Bak
  uint8_t avgrspd[60];
  uint8_t saveFlag;  
}Avrg_MintSpeed;


extern uint32_t jt808_alarm;
extern uint32_t jt808_status;


extern TEXT_INFO TextInfo;
//-------文本信息-------
extern MSG_TEXT       TEXT_Obj;
extern MSG_TEXT       TEXT_Obj_8[8],TEXT_Obj_8bak[8];

//------ 提问  --------
extern CENTRE_ASK     ASK_Centre;  // 中心提问

//------- 事件 ----
extern EVENT          EventObj;    // 事件   
extern EVENT          EventObj_8[8]; // 事件  

//------  信息点播  ---
extern MSG_BRODCAST   MSG_BroadCast_Obj;    // 信息点播         
extern MSG_BRODCAST   MSG_Obj_8[8];  // 信息点播    

//------  电话本  -----
extern PHONE_BOOK    PhoneBook,Rx_PhoneBOOK;   //  电话本
extern PHONE_BOOK    PhoneBook_8[8];


extern MULTIMEDIA   MediaObj;      // 多媒体信息 

extern uint8_t  CarLoadState_Flag;//选中车辆状态的标志   1:空车   2:半空   3:重车
extern uint8_t		Warn_Status[4];

extern u16      ISP_total_packnum;  // ISP  总包数
extern u16      ISP_current_packnum;// ISP  当前包数

extern u8          APN_String[30];

extern u8  Camera_Number;
extern u8	Duomeiti_sdFlag; 

extern Avrg_MintSpeed  Avrgspd_Mint; 
extern u8          avgspd_Mint_Wr;       // 填写每分钟平均速度记录下标




/*for new use*/

typedef struct
{
	uint32_t ver;	/*版本信息四个字节yy_mm_dd_build,比较大小*/
/*网络有关*/
	char	apn[32];
	char	user[32];
	char	psw[32];



	




}JT808_PARAM;


extern JT808_PARAM jt808_param;















#endif


