#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include "circuito.h"

using namespace std;

//OPERADORES
  bool_3S operator~(bool_3S x) //NOT
  {
	if(x==TRUE_3S) return FALSE_3S;
	if(x==FALSE_3S) return TRUE_3S;
	if(x==UNDEF_3S) return UNDEF_3S;
  }
  bool_3S operator&(bool_3S x, bool_3S y) //AND
  {
	//Se os dois forem TRUE, retorna TRUE
	if((x==TRUE_3S)&&(y==TRUE_3S)) return TRUE_3S;
	else 
	{
		//Se ao menos um FALSE retorna FALSE
		if((x==FALSE_3S) || (y==FALSE_3S) return FALSE_3S;
		//Retorna UNDEF para os restantes casos
		/*
		x AND 1 - x
		1 AND x - x
		x AND x	- x	
		*/
		else return UNDEF_3S
		//Se erro, repensar
		//if (((x==TRUE_3S)||(x==UNDEF_3S)) && (y==UNDEF_3S)) return UNDEF_3S
	}
	//if(x==FALSE_3S) return TRUE_3S;
	//if(x==UNDEF_3S) return UNDEF_3S;
  }
  bool_3S operator|(bool_3S x, bool_3S y) //OR
  {
	  
  }
  bool_3S operator^(bool_3S x, bool_3S y) //XOR
  {
	  
  }



//PORTA


Porta::Porta(unsigned int NI)
{
    //alocando porta
    Nin = NI;
    saida = UNDEF_3S;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=UNDEF_3S;
}
Porta::Porta(const Porta &P)
{
    //construtor por cópia
    Nin = P.Nin;
    saida = P.saida;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=P.id_in[i];    
}
void Porta::setSaida(bool_3S s)
{
    //Salva a saída fornecidade, se -1<=s<=1
    if ((s>=UNDEF_3S) && (s<=TRUE_3S)) saida=s; 
    else 
    {
        cerr << "Sinal digital inválido!" << endl;
    }
}
int Porta::getId_in(unsigned int i) const
{
    //Retorna a indicação de da origem do sinal da entrada desse porta
    if ((i>0) && (i<NUM_MAX_INPUTS_PORTA)) return id_in[i]; 
    else 
    {
        cerr << "Número de entradas inválida!" << endl;
        return ;
    }
}
void Porta::setId_in(unsigned int i, int N)
{
    //Oferece uma origem para o sinal da porta  
    if ((i>0) && (i<Nin)) id_in[i]=N;
    else 
    {
        cerr << "Número de entrada inválida!" << endl;
    }
}
void Porta::digitar()
{
    do
    {
    cout << "Digite o número de entradas da porta: ";
    cin >> Nin;
    } while ((Nin<0) || (Nin>NUM_MAX_INPUTS_PORTA));
    
    for (unsigned i=0; i<Nin; i++)
    {
        cout << "Digite a origem do sinal lógico da " << i+1 << "ª entrada da porta: ";
        cin >> id_in[i]; //Que porta ou entrada origina o sinal
    }
}
bool Porta::ler(istream& I)
{
    I.ignore(numeric_limits<streamsize>::max(), ' '); //Ignora até achar um espaço apó so nome da porta
    I >> Nin;
    for (unsigned i=0; i<Nin; i++)
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[i];       
    }
    
    return *this;
}
ostream &Porta::imprimir(ostream &O) const
{
    O << Nin << ": ";
    for (unsigned i=0; i<Nin; i++) O << id_in[i] << " "; 

    return O;
}


//PORTA_NOT


void Porta_NOT::digitar()
{
    Porta::digitar();
}
bool Porta_NOT::ler(istream& I)
{
    
}
ostream &Porta_NOT::imprimir(ostream& O) const
{
    O << "NT ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOT::simular(const bool_3S in[])
{
    bool_3S prov;
	if (in[0]!=UNDEF_3S) prov = (!in[0]);
	else prov = in[0]
	return prov;
}


//PORTA_AND

void Porta_AND::digitar()
{
}
bool Porta_AND::ler(istream& I)
{
}
ostream &Porta_AND::imprimir(ostream& O) const
{
    O << "AN ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_AND::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++) prov = (prov && in[i]);
	return prov;
}


//PORTA_NAND

void Porta_NAND::digitar()
{
}
bool Porta_NAND::ler(istream& I)
{
}
ostream &Porta_NAND::imprimir(ostream& O) const
{
    O << "NA ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NAND::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++) prov = (prov && in[i]);
	return (!prov);
}


//PORTA_OR

void Porta_OR::digitar()
{
}
bool Porta_OR::ler(istream& I)
{
}
ostream &Porta_OR::imprimir(ostream& O) const
{
    O << "OR ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_OR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov || in[i]);
	}
	return prov;
}


//PORTA_NOR

void Porta_NOR::digitar()
{
}
bool Porta_NOR::ler(istream& I)
{
}
ostream &Porta_NOR::imprimir(ostream& O) const
{
    O << "NO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov || in[i]);
	}
	return (!prov);
}


//PORTA_XOR


void Porta_XOR::digitar()
{
}
bool Porta_XOR::ler(istream& I)
{
}
ostream &Porta_XOR::imprimir(ostream& O) const
{
    O << "XO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_XOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov!=in[i]);
	}
	return prov;
}


//PORTA_NXOR

void Porta_NXOR::digitar()
{
}
bool Porta_NXOR::ler(istream& I)
{
}
ostream &Porta_NXOR::imprimir(ostream& O) const
{
    O << "NX ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NXOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov==in[i]);
	}
	return prov;
}


//CIRCUITO 


void Circuito::limpar()
{
    //Libera array inputs
    if (inputs!=NULL)
    {
        delete[] inputs;
        inputs = NULL;
    }
    //Libera array id_out
    if (id_out!=NULL)
    {
        delete[] id_out;
        id_out = NULL;
    }
    //Libera array de ptrs portas
    if (portas!=NULL)
    {
        for (unsigned i=0; i<Nportas; i++) delete portas[i];
        delete[] portas;
        portas = NULL;
    }
    //Zera todos os quantificadores
    Nin = 0;
    Nout = 0;
    Nportas = 0;
}
void Circuito::alocar(unsigned int NI, unsigned int NO, unsigned int NP)
{
    limpar();
    
    //Aloca os quantificadores com os valores fornecidos
    Nin = NI;
    Nout = NO;
    Nportas = NP;
    
    //Aloca dinâmicamente os arrays
    inputs = new bool_3S[Nin];
    id_out = new int[Nout];
    portas = new ptr_Porta[Nportas];
}
void Circuito::copiar(const Circuito& C)
{
    limpar();
    alocar(C.Nin, C.Nout, C.Nportas);
    
    //Realiza as cópias necessárias
    //obs.: uso do método clone
    for (unsigned i=0; i<Nin; i++) inputs[i]=C.inputs[i];
    for (unsigned i=0; i<Nout; i++) id_out[i]=C.id_out[i];
    for (unsigned i=0; i<Nportas; i++) portas[i] = C.portas[i]->clone();
}
void Circuito::digitar()
{
    //Cria as variáveis temporárias
    int op;
    Porta_NOT tNOT;
    Porta_AND tAND;
    Porta_NAND tNAND;
    Porta_OR tOR;
    Porta_NOR tNOR;
    Porta_XOR tXOR;
    Porta_NXOR tNXOR;
    
    //Número de entradas do circuito
    do 
    {
        cout << "Digite o número de entradas do circuito: ";
        cin >> Nin;
    } while (Nin<=0);
    //Número de saídas do circuito
    do 
    {
        cout << "Digite o número de saídas do circuito: ";
        cin >> Nout;
    } while (Nout<=0);
    //Número de portas do circuito
    do 
    {
        cout << "Digite o número de portas lógicas do circuito: ";
        cin >> Nportas;
    } while (Nportas<=0);
    
    //Aloca os arrays
    alocar(Nin, Nout, Nportas);
    
    
    //Definição das portas
    
    for (unsigned i=0; i<Nportas; i++) //ler a quantidade de portas fornecidas
    {
        //Menu de escolha
        cout << "\nINSERIR UMA PORTA:\n";
        do {
            cout << "0 - Porta NOT\n";
            cout << "1 - Porta AND\n";
            cout << "2 - Porta NAND\n";
            cout << "3 - Porta OR\n";
            cout << "4 - Porta NOR\n";
            cout << "5 - Porta XOR\n";
            cout << "6 - Porta NXOR\n";
            cout << "Qual sua opção? ";
            cin >> op;
        } while(op<0 || op>7);
        
        //Ler por meio de teclado o tipo de porta
        switch (op)
        {
            case 0:
                tNOT.digitar();
                portas[i] = (&tNOT)->clone();
                break;
            case 1:
                tAND.digitar();
                portas[i] = (&tAND)->clone();
                break;
            case 2:
                tNAND.digitar();
                portas[i] = (&tNAND)->clone();
                break;
            case 3:
                tOR.digitar();
                portas[i] = (&tOR)->clone();
                break;
            case 4:
                tNOR.digitar();
                portas[i] = (&tNOR)->clone();
                break;
            case 5:
                tXOR.digitar();
                portas[i] = (&tXOR)->clone();
                break;
            case 6:
                tNXOR.digitar();
                portas[i] = (&tNXOR)->clone();
                break;
            default:
                break;
        }
    }
    
    //Define a origem do sinal das saídas do circuitos, se de uma porta ou entrada
    for (unsigned i=0; i<Nout; i++)
    {
        cout << "Digite a origem do sinal lógico da " << i+1 << "ª saída do circuito: ";
        cin >> id_out[i];
    }

}
void Circuito::ler(const char*nome) //Adicionei esse nome, pois antes estava sem variável
{
    ifstream arquivo(nome);
    if (arquivo.is_open())
    {
        //Variáveis temporárias para a leitura
        string prov;
        Porta_NOT tNOT;
        Porta_AND tAND;
        Porta_NAND tNAND;
        Porta_OR tOR;
        Porta_NOR tNOR;
        Porta_XOR tXOR;
        Porta_NXOR tNXOR;


      //Lendo cabeçalho geral
        arquivo >> prov;
        if (prov != "CIRCUITO:")
        {
            cerr << "Arquivo com cabeçalho principal inválido\n";
        }
        else //FAlta Prever erros para a falta de algum dos elementos
        {
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');        
            arquivo >> Nin;//Nin>0;
            if(Nin<=0){
                cerr << "Numero invalido de entradas!"
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nout;//Nout>0;
            if(Nin<=0){
                cerr << "Numero invalido de saidas!"
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nportas;//Nportas>0;
            if(Nportas<=0){
                cerr << "Numero invalido de portas!"
                        return;
            }
        }
        //Aloca os arrays
        alocar(Nin, Nout, Nportas);
        
        arquivo >> prov;
        if (prov != "PORTAS:") //Ler o segundo cabeçalho
        {
            cerr << "Arquivo com cabeçalho de portas inválido\n";
        }
        else
        {
            // Antes de ler os dados de um arquivo, zera o conteudo atual do circuito
            limpar();

            for (unsigned i=0; i<Nportas; i++)
            {
                // Vai para o inicio de uma linha (ignora ENTER de linha anterior)
                arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
                arquivo >> prov;

                switch(prov)
                {

                case 'NT':
					if(tNOT.ler(arquivo)) portas[i]=(&tNOT)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta NOT!";
						return;
					}
					break;
                case 'AN':
					if(tAND.ler(arquivo)) portas[i]=(&tAND)->clone();
					else 
					{
						cerr << "Erro na leitura de uma  AND!";
						return;
					}
                    break;
                }
                case 'NA':
					if(tNAND.ler(arquivo)) portas[i]=(&tNAND)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta NAND!";
						return;
					}
                    break;
                case 'OR':
					if(tOR.ler(arquivo)) portas[i]=(&tOR)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta OR!";
						return;
					}
                    break;
                case 'NO':
					if(tNOR.ler(arquivo)) portas[i]=(&tNOR)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta NOR!";
						return;
					}
                    break;
                case 'XO':
					if(tXOR.ler(arquivo)) portas[i]=(&tXOR)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta XOR!";
						return;
					}
                    break;
                case 'NX':
					if(tNXOR.ler(arquivo)) portas[i]=(&tNXOR)->clone();
					else 
					{
						cerr << "Erro na leitura de uma porta NXOR!";
						return;
					}
                    break;
                default:
                // Primeiro caractere da linha nao era nenhuma das opçoes validas
                cerr << "Arquivo " << arquivo << " parcialmente invalido para leitura\n";
                return;
                //portas[i]->ler(arquivo);
            }
        }
        
        arquivo >> prov;
        if (prov != "SAIDAS:") //Ler o terceiro cabeçalho
        {
            cerr << "Arquivo com cabeçalho de saídas inválido\n";
        }
        else
        {
            for (unsigned i=0; i<Nout; i++)
            {
                arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                arquivo >> id_out[i];
            }
        }
        
        //Fechando arquivo
        arquivo.close();
    }
    else //Erro na abertura geral do arquivo
    {
        cerr << "Erro na abertura do arquivo \"" << nome << "\" para leitura\n";
    }
}
ostream &Circuito::imprimir(ostream& O) const
{
    //Impressão padrão do circuito
    O << "CIRCUITO: " << Nin << " " << Nout << " " << Nportas << endl;
    O << "PORTAS:" << endl;
    for (unsigned i=0; i<Nportas; i++) 
    {
        O << i+1 << ") ";
        portas[i]->imprimir(O);
        O << endl;
    }
    O << "SAIDAS:" << endl;
    for (unsigned i=0; i<Nout; i++)
    {
        O << i+1 << ") ";
        O << id_out[i] << endl;
    }
    //Retorna ostream
    return O;
}
void Circuito::salvar(const char*nome) const //Adicionei esse nome, pois antes estava sem variável
{
    ofstream arquivo(nome);
    //arquivo.is_open();
    if (arquivo.is_open())
    {
        for (unsigned i=0; i<Nportas; i++) arquivo << *portas[i];
        arquivo.close();
    }
    else
    {
      cerr << "Erro na abertura do arquivo \"" << nome << "\" para escrita\n";
    }
}
void Circuito::digitarEntradas()
{
    //Digitar os valores lógicos das entradas em caso de simulação
    cout << "Digite os valores lógicos das entradas: " << endl;
    for (unsigned i=0; i<Nin; i++)
    {
        do
        {
            cout << "Valor lógico da entrada " << i+1 << ": ";
            cin >> inputs[i];
        } while ((inputs[i]!=FALSE_3S) || (inputs[i]!=TRUE_3S) || (inputs[i]!=UNDEF_3S));
    }
}
void Circuito::imprimirEntradas() const
{
    //Imprime os valores lógicos das entradas
    cout << "Valores das entradas do circuito: " << endl;
    for (unsigned i=0; i<Nin; i++) cout << "Entrada " << i+1 << " : " << inputs[i] << endl; 
}
void Circuito::imprimirSaidas() const
{
    //Imprime a origem do sinal das saídas do circuito
    cout << "Origem do sinal das saídas do circuito: " << endl;
    for (unsigned i=0; i<Nout; i++) cout << "Saída " << i+1 << " : " << id_out[i] << endl; 
}
void Circuito::simular()
{
    bool tudo_def, alguma_def, in_portas;
    
    for (unsigned i=0; i<Nportas; i++) *portas[i]->saida = UNDEF_3S;
    
    do 
    {
        tudo_def = TRUE_3S;
        alguma_def = FALSE_3S;
        for (unsigned i=0; i<Nportas; i++)
        {
            if (*portas[i]->saida == UNDEF_3S)
            {
                in_portas = /*entradas booleanas da porta i;*/ 
				portas[i]->simular(in_porta);
                if (portas[i].saida == UNDEF_3S)
                {
                    tudo_def = FALSE_3S;
                }
                else
                {
                    alguma_def = TRUE_3S;
                }
            }
        }
    } while (!tudo_def && alguma_def)
    
}
void Circuito::gerarTabela()
{    
    for (unsigned i=0; i<Nin; i++) *(inputs[i]) = FALSE_3S;
    
    do
    {
        Circuito::simular(inputs);
        
        //Qual input incrementar?
        i = Nin-1;
        while ((i>=0) && (inputs[i]==UNDEF_3S))
        {
            *(inputs[i])=FALSE_3S;
            i--;
        }
        
        //Incrementa a input escolhida
        if (i>=0)
        {
            if (*(inputs[i])==FALSE_3S)
            {
                *(inputs[i])=TRUE_3S;
            }
            else //é true
            {
                *(inputs[i])=UNDEF_3S
            }
        }
    } while (i>=0);
}











