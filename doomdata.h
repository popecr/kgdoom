#ifndef __DOOMDATA__
#define __DOOMDATA__

// The most basic types we use, portability.
#include "doomtype.h"

// Some global defines, that configure the game.
#include "doomdef.h"



//
// Map level types.
// The following data structures define the persistent format
// used in the lumps of the WAD files.
//

// Lump order in a map WAD: each map needs a couple of lumps
// to provide a complete scene geometry description.
enum
{
  ML_LABEL,		// A separator, name, ExMx or MAPxx
  ML_THINGS,		// Monsters, items..
  ML_LINEDEFS,		// LineDefs, from editing
  ML_SIDEDEFS,		// SideDefs, from editing
  ML_VERTEXES,		// Vertices, edited and BSP splits generated
  ML_SEGS,		// LineSegs, from LineDefs split by BSP
  ML_SSECTORS,		// SubSectors, list of LineSegs
  ML_NODES,		// BSP nodes
  ML_SECTORS,		// Sectors, from editing
  ML_REJECT,		// LUT, sector-sector visibility	
  ML_BLOCKMAP,		// LUT, motion clipping, walls/grid element
  ML_BEHAVIOR		// [kg] fun stuff
};


// A single Vertex.
typedef struct
{
  short		x;
  short		y;
} mapvertex_t;


// A SideDef, defining the visual appearance of a wall,
// by setting textures and offsets.
typedef struct
{
  short		textureoffset;
  short		rowoffset;
  char		toptexture[8];
  char		bottomtexture[8];
  char		midtexture[8];
  // Front sector, towards viewer.
  short		sector;
} mapsidedef_t;



// A LineDef, as used for editing, and as input
// to the BSP builder.
typedef struct
{
  short		v1;
  short		v2;
  short		flags;
  short		special;
  short		tag;
  // sidenum[1] will be -1 if one sided
  short		sidenum[2];		
} maplinedef_t;

typedef struct
{
	short v1;
	short v2;
	short flags;
	uint8_t special;
	uint8_t arg[5];
	short sidenum[2];
} maplinedef_hexen_t;

//
// LineDef attributes.
//

// Solid, is an obstacle.
#define LF_BLOCKING		1

// Blocks monsters only.
#define LF_BLOCKMONSTERS	2

// Backside will not be present at all
//  if not two sided.
#define LF_TWOSIDED		4

// If a texture is pegged, the texture will have
// the end exposed to air held constant at the
// top or bottom of the texture (stairs or pulled
// down things) and will move with a height change
// of one of the neighbor sectors.
// Unpegged textures allways have the first row of
// the texture at the top pixel of the line for both
// top and bottom textures (use next to windows).

// upper texture unpegged
#define LF_DONTPEGTOP		8

// lower texture unpegged
#define LF_DONTPEGBOTTOM	16	

// In AutoMap: don't map as two sided: IT'S A SECRET!
#define LF_SECRET		32

// Sound rendering: don't let sound cross two of these.
#define LF_SOUNDBLOCK		64

// Don't draw on the automap at all.
#define LF_DONTDRAW		128

// Set if already seen, thus drawn in automap.
#define LF_MAPPED		256

// [kg] new sector flags
#define SF_SECRET	1
#define SF_WAS_SECRET	2

// Sector definition, from editing.
typedef	struct
{
  short		floorheight;
  short		ceilingheight;
  char		floorpic[8];
  char		ceilingpic[8];
  short		lightlevel;
  short		special;
  short		tag;
} mapsector_t;

// SubSector, as generated by BSP.
typedef struct
{
  short		numsegs;
  // Index of first one, segs are stored sequentially.
  short		firstseg;	
} mapsubsector_t;


// LineSeg, generated by splitting LineDefs
// using partition lines selected by BSP builder.
typedef struct
{
  short		v1;
  short		v2;
  short		angle;		
  short		linedef;
  short		side;
  short		offset;
} mapseg_t;



// BSP node structure.

// Indicate a leaf.
#define	NF_SUBSECTOR	0x8000

typedef struct
{
  // Partition line from (x,y) to x+dx,y+dy)
  short		x;
  short		y;
  short		dx;
  short		dy;

  // Bounding box for each child,
  // clip against view frustum.
  short		bbox[2][4];

  // If NF_SUBSECTOR its a subsector,
  // else it's a node of another subtree.
  unsigned short	children[2];

} mapnode_t;




// Thing definition, position, orientation and type,
// plus skill/visibility flags and attributes.
typedef struct
{
    short		x;
    short		y;
    short		angle;
    short		type;
    short		options;
} mapthing_t;

typedef struct
{
	short tid;
	short x;
	short y;
	short z;
	short angle;
	short type;
	short flags;
	uint8_t special;
	uint8_t arg[5];
} mapthing_hexen_t;


#endif			// __DOOMDATA__

