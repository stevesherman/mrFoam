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

\*---------------------------------------------------------------------------*/

#include "easyMBexp.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(easyMBexp, 0);

    addToRunTimeSelectionTable
    (
        viscosityModel,
        easyMBexp,
        dictionary
    );




// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::easyMBexp::calcNu() const
{
    tmp<volScalarField> sr(strainRate());
	const volScalarField& tau_y_field = 
		U_.mesh().lookupObject<volScalarField>("tau_y_field");

	return min(visc_pre_, visc_po_ + tau_y_field *
		(1 - exp(
				 sr*(visc_po_ - visc_pre_)/max
				 		(
				 			tau_y_field, 
							dimensionedScalar ("VSMALL",dimLength*dimLength/(dimTime*dimTime), VSMALL)
						)
				)
		) / max(sr(), dimensionedScalar ("VSMALL", dimless/dimTime, VSMALL)) 
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::easyMBexp::easyMBexp
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    easyMBexpCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    visc_po_(easyMBexpCoeffs_.lookup("visc_po")),
	visc_pre_(easyMBexpCoeffs_.lookup("visc_pre")),
	nu_
    (
        IOobject
        (
            name,
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::easyMBexp::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    easyMBexpCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");

    easyMBexpCoeffs_.lookup("visc_pre") >> visc_pre_;
	easyMBexpCoeffs_.lookup("visc_po") >> visc_po_;

    return true;
}

//end namespaces
}
}

// ************************************************************************* //
