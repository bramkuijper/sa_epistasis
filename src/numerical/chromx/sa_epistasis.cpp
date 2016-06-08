#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>
#include <cassert>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "bramauxiliary.h"


//#define NDEBUG

using namespace std;

// give the outputfile a unique name based on a timestamp
// involving nanoseconds
// by using the create_filename function (see 
// "bramauxiliary.h")
string filename("iter_sa_epistasis");
string filename_new(create_filename(filename));
ofstream DataFile(filename_new.c_str());  // output file 

int main(int argc, char **argv)
{
    double sAm;
    double hBm;
    double sBm;
    
    double sAf;
    double hBf;
    double sBf;
    
    double r = atof(argv[1]);
    double hAf = atof(argv[2]);
    double hAm = atof(argv[3]);
    double ef = atof(argv[4]);
    double em = atof(argv[5]);

    double x1, x2, x3, x4;
    double y1, y2, y3, y4, y5;
    double wM, wF, Dz, Demax, Dsmax, Dzprime;
    double pAff, pAfm, pAmf, pAmm;
    double pAf, pAm, pBf, pBm;
    double pBff, pBfm, pBmf, pBmm;

    double x1tplus1, x2tplus1, x3tplus1, x4tplus1;
    double y1tplus1, y2tplus1, y3tplus1, y4tplus1, y5tplus1;

    double pe, qe, ps, qs;

    double bound = 1e-12;
    double pol_bound = 1e-05;
    int state;
    int maxt = 10000000;

    int t = 0;

    DataFile << "time;sAm;sAf;sBm;sBf;hAm;hAf;hBm;hBf;em;ef;y1;y2;y3;y4;y5;x1;x2;x3;x4;pAmf;pAff;pBmf;pBff;pAmm;pAfm;pBmm;pBfm;pAm;pAf;pBm;pBf;Dz;Dzprime;state;" << endl;

    double step_s = 0.0025;

    for (sAm = 0; sAm < 0.5 + step_s; sAm += step_s)
    {
        for (sAf = 0; sAf < 0.5 + step_s; sAf += step_s)
        {
//            cout << sAm << " " << sAf << endl;
                            x1 = 0.25;
                            x2 = 0.25; 
                            x3 = 0.25;
                            x4 = 0.25;

                            y1 = 0.125;
                            y2 = 0.125; 
                            y3 = 0.125;
                            y4 = 0.125;
                            y5 = 0.5;

                            sBm = sAm;
                            sBf = sAf;
                            hBm = hAm;
                            hBf = hAf;

                            for (t = 0; t <= maxt; ++t)
                            {
                                ITERATIONS_HERE

                                if (
                                        fabs(y1tplus1 - y1) <= bound &&
                                        fabs(y2tplus1 - y2) <= bound &&
                                        fabs(y3tplus1 - y3) <= bound &&
                                        fabs(y4tplus1 - y4) <= bound &&
                                        fabs(y5tplus1 - y5) <= bound &&
                                        fabs(x1tplus1 - x1) <= bound &&
                                        fabs(x2tplus1 - x2) <= bound &&
                                        fabs(x3tplus1 - x3) <= bound &&
                                        fabs(x4tplus1 - x4) <= bound
                                ) 
                                {
                                    pAmf = x3 + x4;
                                    pAff = x1 + x2;
                                    pBmf = x2 + x4;
                                    pBff = x1 + x3;
                                    
                                    pAmm = y3 + y4;
                                    pAfm = y1 + y2;
                                    pBmm = y2 + y4;
                                    pBfm = y1 + y3;

                                    pAm = (x3 + x4 + y3 + y4)/2;
                                    pAf = (x1 + x2 + y1 + y2)/2;
                                    pBm = (x2 + x4 + y2 + y4)/2;
                                    pBf = (x1 + x3 + y1 + y3)/2;

                                    state = -1;

                                    if (pAmf >= pol_bound && 
                                            pAmf <= 1.0 - pol_bound && 
                                            pBmf >= pol_bound &&
                                            pBmf <= 1.0 - pol_bound &&
                                            pAmm >= pol_bound && 
                                            pAmm <= 0.5 - pol_bound && 
                                            pBmm >= pol_bound &&
                                            pBmm <= 0.5 - pol_bound)
                                    {
                                        state = 1;
                                    }
                                    else if (pAmf > 1.0 - pol_bound &&
                                            pBmf > 1.0 - pol_bound &&
                                            pAmm > 0.5 - pol_bound &&
                                            pBmm > 0.5 - pol_bound)
                                    {
                                        state = 2;

                                    }
                                    else if (pAff >= 1.0 - pol_bound &&
                                            pBff >= 1.0 - pol_bound &&
                                            pAfm >= 0.5 - pol_bound &&
                                            pBfm >= 0.5 - pol_bound)
                                    {
                                        state = 3;
                                    }
                                    else if (
                                            (
                                                (
                                                 (pAff > 1.0 - pol_bound || pAff < pol_bound) &&
                                                pBff >= pol_bound &&
                                                pBff <= 1.0 - pol_bound) 
                                                ||
                                                ((pBff > 1.0 - pol_bound || pBff < pol_bound) &&
                                                pAff >= pol_bound &&
                                                pAff <= 1.0 - pol_bound)
                                            ) &&
                                            (
                                                ((pAfm > 0.5 - pol_bound || pAfm < pol_bound) &&
                                                pBfm >= pol_bound &&
                                                pBfm <= 0.5 - pol_bound) 
                                                ||
                                                ((pBfm > 0.5 - pol_bound || pBfm < pol_bound) &&
                                                pAfm >= pol_bound &&
                                                pAfm <= 0.5 - pol_bound)
                                            )
                                    )
                                    {
                                        state = 4;
                                    }
                                    else if (
                                                (pAff > 1.0 - pol_bound && pBff <  pol_bound)
                                                &&
                                                (pAfm > .5 - pol_bound && pBfm < pol_bound)
                                            )
                                    {
                                        state = 5;
                                    }
                                    else if (
                                                (pAff < pol_bound && pBff > 1.0 - pol_bound)
                                                &&
                                                (pAfm < pol_bound && pBfm > 0.5 - pol_bound)
                                            )
                                    {
                                        state = 6;
                                    }


                                    pe = x1 + x3;
                                    qe = x3 + x4;
                                    ps = .5 * (y1 + y3);
                                    qs = .5 * (y3 + y4);

                                    Dz = x1 * .5 * y4 + x4 * .5 * y1 - x2 * .5 * y3 - x3 * .5 * y2;
                                    Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                                    Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                                    Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));

                                    DataFile << t << ";" 
                                        << sAm << ";"
                                        << sAf << ";"
                                        << sBm << ";"
                                        << sBf << ";"
                                        << hAm << ";"
                                        << hAf << ";"
                                        << hBm << ";"
                                        << hBf << ";"
                                        << em << ";"
                                        << ef << ";"
                                        << y1 << ";" 
                                        << y2 << ";" 
                                        << y3 << ";" 
                                        << y4 << ";" 
                                        << y5 << ";" 
                                        << x1 << ";" 
                                        << x2 << ";" 
                                        << x3 << ";" 
                                        << x4 << ";" 
                                        << pAmf << ";" 
                                        << pAff << ";" 
                                        << pBmf << ";" 
                                        << pBff << ";" 
                                        << pAmm << ";" 
                                        << pAfm << ";" 
                                        << pBmm << ";" 
                                        << pBfm << ";" 
                                        << pAm << ";"
                                        << pAf << ";"
                                        << pBm << ";"
                                        << pBf << ";"
                                        << Dz << ";" 
                                        << Dzprime << ";" 
                                        << state << ";" 
                                        << endl;

                                    break;
                                }
                                else
                                {
                                    y1 = y1tplus1;
                                    y2 = y2tplus1;
                                    y3 = y3tplus1;
                                    y4 = y4tplus1;
                                    y5 = y5tplus1;
                                    x1 = x1tplus1;
                                    x2 = x2tplus1;
                                    x3 = x3tplus1;
                                    x4 = x4tplus1;
                                }
                            }

                            // no convergence, odd.
                            if (t==maxt)
                            {
                                    pAmf = x3 + x4;
                                    pAff = x1 + x2;
                                    pBmf = x2 + x4;
                                    pBff = x1 + x3;
                                    
                                    pAmm = y3 + y4;
                                    pAfm = y1 + y2;
                                    pBmm = y2 + y4;
                                    pBfm = y1 + y3;

                                    pAm = (x3 + x4 + y3 + y4)/2;
                                    pAf = (x1 + x2 + y1 + y2)/2;
                                    pBm = (x2 + x4 + y2 + y4)/2;
                                    pBf = (x1 + x3 + y1 + y3)/2;
                                    
                                    state = -1;

                                    if (pAmf >= pol_bound && 
                                            pAmf <= 1.0 - pol_bound && 
                                            pBmf >= pol_bound &&
                                            pBmf <= 1.0 - pol_bound &&
                                            pAmm >= pol_bound && 
                                            pAmm <= 0.5 - pol_bound && 
                                            pBmm >= pol_bound &&
                                            pBmm <= 0.5 - pol_bound)
                                    {
                                        state = 1;
                                    }
                                    else if (pAmf > 1.0 - pol_bound &&
                                            pBmf > 1.0 - pol_bound &&
                                            pAmm > 0.5 - pol_bound &&
                                            pBmm > 0.5 - pol_bound)
                                    {
                                        state = 2;

                                    }
                                    else if (pAff >= 1.0 - pol_bound &&
                                            pBff >= 1.0 - pol_bound &&
                                            pAfm >= 0.5 - pol_bound &&
                                            pBfm >= 0.5 - pol_bound)
                                    {
                                        state = 3;
                                    }
                                    else if (
                                            (
                                                ((pAff > 1.0 - pol_bound || pAff < pol_bound) &&
                                                pBff >= pol_bound &&
                                                pBff <= 1.0 - pol_bound) 
                                                ||
                                                ((pBff > 1.0 - pol_bound || pBff < pol_bound) &&
                                                pAff >= pol_bound &&
                                                pAff <= 1.0 - pol_bound)
                                            ) &&
                                            (
                                                ((pAfm > 0.5 - pol_bound || pAfm < pol_bound) &&
                                                pBfm >= pol_bound &&
                                                pBfm <= 0.5 - pol_bound) 
                                                ||
                                                ((pBfm > 0.5 - pol_bound || pBfm < pol_bound) &&
                                                pAfm >= pol_bound &&
                                                pAfm <= 0.5 - pol_bound)
                                            )
                                    )
                                    {
                                        state = 4;
                                    }
                                    else if (
                                                (pAff > 1.0 - pol_bound && pBff <  bound)
                                                &&
                                                (pAfm > .5 - pol_bound && pBfm < bound)
                                            )
                                    {
                                        state = 5;
                                    }
                                    else if (
                                                (pAff < pol_bound && pBff > 1.0 - bound)
                                                &&
                                                (pAfm < pol_bound && pBfm > 0.5 - bound)
                                            )
                                    {
                                        state = 6;
                                    }


                                    pe = x1 + x3;
                                    qe = x3 + x4;
                                    ps = .5 * (y1 + y3);
                                    qs = .5 * (y3 + y4);


                                    Dz = x1 * .5 * y4 + x4 * .5 * y1 - x2 * .5 * y3 - x3 * .5 * y2;
                                    Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                                    Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                                    Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));

                                    DataFile << t << ";" 
                                        << sAm << ";"
                                        << sAf << ";"
                                        << sBm << ";"
                                        << sBf << ";"
                                        << hAm << ";"
                                        << hAf << ";"
                                        << hBm << ";"
                                        << hBf << ";"
                                        << em << ";"
                                        << ef << ";"
                                        << y1 << ";" 
                                        << y2 << ";" 
                                        << y3 << ";" 
                                        << y4 << ";" 
                                        << y5 << ";" 
                                        << x1 << ";" 
                                        << x2 << ";" 
                                        << x3 << ";" 
                                        << x4 << ";" 
                                        << pAmf << ";" 
                                        << pAff << ";" 
                                        << pBmf << ";" 
                                        << pBff << ";" 
                                        << pAmm << ";" 
                                        << pAfm << ";" 
                                        << pBmm << ";" 
                                        << pBfm << ";" 
                                        << pAm << ";"
                                        << pAf << ";"
                                        << pBm << ";"
                                        << pBf << ";"
                                        << Dz << ";" 
                                        << Dzprime << ";" 
                                        << state << ";" 
                                        << endl;

                                    break;
                            }

        } // sAf
    } // sAm

    DataFile << endl << endl 
                    << "type;" << "xlinked" << endl
                   << "r;" <<  r << endl
                   << "hAm;" <<  hAm  << endl
                   << "sAm;" << sAm << endl
                   << "hBm;" << hBm  << endl
                   << "sBm;" << sBm  << endl
                   << "em;" << em << endl
                   << "hAf;" << hAf  << endl
                   << "sAf;" << sAf  << endl
                   << "hBf;" << hBf  << endl
                   << "sBf;" << sBf  << endl
                   << "ef;" << ef << endl;
}
