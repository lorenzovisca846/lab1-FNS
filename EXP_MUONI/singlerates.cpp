#include <iostream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TF1.h>

using namespace std;

void singlerates()
{
    double V1[]         = {1889., 1949., 2000.,  2049.,  2098.,  2151.,  2201.,  2248.,   2301.,   2352.,    2401.,    2448.}; //->2030-2050
    double count1[]     = {1440., 5816., 15406., 30816., 45665., 43004., 64865., 135611., 221668., 299716.,  373598.,  465228.};

    double V2[]         = {1907., 1948., 2000.,  2050.,  2100.,  2150.,  2200.,  2256.,   2304.,   2351.,    2403.,    2452.}; //->2300
    double count2[]     = {10.,   34.,   94.,    259.,   1288.,  2350.,  3803.,  5845.,   9404.,   21344.,   49705.,   85101.};

    double V3[]         = {1911., 1954., 2004.,  2050.,  2100.,  2151.,  2204.,  2248.,   2299.,   2352.,    2399.,    2452.}; //->2150
    double count3[]     = {101.,  373.,  854.,   1844.,  3545.,  3515.,  5298.,  7060.,   29626.,  103336.,  139290., 255026};

    double VG[]         = {1298., 1354., 1398.,  1448.,  1501.,  1552.,  1599.,  1652.,   1701.,   1749.,    1803.,    1852.};
    double countG[]     = {568.,  1901., 3410.,  4955.,  6403.,  7518.,  27600., 161087., 570745., 1337899., 3061221., 6406712};

    double T[]          = {300.,  300.,  300.,   300.,   300.,   200.,   200.,   200.,    200.,    200.,     200.,     200.};

    const int Ndata = sizeof(V1) / sizeof(double);
    double errV1[Ndata], errV2[Ndata], errV3[Ndata], errVG[Ndata];
    double errcount1[Ndata], errcount2[Ndata], errcount3[Ndata], errcountG[Ndata];

    for(int i=0; i<Ndata; i++)
    {
        errV1[i] = 5.;
        errV2[i] = 5.;
        errV3[i] = 5.;
        errVG[i] = 5.;

        T[i] /= 300.;

        errcount1[i] = sqrt(count1[i]);
        errcount2[i] = sqrt(count2[i]);
        errcount3[i] = sqrt(count3[i]);
        errcountG[i] = sqrt(countG[i]);
    
        count1[i] /= T[i];
        count2[i] /= T[i];
        count3[i] /= T[i];
        countG[i] /= T[i];
    }

    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
    TCanvas* c3 = new TCanvas("c3", "c3", 800, 600);
    TCanvas* c4 = new TCanvas("c4", "c4", 800, 600);


    TGraphErrors* gr1 = new TGraphErrors(Ndata, V1, count1, errV1, errcount1);
    TGraphErrors* gr2 = new TGraphErrors(Ndata, V2, count2, errV2, errcount2);
    TGraphErrors* gr3 = new TGraphErrors(Ndata, V3, count3, errV3, errcount3);
    TGraphErrors* grG = new TGraphErrors(Ndata, VG, countG, errVG, errcountG);

    c1->SetLogy();
    c2->SetLogy();
    c3->SetLogy();
    c4->SetLogy();

    c1->cd();
    gr1->SetLineColor(kRed);
    gr1->SetMarkerColor(kRed);
    gr1->SetTitle("Conteggi S1");
    gr1->GetXaxis()->SetTitle("V [V]");
    gr1->GetYaxis()->SetTitle("Normalized counts");
    gr1->Draw("APL");

    c2->cd();
    gr2->SetLineColor(kBlue);
    gr2->SetMarkerColor(kBlue);
    gr2->SetTitle("Conteggi S2");
    gr2->GetXaxis()->SetTitle("V [V]");
    gr2->GetYaxis()->SetTitle("Normalized counts");
    gr2->Draw("APL");

    c3->cd();
    gr3->SetLineColor(kGreen+2);
    gr3->SetMarkerColor(kGreen+2);
    gr3->SetTitle("Conteggi S3");
    gr3->GetXaxis()->SetTitle("V [V]");
    gr3->GetYaxis()->SetTitle("Normalized counts");
    gr3->Draw("APL");

    c4->cd();
    grG->SetLineColor(kBlack);
    grG->SetMarkerColor(kBlack);
    grG->SetTitle("Conteggi SG");
    grG->GetXaxis()->SetTitle("V [V]");
    grG->GetYaxis()->SetTitle("Normalized counts");
    grG->Draw("APL");

}
