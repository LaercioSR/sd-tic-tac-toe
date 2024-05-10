# TIC-TAC-TOE

![Jogo em execução](https://raw.githubusercontent.com/LaercioSR/sd-tic-tac-toe/main/doc/screen_recording.gif)

- [Sobre](#sobre)
- [Como Executar](#como-executar)
  - [Pré-requisitos](#pré-requisitos)
  - [Compilação](#compilação)
  - [Execução](#execução)
- [Funcionamento do Jogo](#funcionamento-do-jogo)
- [Detalhes da Implementação](#detalhes-da-implementação)
  - [Entrada do mouse](#obtendo-valores-de-entrada-do-mouse)
  - [Desenhando no terminal](#desenhando-no-terminal)

## Sobre

O projeto se trata de uma versão do famoso Jogo da Velha (Tic-Tac-Toe), desenvolvido para rodar numa placa DE1-SoC.

Seu desenvolvimento ocorreu na disciplina de MI - Sistemas Digitais do curso de [Engenharia da Computação](https://www.ecomp.uefs.br/) da [Universidade Estadual de Feira de Santana (UEFS)](https://uefs.br), sendo orientado pelo professor Anfranserai Dias.

Integrantes:

- [Antônio Felipe](https://github.com/OinotnaEpilef)
- [Fabrício Portela](https://github.com/fabricioportela)
- [Laercio Rios](https://github.com/LaercioSR)

## Como Executar

### Pré-requisitos

Para executar o projeto, é necessário ter uma placa DE1-SoC e um mouse conectado a uma entrada USB da placa.

### Compilação

Para executar o projeto você precisa primeiramente compilar para criar um executável, para isso rode o seguinte comando:

```bash
make all
```

Caso tudo dê certo um executável chamado `tictactoe` será criado.

Após isso você pode executar o seguinte comando para apagar todos os arquivos criados na compilação (menos o executável):

```bash
make clean
```

Lembrando que manter esses arquivos pode acelerar o tempo de uma nova compilação, ajudando desenvolvimento do projeto.

Caso também deseje apagar o executável, você pode executar o seguinte comando:

```bash
make clean-all
```

### Execução

Por fim, para executar o projeto, rode o seguinte comando:

```bash
sudo ./tictactoe
```

## Funcionamento do Jogo

Após inicializar o arquivo de execução, o jogo exibirá um menu que é controlado por botões (push buttons) da placa, com as seguintes opções:

- Botão 1 (PB1): Iniciar partida.
- Botão 2 (PB2): Encerrar o jogo (finalizando a execução do programa).

Baixo é possível ver a disposição dos botões na placa:

![Disposição dos botões](https://raw.githubusercontent.com/LaercioSR/sd-tic-tac-toe/main/doc/buttons.png)

Escolhendo a primeira opção, uma nova partida é inicializada, mostrando o tabuleiro. O jogo é controlado pelo mouse, em que o movimento para baixo, para cima, para direita ou para esquerda faz com que o cursor pule para casa correspondente ao movimento. Para fazer uma jogada, o jogador precisa dar dois clique (com o botão direito do mouse) para confirmar sua jogada.

O display de 7-segmentos mostra qual é o jogador da vez, como na representação abaixo:

![Display mostrando o jogador atual](https://raw.githubusercontent.com/LaercioSR/sd-tic-tac-toe/main/doc/display.gif)

Quando um jogador ganha, no display é exibido uma mensagem mostrando o número do jogador ganhador (como visto abaixo), além disso é mostrado uma mensagem no terminal.

![Display mostrando o jogador atual](https://raw.githubusercontent.com/LaercioSR/sd-tic-tac-toe/main/doc/display_winner.png)

Caso dê empate, é mostrado a mensagem apenas no terminal.

Finalizado a partida, o menu é novamente exibido, para caso os jogadores queiram iniciar uma nova partida ou finalizar a execução do programa.

## Detalhes da Implementação

### Obtendo valores de entrada do mouse

No Linux, é possível obter valores de entradas de dispositivos a partir de arquivos encontrados na pasta `/dev/input`. No caso de mouse é possível usar o arquivo `/dev/input/mice` para obter todas as entradas de todos os mouse conectados a placa.

Nesse arquivo, os dados de entradas são divididos em 3 partes, sendo a primeira referente aos botões de clique do mouse, segunda parte se refere aos valores do movimento do mouse no eixo vertical e por fim, a última parte possui os valores do movimento do mouse no eixo horizontal. Dessa forma, quando lemos a entrada do mouse nós separamos esses valores, por fim, na primeira parte nós pegamos apenas o bit mais significativo, já que no jogo nós usamos apenas o valor do clique do botão esquerdo do mouse.

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
