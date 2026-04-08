
while (simple.correctNonOrthogonal())
{
    R = k * Cy * sqr(Cx);

    fvScalarMatrix CxEqn
    (
        fvm::ddt(Cx)
    + Pe*fvm::div(phi, Cx)
    - fvm::laplacian(D, Cx)
        ==
        R
    );
    // CxEqn.relax();
    CxEqn.solve();
 

    fvScalarMatrix CyEqn
    (
        fvm::ddt(Cy)
    + Pe*fvm::div(phi, Cy)
    - fvm::laplacian(D, Cy)
        ==
        -R
    );

    // CyEqn.relax();
    CyEqn.solve();


}