// Steady-state check for the scalar transport.
//
// The rate of change of each field is normalised by its own maximum magnitude
// and by the time-step size, so the resulting measure is independent of both
// the concentration scale and of deltaT.  Cx.oldTime() holds the field at the
// start of the time step, stored by the fvm::ddt term in solveC.H.

{
    const scalar rDeltaT = 1.0/runTime.deltaTValue();

    const scalar CxNorm = max(gMax(mag(Cx.primitiveField())), SMALL);
    const scalar CyNorm = max(gMax(mag(Cy.primitiveField())), SMALL);

    CxRate =
        rDeltaT
       *gMax(mag(Cx.primitiveField() - Cx.oldTime().primitiveField()))/CxNorm;

    CyRate =
        rDeltaT
       *gMax(mag(Cy.primitiveField() - Cy.oldTime().primitiveField()))/CyNorm;

    Info<< "Rate of change: Cx = " << CxRate
        << ", Cy = " << CyRate << nl << endl;

    scalarConverged =
        (scalarSteadyTol > 0)
     && (CxRate <= scalarSteadyTol)
     && (CyRate <= scalarSteadyTol);
}
