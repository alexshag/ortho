
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
#include "correction.h"
#include "strutils.h"

/*
 * Input:
 * a point for which correction is made
 * true track from the point
 * beacon on which correction is made
 *
 * Output:
 * Correction data (A, D, S, Z)
 */
static void get_correction_data(double true_track, const vordata* vd,
                                const waypoint* wp, correction_data* cd)
{
	double vor_azimuth;
	double vor_distance; 
	double Z, S;

	double pphi = deg2rad(wp->lat);
	double vphi = deg2rad(vd->lat);
	double dlam = deg2rad(vd->lon) - deg2rad(wp->lon) + 0.0001;


	double ctg_az = cos(pphi)*tan(vphi)/sin(dlam) - sin(pphi)/tan(dlam);
	double vor_azimuth_rad = atan2(1, ctg_az);
	double sin_D = cos(vphi) * sin(dlam) / sin(vor_azimuth_rad);
	double alpha_rad = deg2rad(true_track) - vor_azimuth_rad;
	double sin_Z = sin_D * sin(alpha_rad);
	double sin_S = tan(asin(sin_Z)) / tan(alpha_rad);

	/* The same values in kilometres */
	Z = 1.8532 * 60 * rad2deg(asin(sin_Z));
	S = 1.8532 * 60 * rad2deg(asin(sin_S));
	vor_distance = 1.8532 * 60 * rad2deg(asin(sin_D));
	vor_azimuth = rad2deg(vor_azimuth_rad);

	printf("Azimuth: %.2f\nDistance: %.2f\nZ: %.2f\nS: %.2f\n",
		vor_azimuth,
		vor_distance,
		Z, S);

	cd->beacon_azimuth = vor_azimuth;
	cd->beacon_distance = vor_distance;
	cd->S = S;
	cd->Z = Z;

}

static void print_correction_data(const correction_data* cd)
{
	printf("Azimuth: %.2f\nDistance: %.2f\nZ: %.2f\nS: %.2f\n",
		cd->beacon_azimuth,
		cd->beacon_distance,
		cd->S, cd->Z);
}


/* export */
int correction(const char* string)
{
	int result = 0;
	int rec = 0;
	char point[6] = {0};
	char beacon[16] = {0};
	/* The first symbol in input string is correction label, skip it */
	char* beg = (char*)++string;

	char* end = strchr(beg, ',');
	if (end != NULL)
	{
		rec++;
		strncpy(point, beg, sizeof(point));
		point[5] = '\0';
		beg = end + 1;
		while (*beg == ' ') beg++;
	}

	if (rec == 1)
	{
		strncpy(beacon, beg, sizeof(beacon));
		beacon[15] = '\0';
		strcpy(beacon, trimwhitespace(beacon));
	}
	else
	{
		return 1;
	}


	printf("point: |%s|    beacon: |%s|\n", point, beacon);
	return result;
}

/* export */
void test_correction()
{
	correction_data cd;
	waypoint wp = { "SLAVA", 52.6080556, 30.0480556, 10.2 };
	vordata vd = { "ROSTOV", 74.3663889, 30.0480556, 9.89, "112.300" };

	get_correction_data(34.23, &vd, &wp, &cd);

	print_correction_data(&cd);
}


#if 0  /* NOT USED NOW */
static int parse_rsbn_data(const char* string, vordata* vd)
{
	int result = 0;
	char* current;
	char* begin;
	char type[3];

	current = (char*)string;
	begin = current;

	strncpy(type, begin, sizeof(type));
	type[2] = '\0';

	if (strcmp(type, "12") == 0)
	{
		char slat[10];
		char slon[12];
		char name[32];

		begin = current + 4;
		strncpy(slat, begin, sizeof(slat));
		slat[9] = '\0';

		begin = current + 17;
		strncpy(slon, begin, sizeof(slon));
		slon[11] = '\0';

		begin = current + 58;
		strncpy(name, begin, sizeof(name));
		name[31] = '\0';
		strcpy(name, trimwhitespace(name));

		printf("%s %s %s\n", slat, slon, name);

		strncpy(vd->name, name, sizeof(vd->name));
		vd->lat = atof(slat);
		vd->lon = atof(slon);
	}


	return result;
}

static int read_rsbn_file(const char* file_name, vordata* vd)
{
	FILE* fin = NULL;
	char str[MAX_LINE_LENGTH];
	int not_parsed = 0;

	fin = fopen(file_name, "r");
	if (!fin)
	{
		printf("Cannot open RSBN data file.\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(str, MAX_LINE_LENGTH, fin) && (not_parsed != 1))
	{
		not_parsed = parse_rsbn_data(str, vd);
	}

	fclose(fin);
	return 0;
}
#endif

