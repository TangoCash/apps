#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifndef bool
#define bool unsigned char
#define false 0
#define true  1
#endif

#define VFDDISPLAYCHARS         0xc0425a00
#define VFDTESTONE              0xc0425a01
#define VFDTESTTWO              0xc0425a02
#define VFDBRIGHTNESS           0xc0425a03
#define VFDPWRLED               0xc0425a04 /* added by zeroone, also used in nuvoton.h; set PowerLed Brightness on Fortis*/
#define VFDDISPLAYWRITEONOFF    0xc0425a05
#define VFDTESTSIX              0xc0425a06
#define VFDTESTSEVEN            0xc0425a07
#define VFDTESTEIGHT            0xc0425a08
#define VFDTESTNINE             0xc0425a09
#define VFDICONDISPLAYONOFF     0xc0425a0a
#define VFDTESTELEVEN           0xc0425a0b
#define VFDTESTTWELVE           0xc0425a0c
#define VFDTESTTHIRTEEN         0xc0425a0d
#define VFDTESTFOURTEEN         0xc0425a0e
#define VFDTESTFIFTEEN          0xc0425a0f

#define VFDTEST                 0xc0425af0
#define VFDGETBLUEKEY           0xc0425af1 /* spark specific */
#define VFDSETBLUEKEY           0xc0425af2 /* spark specific */
#define VFDGETSTBYKEY           0xc0425af3 /* spark specific */
#define VFDSETSTBYKEY           0xc0425af4 /* spark specific */
#define VFDPOWEROFF             0xc0425af5 /* spark specific */
#define VFDSETPOWERONTIME       0xc0425af6 /* spark specific */
#define VFDGETSTARTUPSTATE      0xc0425af8 /* spark specific */
#define VFDLEDBRIGHTNESS        0xc0425af8 /* ufs912 */
#define VFDGETWAKEUPMODE        0xc0425af9 /* Fortis, does the same as spark VFDGETSTARTUPSTATE */
#define VFDGETTIME              0xc0425afa
#define VFDSETTIME              0xc0425afb
#define VFDSTANDBY              0xc0425afc
#define VFDREBOOT               0xc0425afd /* ufs912, fortis */
#define VFDSETTIME2             0xc0425afd /* spark specific */
#define VFDSETLED               0xc0425afe
#define VFDSETMODE              0xc0425aff /* ufs912, 922, Fortis ->unset compat mode */
#define VFDDISPLAYCLR           0xc0425b00
#define VFDGETLOOPSTATE         0xc0425b01 /* spark specific */
#define VFDSETLOOPSTATE         0xc0425b02 /* spark specific */
#define VFDSETTIMEFORMAT        0xc0425b04 /* Fortis specific */

struct vfd_ioctl_data
{
	unsigned char start;
	unsigned char data[64];
	unsigned char length;
};

typedef enum {NONE, TIMER, POWERON} eWakeupReason;

typedef enum {Unknown, Ufs910_1W, Ufs910_14W, Ufs922, Ufc960, Tf7700, Hl101, Vip2, Fortis, Hs5101, Ufs912, Spark, Cuberevo, Adb_Box, CNBox} eBoxType;

typedef struct Context_s
{
	/* Model_t */
	void *m; /* instance data */
	int fd; /* filedescriptor of fd */

} Context_t;

typedef struct Model_s
{
	char *Name;
	eBoxType Type;
	int (*Init)(Context_t *context);
	int (*Clear)(Context_t *context);
	int (*Usage)(Context_t *context, char *prg_name, char *cmd_name);
	int (*SetTime)(Context_t *context, time_t *theGMTTime);
	int (*SetSTime)(Context_t *context, time_t *theGMTTime);
	int (*GetTime)(Context_t *context, time_t *theGMTTime);
	int (*SetWTime)(Context_t *context, time_t *theGMTTime);
	int (*GetWTime)(Context_t *context, time_t *theGMTTime);
	int (*SetTimer)(Context_t *context, time_t *theGMTTime);
	int (*GetTimer)(Context_t *context, time_t *theGMTTime);
	int (*Shutdown)(Context_t *context, time_t *shutdownTimeGMT);
	int (*Reboot)(Context_t *context, time_t *rebootTimeGMT);
	int (*Sleep)(Context_t *context, time_t *wakeUpGMT);
	int (*SetText)(Context_t *context, char *theText);
	int (*SetLed)(Context_t *context, int which, int on);
	int (*SetIcon)(Context_t *context, int which, int on);
	int (*SetBrightness)(Context_t *context, int brightness);
	int (*GetWakeupReason)(Context_t *context, int *reason);
	int (*SetLight)(Context_t *context, int on);
	int (*Exit)(Context_t *context);
	int (*SetLedBrightness)(Context_t *context, int brightness);
	int (*GetVersion)(Context_t *context, int *version);
	int (*SetRF)(Context_t *context, int on);
	int (*SetFan)(Context_t *context, int on);
	int (*GetWakeupTime)(Context_t *context, time_t *theGMTTime);
	int (*SetDisplayTime)(Context_t *context, int on);
	int (*SetTimeMode)(Context_t *context, int twentyFour);
	int (*ModelSpecific)(Context_t *context, int len, int *testdata);     /* added by audioniek */
	void *private;

} Model_t;

extern Model_t Ufs910_1W_model;
extern Model_t Ufs910_14W_model;
extern Model_t UFS912_model;
extern Model_t UFS922_model;
extern Model_t UFC960_model;
extern Model_t Fortis_model;
extern Model_t HL101_model;
extern Model_t VIP2_model;
extern Model_t Hs5101_model;
extern Model_t Spark_model;
extern Model_t Adb_Box_model;
extern Model_t Cuberevo_model;
extern Model_t CNBOX_model;

double modJulianDate(struct tm *theTime);
time_t read_timers_utc(time_t curTime);
time_t read_fake_timer_utc(time_t curTime);
int searchModel(Context_t *context, eBoxType type);
int checkConfig(int *display, int *display_custom, char **timeFormat, int *wakeup, int verbose);

int getWakeupReasonPseudo(int *reason);
int syncWasTimerWakeup(eWakeupReason reason);

int disp; //controls screen output
int Vdisplay;
int Vdisplay_custom;
char *VtimeFormat;
int Vwakeup;

#endif