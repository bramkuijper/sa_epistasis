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
    double hAm;
    double sAm;
    double hBm;
    double sBm;
    double em;
    
    double hAf;
    double sAf;
    double hBf;
    double sBf;
    double ef;
    
    double r = atof(argv[1]);

    double x1, x2, x3, x4;
    double y1, y2, y3, y4;
    double wM, wF, Dz, De;
    double pAff, pAfm, pAmf, pAmm;
    double pAf, pAm, pBf, pBm;
    double pBff, pBfm, pBmf, pBmm;

    double x1tplus1, x2tplus1, x3tplus1, x4tplus1;
    double y1tplus1, y2tplus1, y3tplus1, y4tplus1;

    double bound = 1e-12;
    int maxt = 10000000;

    int t = 0;

    DataFile << "time;sAm;sAf;sBm;sBf;hAm;hAf;hBm;hBf;em;ef;y1;y2;y3;y4;x1;x2;x3;x4;pAmf;pAff;pBmf;pBff;pAmm;pAfm;pBmm;pBfm;pAm;pAf;pBm;pBf;Dz;De;" << endl;

    for (sAm = 0; sAm <= 0.5; sAm += 0.05)
    {
        for (sAf = 0; sAf <= 0.5; sAf += 0.05)
        {
            cout << sAm << " " << sAf << endl;
            for (hAm = 0.5; hAm <= 0.5; hAm += 0.25)
            {
                for (hAf = 0.5; hAf <= 0.5; hAf += 0.25)
                {
                    for (em = 0; em >= -0.1; em -= 10)
                    {
                        x1 = 0.5;
                        x2 = 0; 
                        x3 = 0.5;
                        x4 = 0;

                        y1 = 0.5;
                        y2 = 0; 
                        y3 = 0.5;
                        y4 = 0;

                        ef = em;
                        sBm = 0;//sAm;
                        sBf = 0;//sAf;
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

                            Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                            De = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;

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
                                    << De << ";" << endl;

                                break;
                            }
                            else
                            {
                                y1 = y1tplus1;
                                y2 = y2tplus1;
                                y3 = y3tplus1;
                                y4 = y4tplus1;
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


                            Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                            De = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;

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
                                    << De << ";" << endl;
                        }
                    }// e
                } // hAf
            } // hAm
        } // sAf
    } // sAm

    DataFile << endl << endl 
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
