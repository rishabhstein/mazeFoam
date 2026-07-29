const dictionary& simpleDict = simple.dict();

const label nCycles = simpleDict.lookupOrDefault<label>("nCycles", 1000);

const dictionary& residualControl = simpleDict.subDict("residualControl");

const scalar tolerance_p =
    residualControl.lookupOrDefault<scalar>("p", -1.0);
const scalar tolerance_U =
    residualControl.lookupOrDefault<scalar>("U", -1.0);

scalar pResidual = GREAT;
scalar UResidual = GREAT;
bool flowConverged = false;

for (label counter = 1; counter <= nCycles; ++counter)
{
    Info<< "Cycle = " << counter << nl << endl;

    // --- Pressure-velocity SIMPLE corrector
    {
        #include "UEqn.H"
        #include "pEqn.H"
    }

    const bool pConverged = (tolerance_p <= 0) || (pResidual <= tolerance_p);
    const bool UConverged = (tolerance_U <= 0) || (UResidual <= tolerance_U);

    Info<< "Residuals: p = " << pResidual << " and, U = " << UResidual << nl << endl;

    if (pConverged && UConverged)
    {
        flowConverged = true;
        Info<< "Flow solution is converged." << nl << endl;
        break;
    }
}

if (!flowConverged)
{
    Info<< "Flow did not converge within nCycles = "
        << nCycles << nl 
        << exit(FatalError) << endl;
}
