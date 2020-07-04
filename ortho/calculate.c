
/*
 * ==========
 * Orthodromy
 * ==========
 * version: 1.0
 * date: June 27, 2020
 *
 */
 
#include "stdafx.h"
#include "orthodromy.h"  /* common definitions */
#include "wplist.h"             /* list of waypoints */
#include "geo_inverse.h"  /* geodesic ploblems */

/*
 The magnetic variation of the reference meridian
 --------------------------------------------------------------
 The list build by push_front() method holds waypoints 
 in the reverse order. The last point is placed at the head 
 of the list.
*/
static double reference_magvar(const wplist* pList)
{
	/* The magnetic variation at the launch airport */
	return pList->value.magvar;
}

/*
=================================================
The subroutine should returns a meridian convergence to caller. 
This value will be sum by caller.

WARNING: The function is called in a loop

Input:
         wp_ini  the first point of the leg
         wp_fin  the last point of the leg
   conv_sum  the sum of convergence on legs before current
ref_magvar  the magnetic variation on the reference meridian

Output:
convergence  meridian convergence (degrees)
        distance  distance between points on  sphere (kilometres)
          magvar  magnetic variation at the last point of the route
=================================================
 */
static void route_leg(const waypoint* wp_ini, const waypoint* wp_fin,
	const double conv_sum, const double ref_magvar,
	double* convergence, double* distance,  double* magvar)
{
	double az1, az2, s, delta, griv, grid_angle, mag_track;

	/*
	Solving of the inverse geodetic problem on sphere
	---------------------------------------------------------------
	az1 initial true angle of orthodromy 
	az2 final true angle of orthodromy 
	    s  orthodromic distance between the points on sphere
	*/
	geo_inverse_sphere(
		wp_ini->lat, wp_ini->lon,
		wp_fin->lat, wp_fin->lon,
		&az1, &az2, &s);
	
	delta = az2 - az1;  /* Convergence */

#if 0
		_geo_inverse_wgs_84(wp_ini->lat, wp_ini->lon,
			wp_fin->lat, wp_fin->lon,
			&az1, &az2, &s);

		az2 = az2-180;
		delta = az2 - az1;  /* Convergence */
		s = s / 1000;
#endif

	griv = conv_sum + ref_magvar - wp_ini->magvar;
	grid_angle = az1 - conv_sum - ref_magvar;
	if (grid_angle < 0) grid_angle = 360.0f + grid_angle;
	mag_track = az1 - wp_ini->magvar;

	/* Output data */
	*convergence = delta;
	*distance= s;
	*magvar = wp_fin->magvar;

	/*
	The result of calculation for each leg of the route:
	-------------------------------------------------------------
	Name of initial point of the leg (ini)
	Name of final point of the leg  (fin)
	Initial true angle of orthodromy (at the point ini)
	Final true angle of orthodromy (at the point fin)
	Orthodromic distance between the points on sphere
	Grivation for the leg
	Grivation angle (orthodromic course)
	Magnetic track at the initial point of the leg
	*/

	printf("%s-%s\t%.2f\t%.2f\t%.1f\t%.2f\t%.2f\t%.2f\t%.2f\t%.0f\n",
		wp_ini->code, wp_fin->code, az1, az2, s, delta,
		conv_sum, griv, grid_angle, mag_track);

}


/*
 ================================
 Calculates values over all legs of the route
 ================================
*/
static void calculate_route(const wplist* pList, double* vilka, double* distance)
{
	double scon = 0; /* the sum of azimuthal corrections */
	double path = 0; /* the sum of the distances */
	double ref_magvar = 0;
	double mv = 0;
	wplist* finish = NULL;

	ref_magvar = reference_magvar(pList);
	finish = (wplist*)pList;
	while (finish)
	{
		double leg = 0;  /* leg length */
		double con = 0;  /* azimuthal correction */

		wplist* start = finish;
		finish = finish->next;
		if (finish)
		{
			route_leg(
				(const waypoint*)&(start->value),
				(const waypoint*)&(finish->value),
				scon, ref_magvar, &con, &leg, &mv);

			path = path + leg;
			scon = scon + con;
		}
	}

	*distance = path;
	*vilka = scon + ref_magvar - mv;
}

/* non static ==> export */
void calculate(const wplist* pList)
{
	double vilka = 0;
	double distance = 0;

	printf("-----------------------------------------------------------------------------\n");
	printf("Route Leg\tTTi\tTTf\tDist\tConv\tSConv\tGriv\tGrid\tMT\n");
	printf("-----------------------------------------------------------------------------\n");

	calculate_route(pList, &vilka, &distance);

	printf("-----------------------------------------------------------------------------\n");
	printf("Grivation: %.2f (deg)\n", vilka);
	printf("Distance: %.0f km\n", distance);

}
