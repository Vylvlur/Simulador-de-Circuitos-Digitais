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
      //Define as operações lógicas NOT para o tipo bool_3S;
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
        if((x==FALSE_3S) || (y==FALSE_3S)) return FALSE_3S;
        //Retorna UNDEF para os restantes casos
        /*
        x AND 1 - x
        1 AND x - x
        x AND x	- x
        */
        else return UNDEF_3S;
        //Se erro, repensar
        //if (((x==TRUE_3S)||(x==UNDEF_3S)) && (y==UNDEF_3S)) return UNDEF_3S
    }
  }
  bool_3S operator|(bool_3S x, bool_3S y) //OR
  {
      //Se um dos dois forem TRUE, retorna TRUE
      if((x==TRUE_3S)||(y==TRUE_3S)) return TRUE_3S;
      else
      {
        //Se ambos forem FALSO, retorna FALSO
        if ((x==FALSE_3S)&&(y==FALSE_3S)) return FALSE_3S;
        //Retorna UNDEF para os restantes casos
        /*
        x OR 0 - x
        0 OR x - x
        x OR x - x
        */
        else return UNDEF_3S;
      }
  }
  bool_3S operator^(bool_3S x, bool_3S y) //XOR
  {
      //Diferentes entre si, assumindo ou TRUE ou FALSE, retorna TRUE
      if(((x==TRUE_3S)&&(y==FALSE_3S))||((x==FALSE_3S)&&(y==TRUE_3S))) return TRUE_3S;
      else
      {
        //Iguais entre si, assumindo ou TRUE ou FALSE, retorna FALSE
        if(((x==TRUE_3S)&&(y==TRUE_3S))||((x==FALSE_3S)&&(y==FALSE_3S))) return FALSE_3S;
        //Retorna UNDEF se tive ao menos um UNDEF
        /*
        x XOR 0 - x
        0 XOR x - x
        x XOR 1 - x
        1 XOR x - x
        x XOR x - x
        */
        else return UNDEF_3S;
      }
  }



//PORTA


Porta::Porta(unsigned int NI)
{
    //Alocando Porta;
    Nin = NI; //Faz o número de entradas ser igual a variável NI, passada como parâmetro;
    saida = UNDEF_3S; //Inicia a saída da porta com o valor UNDEF_3S;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=UNDEF_3S;
}
Porta::Porta(const Porta &P)
{
    //Construtor por cópia
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
        cerr << "Sinal digital invalido!" << endl;
    }
}
int Porta::getId_in(unsigned int i) const
{
    //Retorna a indicação de da origem do sinal da entrada desse porta
    //LINHA 108 ALTERADA
    //if ((i>=0) && (i<NUM_MAX_INPUTS_PORTA)) return id_in[i];
    if ((i>=0) && (i<Nin)) return id_in[i];
    else
    {
        cerr << "Numero de entrada invalido!" << endl;
        return 0;
    }
}
void Porta::setId_in(unsigned int i, int N)
{
    //Oferece uma origem para o sinal da porta
    if ((i>=0) && (i<Nin)) id_in[i]=N;
    else
    {
        cerr << "Numero de entrada invalida!" << endl;
    }
}
void Porta::digitar()
{
    do
    {
    cout << "Digite o numero de entradas da porta: ";
    cin >> Nin;
    } while ((Nin<0) || (Nin>NUM_MAX_INPUTS_PORTA));

    for (unsigned i=0; i<Nin; i++)
    {
        cout << "Digite a origem do sinal logico da " << i+1 << "a entrada da porta: ";

            cin >> id_in[i]; //Que porta ou entrada origina o sinal

    }
}
bool Porta::ler(istream& I)
{
    unsigned count(0);
   // I.ignore(numeric_limits<streamsize>::max(), ' '); //Ignora até achar um espaço após o nome da porta
    I >> Nin;
    if(Nin<=0) return false;
    for (unsigned i=0; i<Nin; i++)
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[i];
        if (id_in[i]!=0) count++; //conta se todos os id_ins são !=0
    }
    //Se Nin for maior que nulo e todas as ids de entrada forem !=0
    if(count==Nin) return true;
    else return false;
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


        cout << "Digite a origem do sinal logico da entrada da porta: ";
        cin >> id_in[0]; //Que porta ou entrada origina o sinal

}
bool Porta_NOT::ler(istream& I)
{
    //I.ignore(numeric_limits<streamsize>::max(), ' '); //Ignora até achar um espaço após o nome da porta
    I >> Nin;
    //Se Nin for diferente de 1, não pode constituir NOT
    if (Nin!=1) return false;
    else
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[0];
        return true;
    }
}
ostream &Porta_NOT::imprimir(ostream& O) const
{
    O << "NT ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOT::simular(const bool_3S in[])
{
    return ~in[0];
}


//PORTA_AND

void Porta_AND::digitar()
{
    Porta::digitar();
}
bool Porta_AND::ler(istream& I)
{
    return Porta::ler(I);
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
    for (unsigned i=1; i<Nin; i++) prov = (prov&in[i]);
    return prov;
}


//PORTA_NAND

void Porta_NAND::digitar()
{
    Porta::digitar();
}
bool Porta_NAND::ler(istream& I)
{
    return Porta::ler(I);
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
    for (unsigned i=1; i<Nin; i++) prov = (prov&in[i]);
    return (~prov);
}


//PORTA_OR

void Porta_OR::digitar()
{
    Porta::digitar();
}
bool Porta_OR::ler(istream& I)
{
    return Porta::ler(I);
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
        prov = (prov|in[i]);
    }
    return prov;
}


//PORTA_NOR

void Porta_NOR::digitar()
{
    Porta::digitar();
}
bool Porta_NOR::ler(istream& I)
{
    return Porta::ler(I);
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
        prov = (prov|in[i]);
    }
    return (~prov);
}


//PORTA_XOR


void Porta_XOR::digitar()
{
    Porta::digitar();
}
bool Porta_XOR::ler(istream& I)
{
    return Porta::ler(I);
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
        prov = (prov^in[i]);
    }
    return prov;
}


//PORTA_NXOR

void Porta_NXOR::digitar()
{
    Porta::digitar();
}
bool Porta_NXOR::ler(istream& I)
{
    return Porta::ler(I);
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
        prov = (prov^in[i]);
    }
    return (~prov);
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
bool Circuito::verificarErros(const Porta& P)
{
    unsigned count(0);
    int ver(0);
    for (unsigned k=0; k<P.getNumInputs(); k++)
    {
        if(P.getId_in(k)<0)//Se entrada for entrada do circuito
        {
            //Módulo do id tem que ser menos/igual a Nout
            if(-(P.getId_in(k))<=Nout) count++;
        }
        else //Se entrada for saída de uma porta
        {
            //Id menor/igual a Nportas
            if(P.getId_in(k)<=Nportas) count++;
        }
        ver++;

        }


    //Se uma das duas condições do for forem atendidas para todos os casos
    if(count==P.getNumInputs())
    {}//continua a leitura
    else //interrompe leitura e msg de erro
    {
        if(ver=1){//Libera array inputs
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
    if (portas!=NULL){
        for (unsigned i=0; i<1; i++) delete portas[i];
        delete[] portas;
        portas = NULL;
    }
    //Zera todos os quantificadores
    Nin = 0;
    Nout = 0;
    Nportas = 0;
    cerr << "Id de entrada da porta maior que o número de portas" << endl;
    return false;
}else{
        cerr << "Id de entrada da porta maior que o número de portas" << endl;
        limpar();
        return false;
    }
}}
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
        cout << "Digite o numero de entradas do circuito: ";
        cin >> Nin;
    } while (Nin<=0);
    //Número de saídas do circuito
    do
    {
        cout << "Digite o numero de saidas do circuito: ";
        cin >> Nout;
    } while (Nout<=0);
    //Número de portas do circuito
    do
    {
        cout << "Digite o numero de portas logicas do circuito: ";
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
            cout << "Qual sua opcao? ";
            cin >> op;
        } while(op<0 || op>7);

        //Ler por meio de teclado o tipo de porta
        switch (op)
        {

        bool verificar, pronto;
        verificar = false;
        pronto = true;

            case 0:

            /*
                Temos que
                Repete enquanto:
                (Id>=Nin || Id<=0)&&(Id>=Nportas || Id<=0)

                */

            do{
                tNOT.digitar();

                portas[i] = (&tNOT)->clone();

                 }while(  (((tNOT.getId_in(0)*(-1))>(Nin))  ||  ((tNOT.getId_in(0)*(-1)<=0)))  &&  (((tNOT.getId_in(0)>Nportas)||(tNOT.getId_in(0)<=0))));



            break;


            case 1:

                do{
                tAND.digitar();

for(int i=0;i<tAND.getNumInputs();i++){
        bool temp, prov;
        temp=false;
        prov=true;

       temp =(((tAND.getId_in(i))*(-1)>(Nin))  ||  ((tAND.getId_in(i)*(-1)<=0)))  &&  (((tAND.getId_in(i)>Nportas)||(tAND.getId_in(i)<=0)));
       temp= !temp;
       verificar = (temp && prov);

}
            if(verificar){
            portas[i] = (&tAND)->clone();
            pronto = false;

}
            else{
            pronto=true;
            cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);







            break;
            case 2:

                do{
                tNAND.digitar();

for(int i=0;i<tNAND.getNumInputs();i++){
        bool temp, prov;
        temp=false;
        prov=true;

       temp =(((tNAND.getId_in(i))*(-1)>(Nin))  ||  ((tNAND.getId_in(i)*(-1)<=0)))  &&  (((tNAND.getId_in(i)>Nportas)||(tNAND.getId_in(i)<=0)));
       temp= !temp;
       verificar = (temp && prov);

}
            if(verificar){
            portas[i] = (&tNAND)->clone();
            pronto = false;

}
            else{
            pronto=true;
            cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);

                break;
            case 3:
            do{
            tOR.digitar();

for(int i=0;i<tOR.getNumInputs();i++){
    bool temp, prov;
    temp=false;
    prov=true;

   temp =(((tOR.getId_in(i))*(-1)>(Nin))  ||  ((tOR.getId_in(i)*(-1)<=0)))  &&  (((tOR.getId_in(i)>Nportas)||(tOR.getId_in(i)<=0)));
   temp= !temp;
   verificar = (temp && prov);

}
        if(verificar){
        portas[i] = (&tOR)->clone();
        pronto = false;

}
        else{
        pronto=true;
        cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);
                break;
            case 4:
            do{
            tNOR.digitar();

for(int i=0;i<tNOR.getNumInputs();i++){
    bool temp, prov;
    temp=false;
    prov=true;

   temp =(((tNOR.getId_in(i))*(-1)>(Nin))  ||  ((tNOR.getId_in(i)*(-1)<=0)))  &&  (((tNOR.getId_in(i)>Nportas)||(tNOR.getId_in(i)<=0)));
   temp= !temp;
   verificar = (temp && prov);

}
        if(verificar){
        portas[i] = (&tNOR)->clone();
        pronto = false;

}
        else{
        pronto=true;
        cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);
                break;
            case 5:
            do{
            tXOR.digitar();

for(int i=0;i<tXOR.getNumInputs();i++){
    bool temp, prov;
    temp=false;
    prov=true;

   temp =(((tXOR.getId_in(i))*(-1)>(Nin))  ||  ((tXOR.getId_in(i)*(-1)<=0)))  &&  (((tXOR.getId_in(i)>Nportas)||(tXOR.getId_in(i)<=0)));
   temp= !temp;
   verificar = (temp && prov);

}
        if(verificar){
        portas[i] = (&tXOR)->clone();
        pronto = false;

}
        else{
        pronto=true;
        cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);
                break;
            case 6:
            do{
            tXOR.digitar();

for(int i=0;i<tNXOR.getNumInputs();i++){
    bool temp, prov;
    temp=false;
    prov=true;

   temp =(((tNXOR.getId_in(i))*(-1)>(Nin))  ||  ((tNXOR.getId_in(i)*(-1)<=0)))  &&  (((tNXOR.getId_in(i)>Nportas)||(tNXOR.getId_in(i)<=0)));
   temp= !temp;
   verificar = (temp && prov);

}
        if(verificar){
        portas[i] = (&tNXOR)->clone();
        pronto = false;

}
        else{
        pronto=true;
        cout<<"Dados incorretos, por favor, digite novamente:"<< endl;
}

}while(pronto);
                break;
            default:
                break;
        }
    }

    //Define a origem do sinal das saídas do circuitos, se de uma porta ou entrada
    for (unsigned i=0; i<Nout; i++)
    {
        cout << "Digite a origem do sinal logico da " << i+1 << "a saida do circuito: ";
        cin >> id_out[i];
    }

}
void Circuito::ler(const char*nome) //Adicionei esse nome, pois antes estava sem variável
{
    ifstream arquivo(nome);
    limpar(); //limpar o conteúdo já existente
    if (arquivo.is_open())
    {
        //Variáveis temporárias para a leitura
		unsigned temp;
        string prov;
        char p;
        Porta_NOT tNOT;
        Porta_AND tAND;
        Porta_NAND tNAND;
        Porta_OR tOR;
        Porta_NOR tNOR;
        Porta_XOR tXOR;
        Porta_NXOR tNXOR;


      //Lendo cabeçalho geral;
        arquivo >> prov;
        if (prov != "CIRCUITO:")
        {
            cerr << "Arquivo com cabeçalho principal invalido\n";
        }
        else //FAlta Prever erros para a falta de algum dos elementos
        {
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nin;//Nin>0;
            if(Nin<=0){
                cerr << "Numero invalido de entradas!" << endl;
                limpar();
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nout;//Nout>0;
            if(Nout<=0){
                cerr << "Numero invalido de saidas!" << endl;
                limpar();
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nportas;//Nportas>0;
            if(Nportas<=0){
                cerr << "Numero invalido de portas!" << endl;
                limpar();
                return;
            }
        }
        //Aloca os arrays
        alocar(Nin, Nout, Nportas);

        arquivo >> prov;
        if (prov != "PORTAS:") //Ler o segundo cabeçalho
        {
            cerr << "Arquivo com cabeçalho de portas invalido!" << endl;
        }
        else
        {
            // Antes de ler os dados de um arquivo, zera o conteudo atual do circuito
            //limpar();

            for (unsigned i=0; i<Nportas; i++)
            {
                // Vai para o inicio de uma linha (ignora ENTER de linha anterior)
                arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
				arquivo >> temp; //Recebe o número antes do parênteses ")"
				if(temp!=i+1) //Se
				{
					cerr << "Numeracao da porta fora de ordem!" << endl;
                    limpar();
					return;
				}
				arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                getline(arquivo, prov, ' ');

                if(prov=="NT")
                {
                    if(tNOT.ler(arquivo))
                    {
                        portas[i]=(&tNOT)->clone();
                        if(verificarErros(tNOT))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta NOT!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="NA")
                {
                    if(tNAND.ler(arquivo))
                    {
                        portas[i]=(&tNAND)->clone();
                        if(verificarErros(tNAND))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta NAND!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="NO")
                {
                    if(tNOR.ler(arquivo))
                    {
                        portas[i]=(&tNOR)->clone();
                        if(verificarErros(tNOR))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta NOR!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="NX")
                {
                    if(tNXOR.ler(arquivo))
                    {
                        portas[i]=(&tNXOR)->clone();
                        if(verificarErros(tNXOR))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta NXOR!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="AN")
                {
                    if(tAND.ler(arquivo))
                    {
                        portas[i]=(&tAND)->clone();
                        if(verificarErros(tAND))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta AND!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="OR")
                {
                    if(tOR.ler(arquivo))
                    {
                        portas[i]=(&tOR)->clone();
                        if(verificarErros(tOR))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta OR!\n";
                        limpar();
                        return;
                    }
                }
                if(prov=="XO")
                {
                    if(tXOR.ler(arquivo))
                    {
                        portas[i]=(&tXOR)->clone();
                        if(verificarErros(tXOR))
                        {}
                        else return;
                    }
                    else
                    {
                        cerr << "Erro na leitura de uma porta XOR!\n";
                        limpar();
                        return;
                    }
                }
                if((prov!="NX")&&(prov!="NO")&&(prov!="NA")&&(prov!="NT")&&(prov!="XO")&&(prov!="OR")&&(prov!="AN"))
                {
					// Caracteres não eram nenhuma das opçoes validas
					cerr << "Nome da porta invalido!\n";
                    limpar();
					return;
				}
            }
        }

        arquivo >> prov;
        if (prov != "SAIDAS:") //Ler o terceiro cabeçalho
        {
            cerr << "Arquivo com cabeçalho de saidas invalido\n";
        }
        else
        {
            for (unsigned i=0; i<Nout; i++)
            {
                /*arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                arquivo >> id_out[i];*/
                arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
				arquivo >> temp; //Recebe o número antes do parênteses ")"
				arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                arquivo >> id_out[i];
				if(temp!=i+1) //Se
				{
					cerr << "Numeração da porta fora de ordem!" << endl;
                    limpar();
					return;
				}
				if ((id_out[i]==0)||(id_out[i]>Nportas))
				{
					cerr << "Id de porta incompativel!" << endl;
                    limpar();
					return;
				}
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
        imprimir(arquivo);
        arquivo.close();
    }
    else
    {
      cerr << "Erro na abertura do arquivo \"" << nome << "\" para escrita\n";
    }
}
void Circuito::digitarEntradas()
{
    int temp;
    //Digitar os valores lógicos das entradas em caso de simulação
    cout << "Digite os valores logicos das entradas: " << endl;
    for (unsigned i=0; i<Nin; i++)
    {
        do {
            cout << "Valor para a entrada número " << i+1 << ": " << endl;
            cout << "-1 - INDEFINIDO;\n";
            cout << "0 - FALSO;\n";
            cout << "1 - TRUE;\n";
            cout << "Valor: "; 
            cin >> temp;
        } while((temp<-1) || (temp>1));
        switch (temp)
        {
            case -1:
                inputs[i]=UNDEF_3S;
                break;
            case 0:
                inputs[i]=FALSE_3S;
                break;
            case 1:
                inputs[i]=TRUE_3S;
                break;
            default:
                break;
        }
    }
}

void Circuito::imprimirEntradas() const
{
        //Imprime os valores lógicos das entradas
    //imprime as entradas do vetor de inputs
    cout << "ENTRADAS: ";
    for (unsigned i=0; i<Nin; i++)
    {
        if(inputs[i]==TRUE_3S) cout << "T ";
        else
        {
            if(inputs[i]==FALSE_3S) cout << "F ";
            else cout << "? ";
        }
    }
}
void Circuito::imprimirSaidas() const
{
    //Só faz sentido imprimirSaidas <=> já imprimiu entradas
    //Lembrando que de acordo com que as entradas mudam, as saidas tbm mudam
    imprimirEntradas();

    //Imprime a origem do sinal das saídas do circuito
    //imprime as saidas do circuito
    //as saídas dos circuitos vão receber a saída de alguma porta
    //a id dessa porta que vai oferecer saída para o circuito está
    //nos Nout elementos do vetor id_out
    //cada int do id_out vai ser projetado para procurar a saída da porta indicada
    //imprimindo-a
    cout << "SAIDAS: ";
    for (unsigned i=0; i<Nout; i++) 
    {
        if((*portas[id_out[i]-1]).getSaida()==TRUE_3S) cout << "T ";
        else
        {
            if((*portas[id_out[i]-1]).getSaida()==FALSE_3S) cout << "F ";
            else cout << "? ";
        } 
    }
    cout << endl; //Enter para a próxima leitura
}
void Circuito::simular()
{
    bool tudo_def, alguma_def;
    bool_3S in_portas[4];
    for (unsigned i=0; i<Nportas; i++) (*portas[i]).setSaida(UNDEF_3S);

    do
    {
        tudo_def = TRUE_3S;
        alguma_def = FALSE_3S;
        for (unsigned i=0; i<Nportas; i++)
        {
            if ((*portas[i]).getSaida() == UNDEF_3S)
            {
                //ATENÇÃO, IMPORTANTE
                //Nesse FOR, cada coordenada de in_portas[]
                //Recebe valor lógico da saída das portas de id_in[0] até id_in[Nin-1]
                //Que servem de entradas para *portas[i]
                for (unsigned j=0; j<(*portas[i]).getNumInputs(); j++)
                {
                    if(portas[i]->getId_in(j) < 0) {in_portas[j] = inputs[(-(portas[i]->getId_in(j))) - 1];}
                    if(portas[i]->getId_in(j) > 0) {in_portas[j] = portas[(portas[i]->getId_in(j))-1]->getSaida();}
                    //in_portas[j]=(*portas[(*portas[i]).getId_in(j)]).getSaida();
                }
                //in_portas = //entradas booleanas da porta i;// //Vetor de valores lógicos das entradas da porta

                (*portas[i]).setSaida((*portas[i]).simular(in_portas));//Simula a porta e armazena o resultado em sua saída
                if ((*portas[i]).getSaida() == UNDEF_3S)
                {
                    tudo_def = FALSE_3S;
                }
                else
                {
                    alguma_def = TRUE_3S;
                }
            }
        }
    } while (!tudo_def && alguma_def);
}
void Circuito::gerarTabela()
{
    for (unsigned i=0; i<Nin; i++) (inputs[i]) = FALSE_3S;

    int i;
    do
    {
        Circuito::simular();
        Circuito::imprimirSaidas();

        //Qual input incrementar?
        i = Nin-1;
        while ((i>=0) && (inputs[i]==UNDEF_3S)) //se for undef, coloca para false
        {
            (inputs[i])=FALSE_3S;
            i--;
        }

        //Incrementa a input escolhida
        if (i>=0)
        {
            if ((inputs[i])==FALSE_3S)//se for false, coloca para true
            {
                (inputs[i])=TRUE_3S;
            }
            else //se for true, coloca para undef, pq false já foi
            {
                (inputs[i])=UNDEF_3S;
            }
        }
    } while (i>=0);


}











