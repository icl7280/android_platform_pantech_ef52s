/*
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
 
 /****************************************************************************************************
	Filename
	liba2dp_log.h

	Description
	dynamic logging for liba2dp

	Copyright (c) 2012 by  Pantech All Rights Reserved.

 ****************************************************************************************************/
/****************************************************************************************************
	History

	when                who                         what,where,why
	--------------  ------------               -------------------------------------------------
	2012-11-27      Lee.Hyunwoo                Create.
 ****************************************************************************************************/
 
 
#ifdef ANDROID
#include <android/log.h>
#include <cutils/properties.h>
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LIBA2DP_LOG_PROP "debug.liba2dp.log.enable"
#else
#define LOGE(...) ((void) 0)
#endif

#define GET_PROP(property_name) \
	char property_value[PROPERTY_VALUE_MAX]; \
	int len = property_get(property_name, property_value, "none"); \
	property_value[len]='\0';
	
#define DBG(fmt, arg...) do { \
	GET_PROP(LIBA2DP_LOG_PROP) \
	if ((!strncmp(property_value, "all", 3)) || (!strncmp(property_value, "debug", 5))) {\
		LOGE("%s:%s()" fmt, __FILE__, __func__, ##arg); \
	} \
} while (0)

#define VDBG(fmt, arg...) do { \
	GET_PROP(LIBA2DP_LOG_PROP) \
	if ((!strncmp(property_value, "all", 3)) || (!strncmp(property_value, "verbose", 7))) {\
		LOGE("%s:%s()" fmt, __FILE__, __func__, ##arg); \
	} \
} while (0)

#define ALOGV(fmt, arg...) do { \
	GET_PROP(LIBA2DP_LOG_PROP) \
	if ((!strncmp(property_value, "all", 3)) \
		|| (!strncmp(property_value, "debug", 5)) \
		|| (!strncmp(property_value, "verbose", 7))) {\
		LOGE("%s:%s()" fmt, __FILE__, __func__, ##arg); \
	} \
} while (0)

#define CONDITION(cond)     (__builtin_expect((cond)!=0, 0))
#define ALOGV_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? LOGE( __VA_ARGS__) \
    : (void)0 )
#define ALOGE_IF ALOGV_IF
