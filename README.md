# 42 Labs Challange (Book Api)

Projeto desenvolvido para o desafio do  42labs da escola 42 São Paulo

Esse projeto consiste em uma api simples construida em **C** com as operações de **crud** basico e persistencia de aplicação com o banco de dados mysql, onde é possivel criar, alterar, ver e deletar livro do sistema, alem da inclusão de categorias e um cli para acompanhar o log das requesições.

## Dependencias

* libjson-c-dv
* mysql-server
* gcc

## Desenvolvimento do projeto
Para entender sobre o desenvolvimento do projeto acesse esse [Notion](https://www.notion.so/42labs-Challenge-5d40b5bf6ab34d899a96273ec00420b8)

## Como utilizar a API
* Insira suas credencias de login do banco de dados no arquivo server.h e no arquvio database.h(caso deseje criar e popular as tabelas automaticamente)

```c
HOSTDB "Link para seu banco de dados"
USER "Usuario do seu banco de dados"
PASSWORD "Senha do ser usuário"
DB "nome do seu banco de dados"
```

* Caso deseje você pode utilizar o comando `make init_db` para criar as tabelas e popular elas já com informações para teste
* Execute o comando `make` para compilar o API e `./bookApi` para executar ela

* Em caso de problemas de dependências utilize o comando  `make dependencies` para instalar as dependências necessárias para o projeto



## Como utilizar a CLI

* Utilize o comando `make cli` para compilar a cli é `./cli [OPTIONS]` para executar a cli



## Bibliotecas utilizadas

* mongoose.h

  > Parar criar o servidor http da api rest

* mjson.h

  > Para parsear os dados do corpo da requesição 

* json-c.h

  > Para gerar os objetos json de resposta

* stdio.h

  > Para operações de de entrada e saida

* string.h

  > Para manipulação de string

* stdlib.h

  > Para funções de manipulação em geral

## Future 
- [ ] Adicionar autenticação com JWT
- [ ] Disponibilizar a aplicação na API
- [ ] Implementar sistema de emprestimo para livros
- [ ] Implementar niveis de acesso para usuários

## Contribuição
Fique a vontade para fazer um pull request ou criar um issue

Feito com 💗 por mamaro-d.
