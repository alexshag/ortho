
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

#include "coord_conv.h"


/* ------------------------------------------------------------------------
 * It converts geographical coordinate given as a string to double value.
 * The value is positive for north and east hemisphere and negative for
 * south and west one.

 * In error case it returns: -9999.0f
 *
 * If the string has a prefix which specified a hemisphere the function
 * check its result over range 90 degrees for latitude and 180 degrees
 * for longitude.
 *
 * WARNING:
 * If the input string is given as a number then the function does not check
 * its result over range 90/180 degrees because it is unknown what is that 
 * latitude or longitude
 * ------------------------------------------------------------------------
 */
double coord_conv(const char* coordinate_string)
{
	/* the size of the buffer is maximum length of string */
	#define BUF_SIZE 64

	int error_code = 0;
	int hemisphere_sign = 0;

	double result = -9999.0f; /* set an error by default */
	double minutes = 0.0;
	double frac = 0.0;
	double whole = 0.0;

	char* current = NULL;
	char temp[BUF_SIZE] = {0}; 
	char* buffer = NULL;
	char degrees_string[32] = {0}; /* The first buffet holds degrees */
	char minutes_string[32] = {0}; /* The second buffer hold minutes */

	strncpy(temp, coordinate_string, sizeof(temp));

	/* Is the first symbol hemisphere letter */
	if (isalpha(temp[0]))
	{
		switch (temp[0])
		{
		case 'n':
		case 'N':
			hemisphere_sign = 0;
			break;

		case 's':
		case 'S':
			hemisphere_sign = 1;
			break;

		case 'e':
		case 'E':
			hemisphere_sign = 2;
			break;

		case 'w':
		case 'W':
			hemisphere_sign = 3;
			break;

		default:
			/* error here */
			hemisphere_sign = 4;
			break;
		}

		/* If zero is followed after hemisphere letter skip it */
		if (temp[1] == '0')
			current = &temp[2];
		else
			current = &temp[1];
	}
	else if (temp[0] == '-')
	{
		/* The first symbol is minus sign */
		/* Is there a space in the string?  */
		char* tmp = temp;
		while (*tmp++)
		{
			hemisphere_sign = 5; /* No, there is not  a space */
			if (isspace(*tmp))
			{
				hemisphere_sign = 3; /* Yes, there is a space */
				break;
			}
		}
		
		/* South or East hemisphere */
		if (hemisphere_sign == 3)
			current = &temp[1];
		else
			current = &temp[0];
	}

	if (isdigit(temp[0]))
	{
		/* The first symbol is digit */
		/* Is there a space in the string? */
		char* tmp = temp;
		while (*tmp++)
		{
			hemisphere_sign = 5; 
			if (isspace(*tmp))
			{
				hemisphere_sign = 3; 
				break;
			}
		}		
		/* Start analyse from the first symbol */
		current = &temp[0];
	}

	/* Must be checked !!! */
	if (!current)
		return result;
	
	buffer = &degrees_string[0];
	while(*current != '\0')
	{
		/* Write symbols at the current position of buffer */
		while (*current != ' ')
		{
			if (*current == '\0')
				break;

			*buffer = *current;
			current++;
			buffer++;
		}
		*buffer = '\0';

		/* the second buffer holds minutes*/
		buffer = &minutes_string[0];
		
		if (*current == '\0')
			break;

		current++;
	}

	/*  Error: Wrong hemisphere letter */
	if (hemisphere_sign == 4)
		error_code = 1;

	/* Check range */
	whole = (double)atof(degrees_string);

	if ((hemisphere_sign == 0) || (hemisphere_sign == 1))
	    if (whole > 90.0f)
		    error_code = 1;

	if ((hemisphere_sign == 2) || (hemisphere_sign == 3))
	    if (whole > 180.0f)
		    error_code = 1;

	minutes = (double)atof(minutes_string);

	if (minutes > 60.0f)
		error_code = 1;

	frac = minutes/60;
	result = whole + frac;

	/* The result is here */
	if (((hemisphere_sign == 1) || (hemisphere_sign == 3)))
		result = -result;

	if (error_code != 0)
		result = -9999.0f;

	return result;
}

