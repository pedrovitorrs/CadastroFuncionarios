#ifndef CONTROLE_H_INCLUDED
#define CONTROLE_H_INCLUDED

/// Constantes Estrutura Funcion�rios
#define MATRICULA 10
#define NOME 60
#define DATA 11
#define CPF 12
#define RUA 40
#define BAIRRO 30
#define COMPLEMENTO 30
#define CIDADE 40
#define UF 3
#define CEP 9
#define EMAIL 40

/// Constantes Estrutura Departamento
#define NOME_DEP 40
#define SIGLA 10



                    /* ---------------------------------------------------------- SE��O DE ESTRUTURAS USADAS NO PROGRAMA -------------------------------------------------------------- */



/// Estrutura Funcion�rios
typedef struct{
    long int id, id_departamento;
    char matricula[MATRICULA], nome[NOME], dataNascimento[DATA],
         cpf[CPF], rua[RUA], bairro[BAIRRO], complemento[COMPLEMENTO],
         cidade[CIDADE], uf[UF], cep[CEP], email[EMAIL];
    unsigned int Numero;
    float salario;
}TFuncionario;


/// Estrutura HistoricoFuncionarios
typedef struct{
    long int id_funcionario, id_departamento;
    char data[DATA];
}THistoricoFuncionario;


/// Estrutura Departamento
typedef struct{
    long int id, id_gerente;
    char nome[NOME_DEP], sigla[SIGLA];
    unsigned short int Ramal;
}TDepartamento;


/// Estrutura Historico Departamento
typedef struct{
    long int id_departamento, id_gerente;
    char data[DATA];
}THistoricoDepartamento;


/// Estrutura Historico Salario
typedef struct{
    long int id_funcionario;
    float salario;
    unsigned short int mes, ano;
}THistoricoSalario;


                                /* ---------------------------------------------------------- SE��O DE ARQUIVOS USADOS NO PROGRAMA -------------------------------------------------------------- */



FILE *arq_func, *arq_hist_func, *arq_dept, *arq_hist_dept, *arq_hist_sal;



                                /* ---------------------------------------------------------- SE��O DE FUN��ES USADAS NO PROGRAMA -------------------------------------------------------------- */



/// FUN��O QUE PRINTA O MENU DE OP��ES NA TELA
void menu();

/// FUN��ES PRINCIPAIS DE CADASTRO
int cadastro_dept(FILE*);
int cadastro_func(FILE*, int);

/// FUN��O PARA ALTERAR DADOS DE FUNCION�RIOS
void alteraDadosFunc(FILE*);
void alterarDeptFunc(FILE*);
void alterarGerenteDept(FILE*);
void alterarSalarioFunc(FILE*);

/// FUN��O PARA PROCURAR FUNCION�RIO
void consultaFunc(FILE*);

/// FUN��ES UTILIZADAS PARA FAZER DIVERSAS VERIFICACOES
int verificaLetra(char*);
void retiraEnter(char*);
int verificaNum(char*);
int pesquisa_Matricula(FILE*,char*);
int verificaData(char*);
int verificaCPF(char*);
int verificaId_Dept(FILE*,int);
int verificaId_Func(FILE*, long int);

/// FUN��ES PARA EXIBI��O DE ALGUNS DADOS
void exibeFunc(FILE*, long int);
void exibeDept(FILE*);
void FolhaPag(FILE*);
void relatorioDeptFunc(FILE*);
void relatorioDeptGer(FILE*);

/// FUN��ES QUE DEVEMOS LEMBRAR DE APAGAR
void exibeHistFunc(FILE*);
void exibeHistSal(FILE*);


#endif // CONTROLE_H_INCLUDED
