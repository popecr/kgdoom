#ifndef __R_SKY__
#define __R_SKY__


#ifdef __GNUG__
#pragma interface
#endif

// SKY, store the number for name.
#define			SKYFLATNAME  "F_SKY1"

// The sky map is 256*128*4 maps.
#define ANGLETOSKYSHIFT		22

extern  int		skytexture;
extern int		skytexturemid;

// Called whenever the view size changes.
void R_InitSkyMap (void);

#endif

