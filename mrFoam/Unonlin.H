    // Momentum predictor
	// explicit resolution of the viscosity gradient terms
	// but no turbulence models
    tmp<fvVectorMatrix> UEqn
    (
        fvm::div(phi, U)
	  - fvm::laplacian(fluid.nu(), U)
	  - (fvc::grad(U) & fvc::grad(fluid.nu()))
      ==
        fvOptions(U)
    );

    UEqn().relax();

    fvOptions.constrain(UEqn());

    solve(UEqn() == -fvc::grad(p));

    fvOptions.correct(U);
