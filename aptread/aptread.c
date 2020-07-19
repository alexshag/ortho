
/**/

#define _CRT_SECURE_NO_WARNINGS

#define _DEFAULT_SOURCE /* it's need for 'strcasecmp' */

#include <stdio.h>
#include <string.h> /* strcasecmp */
#include <stdlib.h>
#include <ctype.h>  /* isspace */


#define MAX_LINE_LENGTH 256

/*
 * Remove leading and trailing spaces from a string
 */
char* trimwhitespace(char* str)
{
	char* end;

	/* Trim leading space */
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)  /* All spaces? */
		return str;

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	/* Write new null terminator character */
	end[1] = '\0';

	return str;
}

void parse_string(const char* buffer, const char* search)
{
	char* current;
	char* begin;
	char name[26] = {0};
	char code[5] = {0};
	char rwy[4] = {0};
	char len[6];
	char num[4];
	char slat[10];
	char slon[12];
	char ils[7];
	char hdg[4];
	char salt[6];

	double lat;
	double lon;
	double alt;

	current = (char*)buffer;
	begin = current;
	strncpy(name, begin, 24);
	name[25] = '\0';
	strcpy(name, trimwhitespace(name));

	begin = current + 24;
	strncpy(code, begin, 4);
	code[4] = '\0';

	begin = current + 28;
	strncpy(rwy, begin, 2);
	rwy[3] = '\0';

	begin = current + 31;
	strncpy(len, begin, 5);
	len[5] = '\0';

	begin = current + 36;
	strncpy(num, begin, 4);
	num[3] = '\0';

	begin = current + 40;
	strncpy(slat, begin, 10);
	slat[9] = '\0';

	begin = current + 50;
	strncpy(slon, begin, 12);
	slon[11] = '\0';

	lat = atof(slat);
	lon = atof(slon);

	begin = current + 60;
	strncpy(ils, begin, 7);
	ils[6] = '\0';

	begin = current + 66;
	strncpy(hdg, begin, 4);
	hdg[3] = '\0';

	begin = current + 69;
	strncpy(salt, begin, 6);
	salt[5] = '\0';

	alt = atof(salt);

	if (strcasecmp(code, search) == 0)
	{
		/*
		printf("%s|", name);
		printf("%s|", code);
		printf("%s|", rwy);
		printf("%s|", len);
		printf("%s|", num);
		printf("%.6f|", lat);
		printf("%.6f|", lon);
		printf("%s|", ils);
		printf("%s|", hdg);
		printf("%.0f\n", alt);
		*/
/*
		printf("%s\t", name);
		printf("%s\t", code);
		printf("%s\t", rwy);
		printf("%s\t", len);
		printf("%s\t", num);
		printf("%.6f\t", lat);
		printf("%.6f\t", lon);
		printf("%s\t", ils);
		printf("%s\t", hdg);
		printf("%.0f\n", alt);
*/
			printf("%s ", name);
			printf("%s ", code);
			printf("%s ", rwy);
			printf("%s ", len);
			printf("%s ", num);
			printf("%.6f ", lat);
			printf("%.6f ", lon);
			printf("%s ", ils);
			printf("%s ", hdg);
			printf("%.0f\n", alt);

	}
	
}

int main(int argc, char* argv[])
{
	FILE* fin;
	char buffer[MAX_LINE_LENGTH];

	if (argc == 1)
	{
		printf("Nothing search.\nEnter airport's ICAO code as an argument.\n");
		return (EXIT_SUCCESS);
	}

	fin = fopen("wpnavapt.txt", "r");
	if (fin == NULL)
	{
		printf("Cannot open route file.\n");
		return (EXIT_FAILURE);
	}

	printf("Display values are:\n");
/*	printf("Airport Name\tICAO\tRWY\tLength\tMagHdg\tLat\tLon\tILS\tILS Hdg\tAlt (ft)\n");
	i*/
	printf("Airport ICAO RWY Length MagHdg Lat Lon ILS Hdg Alt\n");
	
	printf("===========================================================================\n");
	
	while (fgets(buffer, MAX_LINE_LENGTH, fin))
	{
		if ((buffer[0] != ';') && (buffer[0] != '#'))
			parse_string((const char*)&buffer, argv[1]);
	} 
	fclose(fin);

	return (EXIT_SUCCESS);
}
