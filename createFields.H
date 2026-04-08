Info<< "Reading transportProperties\n" << endl;
IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

Info<< "Reading dynamic viscosity\n" << endl;
dimensionedScalar nu
(
    transportProperties.lookup("nu")
);

Info<< "Reading diffusion coeff\n" << endl;

dimensionedScalar D("D", dimViscosity, transportProperties);

Info<< "Reading reaction rate\n" << endl;
dimensionedScalar k
(
    transportProperties.lookup("k")
);

Info<< "Reading Pe number\n" << endl;
dimensionedScalar Pe
(
    transportProperties.lookup("Pe")
);




Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


volScalarField Cx
(
    IOobject
    (
        "Cx",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField Cy
(
    IOobject
    (
        "Cy",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField R
(
    IOobject
    (
        "R",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    k * Cy * sqr(Cx)
);


// Info<< "Reading field phi\n" << endl;
// volVectorField phi
// (
//     IOobject
//     (
//         "phi",
//         runTime.timeName(),
//         mesh,
//         IOobject::NO_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
//     dimensionedScalar
//     (
//         "phi",
//         dimArea*dimVelocity, 
//         scalar(0)
//     )
// );



label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, simple.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());

#include "createPhi.H"
#include "createFvOptions.H"
