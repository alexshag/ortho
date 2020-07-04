
/*
 * ==========
 * Orthodromy
 * ==========
 * version: 1.0
 * date: June 27, 2020
 *
 */
 
#include "stdafx.h"
#include "getopt.h"      /* cmdline opt */
#include "orthodromy.h"  /* globals     */
#include "wplist.h"      /* waypoints   */
#include "coord_conv.h"  /* coord_conv  */
#include "correction.h"  /* correction  */
#include "parser.h"      /* all parser  */
#include "calculate.h"   /* calculation */

static int open_route_file(const char* file_name, int flag, wplist** ppList);
static void print_waypoint(const wplist* pList);

static void usage(void)
{
	printf("\nThis program calculates the route between two points (airfields).\n");
	printf("The route file must be specified as an argument to the program call.\n");
	printf("For example: $ orthodromy -f KLAX-KSFO.txt\n");
}

int main(int argc, char* argv[])
{
	wplist* pList = NULL;
	int flag = 0;
	char route_file[MAX_PATH_LENGTH] = {0};

	int aflag = 0;
	int bflag = 0;
	char* cvalue = NULL;
	int index;
	int c;
	opterr = 0;

	if (argc <= 1)
	{
		usage();
		exit(EXIT_SUCCESS);
	}

	/* TODO: Temporary command line arguments are not used */
	if (argc == 2)
	{
		strncpy(route_file, argv[1], sizeof(route_file));
		flag = 2;
	}
	else
	{

	/* ----------------- START OF COMMAND LINE PARSING ------------------ */
	while ((c = getopt(argc, argv, "abc:")) != -1)
		switch (c)
		{
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'c':
			cvalue = optarg;
			break;
		case '?':
			if (optopt == 'c')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;

		default:
			abort();
		}

	printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

	for (index = optind; index < argc; index++)
		printf("Non-option argument %s\n", argv[index]);

	if (cvalue)
		strncpy(route_file, cvalue, sizeof(route_file));
	else
	{
		usage();
		exit(EXIT_SUCCESS);
	}

	/* -------------- END OF COMMAND LINE PARSING ----------------- */
	}

	if (open_route_file(route_file, flag, &pList) != 0)
		exit(EXIT_FAILURE);

	if (wplist_size(pList) == 0)
		exit(EXIT_FAILURE);

	/* Reverse the list */
	wplist_reverse(&pList);
	print_waypoint(pList);
	calculate(pList);

	
	/*
	printf("\n\n$$$$$$$$$$$$$$$$$$$$$\n\n");
	wplist_reverse(&pList);
	calculate(pList);
	*/

	wplist_free(&pList);

	/*_CrtDumpMemoryLeaks();*/
	
	exit(EXIT_SUCCESS);
}


static int parse_with_flag(const char* str, int flag, wplist** ppList)
{
	int res = 0;

	switch (flag)
	{
	case 0:
	case 1:
		res = parse_magvar(str, ppList);
		break;

	case 2:
		res = parse_waypoints(str, ppList);
		break;

	case 3:
		res = parse_pmdg(str, ppList);
		break;

	default:
		break;
	} /* switch */

	return res;
}

/*
   Returns:
   0   success
   -1 failure, print message "cannot parse the file"
*/

static int open_route_file(const char* file_name, int flag, wplist** ppList)
{
	FILE* stream;
	char str[MAX_LINE_LENGTH] = {0};
	int not_parsed = 0;

	stream = fopen(file_name, "r");
	if (stream == NULL)
	{
		printf("Cannot open route file %s.\n", file_name);
		return -1;
	}

	/* Enumerate all points of the route */
	while(fgets(str, MAX_LINE_LENGTH, stream) && !not_parsed)
	{
		/* Skip commented and empty lines */
		if ((((str[0] == '/') && (str[1] == '/')) || (str[0] == '\n')))
			continue;
		/* The symbol # is label of correction */
		if ((str[0] == ';') || (str[0] == '#'))
		{
			not_parsed = correction(str);
			continue;
		}

		/* This call MUST BE last !!!??? */
		not_parsed = parse_with_flag(str, flag, ppList);

	} /* while (eof) */

	fclose(stream);

	if (not_parsed)
		printf("Cannot parse the file. Incorrect format.\n");

	/* At this point the list holds all points of the route */
	/*__debugbreak();*/

	return not_parsed;
}

static void print_wp(const waypoint* point)
{
	if (point != NULL)
		printf("%s\t\t%.5f\t%.5f\t%.2f\n",
			point->code,
			point->lat,
			point->lon,
			point->magvar);
}


static void print_waypoint(const wplist* pList)
{
	wplist* cur = NULL;
	printf("-------------------------------------------------------\n");
	printf("Waypoint\tLatitude\tLongitude\tMagVar\n");
	printf("-------------------------------------------------------\n");
	for (cur = (wplist*)pList; cur != NULL; cur = cur->next)
	{
		print_wp((const waypoint*)&(cur->value));
	}
	printf("-------------------------------------------------------\n");
}

