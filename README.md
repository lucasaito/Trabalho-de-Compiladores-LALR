# LALR Parser – Implementação em C++

Este repositório contém a implementação de um **analisador sintático LALR(1)** desenvolvido como parte da disciplina de **Compiladores**, no curso de Ciência da Computação.  

---

## 📘 Visão Geral

O trabalho consiste na implementação, em C++, de um **parser LALR(1)** baseado em uma gramática definida.  
O fluxo geral segue as etapas clássicas de um compilador:

1. Definição da gramática (GLC)  
2. Construção dos conjuntos LR  
3. Fusão dos estados para obtenção da tabela LALR  
4. Implementação das estruturas de análise  
5. Testes com entradas válidas e inválidas  

O objetivo é consolidar os conceitos estudados na disciplina, trazendo a teoria para um ambiente prático de programação.

---
## 🧱 Funcionalidades Implementadas

- Construção programática da tabela **ACTION** e **GOTO**  
- Implementação de um analisador **shift-reduce**  
- Tratamento de erros sintáticos  
- Impressão passo a passo da análise (modo detalhado)  
- Suporte a:
  - Produções recursivas
  - Alternativas múltiplas
  - Tokens terminais e não terminais bem definidos

---

## 🧩 Estrutura do Projeto
/src
├── lexer.cpp # (opcional) analisador léxico simples
├── parser.cpp # implementação do algoritmo LALR
├── grammar.hpp # definição da gramática
├── table.hpp # tabela ACTION/GOTO
├── utils.hpp # funções auxiliares
└── main.cpp # ponto de entrada do compilador

/tests
├── valid/ # entradas válidas
└── invalid/ # entradas inválidas

---

## ⚙️ Como Compilar

Certifique-se de usar C++17 ou superior.

Windows (MinGW)
```bash
g++ -std=c++17 src/*.cpp -o lalr.exe
```

---

## ▶️ Como Executar

### Executar com arquivo de entrada
```bash
./lalr entrada.txt
```
### Executar passando a string diretamente
```bash
echo "x = x + 1;" | ./lalr
```
### Gramática Utilizada 
S → E
E → E + T | T
T → T * F | F
F → ( E ) | id

---

## 🧪 Testes

### ✔️ Exemplos válidos
id + id
id * ( id + id )

### ❌ Exemplos inválidos
+ id id
id * ( )

---

## 🏫 Objetivos Educacionais
Este trabalho visa:

1. Entender profundamente o método LALR(1)
2. Implementar na prática um autômato LR
3. Resolver conflitos shift/reduce e reduce/reduce
4. Relacionar teoria → prática no contexto de compiladores
5. Fortalecer a capacidade de analisar gramáticas e implementar parsers reais

---

## 👥 Integrantes do Grupo
- Gustavo Tramarin
- Ivan Carlos Amaral Galvão Ribeiro
- João Filipe Castoldo Liotto
- Lucas Saito Sanzovo
- Renato Parra

---

##📚 Referências

Aho, A. V.; Lam, M.; Sethi, R.; Ullman, J.
Compiladores – Princípios, Técnicas e Ferramentas (Dragon Book)

Appel, A. W.
Modern Compiler Implementation

Material da disciplina de Compiladores — [Nome da Instituição]

