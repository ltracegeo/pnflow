#include <iostream>
#include <string>

#include "pnflow.h"

std::string FILECONTENT = R"(
TITLE  Output;  // base name for the output files

writeStatistics true;

NETWORK  F Image;   // the base name for of the network file, without _link1.dat, _link2, _pore1

//!cycle#  Final Sw        Final Pc       Sw steps          Compute Kr   Compute RI
cycle1:    0.0 20000000.0 0.005     T            T;
cycle2:    1.0 -20000000.0 0.005     T            T;
cycle3:    0.0 20000000.0 0.005     T            T;

//!cycle#       Inject from                    Produce from                  Boundary-condition
//!        Left           Right            Left            Right            Type   Water  Oil
cycle1_BC: T F  F T  DP    1.00   2.00;
cycle2_BC: T F  F T  DP    2.00   1.00;
cycle3_BC:  T F  F T  DP    1.00   2.00;

//!       x[range]
CALC_BOX: 0.1 0.9; //!bounding box for computing rel-permss

//!            model                min                      max                       delta                      gamma                     RCtrl                        Mdl2Sep
INIT_CONT_ANG: 3  15.0  25.0   -1.0    -1.0   rand    25.2;
EQUIL_CON_ANG: 3 15.0 25.0  -1.0   -1.0  rand   25.2;

//!          fraction                  min                        max                        delta                       gamma                      RCtrl
2ND_CON_ANG: 0.0  15.0  25.0  -1.0   -1.0  rand;

//!            fraction              volBased              min              max              delta              gamma              method               corrDiam
FRAC_CON_ANG:  0.0 T 15.0 25.0 -1.0 -1.0 corr  7.0

//     viscosity(Pa.s)   resistivity(Ohm.m)  density(kg/m3)
Water  1000.0  1.2  1.0;
Oil    1100.0    1000.0    0.9;
ClayResistivity          2.0;

WaterOilInterface        2.0;  // interfacial tension (N/m)

DRAIN_SINGLETS: T;   // T for yes, F for no. singlets are dead-end pores

visuaLight  T        T          T         F          T ;

PORE_FILL_ALG: blunt2;
PORE_FILL_WGT: 0.0 0.5 1.0 2.0 5.0 10.0;
)";

int main() {
    pnflow(FILECONTENT);
}
