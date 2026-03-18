// PER COMPILARE ED ESEGUIRE
// clang++ letturahex letturahex.cpp && ./letturahex

#include <iostream>
#include <fstream>
#include <cstdint>

/*
Esempio: il file test.dat contiene dati esadecimali relativi a 50 eventi. Ogni evento è costruito nel seguente modo:
[ valore 1 (unsigned int 16bit)]
[ valore 2 (unsigned int 16bit)]
[ valore 3 (unsigned int 32bit)]
[ 4 bytes vuoti (contenenti zeri)]

Calcolare le medie per i tre set di valori.

!I valori nel file sono scritti in big endian, vanno convertiti a little endian
*/



//Funzioni di swap, implementate in fondo
uint16_t swapEndian16(uint16_t v);
uint32_t swapEndian32(uint32_t v);

int main()
{
    //Numero di eventi
    const int N = 50;

    //Grandezza in bytes di un evento
    const int RECORD_SIZE  = 12;

    //Numero di bytes vuoti
    const int PADDING_SIZE =  4;

    //La flag binary nella dichiarazione del file evita di interpretare gli escape characters solitamente presenti in un file di testo
    std::ifstream file("test.dat", std::ios::binary);
    if (!file) {
        std::cerr << "Errore apertura file\n";
        return 1;
    }

    double sommaA = 0, sommaB = 0, sommaC = 0;

    for (int i = 0; i < N; i++)
    {

        //Ci si posiziona al byte numero i*RECORD_SIZE, ovvero all'inizio dell'i-esimo record (partendo da zero)
        //ios::beg significa che il valore precedente va inteso rispetto all'inizio del file
        file.seekg(i * RECORD_SIZE, std::ios::beg);

        uint16_t A, B;
        uint32_t C;

        //Quello che viene fatto con reinterpret_cast<char*>(&A) è puntare al primo byte di A
        //A quel punto la funzione file.read scrive all'indirizzo puntato quello che legge dal file, e lo fa per un numero di byte dato dal secondo argomento (in questo caso sizeof(A) ovvero 2 bytes)
        file.read(reinterpret_cast<char*>(&A), sizeof(A));

        //In questo caso non serve fare seekg, ma solo perché sappiamo che all'interno del file ciò che va dentro B è sequenzialmente appena dopo A. Lo stesso vale per C
        file.read(reinterpret_cast<char*>(&B), sizeof(B));
        file.read(reinterpret_cast<char*>(&C), sizeof(C));

        //Queste funzioni convertono da big a little endian
        A = swapEndian16(A);
        B = swapEndian16(B);
        C = swapEndian32(C);

        sommaA += A;
        sommaB += B;
        sommaC += C;
    }

    file.close();

    std::cout << "Media A (uint16): " << sommaA / N << "\n";
    std::cout << "Media B (uint16): " << sommaB / N << "\n";
    std::cout << "Media C (uint32): " << sommaC / N << "\n";

    return 0;
}


uint16_t swapEndian16(uint16_t v)
{
    return ((v >> 8) & 0x00FF) |            //Manda il primo byte nel secondo
           ((v << 8) & 0xFF00);             //Manda il secondo byte nel primo
}

uint32_t swapEndian32(uint32_t v)
{
    return ((v >> 8*3) & 0x000000FF) |      //Manda il primo byte nel quarto
           ((v >> 8*1) & 0x0000FF00) |      //Manda il secondo byte nel terzo
           ((v << 8*1) & 0x00FF0000) |      //Manda il terzo byte nel secondo
           ((v << 8*3) & 0xFF000000);       //Manda il quarto byte nel primo
}