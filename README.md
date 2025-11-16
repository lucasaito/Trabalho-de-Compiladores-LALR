
![Demonstração](https://media.tenor.com/PDZBrAetTUIAAAAi/r2d-reason2die-r2da-placerebuilder-gosinister-css-cool.gif)


# LALR Parser – Implementação em C++

Este repositório contém a implementação de um **analisador sintático LALR(1)** com construção de Árvore Sintática Abstrata (AST), desenvolvido como parte da disciplina de **Compiladores**, no curso de Ciência da Computação.  
---

## 📘 Visão Geral

O projeto implementa um parser LALR(1) simples para expressões aritméticas envolvendo:
- identificadores (id)
- números (num)
- operadores + e *
- parênteses

### 📝Gramática Utilizada 
S → E

E → E + T | T

T → T * F | F

F → ( E ) | id

---
## 🧱 Funcionalidades Implementadas
- Tokenização
- Parsing LALR(1)
- Impressão detalhada (trace)
- Construção da AST
  
---

## ⚙️ Como Compilar

Certifique-se de usar G++ (GNU C++ Compiler).

---

## ▶️ Como Executar

### Gerar um executável na pasta local:
```bash
g++ lalr.cpp -o lalr
```

### No terminal, dentro do diretório acessar o executável:
```bash
./lalr.exe
```

### Digitar uma entrada
```bash
(a + b) * c
```
### O parser exibirá as reduções e, se tudo estiver correto:
- shifts
- reduces
- transições
- pilha
- AST final
- mensagem de aceitação
```bash
Entrada aceita pela gramática LALR(1).
```

---

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

## 📚 Referências

Aho, A. V.; Lam, M.; Sethi, R.; Ullman, J.
Compiladores – Princípios, Técnicas e Ferramentas (Dragon Book)



