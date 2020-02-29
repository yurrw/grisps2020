# Dcrypter

    De forma simples, o código recupera a chave utilizada para 'encriptar' os arquivos, que está guardada em /tmp/key.
    Depois disso ele percorre todos os arquivos da pasta e, uma vez que para encriptar foi somado a key + cada_caracter_do_arquivo
    agora fazemos cada_caracter_do_arquivo - key.
    Por último o programa retira a extensão .leo dos arquivos.

## como rodar :

     > go run main.go      #caso o main.go esteja no mesmo local onde a pasta encriptada está
    ou
     > ./[TAG]RevENG/Dcrypt  

o arquivo precisa estar no mesmo local onde a pasta executada está, isto é, "./$USER/".
