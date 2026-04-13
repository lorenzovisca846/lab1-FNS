#include <iostream>
#include <TGraphErrors.h>

using namespace std;

void singlerates()
{
    double V1[]         = {};
    double count1[]     = {};

    double V2[]         = {};
    double count2[]     = {};

    double V3[]         = {};
    double count3[]     = {};

    double VG[]         = {};
    double countG[]     = {};


    const int Ndata = sizeof(V1) / sizeof(double);
    double errV1[Ndata], errV2[Ndata], errV3[Ndata], errVG[Ndata];
    double errcount1[Ndata], errcount2[Ndata], errcount3[Ndata], errcountG[Ndata];

    for(int i=0; i<Ndata; i++)
    {
        errV1[i] = 5.;
        errV2[i] = 5.;
        errV3[i] = 5.;
        errVG[i] = 5.;

        errcount1[i] = sqrt(count1[i]);
        errcount2[i] = sqrt(count2[i]);
        errcount3[i] = sqrt(count3[i]);
        errcountG[i] = sqrt(countG[i]);
    }
}
