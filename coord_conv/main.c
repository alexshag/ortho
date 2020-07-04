
/* ----------------------------------------- */
/* Convert coordinate string to double value */
/* For example: "W43 36.4812" to -43.608020  */
/* ----------------------------------------- */

#include <stdio.h>
#include <string.h>

#include "coord_conv.h"

int main(int argc, char* argv[])
{
	double lat = 0.0f;
	char slat[9] = {'\0'};

	if (argc > 1)
	{
		strcpy(slat, argv[1]);
		lat = coord_conv(slat);
		printf("Coordinate (double): %.6f\n", lat);
	}
	else
	{
		printf("Convert geographic coordinate string to double value\n");
		printf("Enter geographic coordinate as an argument\n");
		printf("For example: \"W43 36.4812\"\n\n");
	}

	return 0;
}

