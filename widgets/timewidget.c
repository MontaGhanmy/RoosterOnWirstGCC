#include "timewidget.h"
#include "stm32f4xx_rtc.h"

char timeHex[] = {
		0x00,0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40,
		0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50,
		0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60
};
char *days [8] = {
		"Holder","MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"
};
void RTC_Configuration(int hours, int minutes)
{
  RTC_InitTypeDef RTC_InitStructure;
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;

  uint32_t uwSynchPrediv, uwAsynchPrediv;

  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

    #if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
    /* The RTC Clock may varies due to LSI frequency dispersion. */
      /* Enable the LSI OSC */
      RCC_LSICmd(ENABLE);

      /* Wait till LSI is ready */
      while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
      {
      }

      /* Select the LSI as RTC Clock Source */
      RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
      /* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
      uwSynchPrediv = 0xFF; //  17 KHz min, 32 KHz typ, 47 KHz max, ie pretty hideous
      uwAsynchPrediv = 0x7F;

    #elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
      /* Enable the LSE OSC */
      RCC_LSEConfig(RCC_LSE_ON);

      /* Wait till LSE is ready */
      while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
      {
      }

      /* Select the LSE as RTC Clock Source */
      RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
     /* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
      uwSynchPrediv = 0xFF;
      uwAsynchPrediv = 0x7F;

    #else
      #error Please select the RTC Clock source inside the main.c file
    #endif /* RTC_CLOCK_SOURCE_LSI */

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    /* Write to the first RTC Backup Data Register */
    RTC_WriteBackupRegister(RTC_BKP_DR0, FIRST_DATA);

// 8 AM 27-July-2014 using HEX because setting with BCD digits, 24 HR format

    /* Set the Time */
    RTC_TimeStructure.RTC_Hours   = timeHex[hours];
    RTC_TimeStructure.RTC_Minutes = timeHex[minutes];
    RTC_TimeStructure.RTC_Seconds = 0x00;

    /* Set the Date */
    RTC_DateStructure.RTC_Month = RTC_Month_July;
    RTC_DateStructure.RTC_Date = 0x27;
    RTC_DateStructure.RTC_Year = 0x14;
    RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Sunday;

    /* Calendar Configuration */
    RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv =  uwSynchPrediv;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);

    /* Set Current Time and Date */
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
    RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
}

void TimeWidget() {
	RTC_TimeTypeDef RTC_TS;
	RTC_DateTypeDef RTC_DS;
	int index;

	while(1) {

		// Getting seconds
		RTC_GetTime(RTC_Format_BIN, &RTC_TS);
		char ss[15];
		if (RTC_TS.RTC_Seconds < 10) {
			sprintf(ss, "0%d",  RTC_TS.RTC_Seconds);
		}
		else {
			sprintf(ss, "%d",  RTC_TS.RTC_Seconds);
		}
		// Getting Minutes
		RTC_GetTime(RTC_Format_BIN, &RTC_TS);
		char mm[15];
		if (RTC_TS.RTC_Minutes < 10) {
			sprintf(mm, "0%d",  RTC_TS.RTC_Minutes);
		}
		else {
			sprintf(mm, "%d",  RTC_TS.RTC_Minutes);
		}
		//Getting Hours
		RTC_GetTime(RTC_Format_BIN, &RTC_TS);
		char hh[15];
		if (RTC_TS.RTC_Hours < 10) {
			sprintf(hh, "0%d",  RTC_TS.RTC_Hours);
		}
		else {
			sprintf(hh, "%d",  RTC_TS.RTC_Hours);
		}

		PStr(mm,70,20,1,0xFFFF,0x0000);
		PStr(":",55,20,1,0xFFFF,0x0000);
		PStr(hh,25,20,1,0xFFFF,0x0000);
		PStr(ss,20,45,3,0xFFFF,0x0000);

		RTC_GetDate(RTC_Format_BIN, &RTC_DS);

		PStr(days[RTC_DS.RTC_WeekDay],30,100,1,0x0000,0xFFFF);
		for (index = 0; index < 1500000; index++);

	}
}
