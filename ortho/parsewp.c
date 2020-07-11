
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "orthodromy.h"
#include "wplist.h"
#include "magmodel.h"
#include "coord_conv.h" /* coord_conv*/


/*
Parse a string in which must be four records divided by comma:
name, latitude, longitude, magnetic variation.
If there are only three record magnetic variation is omitted, 
the function gets this value from WMM
-------------------------------------------------
Call in open_route_file
Use: coord_conv

Returns:
   0   success
   -1 failure, print message "cannot open the file"
*/

int parse_waypoints(const char* string, wplist** ppList)
{
	int corrupted_file = 0;

	waypoint wp = {{'\0'}, 0, 0, 0};
	char scode[6] = { 0 };
	char slat[10] = { 0 };
	char slon[12] = { 0 };
	char smag[6] = { 0 };

	int rec = 0;
	char* beg = (char*)string;
	char tmp[MAX_LINE_LENGTH] = { 0 };

	while (rec != 4)
	{
		char* end = strchr(beg, ',');
		if (end != NULL)
		{
			rec++;
			strcpy(tmp, beg);
			tmp[end - beg] = '\0';
			beg = end + 1;

			while (isspace(*beg)) beg++;
			switch (rec)
			{
			case 1: /* name */
				strncpy(scode, tmp, sizeof(scode));
				break;
			case 2:	/* latitude */
				strncpy(slat, tmp, sizeof(slat));
				break;
			case 3: /* longitude */
				strncpy(slon, tmp, sizeof(slon));
				break;
			}
		}
		else if (rec == 3)
		{
			/* Comma is not found */
			/* magnetic variation is here */
			strncpy(tmp, beg, sizeof(tmp));
			tmp[5] = '\0';
			strncpy(smag, tmp, sizeof(smag));
			rec++; /* set 4 i.e. exit */
		}
		else if (rec == 2)
		{
			/*At this point 'beg' is longitude */
			strncpy(slon, beg, sizeof(slon));
			rec++;
			break;
		}
		else
		{
			printf("The file is corrupted.\n");
			corrupted_file = 1;
			break;
		} /* Comma is not found */
	} /* while (rec !=4) */

	if (corrupted_file)
		return -1;

	/* Out data in the list  */
	scode[5] = '\0';
	strncpy(wp.code, scode, sizeof(wp.code));
	wp.lat = coord_conv(slat);
	wp.lon = coord_conv(slon);
	/* If res == 4 then the file is completed and mv record is present */
	/* If rec == 3 then the mv record is absent and we get it from WMM */
	if (rec > 3)
		wp.magvar = atof(smag);
	else if (rec == 3)
		get_magnetic_variation(wp.lat, wp.lon, &wp.magvar);

	if ((wp.lat == -9999.0) || (wp.lon == -9999.0))
		return -1;

	/* Call list fucntion */
	wplist_addpoint(ppList, &wp);

	return 0;
}
