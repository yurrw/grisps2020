# Welcome to StackEdit!

Hi! I'm your first Markdown file in **StackEdit**. If you want to learn about StackEdit, you can read me. If you want to play with Markdown, you can edit me. Once you have finished with me, you can create new files by opening the **file explorer** on the left corner of the navigation bar.


# First things first
Primeiro, o objetivo desse projeto é apenas para estudo, nada feito aqui tem caráter malicioso e não me responsabilizo pela má-utilização desses códigos.

Boa parte desse projeto foi baseado em : https://www.youtube.com/watch?v=I-YKRKIA1Eo
créditos devidos dados à [Seytonic](https://www.youtube.com/channel/UCW6xlqxSY3gGur4PkGPEUeA) e [Spacehuhn](https://www.youtube.com/user/g0ldk/videos)

As maiores alterações são :
 - Página web com autoupdate
 - Código comentado 
 - Caracteres especiais como Enter, Backspace e os do numpad agora funcionam e são logados.
 - Modo troll

Material utilizado :

 1. Arduino leonardo
 2. USB host shield
 3. nodemcu
 4. protoboard e jumpers


## O que é um keylogger ? 
Um keylogger pode ser considerado como um *software* de monitoramento, onde o que é digitado e/ou visto é registrado para que outra pessoa veja também. Alguns pais utilizam keyloggers para monitorar o que seus filhos mais novos fazem na internet, contudo,boa parte do uso de keyloggers é por pessoas má-intencionadas para roubar dados de cartão, senhas de banco entre outros. Vale também comentar que além dos mais conhecidos keyloggers de software existem também os keyloggers físicos, que é, o objetivo desse trabalho.

#### Tipos de keyloggers
Além dos keyloggers de keystroke (que registram as teclas digitadas) também existem keyloggers que tiram print da tela a cada intervalo de tempo. 


## Por que um keylogger físico ?
Conforme o tempo vem passando, a concientização das pessoas sobre os meios online tem melhorado *(com ressalvas para fakenews)*, e vemos muitos casos onde o meio físico é tido como muito mais confiável, como por exemplo, as pessoas passam seus cartões em leitores rfid todo tempo, e muitas nem sabem o que realmente está acontecendo ali por trás ( https://www.infosec.com.br/seguranca-atraves-da-obscuridade/ ). O ponto é, as vezes, as coisas simples ( um usb no caso ) acabam se tornando o melhor ataque. 

Assim, com um modelo devidamente propotipatido do keylogger aqui apresentado, em tamanho pequeno, precisariamos apenas de acesso por alguns minutos a algum computador e pronto, já conseguiriamos acesso aos dados que estao sendo digitados, e tudo isso através da internet.

## Como funciona
Para acessarmos o output do keylogger basta conectarmos na rede gerada pelo *nodemcu* e acessarmos : 
		
	192.168.4.1/keylogger
		
É legal comentar o porque da escolha de um *Arduino Leonardo*, simplesmente quando conectamos o Leonardo em um computador o computador o reconhece como um dispositivo de entrada como mouse,teclado, ... já quando conectamos um *Arduino Uno* ele é reconhecido como um dispositivo serial, então, como queremos simular um teclado do outro lado de forma que não sejamos reconhecidos, usamos o Leonardo.

[Arduino Keylogger em funcionamento](https://www.youtube.com/watch?v=8gcdwo4wrDA&feature=youtu.be)
https://www.youtube.com/watch?v=8gcdwo4wrDA&feature=youtu.be

Comentários sobre o código:

Além de consultarmos o código do Seytonic, utilizamos como base o código de exemplo da lib do USB HOST SHIELD do arduino,e, em cima dele, apenas alteramos as principais funções que controlam keyDown e keyUp. Também precisamos verificar as teclas de escape/caracteres especiais, como return,backspace.  Assim, uma vez que as teclas estavam verificadas, utilizamos da lib ***"keyboard.h"***  com *.press(key)* e *.release(key)* para teclarmos, sendo key o valor em ascii ou em hex.
#### Modo troll
O modo troll foi uma adição ao keylogger, com ele, toda vez que a pessoa digita uma caracter no teclado tem a chance de vir outro caracter aleatório, tentei nao colocar um padrão para parecer com defeito do teclado. ( na verdade, tem um padrão, só que ele apresentou um comportamento não esperado - porque precisariamos travar a escrita na variavel -  contudo, achei esse comportamento menos suspeito, então deixei).

[Video no youtube do modo troll](https://www.youtube.com/watch?v=oL__Sit8u1A&feature=youtu.be)
https://www.youtube.com/watch?v=oL__Sit8u1A&feature=youtu.be


## Considerações finais
[aviso: a escrita abaixo é totalmente pessoal]
De fato quando durante o projeto eu acabei descobrindo que era menos complexo do que inicialmente eu tinha pensado- maioria das libs do arduino já tinha as funções prontas, caso eu tivesse implementando um virus que se propagasse pela rede teria, de fato, sido mais complexo (essa foi uma outra ideia).
Entretanto, eu acredito que o aprendizado tido nesse foi bem maior pra mim, meu conhecimento com arduino, soldagem, nodemcu, protoboard,... era quase nulo e sempre foi algo que quis aprender - logo quando chegou o shield USB já tive o primeiro problema, o shield nao funcionava, e eu nao consegui a principio descobrir o porque, só depois de muito pesquisar descobri que tinha que soldar 3 pontes no shield  - E EU NUNCA TINHA SOLDADO NADA NA VIDA (creditos ao Luiz e ao Sidney que me ajudaram muito nessa parte), sem contar toda parte de pesquisa e entender como a plaquinha funciona. Sem falar nas mágicas que da pra fazer só com o nodemcu.



