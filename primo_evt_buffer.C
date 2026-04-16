#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

#include <iomanip>
#include <bitset>

using namespace std;

int primo_evt_buffer(string inputfile="test.txt")
{
	//definisco alcune variabili
	int Q, n_evt,evt_lenght, totevt=0;
	size_t pos_finale;
	string line;
	int contatore=0;
	int limite=15;
	
		
		//apro il file
		TFile *out_file= new TFile("out_file.root","RECREATE");
	
	fstream evtfile(inputfile.c_str(), ios::in);
	if(evtfile.is_open())
	{
		
		while (contatore < limite)
		//while(!evtfile.eof())
		{
		/*	if(totevt%10000==0)
			    cout<<"Evt number "<<totevt<<endl;*/
	

	getline(evtfile, line);
	contatore++;
	
	
	//leggo la lunghezza dell'evento
	string p1 = line.substr(0, 4);
        unsigned int dec1 = stoul(p1, nullptr, 16);
                
        evt_lenght=dec1/16;
        
        // leggo il numero dell'evento
        string p2 = line.substr(4, 8);     //l'esadecimale è da leggere tutto insieme?
        unsigned int n_evt = stoul(p2, nullptr, 16);

        // leggo Q e lo trasformo in binario
        string p3 = line.substr(12, 2);
        unsigned int dec3 = stoul(p3, nullptr,16);
        bitset<8> binario(dec3);
        
        cout << "--------------- Prima riga ---------------" << endl;
        cout << "La lunghezza di un evento è " << p1 << " -> " << evt_lenght << " righe" <<endl;
        cout << "Evento numero: " << p2 << " -> " << n_evt << endl;
        cout << "Il valore Q è " << p3 << " -> " << dec3 << " -> " << binario << endl;
       
        
        
        cout << "------------------ ASCII ------------------";
        
        //trasformo in ASCII il resto della riga
        for (size_t i = 16; i < line.length(); i += 2) {
            // prendo i caratteri a coppie
            string byteStr = line.substr(i, 2);
            
            // li converto in ASCII
            char c = (char)stoul(byteStr, nullptr, 16);
            
            // stampo se è leggibile, altrimenti un punto
            //if (isprint((unsigned char)c)) cout << c;
            //else cout << ".";
        }
        cout << endl;
        
       //Leggo le restanti righe
		for (int i=1; i<evt_lenght; i++){
			getline(evtfile, line);
			contatore++;
			
			for (size_t j = 0; j < line.length(); j += 2) {
				string byteStr = line.substr(j, 2);
				char c = (char)stoul(byteStr, nullptr, 16);
				if (isprint((unsigned char)c)) cout << c;
				else cout << ".";	
			}
			cout<<endl; //se voglio che vada a capo dopo ogni riga
			
		} cout<<endl;
	}}
         evtfile.close();
	
	
	return 0;
}
