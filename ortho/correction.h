#pragma once

typedef struct vordata
{
	char name[32];
	double lat;
	double lon;
	double magvar;
	char freq[8];
}vordata;

/* A, D, S, Z */
typedef struct corrention_data
{
	double beacon_azimuth; 
	double beacon_distance;
	double Z;
	double S;
}correction_data;

int correction(const char* string);
