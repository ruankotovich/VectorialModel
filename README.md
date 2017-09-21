# Implementação do Modelo Vetorial

#### Alunos 
 - Ruan Gabriel (21553690)
 - Gabriel Pereira (21553686)

## O modelo vetorial 

O modelo vetorial foi implementado utilizando o `TF` como o contador de ocorrências da palavra no texto, visando a simplicidade. Já o `IDF` foi implementado adicionando uma unidade a mais na quantidade de documentos que contém tal palavra chave, visando diminuir a importância de algumas palavras.

<center>
    <img src="https://imgur.com/IzX3XhV.png"></img>
</center>

<center>
    <img src="https://imgur.com/mHD8tWD.png"></img>
</center>

## As melhorias
Desde o parsing, removemos caracteres indesejados tais como pontuações e outros símbolos gráficos que não são letras (incluindo números). 

Além disso, removemos as `stopwords` de entrada de indexação e da busca para indexar menos elementos já que durante as buscas detectamos muitas `stopwords`.

Inserimos mais peso ao IDF já que consideramos que a raridade de uma palavra é importante nessa base, uma vez que existem muitos nomes de doenças em vários artigos diferentes.

Para o nome dos autores, não removemos o caractér `- (hífen)` , que se mostrou ser muito utilizado para separar o nome de tais autores.

![](https://imgur.com/3GGvJ5r.png) 

No que diz respeito ao cálculo de correlação entre os documentos do modelo e o documento da busca, utilizamos uma técnica que consiste em interseccionar o conjunto de palavras do maior dos documentos, seja o da query ou os do modelo (sendo este com muito mais frequência) com o outro documento, de forma que, quando existe um casamento entre tais conjuntos, o conteúdo do conjunto menor é excluído.

&nbsp;
&nbsp;

## Ambiente de Produção/Teste

Para executar os programas, só é necessário executar os seguintes comandos no terminal : 

```shell
make
./vmodel
```

**Observação**
- O diretório com os arquivos de documentos e consultas **cfc** assim como o arquivo de **stopword_en** devem estar no mesmo nível do executável

<center><img src="https://imgur.com/GJh207j.png"/></center>

Alguns detalhes do ambiente de desenvolvimento e de teste:
- Informações do Computador
    - Modelo: Toshiba Satellite P855
    - Processador: i7-3610QM 2.30 GHz (8 CPUs)
    - Memória: 8192MB RAM
- Informações do Sistema
    - Sistema Operacional: Windows 10 Pro 64 bits
    - Nodejs versão 8.1.0
    - NPM versão 5.0.3
    - Python 2.7v 32 bits

## Comparativo

Para realização das comparações, escolhemos as métricas `P@` e `MAP`.
O `P@` foi escolhido devido sua capacidade de avaliar uma recuperação classificada e ordenada por ordem de relevância de forma com que os documentos recuperados relevantes estejam entre os K primeiros documentos resultantes da consulta. Essa métrica parte do princípio de que o usuário verifica o resultado da consulta do topo para baixo até encontrar um resultado satisfatório ou desistir da consulta.
Com base nisso, achamos interessante medir a capacidade do nosso modelo de recuperar os documentos relevantes entre os K primeiros.

No que diz respeito à métrica `MAP`, tal métrica inside na pesquisa de resultados relevantes e na média de pontos de revocação. Escolhemos tal métrica uma vez que ela penaliza resultados muito distantes da origem, porém, auxilia os resultados mais relevantes.

Os resultados obtidos foram:

| Modelo        | Map Score           | P@ Score  |
| ------------- |:-------------:| -----:|
| Modelo Vetorial Simplificado      | 0.2301733568 | 0.4793650794 |
| Modelo Vetorial Otimizado      | 0.2808638129      |   0.5269841270 |

