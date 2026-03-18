
// PER COMPILARE ED ESEGUIRE
// clang++ provahex.cpp -o provahex && ./provahex

#include <iostream>
#include <iomanip>
#include <cstdint>     // definisce i tipi uint8_t (1 byte), uint16_t (2 byte), uint32_t (4 byte), uint64_t (8 byte)

void print_bytes(const void* ptr, size_t size);

int main()
{
    //Scrivendo uint32_t definisco semplicemente un unsigned int ma la cui grandezza non varia con il compilatore, bensì è fissata e vale 32bit = 4byte
    //Se assegno un valore intero che inizia con 0x gli sto dando un esadecimale
    uint32_t val = 0xA1B2C3D4;

    //Con iomanip se faccio [ cout << hex << val ] lo stampa in esadecimale
    //Dopo devo tornare alla visualizzazione standard con [ cout << dec ] 
    std::cout << "  decimale  : " << val << "\n";
    std::cout << "  esadec.   : 0x" << std::hex << val << std::dec << "\n";

    //La funzione print_bytes stampa i singoli bytes VAI A VEDERLA ADESSO O TE LA DIMENTICHI
    //Una coppia di numeri esadecimali definisce un byte
    //Apple Silicon e gli intel sono little endian, quindi il primo byte è quello più a destra nella definizione (il meno significativo, Least Significant Byte LSB)
    std::cout << "\nSTAMPA BYTES (little endian):\n";
    print_bytes(&val, sizeof(val));

    //Stampiamo di nuovo il primo byte (Che è LSB, ciò dipende dal fatto che la macchina è little endian)
    //In questo caso il cast non è static ma reinterpret, quindi se ne sbatte del fatto che &val è un puntatore ad un intero a 4 bytes, lo tratta come un puntatore ad un intero a un byte
    uint8_t* p = reinterpret_cast<uint8_t*>(&val);
    std::cout << "\n=== accesso via puntatore ===\n";
    std::cout << " Indirizzo LSB: 0x"
              << std::hex  << std::setw(2) << std::setfill('0')
              << (unsigned)p[0]
              << std::dec << "\n";

    //Questa tecnica non richiede la conoscenza dell'endianness della macchina e dei dati.
    //La sintassi [ val >> (n * 8) ] vuol dire: shiftati a destra di 8*n bit (ovvero n bytes), ovvero butta via gli n bytes più a destra del valore logico (indipendentemente da come questi bytes si dispongono nella memoria)
    //Facendo [risultato & 0xFF] si applica una maschera: 0xFF è il byte 11111111; essendo di fianco ad un intero a 4 byte diventa    00000000 00000000 00000000 11111111
    // & è l'operatore AND bit per bit: facendo [ risultato & 0xFF ] in pratica si estrae l'ultimo byte di risultato (perché tutti gli altri sono azzerati dall'and con 00 00 00 FF)
    std::cout << "\n=== shift + maschera (endianness-safe) ===\n";
    for (int n = 0; n < 4; ++n)
    {
        uint8_t byte_n = (val >> (n * 8)) & 0xFF;
        std::cout << "  byte logico [" << n << "] = 0x"
                  << std::hex << std::setw(2) << std::setfill('0')
                  << (unsigned)byte_n << std::dec << "\n";
    }

    //Salviamo come prima i singoli bytes dal meno al più significativo (! indipendente da come sono disposti in memoria)
    uint8_t b0 = (val >> 8*0) & 0xFF;    // 0xD4
    uint8_t b1 = (val >> 8*1) & 0xFF;    // 0xC3
    uint8_t b2 = (val >> 8*2) & 0xFF;    // 0xB2
    uint8_t b3 = (val >> 8*3) & 0xFF;    // 0xA1

    //Ora cerchiamo di ricostruire un numero dai singoli bytes: per farlo, ogni byte deve essere castato a un oggetto di 4 bytes.
    //I bits che erano stati traslati verso destra vengono ritraslati a sinistra con <<
    //Per combinare i 4 bytes (che hanno già l'offset) in un unico oggetto a 4 bytes si sovrappongono con | che è l'operatore OR bit per bit
    uint32_t ricostruito =
        (static_cast<uint32_t>(b3) << 8*3) |
        (static_cast<uint32_t>(b2) << 8*2) |
        (static_cast<uint32_t>(b1) << 8*1) |
        (static_cast<uint32_t>(b0) << 8*0);

    std::cout << "\n=== ricostruzione ===\n";
    std::cout << "  originale   : 0x" << std::hex << val         << std::dec << "\n";
    std::cout << "  ricostruito : 0x" << std::hex << ricostruito << std::dec
              << (ricostruito == val ? "  OK" : "  ERRORE!") << "\n";

    return 0;
}



// ─────────────────────────────────────────────
//  Stampa i byte di qualsiasi variabile
// ─────────────────────────────────────────────

//size_t di fatto è un unsigned int, è il tipo standard quando si richiama sizeof()
//sizeof() restituisce la dimensione di val, che essendo un unsigned int32 restituisce 4 (ha 4 bytes)
//il puntatore void serve ad accettare un tipo generico, il casting viene fatto dopo
void print_bytes(const void* ptr, size_t size)
{
    
    //Qui il puntatore viene castato a un unsigned int a 1 byte
    const uint8_t* bytes = static_cast<const uint8_t*>(ptr);

    std::cout << "  byte#   hex\n"
              << "  ─────  ────\n";
    for (size_t i = 0; i < size; ++i)
    {

        //Questioni grafiche a parte qui ci sono due concetti importanti:
        //1) (unsigned) è un tecnicismo necessario perché sto trattando un intero a un byte, cout lo tratta come un carattere ASCII
        //2) la sintassi bytes[0] equivale a *bytes, ovvero il valore a cui punta il puntatore. Ciò che viene puntato è il primo byte del valore.
        //3) la sintassi bytes[i] equivale a *(bytes+i), ovvero il valore puntato spostandosi di i a partire da bytes. Visto che il tipo puntato da bytes è un intero a 1 byte, con +i ci si sposta di un byte alla volta
        std::cout << "  [" << i << "]    0x"
            << std::hex << std::setw(2) << std::setfill('0')
            << (unsigned)bytes[i]
            << std::dec << "\n";
    }
}