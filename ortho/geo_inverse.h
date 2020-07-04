
#pragma once

int geo_inverse_sphere(double lat1, double lon1, double lat2, double lon2,
	double* az1, double* az2, double* s);
int _geo_inverse_wgs_84(double lat1, double lon1, double lat2, double lon2,
	double* az1, double* az2, double* s);
