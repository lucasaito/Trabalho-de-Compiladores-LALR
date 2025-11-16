
![Demonstração](https://media.tenor.com/PDZBrAetTUIAAAAi/r2d-reason2die-r2da-placerebuilder-gosinister-css-cool.gif)


# LALR Parser – Implementação em C++

Este repositório contém a implementação de um **analisador sintático LALR(1)** desenvolvido como parte da disciplina de **Compiladores**, no curso de Ciência da Computação.  
---

## 📘 Visão Geral

O projeto implementa um parser LALR(1) simples para expressões aritméticas envolvendo:
- identificadores (id)
- números (num)
- operadores + e *
- parênteses

Toda a lógica do lexer, das tabelas ACTION/GOTO e do parser shift-reduce foi implementada manualmente, de forma totalmente didática.

### Gramática Utilizada 
S → E

E → E + T | T

T → T * F | F

F → ( E ) | id

## O Código inclui
1. Tokenização simples (sem analisador léxico externo)
2. Tabelas ACTION e GOTO preenchidas manualmente
3. Produções armazenadas em vetor de regras
4. Implementação do autômato shift-reduce LALR(1)
5. Mensagens de redução + aceitação da entrada
---
## 🧱 Funcionalidades Implementadas

- Tokenização de lexemas individuais (id, num, operadores, parênteses) 
- Tabela ACTION[12][7] totalmente construída na função initTables() 
- Tabela GOTO[12][3] também definida manualmente   
- Processo de parsing:
  - shift
  - reduce
  - accept
  - erro sintático
- Pilha de estados implementada com std::stack
- Reduções impressas durante a análise (Reduce usando produção X)
- Suporte a fim de entrada com token $
  
---

## 🧩 Estrutura do Projeto
/src

└── main.cpp   

tokenização, tabelas, produções, parser e main()
### O código inclui as seguintes seções:
- Tokenização
- Definição de tipos de tokens
- Definição da tabela ACTION
- Definição da tabela GOTO
- Produções
- Parser shift-reduce
- Função main


---

## ⚙️ Como Compilar

Certifique-se de usar G++ (GNU C++ Compiler).

---

## ▶️ Como Executar

### Gerar um executável na pasta local:
```bash
g++ lalr.cpp -o lalr
```
### Digitar uma entrada
```bash
(a + b) * c
```
### O parser exibirá as reduções e, se tudo estiver correto:
```bash
Entrada aceita pela gramática LALR(1).
```

## 🧪 Testes

### ✔️ Exemplos válidos
- id + id
- id * (id + id)
- ( id )
- a + b * c

### ❌ Exemplos inválidos
- + id
- id * ( )
- ( id + * id )

---

## 🏫 Objetivos Educacionais
Este trabalho busca reforçar:

1. Compreensão de gramáticas LR
2. Construção de tabelas LALR(1)
3. Uso de autômatos de pilha LR
4. Resolução prática de conflitos shift/reduce
5. Implementação manual de parsers reais
6. Relação entre teoria e implementação em C++

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



