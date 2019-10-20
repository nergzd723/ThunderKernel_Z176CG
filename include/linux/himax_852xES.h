#ifndef HIMAX852xES_H
#define HIMAX852xES_H

#include <asm/segment.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>

#include <linux/himax_852xES.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/async.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/input/mt.h>
#include <linux/firmware.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/wakelock.h>
#include <linux/mutex.h>

#if defined(CONFIG_FB)
#include <linux/notifier.h>
#include <linux/fb.h>
#elif defined(CONFIG_HAS_EARLYSUSPEND)
#include <linux/earlysuspend.h>
#endif

#ifdef CONFIG_OF
#include <linux/of_gpio.h>
#endif
#if defined(CONFIG_TOUCHSCREEN_PROXIMITY)
#include <linux/touch_psensor.h>
#endif

#define HIMAX852xes_NAME "Himax852xes"
#define HIMAX852xes_FINGER_SUPPORT_NUM 10
#define HIMAX_I2C_ADDR				0x48
#define INPUT_DEV_NAME	"himax-touchscreen"
#define FLASH_DUMP_FILE "/data/user/Flash_Dump.bin"
#define DIAG_COORDINATE_FILE "/sdcard/Coordinate_Dump.csv"
#define CONFIG_TOUCHSCREEN_HIMAX_DEBUG

#if defined(CONFIG_TOUCHSCREEN_HIMAX_DEBUG)
#define D(x...) printk("[HXTP] " x)
#define I(x...) printk("[HXTP] " x)
#define W(x...) printk("[HXTP][WARNING] " x)
#define E(x...) printk("[HXTP][ERROR] " x)
#define DIF(x...) \
	if (debug_flag) \
	printk(KERN_DEBUG "[HXTP][DEBUG] " x) \
} while(0)

#define HX_TP_SYS_DIAG
#define HX_TP_SYS_REGISTER
#define HX_TP_SYS_DEBUG
#define HX_TP_SYS_FLASH_DUMP
#define HX_TP_SYS_SELF_TEST
#define HX_TP_SYS_RESET 
#define HX_TP_SYS_HITOUCH
#else
#define D(x...) 
#define I(x...) 
#define W(x...) 
#define E(x...) 
#define DIF(x...)
#endif
//===========Himax Option function=============
#define HX_RST_PIN_FUNC
//#define HX_LOADIN_CONFIG
#define HX_AUTO_UPDATE_FW 		//if enable HX_AUTO_UPDATE_FW, need to disable HX_LOADIN_CONFIG
//#define HX_AUTO_UPDATE_CONFIG		//if enable HX_AUTO_UPDATE_CONFIG, need to disable HX_LOADIN_CONFIG
#define HX_SMART_WAKEUP
//#define HX_DOT_VIEW
//#define HX_PALM_REPORT
#define HX_ESD_WORKAROUND
#define HX_USB_DETECT

#define HX_85XX_A_SERIES_PWON		1
#define HX_85XX_B_SERIES_PWON		2
#define HX_85XX_C_SERIES_PWON		3
#define HX_85XX_D_SERIES_PWON		4
#define HX_85XX_E_SERIES_PWON		5
#define HX_85XX_ES_SERIES_PWON		6

#define HX_TP_BIN_CHECKSUM_SW		1
#define HX_TP_BIN_CHECKSUM_HW		2
#define HX_TP_BIN_CHECKSUM_CRC		3
	
#define HX_KEY_MAX_COUNT             4			
#define DEFAULT_RETRY_CNT            3

#define HX_VKEY_0   KEY_BACK
#define HX_VKEY_1   KEY_HOME
#define HX_VKEY_2   KEY_RESERVED
#define HX_VKEY_3   KEY_RESERVED
#define HX_KEY_ARRAY    {HX_VKEY_0, HX_VKEY_1, HX_VKEY_2, HX_VKEY_3}

#define SHIFTBITS 5
#define FLASH_SIZE 32768

#define GESTURE_DOUBLE_CLICK	(1 << 6)
#define GESTURE_V		(1 << 5)
#define GESTURE_W		(1 << 4)
#define GESTURE_E		(1 << 3)
#define GESTURE_C		(1 << 2)
#define GESTURE_S		(1 << 1)
#define GESTURE_Z		(1 << 0)


struct himax_virtual_key {
	int index;
	int keycode;
	int x_range_min;
	int x_range_max;
	int y_range_min;
	int y_range_max;
};

struct himax_config {
	uint8_t  default_cfg;
	uint8_t  sensor_id;
	uint8_t  fw_ver;
	uint16_t length;
	uint32_t tw_x_min;
	uint32_t tw_x_max;
	uint32_t tw_y_min;
	uint32_t tw_y_max;
	uint32_t pl_x_min;
	uint32_t pl_x_max;
	uint32_t pl_y_min;
	uint32_t pl_y_max;
	uint8_t c1[11];
	uint8_t c2[11];
	uint8_t c3[11];
	uint8_t c4[11];
	uint8_t c5[11];
	uint8_t c6[11];
	uint8_t c7[11];
	uint8_t c8[11];
	uint8_t c9[11];
	uint8_t c10[11];
	uint8_t c11[11];
	uint8_t c12[11];
	uint8_t c13[11];
	uint8_t c14[11];
	uint8_t c15[11];
	uint8_t c16[11];
	uint8_t c17[11];
	uint8_t c18[17];
	uint8_t c19[15];
	uint8_t c20[5];
	uint8_t c21[11];
	uint8_t c22[4];
	uint8_t c23[3];
	uint8_t c24[3];
	uint8_t c25[4];
	uint8_t c26[2];
	uint8_t c27[2];
	uint8_t c28[2];
	uint8_t c29[2];
	uint8_t c30[2];
	uint8_t c31[2];
	uint8_t c32[2];
	uint8_t c33[2];
	uint8_t c34[2];
	uint8_t c35[3];
	uint8_t c36[5];
	uint8_t c37[5];
	uint8_t c38[9];
	uint8_t c39[14];
	uint8_t c40[159];
	uint8_t c41[99];
};

struct himax_i2c_platform_data {	
	int abs_x_min;
	int abs_x_max;
	int abs_x_fuzz;
	int abs_y_min;
	int abs_y_max;
	int abs_y_fuzz;
	int abs_pressure_min;
	int abs_pressure_max;
	int abs_pressure_fuzz;
	int abs_width_min;
	int abs_width_max;
	int screenWidth;
	int screenHeight;
	uint8_t fw_version;
	uint8_t tw_id;
	uint8_t powerOff3V3;
	uint8_t cable_config[2];
	uint8_t protocol_type;
	int gpio_irq;
	int gpio_reset;
	int gpio_3v3_en;
	int (*power)(int on);
	struct himax_virtual_key *virtual_key;
	struct kobject *vk_obj;
	struct kobj_attribute *vk2Use;
	
	void (*reset)(void);

	struct himax_config *hx_config;
	int hx_config_size;
#if defined(CONFIG_HMX_DB)	
	unsigned long irqflags;
	bool	i2c_pull_up;
	bool	digital_pwr_regulator;
	int reset_gpio;
	u32 reset_gpio_flags;
	int irq_gpio;
	u32 irq_gpio_flags;

	int (*init_hw) (bool);
	int (*power_on) (bool);
#endif	
};

struct himax_ts_data {
	bool suspended;
	atomic_t suspend_mode;
	uint8_t x_channel;
	uint8_t y_channel;
	uint8_t useScreenRes;
	uint8_t diag_command;
	uint8_t protocol_type;
	uint8_t first_pressed;
	uint8_t coord_data_size;
	uint8_t area_data_size;
	uint8_t raw_data_frame_size;
	uint8_t raw_data_nframes;
	uint8_t nFinger_support;
	uint8_t irq_enabled;
	uint8_t diag_self[50];
	
	uint16_t finger_pressed;
	uint16_t last_slot;
	uint16_t pre_finger_mask;

	uint32_t debug_log_level;
	uint32_t irq;
	uint32_t widthFactor;
	uint32_t heightFactor;
	uint32_t tw_x_min;
	uint32_t tw_x_max;
	uint32_t tw_y_min;
	uint32_t tw_y_max;
	uint32_t pl_x_min;
	uint32_t pl_x_max;
	uint32_t pl_y_min;
	uint32_t pl_y_max;
	
	int use_irq;
	int vendor_fw_ver;
	int vendor_config_ver;
	int vendor_sensor_id;
	int (*power)(int on);
	int pre_finger_data[10][2];
	int usb_status;

	struct device *dev;
	struct workqueue_struct *himax_wq;
	struct work_struct work;
	struct input_dev *input_dev;
	struct hrtimer timer;
	struct i2c_client *client;
	struct himax_i2c_platform_data *pdata;	
	struct himax_virtual_key *button;
	
#if defined(CONFIG_FB)
	struct notifier_block fb_notif;
	struct workqueue_struct *himax_att_wq;
	struct delayed_work work_att;
#elif defined(CONFIG_HAS_EARLYSUSPEND)
	struct early_suspend early_suspend;
#endif
	struct wake_lock ts_wake_lock;
	struct mutex ts_mutex;
#ifdef HX_TP_SYS_FLASH_DUMP
	struct workqueue_struct 			*flash_wq;
	struct work_struct 					flash_work;
#endif
#ifdef HX_RST_PIN_FUNC
	int rst_gpio;
#endif
#if defined(CONFIG_HMX_DB)
	struct regulator *vcc_ana; //For Dragon Board
	struct regulator *vcc_dig; //For Dragon Board
	struct regulator *vcc_i2c; //For Dragon Board
#endif
#ifdef HX_SMART_WAKEUP
	uint8_t SMWP_enable;
	struct wake_lock ts_SMWP_wake_lock;
	int gesture_all;
	int gesture_w;
	int gesture_s;
	int gesture_e;
	int gesture_c;
	int gesture_z;
	int gesture_v;
#endif
#ifdef HX_DOT_VIEW
	uint8_t cover_enable;
#endif
	struct workqueue_struct *himax_usb_wq;
	struct delayed_work usb_detect_work;
#ifdef HX_USB_DETECT
	uint8_t *cable_config;
#endif
};

static struct himax_ts_data *private_ts;

#define HX_CMD_NOP					 0x00	
#define HX_CMD_SETMICROOFF			 0x35	
#define HX_CMD_SETROMRDY			 0x36	
#define HX_CMD_TSSLPIN				 0x80	
#define HX_CMD_TSSLPOUT 			 0x81	
#define HX_CMD_TSSOFF				 0x82	
#define HX_CMD_TSSON				 0x83	
#define HX_CMD_ROE					 0x85	
#define HX_CMD_RAE					 0x86	
#define HX_CMD_RLE					 0x87	
#define HX_CMD_CLRES				 0x88	
#define HX_CMD_TSSWRESET			 0x9E	
#define HX_CMD_SETDEEPSTB			 0xD7	
#define HX_CMD_SET_CACHE_FUN		 0xDD	
#define HX_CMD_SETIDLE				 0xF2	
#define HX_CMD_SETIDLEDELAY 		 0xF3	
#define HX_CMD_SELFTEST_BUFFER		 0x8D	
#define HX_CMD_MANUALMODE			 0x42
#define HX_CMD_FLASH_ENABLE 		 0x43
#define HX_CMD_FLASH_SET_ADDRESS	 0x44
#define HX_CMD_FLASH_WRITE_REGISTER  0x45
#define HX_CMD_FLASH_SET_COMMAND	 0x47
#define HX_CMD_FLASH_WRITE_BUFFER	 0x48
#define HX_CMD_FLASH_PAGE_ERASE 	 0x4D
#define HX_CMD_FLASH_SECTOR_ERASE	 0x4E
#define HX_CMD_CB					 0xCB
#define HX_CMD_EA					 0xEA
#define HX_CMD_4A					 0x4A
#define HX_CMD_4F					 0x4F
#define HX_CMD_B9					 0xB9
#define HX_CMD_76					 0x76

enum input_protocol_type {
	PROTOCOL_TYPE_A	= 0x00,
	PROTOCOL_TYPE_B	= 0x01,
};

//1uA
static unsigned char E_IrefTable_1[16][2] = { {0x20,0x0F},{0x20,0x1F},{0x20,0x2F},{0x20,0x3F},
											{0x20,0x4F},{0x20,0x5F},{0x20,0x6F},{0x20,0x7F},
											{0x20,0x8F},{0x20,0x9F},{0x20,0xAF},{0x20,0xBF},
											{0x20,0xCF},{0x20,0xDF},{0x20,0xEF},{0x20,0xFF}};

//2uA
static unsigned char E_IrefTable_2[16][2] = { {0xA0,0x0E},{0xA0,0x1E},{0xA0,0x2E},{0xA0,0x3E},
											{0xA0,0x4E},{0xA0,0x5E},{0xA0,0x6E},{0xA0,0x7E},
											{0xA0,0x8E},{0xA0,0x9E},{0xA0,0xAE},{0xA0,0xBE},
											{0xA0,0xCE},{0xA0,0xDE},{0xA0,0xEE},{0xA0,0xFE}};													

//3uA
static unsigned char E_IrefTable_3[16][2] = { {0x20,0x0E},{0x20,0x1E},{0x20,0x2E},{0x20,0x3E},
											{0x20,0x4E},{0x20,0x5E},{0x20,0x6E},{0x20,0x7E},
											{0x20,0x8E},{0x20,0x9E},{0x20,0xAE},{0x20,0xBE},
											{0x20,0xCE},{0x20,0xDE},{0x20,0xEE},{0x20,0xFE}};			
		
//4uA
static unsigned char E_IrefTable_4[16][2] = { {0xA0,0x0D},{0xA0,0x1D},{0xA0,0x2D},{0xA0,0x3D},
											{0xA0,0x4D},{0xA0,0x5D},{0xA0,0x6D},{0xA0,0x7D},
											{0xA0,0x8D},{0xA0,0x9D},{0xA0,0xAD},{0xA0,0xBD},
											{0xA0,0xCD},{0xA0,0xDD},{0xA0,0xED},{0xA0,0xFD}};	 
																
//5uA
static unsigned char E_IrefTable_5[16][2] = { {0x20,0x0D},{0x20,0x1D},{0x20,0x2D},{0x20,0x3D},
											{0x20,0x4D},{0x20,0x5D},{0x20,0x6D},{0x20,0x7D},
											{0x20,0x8D},{0x20,0x9D},{0x20,0xAD},{0x20,0xBD},
											{0x20,0xCD},{0x20,0xDD},{0x20,0xED},{0x20,0xFD}};	 
																
//6uA
static unsigned char E_IrefTable_6[16][2] = { {0xA0,0x0C},{0xA0,0x1C},{0xA0,0x2C},{0xA0,0x3C},
											{0xA0,0x4C},{0xA0,0x5C},{0xA0,0x6C},{0xA0,0x7C},
											{0xA0,0x8C},{0xA0,0x9C},{0xA0,0xAC},{0xA0,0xBC},
											{0xA0,0xCC},{0xA0,0xDC},{0xA0,0xEC},{0xA0,0xFC}};	 
																
//7uA
static unsigned char E_IrefTable_7[16][2] = { {0x20,0x0C},{0x20,0x1C},{0x20,0x2C},{0x20,0x3C},
											{0x20,0x4C},{0x20,0x5C},{0x20,0x6C},{0x20,0x7C},
											{0x20,0x8C},{0x20,0x9C},{0x20,0xAC},{0x20,0xBC},
											{0x20,0xCC},{0x20,0xDC},{0x20,0xEC},{0x20,0xFC}}; 

#ifdef HX_TP_SYS_REGISTER
	static uint8_t register_command 			= 0;
	static uint8_t multi_register_command = 0;
	static uint8_t multi_register[8] 			= {0x00};
	static uint8_t multi_cfg_bank[8] 			= {0x00};
	static uint8_t multi_value[1024] 			= {0x00};
	static bool 	config_bank_reg 				= false;
#endif

#ifdef HX_ESD_WORKAROUND
	static u8 		ESD_RESET_ACTIVATE 	= 1;
	static u8 		ESD_COUNTER 		= 0;
	//static int 		ESD_COUNTER_SETTING = 3;
	static u8		ESD_R36_FAIL		= 0;
#endif											
	static u8		HW_RESET_ACTIVATE	= 1;
#ifdef HX_TP_SYS_DIAG
	static bool Is_2T3R = false;

	static uint8_t x_channel 		= 0;
	static uint8_t y_channel 		= 0;
	static uint8_t *diag_mutual = NULL;

	static uint8_t x_channel_2 = 0;
	static uint8_t y_channel_2 = 0;
	static uint8_t *diag_mutual_2 = NULL;

	static int diag_command = 0;
	static uint8_t diag_coor[128];// = {0xFF};

	static uint8_t diag_self[100] = {0};

	static uint8_t *getMutualBuffer(void);
	static uint8_t *getSelfBuffer(void);
	static uint8_t 	getDiagCommand(void);
	static uint8_t 	getXChannel(void);
	static uint8_t 	getYChannel(void);

	static uint8_t *getMutualBuffer_2(void);
	static uint8_t 	getXChannel_2(void);
	static uint8_t 	getYChannel_2(void);

	static void 	setMutualBuffer(void);
	static void 	setXChannel(uint8_t x);
	static void 	setYChannel(uint8_t y);

	static void 	setMutualBuffer_2(void);
	static void 	setXChannel_2(uint8_t x);
	static void 	setYChannel_2(uint8_t y);

	static uint8_t	coordinate_dump_enable = 0;
	struct file	*coordinate_fn;
#endif

#ifdef HX_TP_SYS_DEBUG
	static bool	fw_update_complete = false;
	static int handshaking_result = 0;
	static unsigned char debug_level_cmd = 0;
	static unsigned char upgrade_fw[32*1024];
#endif

#ifdef HX_TP_SYS_FLASH_DUMP
	static uint8_t *flash_buffer 				= NULL;
	static uint8_t flash_command 				= 0;
	static uint8_t flash_read_step 			= 0;
	static uint8_t flash_progress 			= 0;
	static uint8_t flash_dump_complete	= 0;
	static uint8_t flash_dump_fail 			= 0;
	static uint8_t sys_operation				= 0;
	static uint8_t flash_dump_sector	 	= 0;
	static uint8_t flash_dump_page 			= 0;
	static bool    flash_dump_going			= false;

	static uint8_t getFlashCommand(void);
	static uint8_t getFlashDumpComplete(void);
	static uint8_t getFlashDumpFail(void);
	static uint8_t getFlashDumpProgress(void);
	static uint8_t getFlashReadStep(void);
	static uint8_t getSysOperation(void);
	static uint8_t getFlashDumpSector(void);
	static uint8_t getFlashDumpPage(void);
	static bool	   getFlashDumpGoing(void);

	static void setFlashBuffer(void);
	static void setFlashCommand(uint8_t command);
	static void setFlashReadStep(uint8_t step);
	static void setFlashDumpComplete(uint8_t complete);
	static void setFlashDumpFail(uint8_t fail);
	static void setFlashDumpProgress(uint8_t progress);
	static void setSysOperation(uint8_t operation);
	static void setFlashDumpSector(uint8_t sector);
	static void setFlashDumpPage(uint8_t page);
	static void setFlashDumpGoing(bool going);
#endif

#ifdef HX_RST_PIN_FUNC
	void himax_HW_reset(uint8_t loadconfig,uint8_t int_off);
#endif

#ifdef HX_TP_SYS_SELF_TEST
	static ssize_t himax_chip_self_test_function(struct device *dev, struct device_attribute *attr, char *buf);
	static int himax_chip_self_test(void);
#endif

#ifdef HX_TP_SYS_HITOUCH
	static int	hitouch_command			= 0;
	static bool hitouch_is_connect	= false;
#endif

#ifdef HX_SMART_WAKEUP
	enum gesture_event_type {
	EV_GESTURE_U = 0x01,
	EV_GESTURE_V,
	EV_GESTURE_W,
	EV_GESTURE_E,
	EV_GESTURE_C,
	EV_GESTURE_S,
	EV_GESTURE_Z,
};
	static bool FAKE_POWER_KEY_SEND = false;
#endif

#ifdef HX_DOT_VIEW
	#include <linux/hall_sensor.h>
#endif

#if defined(CONFIG_HMX_DB)
/* Analog voltage @2.7 V */
#define HX_VTG_MIN_UV			2700000
#define HX_VTG_MAX_UV			3300000
#define HX_ACTIVE_LOAD_UA		15000
#define HX_LPM_LOAD_UA 			10
/* Digital voltage @1.8 V */
#define HX_VTG_DIG_MIN_UV		1800000
#define HX_VTG_DIG_MAX_UV		1800000
#define HX_ACTIVE_LOAD_DIG_UA	10000
#define HX_LPM_LOAD_DIG_UA 		10

#define HX_I2C_VTG_MIN_UV		1800000
#define HX_I2C_VTG_MAX_UV		1800000
#define HX_I2C_LOAD_UA 			10000
#define HX_I2C_LPM_LOAD_UA 		10
#endif

#ifdef HX_AUTO_UPDATE_CONFIG
static int		CFB_START_ADDR					= 0;
static int		CFB_LENGTH						= 0;
static int		CFB_INFO_LENGTH 				= 0;
#endif

#endif