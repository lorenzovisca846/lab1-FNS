#define _USE_MATH_DEFINES

#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>   

#include "TH1F.h"
#include "TF1.h"
#include "TLine.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;

void Eff_Vthr_(){

const int nmisure = 7;
    float T[] = {100,100,100,100,100,100,100}; //tempo
    float B[] = {12034,2187,4216,951,316,208,2931}; //conteggi di B
    float AC[] = {110,105,109,98,93,119,111}; //conteggi AC
    float ABC[] = {109,97,106,72,31,22,108}; //conteggi di ABC
    float THR[] = {0.0530,0.1510,0.1011,0.2509,0.4023,0.509,0.1223}; //Tensione di soglia espressa in VOLT
    float R1[nmisure] = {};
    float R2[nmisure] = {};
    float R3[nmisure] = {};
    float sR1[nmisure] = {};
    float sR2[nmisure] = {};
    float sR3[nmisure] = {};
    float sT[nmisure] = {0.001,0.001,0.001,0.001,0.001,0.001,0.001};  //errore associato ai tempi dello scaler, equivale alla sua risoluzione
    float sB[nmisure] = {};
    float sAC[nmisure] = {};
    float sABC[nmisure] = {};
    float sTHR[nmisure] = {};
    float EFF[nmisure] = {};
    float sEFF[nmisure] = {};
    
//Calcolo dell'errore sulla tensione di SOGLIA
    for(int i=0; i<nmisure; ++i){
        sTHR[i] = THR[i]*0.001 + 5e-4;
        cout << "\nMISURA DELLA TENSIONE DI SOGLIA NUMERO  " << i << " : Vthr = " << THR[i] << "\t sHV = " << sTHR[i] << endl;
    };

    cout << "|---------------------------------------------------|";
 
//Calcolo dell'errore sui conteggi
for(int i=0; i<nmisure; ++i){
        sB[i] = sqrt(B[i]);
        cout << "\nMISURA CONTEGGIO " << i << " : B = " << B[i] << "\t sB = " << sB[i] << endl;
    };

    cout << "|---------------------------------------------------|";
 
 for(int i=0; i<nmisure; ++i){
        sAC[i] = sqrt(AC[i]);
        cout << "\nMISURA CONTEGGIO " << i << " : AC = " << AC[i] << "\t sAC = " << sAC[i] << endl;
    };

    cout << "|---------------------------------------------------|";

for(int i=0; i<nmisure; ++i){
        sABC[i] = sqrt(ABC[i]);
        cout << "\nMISURA CONTEGGIO " << i << " : ABC = " << ABC[i] << "\t sABC = " << sABC[i] << endl;
    };

    cout << "|---------------------------------------------------|";
//RATE di B (R1), RATE di AC (R2), RATE di ABC (R3) con i relativi errori
for(int i=0; i<nmisure; ++i){
        R1[i] = B[i]/T[i];
        sR1[i] = sqrt(pow((B[i]/(T[i]*T[i]))*sT[i], 2) + pow((1/T[i])*sB[i], 2));
        cout << "\nMISURA DI RATE B " << i << " : R1 = " << R1[i] << "\t sR1 = " << sR1[i] << endl;
    };

    cout << "|---------------------------------------------------|";
 
for(int i=0; i<nmisure; ++i){
        R2[i] = AC[i]/T[i];
        sR2[i] = sqrt(pow((AC[i]/(T[i]*T[i]))*sT[i], 2) + pow((1/T[i])*sAC[i], 2));

    cout << "\nMISURA DI RATE AC " << i << " : R2 = " << R2[i] << "\t sR2 = " << sR2[i] << endl;
   
    };

    cout << "|---------------------------------------------------|";
       
for(int i=0; i<nmisure; ++i){
        R3[i] = ABC[i]/T[i];
        sR3[i] = sqrt(pow((ABC[i]/(T[i]*T[i]))*sT[i], 2) + pow((1/T[i])*sABC[i], 2));
        cout << "\nMISURA DI RATE ABC  " << i << " : R3 = " << R3[i] << "\t sR3 = " << sR3[i] << endl;
    };

    cout << "|---------------------------------------------------|";

//Calcolo dell'efficienza EFF e del suo errore sEFF
  for(int i=0; i<nmisure; ++i){
        EFF[i] = R3[i]/R2[i];
        sEFF[i] = sqrt((EFF[i]*(1-EFF[i]))/AC[i]);

 cout << "\nMISURA DI EFFICIENZA " << i << ": Eff = " << EFF[i] << "\t sEFF = " << sEFF[i] << endl;
    };

    cout << "|---------------------------------------------------|";
 
TCanvas *cEthr= new TCanvas("cEthr","Eff(Vthr)",0,1,600,400); //inserire le dimensioni in base ai dati raccolti
    cEthr->SetFillColor(0);
    cEthr->cd();

TGraphErrors *gEthr1 = new TGraphErrors(7,THR,EFF,sTHR,sEFF);
   ;
    gEthr1->SetMarkerSize(0.6);
    gEthr1->SetMarkerStyle(21);
   
    gEthr1->SetTitle("Eff(Vthr)");
    gEthr1->GetXaxis()->SetTitle("Vthr (V)");
    gEthr1->GetYaxis()->SetTitle("Eff(ADIM)");
   
    gEthr1 ->Draw("AP ");


     gEthr1->GetXaxis()->SetRangeUser(-0.1,0.600);
     gEthr1->GetYaxis()->SetRangeUser(0.001,1.10);
     cEthr -> Update();

    TF1 *funz1 = new TF1("funz1","[0]/(1+exp([1]*(x-[2])))",0.04,0.600); //ho usato una funzione che si chiama logistica
  
    funz1->SetParameter(0, 0.5); // Ampiezza iniziale
    funz1->SetParameter(1, 13); // Pendenza iniziale
    funz1->SetParameter(2, 0.2); // Centro iniziale

    funz1->SetParLimits(0, 0.1, 2); // Limite per l'ampiezza
    funz1->SetParLimits(1, 1, 510); // Limite per la pendenza
    funz1->SetParLimits(2, 0.1, 0.45); // Limite per il centro


    funz1->SetLineColor(2);
    
     TFitResultPtr  fit_res = gEthr1->Fit(funz1,"RMS+");

     fit_res->PrintCovMatrix(cout);
     gStyle->SetOptFit(1111);


cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}
   
  

