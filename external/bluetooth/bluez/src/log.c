/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2004-2010  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

#include <glib.h>

#include "log.h"

//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ++++
#if 0
//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ----
void info(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

	vsyslog(LOG_INFO, format, ap);

	va_end(ap);
}

void error(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

	vsyslog(LOG_ERR, format, ap);

	va_end(ap);
}
//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ++++
#endif
//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ----

void btd_debug(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

	vsyslog(LOG_DEBUG, format, ap);

	va_end(ap);
}

extern struct btd_debug_desc __start___debug[];
extern struct btd_debug_desc __stop___debug[];

static gchar **enabled = NULL;

static gboolean is_enabled(struct btd_debug_desc *desc)
{
	int i;

	if (enabled == NULL)
		return 0;

	for (i = 0; enabled[i] != NULL; i++)
		if (desc->file != NULL && g_pattern_match_simple(enabled[i],
							desc->file) == TRUE)
			return 1;

	return 0;
}

void __btd_toggle_debug(void)
{
	struct btd_debug_desc *desc;
	
	//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ++++
	char property_value[PROPERTY_VALUE_MAX];
	int len = property_get(BLUEZ_LOG_PROP, property_value, "");
	property_value[len]='\0';
	LOGE("__btd_toggle_debug() - property_get()  len : %d  property_value : %s", len, property_value);

	if(!strcmp(property_value, "true")){	
		len = property_set(BLUEZ_LOG_PROP, "false");
		LOGE("BLUEZ_LOG_PROP is set to false");
	} else {
		len = property_set(BLUEZ_LOG_PROP, "true");
		LOGE("BLUEZ_LOG_PROP is set to true");
	}
	//P12116_BT_SYSTEM BlueZ_dynamic_logging(including audio folder) ----

	for (desc = __start___debug; desc < __stop___debug; desc++)
		desc->flags |= BTD_DEBUG_FLAG_PRINT;
}

void __btd_log_init(const char *debug, int detach)
{
	int option = LOG_NDELAY | LOG_PID;
	struct btd_debug_desc *desc;

	if (debug != NULL)
		enabled = g_strsplit_set(debug, ":, ", 0);

	for (desc = __start___debug; desc < __stop___debug; desc++)
		if (is_enabled(desc))
			desc->flags |= BTD_DEBUG_FLAG_PRINT;

	if (!detach)
		option |= LOG_PERROR;

	openlog("bluetoothd", option, LOG_DAEMON);

	syslog(LOG_INFO, "Bluetooth deamon %s", VERSION);
}

void __btd_log_cleanup(void)
{
	closelog();

	g_strfreev(enabled);
}
