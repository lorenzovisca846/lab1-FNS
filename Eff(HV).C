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

void Eff_HV_(){

const int nmisure = 9;
    float T[] = {100,200,200,200,100,100,100,100,100}; //tempo
    float B[] = {50,721,1655,3466,3228,5530,9632,17722,56618}; //conteggi di B
    float AC[] = {112,178,204,204,110,111,98,99,106}; //conteggi AC
    float ABC[] = {2,68,130,179,108,108,97,96,105}; //conteggi di ABC
    float HV[] = {1399,1524,1585,1645,1705,1764,1824,1886,2000}; //Tensione di alimentazione
    float R1[nmisure] = {};
    float R2[nmisure] = {};
    float R3[nmisure] = {};
    float sR1[nmisure] = {};
    float sR2[nmisure] = {};
    float sR3[nmisure] = {};
    float sT[] = {0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001};  //errore associato ai tempi dello scaler, equivale alla sua risoluzione
    float sB[nmisure] = {};
    float sAC[nmisure] = {};
    float sABC[nmisure] = {};
    float sHV[nmisure] = {};
    float EFF[nmisure] = {};
    float sEFF[nmisure] = {};
    
//Calcolo dell'errore sulla tensione di alimentazione
    for(int i=0; i<nmisure; ++i){

        sHV[i] = HV[i]*0.001 + 5;
        
        cout << "\nMISURA DI HV NUMERO  " << i << " : HV = " << HV[i] << "\t sHV = " << sHV[i] << endl;
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
 
TCanvas *cEhv= new TCanvas("cEhv","Eff(HV)",0,1,600,400); //inserire le dimensioni in base ai dati raccolti
    cEhv->SetFillColor(0);
    cEhv->cd();

TGraphErrors *gEhv1 = new TGraphErrors(10,HV,EFF,sHV,sEFF);
   ;
    gEhv1->SetMarkerSize(0.6);
    gEhv1->SetMarkerStyle(21);
   
    gEhv1->SetTitle("Eff(HV)");
    gEhv1->GetXaxis()->SetTitle("HV (V)");
    gEhv1->GetYaxis()->SetTitle("Eff(ADIM)");
   
    gEhv1 ->Draw("AP ");


     gEhv1->GetXaxis()->SetRangeUser(1250,2150);
     gEhv1->GetYaxis()->SetRangeUser(0.001,1.10);
     cEhv -> Update();

    TF1 *funz1 = new TF1("funz1","[0]/(1+exp(-((x - [1])/[2])))",1250,2024);
  
    funz1->SetParameter(0,0.5); // Parametro 0, ampiezza della sigmoide
    funz1->SetParameter(1,1500); // Parametro 1, pendenza
    funz1->SetParameter(2,1500);  // Parametro 2, Centro

    funz1->SetParLimits(0,0.1,1);   // Limiti per il parametro 0
    funz1->SetParLimits(1,1200,1800); // Limiti per il parametro 1
    funz1->SetParLimits(2,50,200);    // Limiti per il parametro 2


    funz1->SetLineColor(2);
    
     TFitResultPtr  fit_res = gEhv1->Fit(funz1,"RMS+");

     fit_res->PrintCovMatrix(cout);
     gStyle->SetOptFit(1111);


cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}
   
  

