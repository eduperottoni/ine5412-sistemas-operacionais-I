#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; //declaração das classes criadas nos trabalhos devem ser colocadas aqui
class Thread;
class Debug;

//declaração da classe Traits
template<typename T>
struct Traits {
};

template<> struct Traits<CPU>
{
    //Adicionar aqui a declaração do tamanho da Pilha
    static const unsigned int STACK_SIZE = 8 * 1024; // 1Kb
};

template<> struct Traits<Debug>: public Traits<void>
{
    static const bool error = false;
    static const bool warning = false;
    static const bool info = false;
    static const bool trace = true;
};

// Inserir os debugs para cada classe


__END_API

#endif