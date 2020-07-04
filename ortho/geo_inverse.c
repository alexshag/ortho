
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
 geo_inverse_sphere
 ==================

 This solves an inverse geodesic problem on sphere.
 It calculates initial and final true courses of orthodrome
 between the two points by using formula for solving spherical
 triangle (tangens formula). Distance is calculated by using
 the central angle between these two points. The distance
 calculated by the function is within 1% of the geodesic
 distance for the WGS84 ellipsoid.
*/

int geo_inverse_sphere(double lat1, double lon1, double lat2, double lon2, 
                       double *az1, double *az2, double *s)
{
	double x2, y2, z;
	double phi1 = deg2rad(lat1);
	double phi2 = deg2rad(lat2);
	double lam1 = deg2rad(lon1);
	double lam2 = deg2rad(lon2);
	double dlam = lam2-lam1;

	double a = cos(phi2)*sin(dlam);
	double b = cos(phi1)*sin(phi2)-sin(phi1)*cos(phi2)*cos(dlam);
	x2 = b*b;
	y2 = a*a;
	*az1 = rad2deg(atan2(a, b));

	if (*az1 < 0)
		*az1 = 360 + *az1;

	a = cos(phi1)*sin(dlam);
	b = sin(phi2)*cos(phi1)*cos(dlam)-cos(phi2)*sin(phi1);
	*az2 = rad2deg(atan2(a, b));

	if (*az2 < 0)
		*az2 = 360 +*az2;

	/* Distance calculation */
	z = sin(phi1)*sin(phi2)+cos(phi1)*cos(phi2)*cos(dlam);
	/* The central angle must be expressed in RADIANS !!! */
	*s = atan2(sqrt(x2+y2), z)*6371.0;

	return 0;
}

