/*Grupo: Arthur Procópio(34464), Tyago Augusto(33621), Fabrício Gonçalves do Carmo (35007)
Data: 22/06/15
Descrição do programa: O programa a seguir realiza as principais tarefas de um banco comum,
ele armazena dados do cliente e seu saldo, e realiza seus saques e depósitos de todos auxiliados por um menu*/
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <ctime>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "banco.h"
#include <fstream>
using namespace std;
/*Recebe o numero da conta a ser pesquisado e o vetor de clientes, pesquisa se existe essa conta
e retorna verdadeiro caso exista e o indice dessa conta*/
bool ValidaConta(int NumConta, Clientes cadastro[NUMCLIENTES], int &i)
{
    for (i=0; i<NUMCLIENTES; i++)
    {
        if (NumConta==cadastro[i].NumeroConta)

            return true;
    }
    return false;
}
void dormir( clock_t wait )//Funcao para pausar a execucao do programa
{
    clock_t goal = ( wait + clock() );
    while( goal > clock() );
}
void CriaCadastro(Clientes cadastro[NUMCLIENTES],int &quantAtiva, int &quantRegistrada )//Cria um novo cadastro com saldo 0
{
    ofstream ofs;
    cout<<"Entre com o nome do cliente que deseja cadastrar: \n";
    fflush(stdin);
    gets(cadastro[quantAtiva].Nome);
    cadastro[quantAtiva].Saldo=0;
    cadastro[quantAtiva].NumeroConta=quantRegistrada+1;
    quantAtiva++;
    quantRegistrada++;
    system("cls");
    cout<<"\n                    Conta criada com sucesso!\n\n\n";
}
void gravaClientes(ofstream &ofs, Clientes cadastro[NUMCLIENTES], int quantAtiva, int quantRegistrada)
{
    ofs.open("ClientesSalvos", ios::binary);
    ofs.write((char*)&quantAtiva, sizeof(int));
    ofs.write((char*)&quantRegistrada, sizeof(int));
    for (int i = 0; i < quantAtiva; i++)
        ofs.write((char*)&cadastro[i], sizeof(cadastro[i]));
}
void LeSalvos(ifstream &ifs, Clientes cadastro[NUMCLIENTES], int &quantAtiva, int &quantRegistrada)
{
    ifs.open("ClientesSalvos", ios::binary);
    ifs.read((char*)&quantAtiva, sizeof(quantAtiva));
    ifs.read((char*)&quantRegistrada, sizeof(quantRegistrada));
    for (int i = 0; i < quantAtiva; i++)
        ifs.read((char*)&cadastro[i], sizeof(cadastro[i]));
}
void MovimentacaoConta(Clientes cadastro[NUMCLIENTES])//Dado o numero da conta movimenta saques ou depositos
{
    int op, i, Num;
    float Deposito, Saque;
    cout<<"Entre com o numero da conta: ";
    cin>>Num;
    if (ValidaConta(Num, cadastro, i))
        do
        {

            cout<<"Digite 1 para dealizar deposito\n"
                <<"Digite 2 para realizar um saque\n"
                <<"Digite 0 para voltar ao menu principal\n";
            cin>>op;

            system("cls");
            switch (op)
            {
            case 1:
                system("cls");
                cout<<"Entre com o valor que deseja depositar: ";
                cin>>Deposito;
                cadastro[i].Saldo=cadastro[i].Saldo+Deposito;
                system("cls");
                cout<<"Deposito efetuado com sucesso!\n"
                    <<"Saldo atual: "
                    <<cadastro[i].Saldo
                    <<endl;
                dormir(1000);
                 break;
            case 2:
                system("cls");
                cout<<"Entre com o valor que deseja sacar: ";
                cin>>Saque;
                if(Saque>cadastro[i].Saldo)
                {
                    system("cls");
                    cout<<"\n           Saldo insuficiente para saque\n\n";
                }
                else
                {
                    cadastro[i].Saldo=cadastro[i].Saldo-Saque;
                    system("cls");
                    cout<<"Saque efetuado com sucesso!\n"
                        <<"\nSaldo atual: "
                        <<cadastro[i].Saldo
                        <<endl;
                }
                dormir(1000);
                break;
            default:
                if(op!=0)
                {
                    cout<<"    Opção invalida!!\n";
                    cin>>op;
                }
                break;
            }
        }
        while(op!=0);

    else cout<<"\nNumero de conta invalido!\n";
    dormir(1000);
}
void imprimeContas(Clientes cadastro[NUMCLIENTES], int quantAtiva)//Imprime todas as contas ativas no banco e seus saldos
{
    system("cls");

    for(int x=0; x<quantAtiva; x++)
    {
        cout<<"Numero da conta: "<<cadastro[x].NumeroConta<<" "
            <<" Nome do Titular: "<<cadastro[x].Nome<<" Saldo: R$ "
            <<cadastro[x].Saldo <<endl;
    }
}
void ExcluirConta(Clientes cadastro[NUMCLIENTES], int &quantAtiva)//Dado o numero da conta a exclui
{
    int num, i, x;
    cout<<"Entre com o numero da conta a ser excluida: \n";
    cin>>num;

    if (ValidaConta(num, cadastro, i)&&cadastro[i].Saldo==0)
    {
        for (x=i; x<NUMCLIENTES; x++)
        {
            cadastro[x]=cadastro[x+1];
        }
        quantAtiva--;
        system("cls");
        cout<<"                 Conta excluida com exito!\n\n";
    }

    else
    {
        system("cls");
        cout<<"Impossivel excluir conta!\nSaldo maior que zero ou numero de conta inexistente\n\n";

    }
    dormir(1000);

}
void Menu()//Imprime um menu direcionando cada funcao a uma opcao especifica
{
    ifstream ifs;
    ofstream ofs;
    int op, quantAtiva=0, quantRegistrada=0;
    Clientes cadastro[NUMCLIENTES];
    LeSalvos(ifs, cadastro, quantAtiva, quantRegistrada);
    do
    {
        cout<<"______________________________MENU______________________________\n"
            <<"1-Inclusao de uma nova conta\n"
            <<"2-Exclusao de conta\n"
            <<"3-Movimentação de conta\n"
            <<"4-Lista de contas e saldos\n"
            <<"0-Sair\n\n"
            <<"\nEntre com uma opcao:\n";
        cin>>op;
        switch(op)
        {
        case 1:
            system("cls");
            if (NUMCLIENTES==quantAtiva)

                cout<<"Numero maximo atingido!\n";

            else
                CriaCadastro(cadastro, quantAtiva, quantRegistrada);
            dormir(1000);

            break;
        case 2:
            if (quantAtiva>0)
            {
                system("cls");
                ExcluirConta(cadastro, quantAtiva);
            }
            else
                cout<<"Nenhuma conta ativa no momento\n";
            dormir(1000);
            break;
        case 3:
            if (quantAtiva>0)
            {
                system("cls");
                MovimentacaoConta(cadastro);
            }
            else
                cout<<"Nenhuma conta ativa no momento\n";
            dormir(1000);
            break;
        case 4:
            if (quantAtiva>0)
            {
                system("cls");
                imprimeContas(cadastro, quantAtiva);
            }
            else
                cout<<"Nenhuma conta ativa no momento\n";
            dormir(1000);
            break;
        default:
            system("cls");
            if (op!=0)
            {
                cout<<"Opção invalida!\n";
                dormir(1000);
            }
            else
            {
                system("cls");
                cout<<"                         Saindo.";
                dormir(800);
                system("cls");
                cout<<"                         Saindo .";
                dormir(800);
                system("cls");
                cout<<"                         Saindo  .";
            }
            break;
        }
    }
    while(op!=0);
    gravaClientes(ofs, cadastro, quantAtiva, quantRegistrada);
}
