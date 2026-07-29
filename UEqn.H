    // Momentum predictor


    tmp<fvVectorMatrix> tUEqn
    (
//        fvm::div(phi, U)
      - fvm::laplacian(nu, U)
     ==
        fvOptions(U)
    );
    fvVectorMatrix& UEqn = tUEqn.ref();

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (simple.momentumPredictor())
    {
        const SolverPerformance<vector> USolverPerf =
            solve(UEqn == -fvc::grad(p));
        UResidual = cmptMax(cmptMag(USolverPerf.initialResidual()));

        fvOptions.correct(U);
    }
    else
    {
        UResidual = 0.0;
    }
