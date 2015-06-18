/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  2.3.0                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    `format'      ascii;
    class       dictionary;
    object      blockMeshDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// block definition for a porosity with an angled inlet/outlet
// the porosity is not aligned with the main axes
//
dnl> -----------------------------------------------------------------
dnl> <STANDARD DEFINTIONS>
dnl>
changecom(//)changequote([,]) dnl>
define(calc, [esyscmd(perl -e 'print ($1)')]) dnl>
define(VCOUNT, 0)  dnl>
define(vlabel, [[// ]pt VCOUNT ($1) define($1, VCOUNT)define([VCOUNT], incr(VCOUNT))])  dnl>
dnl>
define(hex2D, hex ($1b $2b $3b $4b $1f $2f $3f $4f)) dnl>
define(quad2D, ($1f $1b $2b $2f))  dnl>
define(frontQuad, ($1f $2f $3f $4f)) dnl>
define(backQuad, ($4b $3b $2b $1b)) dnl>
dnl>
dnl> </STANDARD DEFINTIONS>
dnl> -----------------------------------------------------------------
dnl>

define(xa, -.2) dnl>
define(xb, .2) dnl>
define(ybot, 0.0) dnl>
define(ytop, 1.0) dnl>
define(depth, 0.005) dnl>

define(nxinlet, 10) dnl>
define(ny,50) dnl>
define(nz,1) dnl>
dnl>
convertToMeters 0.001;

vertices
(
    // A line vertices 
    ( xa  ybot -depth )  vlabel(A1b)
    ( xa  ytop  -depth )  vlabel(A2b)
    ( xa  ybot depth )  vlabel(A1f)
    ( xa  ytop  depth )  vlabel(A2f)

    // B line vertices 
    ( xb  ybot -depth )  vlabel(B1b)
    ( xb  ytop  -depth )  vlabel(B2b)
    ( xb  ybot depth )  vlabel(B1f)
    ( xb  ytop  depth )  vlabel(B2f)


);

blocks
(
    
    // inlet block
    hex2D(A1, B1, B2, A2)
    ( nxinlet ny nz) simpleGrading (1 1 1)

	
);

edges
(
);

boundary
(
   
    lowerWall
	{
		type wall;
		faces
		(
			quad2D(A1, B1)
		);
	}

	upperWall
	{
		type symmetryPlane;
		faces
		(
			quad2D(A2, B2)
		);
	}
    inlet
	{
		type cyclic;
		neighbourPatch outlet;
		faces 
		(
			quad2D(A1, A2)
		);
	}

    outlet
	{
		type cyclic;
		neighbourPatch inlet;
		faces
		(
			quad2D(B1, B2)
		);
	}
);

mergePatchPairs
(
);

// ************************************************************************* //
