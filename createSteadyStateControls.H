// Controls for the steady-state detection of the scalar transport.
//
// The time loop is stopped once the normalised rate of change of Cx and Cy
// drops below "steadyStateTolerance", read from constant/transportProperties.
// A non-positive tolerance disables the check and the run then ends at
// endTime as usual.

const scalar scalarSteadyTol
(
    transportProperties.lookupOrDefault<scalar>("steadyStateTolerance", 1e-5)
);

scalar CxRate = GREAT;
scalar CyRate = GREAT;
bool scalarConverged = false;

if (scalarSteadyTol > 0)
{
    Info<< "Steady-state detection enabled, tolerance = "
        << scalarSteadyTol << nl << endl;
}
else
{
    Info<< "Steady-state detection disabled, set steadyStateTolerance"
           " in transportProperties to enable it" << nl << endl;
}
