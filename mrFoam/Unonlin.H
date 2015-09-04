    // Momentum predictor
	// explicit resolution of the viscosity gradient terms
	// but no turbulence models
    tmp<fvVectorMatrix> UEqn
    (
        fvm::div(phi, U)
	  - fvm::laplacian(turbulence->nuEff(), U)
	  - (fvc::grad(U) & fvc::grad(turbulence->nuEff()))
      ==
        fvOptions(U)
    );

    UEqn().relax();

    fvOptions.constrain(UEqn());

    solve(UEqn() == -fvc::grad(p));

    fvOptions.correct(U);
