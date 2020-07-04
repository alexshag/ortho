
#pragma once

int geo_inverse_wgs84(double lat1, double lon1, double lat2, double lon2, double *az1, double *az2, double *s);
int geo_direct_wgs84(double lat1, double lon1, double az1, double s, double *lat2, double *lon2, double *az2 );
