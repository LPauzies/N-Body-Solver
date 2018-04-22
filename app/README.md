# App

## Installation
```
$ mkdir bin
$ make
$ cd web/Flask
$ [sudo] pip install virtualenv
$ virtualenv ENV
$ pip install -r requirements.txt

```

## Architecture des dossiers
- bin/ : Exécutable
- class/ : Classe C++
- log/ : Dossier de log
- web/Flask/static/ : Dossier contenant les fichiers CSS
- web/Flask/templates/ : Dossier contenant les fichiers html


## Compilation du C++
```
$ cd app/
$ make
```

## Lancer l'application web
```
$ export FLASK_APP=hello.py
$ flask run
```

## Envoyer les données
```
$ ./bin/prog -h

#========== N-Body Problem Solver Help documentation ==========#

-h or --help : display help of N-Body Problem Solver
-f or --file : (compulsory) using the program with this dataset path
-n or --nbit : (optionnal) if given, execute the program with this number of iterations else do 2000 iterations
-s or --socket : (optionnal) if given, execute the program with socket (cesga: client, serveur extern python:server, pc:client)
-p or --port : (optionnal) if given, execute the program on the port specified else 15556
-a or --adresse : (optionnal) if given, execute the program on the adresse specified else localhost

#========== N-Body Problem Solver Help documentation ==========#
```

Pour lancer sur les calculs sur C++ sur le localhost :
```
$ ./bin/prog -f ../data/test.csv -s -p 15556 -n 10000
```

## Lancer le benchmark
```
$ ./benchmark.sh -n 100 -f ../data/tab2.csv
```