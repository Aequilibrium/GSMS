#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstring>
#include <iostream>

#define	__ERR_UNDEFINED	0L

/*!\typedef unsigned_int64
 * \brief simplified unsigned int64
 */
typedef	unsigned long long	unsigned_int64;

/*!\def GSMS_OK
 * \brief exit code OK
 */
#define	GSMS_OK		0

/*!\def GSMS_ERR
 * \brief generic error exit code
 */
#define GSMS_ERR	1000

//////////////////////////////////

#define	GSMS_COLOR_ALUMINIUM	G4Colour(0.,0.,1.)
#define	GSMS_COLOR_MGO		G4Colour(.5,.5,.5)
#define	GSMS_COLOR_CRYSTAL	G4Colour(0.,1.,0.)
#define	GSMS_COLOR_ELEMENT	G4Colour(1.,0.,0.)
#define	GSMS_COLOR_PLASTIC	G4Colour(0.25,0.25,0.25)
#define	GSMS_COLOR_STEEL	G4Colour(0.,0.,0.)

bool	__SUCCEEDED(unsigned int GSMS_CODE);

enum ErrorLevel {
	EL_Fatal,
	EL_Error,
	EL_Warning,
	EL_Notice
};

#endif /* TYPEDEFS_H */
