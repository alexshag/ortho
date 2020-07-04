
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


/*
Note: This function returns a pointer to a substring of the original string.
If the given string was allocated dynamically, the caller must not overwrite
that pointer with the returned value, since the original pointer must be
deallocated using the same allocator with which it was allocated.  The return
value must NOT be deallocated using free() etc.
*/
/* export */
char* trimwhitespace(char* str)
{
	char* end;

	/* Trim leading space */
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)
		return str;

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	/* Write new null terminator character */
	end[1] = '\0';

	return str;
}

static void parse_airport(const char* buffer, const char* search)
{
	char* current;
	char* begin;
	char name[26] = { 0 };
	char code[5] = { 0 };
	char rwy[4] = { 0 };
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
	strncpy(name, begin, sizeof(name));
	name[25] = '\0';
	strcpy(name, trimwhitespace(name));

	begin = current + 24;
	strncpy(code, begin, sizeof(code));
	code[4] = '\0';

	begin = current + 28;
	strncpy(rwy, begin, sizeof(rwy));
	rwy[3] = '\0';

	begin = current + 31;
	strncpy(len, begin, sizeof(len));
	len[5] = '\0';

	begin = current + 36;
	strncpy(num, begin, sizeof(num));
	num[3] = '\0';

	begin = current + 40;
	strncpy(slat, begin, sizeof(slat));
	slat[9] = '\0';

	begin = current + 50;
	strncpy(slon, begin, sizeof(slon));
	slon[11] = '\0';

	lat = atof(slat);
	lon = atof(slon);

	begin = current + 60;
	strncpy(ils, begin, sizeof(ils));
	ils[6] = '\0';

	begin = current + 66;
	strncpy(hdg, begin, sizeof(hdg));
	hdg[3] = '\0';

	begin = current + 69;
	strncpy(salt, begin, sizeof(salt));
	salt[5] = '\0';

	alt = atof(salt);

	if (strcmp(code, search) == 0)
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
	}

}

