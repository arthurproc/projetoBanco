#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED
#include <fstream>
using namespace std;
const long int NUMCLIENTES=10;
struct Clientes
{
    char Nome[30];
    int NumeroConta;
    float Saldo;
};
void Menu();

bool ValidaConta(int NumConta, Clientes cadastro[NUMCLIENTES], int &i);

void CriaCadastro(Clientes cadastro[NUMCLIENTES],int &quantAtiva, int &quantRegistrada );

void MovimentacaoConta(Clientes cadastro[NUMCLIENTES]);

void imprimeContas(Clientes cadastro[NUMCLIENTES], int quantAtiva);

void ExcluirConta(Clientes cadastro[NUMCLIENTES], int &quantAtiva);

void LeSalvos(ifstream &ifs, Clientes cadastro[NUMCLIENTES], int &quantAtiva, int &quantRegistrada);

void gravaClientes(ofstream &ofs, Clientes cadastro[NUMCLIENTES], int quantAtiva, int quantRegistrada);


#endif // BANCO_H_INCLUDED
