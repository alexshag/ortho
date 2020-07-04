
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
#include "coord_conv.h"
#include "wplist.h"


int parse_pmdg(const char* string, wplist** pList)
{
    waypoint wp = {{'\0'},0,0,0};
    int rec = 0;

	/* After the parsing is completed this value is the string length 
	without null terminator*/
    int pos = 0;

    char swpt[16] = {0};
    char slat[16]  = {0};
    char slon[16]  = {0};

    char tmp[MAX_LINE_LENGTH] = {0};
    char* current = (char*)string;
    char* beg = current;

    while(*current != '\0')
    {
        if (*current == 0x20)
        {
            strcpy(tmp, beg);
			rec++;
			if (pos > (MAX_LINE_LENGTH-1)) pos = MAX_LINE_LENGTH-1;
            tmp[pos] = '\0';

            switch (rec)
            {
            case 3:
                strncpy(swpt, tmp, sizeof(swpt));
                break;
            case 4:
                strncpy(slat, tmp, sizeof(slat));
                break;
            }

            while(*current == 0x20) current++;
			/* Reinitialization !!! */
            beg = current;
            pos = 0;

        }
        current++; 
        pos++; 
    }

	/* Space is not found */
    if (rec == 4)
    {
		/* This is the fourths record */
        rec++; 
		pos--; /* Step back because was step forward */
        strcpy(tmp, beg);
        if (pos > (MAX_LINE_LENGTH - 1)) pos = MAX_LINE_LENGTH - 1;
        tmp[pos] = '\0';
        strncpy(slon, tmp, sizeof(slon));
    }
    else
    {
		/* Id the fourths record is absent the file is corrupted */
        printf("Corrupted input file.\n");
		return -1;
    }

    strcpy(wp.code, swpt);
    wp.lat = coord_conv(slat);
    wp.lon = coord_conv(slon);
    wp.magvar = 0.0;

    /* TODO: get magnetic variation from WMM */
    /* get_magnetic_variation(wp.lat, wp.lon, &wp.magvar);*/

	wplist_addpoint(pList, &wp);

    return 0;

}
