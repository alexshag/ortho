
/*
 * ==========
 * Orthodromy
 * ==========
 * version: 1.0
 * date: June 27, 2020
 *
 */
 
#include "stdafx.h"
#include "orthodromy.h"
#include "wplist.h"
#include "coord_conv.h"
#include "magmodel.h"

int parse_magvar(const char* string, wplist** ppList)
{
	int corrupted_file = 0;

	waypoint wp = {{'\0'}, 0, 0, 0};
	char scode[6] = {'\0'};
	char slat[10] = {0};
	char slon[12] = {0};

	int rec = 0;
	char* beg = (char*)string;
	char tmp[MAX_LINE_LENGTH] = {0};

	while (rec != 3)
	{
		char* end = strchr(beg, ',');
		if (end != NULL)
		{
			rec++;
			strcpy(tmp, beg);
			tmp[end-beg] = '\0';
			beg = end+1;
			while(*beg == ' ') beg++;
			switch (rec)
			{
			case 1: 
				strncpy(scode, tmp, sizeof(scode));
				break;
			case 2:	
				strncpy(slat, tmp, sizeof(slat));
				break;
			}
		}
		else
		{
			if (rec == 2)
			{
				strncpy(tmp, beg, sizeof(tmp));
				tmp[9] = '\0';
				strncpy(slon, tmp, sizeof(slon));
				rec++;
			}
			else
			{
				printf("The file is corrupted.\n");
				corrupted_file = 1;
				break;
			}
		}
	}/* while (rec !=3) */

	if (corrupted_file)
		return -1;

	scode[5] = '\0';
	strncpy(wp.code, scode, sizeof(wp.code));
	wp.lat = coord_conv(slat);
	wp.lon = coord_conv(slon);

	if ((wp.lat == -9999.0) || (wp.lon == -9999.0))
		return -1;

	/* TODO: Return error code to the caller */
	get_magnetic_variation(wp.lat, wp.lon, &wp.magvar);

	wplist_addpoint(ppList, &wp);

	return 0;
}

