/*    Info<< "Reading physicalProperties\n" << endl;

    IOdictionary physicalProperties
    (
        IOobject
        (
            "physicalProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    dimensionedScalar epsilon0
    (
        physicalProperties.lookup("epsilon0")
    );
*/
/*
    Info<< "Reading field magPot\n" << endl;
    volScalarField magPot
    (
        IOobject
        (
            "magPot",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

	Info<< "Calculating field Hfield\n" << endl;
    volVectorField Hfield
    (
        IOobject
        (
            "Hfield",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
		mesh
    );


    Info<< "Reading field magCharge\n" << endl;
    volScalarField magCharge
    (
        IOobject
        (
            "magCharge",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh
    );*/

	volScalarField tau_y_field
	(
		IOobject
		(
		 	"tau_y_field",
			runTime.timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	);
