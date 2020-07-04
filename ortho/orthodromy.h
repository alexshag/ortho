
#ifndef __ORTHODROMY_H__
#define __ORTHODROMY_H__

/* for vc6.0 and gcc without -ansi */
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#ifndef PI
#define PI M_PI
#endif

#define rad2deg(val) (val)*180/PI
#define deg2rad(val) (val)*PI/180


#define MAX_PATH_LENGTH   256
#define MAX_LINE_LENGTH	  256


#endif /* __ORTHODROMY_H__ */
