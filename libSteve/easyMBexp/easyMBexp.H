/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::viscosityModels::easyMBexp

Description
     Herschel-Bulkley non-Newtonian viscosity model.

SourceFiles
    easyMBexp.C

\*---------------------------------------------------------------------------*/

#ifndef easyMBexp_H
#define easyMBexp_H

#include "viscosityModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{

/*---------------------------------------------------------------------------*\
                           Class easyMBexp Declaration
\*---------------------------------------------------------------------------*/

class easyMBexp
:
    public viscosityModel
{
    // Private data

        dictionary easyMBexpCoeffs_;

        dimensionedScalar visc_po_;
		dimensionedScalar visc_pre_;

        volScalarField nu_;

    // Private Member Functions

    //- Calculate and return the laminar viscosity
    tmp<volScalarField> calcNu() const;


public:

    //- Runtime type information
    TypeName("easyMBexp");


    // Constructors

        //- Construct from components
        easyMBexp
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    ~easyMBexp()
    {}


    // Member Functions

	//- Return the laminar viscosity
	tmp<volScalarField> nu() const
	{
		return nu_;
	}

	//- Return the laminar viscosity for patch
	tmp<scalarField> nu(const label patchi) const
	{
		return nu_.boundaryField()[patchi];
	}

	//- Correct the laminar viscosity
	void correct()
	{
		nu_ = calcNu();
	}

	//- Read transportProperties dictionary
	bool read(const dictionary& viscosityProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace viscosityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
