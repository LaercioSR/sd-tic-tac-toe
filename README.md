# TIC-TAC-TOE

![Game in Execution](https://raw.githubusercontent.com/LaercioSR/sd-tic-tac-toe/main/doc/screen_recording.gif)

- [Sobre](#sobre)
- [Como Executar](#como-executar)
- [Detalhes da Implementação](#detalhes-da-implementação)
  - [Entrada do mouse](#obtendo-valores-de-entrada-do-mouse)
  - [Desenhando no terminal](#desenhando-no-terminal)

## Sobre

O projeto foi desenvolvido na disciplina de MI - Sistemas Digitais do curso de [Engenharia da Computação](https://www.ecomp.uefs.br/) da [Universidade Estadual de Feira de Santana (UEFS)](https://uefs.br).

## Como Executar

Para executar o projeto você precisa primeiramente compilar para criar um executável, para isso rode o seguinte comando:

```bash
make all
```

Caso tudo dê certo será criado um executável chamado "tictactoe" para executá-lo rode o seguinte comando:

```bash
sudo ./tictactoe
```

## Detalhes da Implementação

### Obtendo valores de entrada do mouse

### Desenhando no terminal

Para realizar os desenhos do tabuleiro e dos valores de X e O no terminal foi usado o Códigos de Console (console_codes) disponíveis na maioria dos terminais Linux.

Esses Códigos de Consoles disponibilizam alguns comando como o de mudar a cor dos caracteres ou mudar a posição do cursor no terminal. Para isso usamos um comando de escape (\033) seguido de [ e valor (caso necessário) e do caractere que representa a função a ser realizada.

Para mais detalhes veja na seguinte documentação: [console_codes — Linux manual](https://man7.org/linux/man-pages/man4/console_codes.4.html)

#### Códigos de Console usados no projeto

- \033 [ A - Move o cursor para cima
  - Ex: \033[1A - Move o cursor 1 linhas para cima
- \033 [ B - Move o cursor para baixo
  - Ex: \033[2B - Move o cursor 2 linhas para baixo
- \033 [ C - Move o cursor para direita
  - Ex: \033[3C - Move o cursor 3 casas para direita
- \033 [ D - Move o cursor para esquerda
  - Ex: \033[4C - Move o cursor 4 casas para esquerda
- \033 [ m - Muda a cor dos caracteres/fundo
  - Ex: \033[31;42m - Muda os caracteres para vermelho e o fundo para verde
