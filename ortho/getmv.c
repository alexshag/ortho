
/*
 * ==========
 * Orthodromy
 * ==========
 * version: 1.0
 * date: June 27, 2020
 *
 */
 
#include "stdafx.h"
#include "magmodel.h"


void geomag(int* maxdeg);
void geomg1(double alt, double glat, double glon, double time, double* dec, double* dip, double* ti, double* gv);

/* export */
void get_magnetic_variation(double lat, double lon, double* mv)
{
	double alt, time, dec, dip, ti, gv;
	static int maxdeg;
	FILE *wmmtemp;
	char d_str[81], modl[20];
	double epochlowlim;

	alt = 0;		/* Set as need */
	time = 2024.0;	/* Set as need */

	maxdeg = 12;

	wmmtemp = fopen("WMM.COF","r");
	if (wmmtemp == NULL) 
	{
		fprintf(stderr, "Error opening model file WMM.COF\n");
		exit(1);
	}

	fgets(d_str, 80, wmmtemp);
	if (sscanf(d_str,"%lf%8s",&epochlowlim, modl) < 2) 
	{
		fprintf(stderr, "Invalid header in model file WMM.COF\n");
		exit(1);
	}

	fclose(wmmtemp);

	geomag(&maxdeg);

	/*
    dec  declination
	dip inclination
    ti total intensity
	gv magnetic grid variation

    compute magnetic grid variation (gv) if the current
    geodetic position is in the arctic or antarctic
    (i.e. lat > +55 degrees or lat < -55 degrees)
    otherwise, set magnetic grid variation to -999.0
	*/
	geomg1(alt, lat, lon, time, &dec, &dip, &ti, &gv);

	*mv = dec;
}

