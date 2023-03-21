### COMANDOS PARA COMPILAR, EXECUTAR E TESTAR O PROGRAMA

Para utilização desses comandos é necessário instalar o make na máquina. Para isso, execute o comando:

```
    sudo apt install make
```

 - Para compilar, basta digitar:

```
    make compile
```

 - Para executar o código:

```
    make run
 ```

 - Para gerar o teste de Leak Memory (Valgrind):

 ```
    make check
 ```
 
 **OBS.:** Para executar o comando acima, o valgrind deve estar instalado na máquina. Veja como instalar o valgrind [aqui](https://wiki.ubuntu.com/Valgrind)

 - Para gerar o arquivo tar.gz:

 ```
    make submission
 ```
