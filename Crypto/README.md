# Crypt
Un moyen simple de (dé)crypter des données. Ce code est difficilement violable par une autre méthode que le brute-force.


# Plus d'info:

## Encode / decode char
Nous disposons d'une table de caractère (table ci-dessous) pour coder du texte de 8bit (256 possibilités) en 6bit (64 possibilités). Cela a pour but de pouvoir envoyer des messages de texte cryptés et non plus de simples données.

Les valeurs sont tirées de la table ASCII

    index |      donnée
     1-10 | '0'-'9' 0x30 - 0x39
    11-36 | 'A'-'Z' 0x41 - 0x5a
    37-62 | 'a'-'z' 0x61 - 0x7a
      63  |  space     0x20
      0   | extensible array

En plus de cette table j'ai ajouté une extension pour les caractères qui ne pouvait pas entrer dans la première table:

    index |      donnée
      0   |  '\0'      0x00
      1   |  '\n'      0x0a
     2-16 | '!'-'/' 0x21 - 0x2f
    17-23 | ':'-'@' 0x3a - 0x40
    24-29 | '['-'`' 0x5b - 0x60
    30-33 | '{'-'~' 0x7b - 0x7e

## Mask: C'est une méthode pour cacher des données grâce à un nombre (facile à décoder)
C'est une simple opération au niveau binaire.
  Voici comment cela fonctionne:  

```c++
  // Le ^ est l'oppération XOR
  1^1 = 0;
  0^1 = 1;
  1^0 = 1;
  0^0 = 0;
```
Si deux bits ont la même valeur le résultat sera 0, si les deux bits ont une valeur différente le résultat sera 1.

Exemple:

    11110000
           |---->00110011
    11001100

Dans le cas de mon programme je fait un mask de la valeur *array[V]* avec la valeur *array[V-1]* (celle juste avant) 
    
    input[4] = {0000, 0010, 0100, 0101}
    0000  --> 0011    étape 4 (cette valeur est calculée en dernier)
        input[0] ^ ouput[3] = output[0]
        0000 ^ 0011 = 0011
    
    0010  --> 0010    étape 1
        input[1] ^ input[0] = ouput[1]
        0010 ^ 0000 = 0010                              
    
    0100  --> 0110    étape 2 (j'utilise la valeur calculée)
        input[2] ^ output[1] = ouput[2]
        0100 ^ 0010 = 0110

    0101  --> 0011    étape 3 (j'utilise la valeur calculée)
        input[3] ^ output[2] = ouput[3]
        0101 ^ 0110 = 0011

Pour le décryptage c'est la même chose dans le sens inverse:
      
    ouput[4] = {0011, 0010, 0110, 0011}
    0011  --> 0000    étape 1
        ouptut[0] ^ output[3] = input[0]
        0011 ^ 0011 = 0000

    0010  --> 0010    étape 4
        output[1] ^ input[0] = input[1]
        0010 ^ 0000 = 0010

    0110  --> 0100    étape 3
        output[2] ^ output[1] = input[2]
        0110 ^ 0010 = 0100

    0011  --> 0101    étape 2
        output[3] ^ ouput[2] = input[3]
        0011 ^ 0110 = 0101

Cela nous donne {0000, 0010, 0100, 0101}

## Move: C'est une méthode pour changer les données de places dans un tableau pour les rendre inutilisable.

    key = {6, 8, 7, 9, 5, 4, 3, 2, 1, 0};
    data = {56, 78, 16, 38, 98, 21, 18, 85, 91, 61};
  
    key est un tableau donc chaque donnée a un index
    ex: 
      - l'index de 6 est 0
      - l'index de 8 est 1
      - l'index de 7 est 2
      - etc
    
La fonction:
```c
  for (byte i = 0; i < keylen; i++) {
    data1[ key[i] ] = data[i];
  }
```

  Au lieu de mettre la donnée *data* au même index que *data1* on la change de place, si on détaille la boucle cela fait:

    data1[ key[0] ] = data[0]   <=>   data1[6] = 56
    data1[ key[1] ] = data[1]   <=>   data1[8] = 78
    data1[ key[2] ] = data[2]   <=>   data1[7] = 16
    data1[ key[3] ] = data[3]   <=>   data1[9] = 38
    data1[ key[4] ] = data[4]   <=>   data1[5] = 98
    data1[ key[5] ] = data[5]   <=>   data1[4] = 21
    data1[ key[6] ] = data[6]   <=>   data1[3] = 18
    data1[ key[7] ] = data[7]   <=>   data1[2] = 85
    data1[ key[8] ] = data[8]   <=>   data1[1] = 91
    data1[ key[9] ] = data[9]   <=>   data1[0] = 61

Cela nous donne:

    data  --> {56, 78, 16, 38, 98, 21, 18, 85, 91, 61}
    data1 --> {61, 91, 85, 18, 21, 98, 56, 16, 78, 38}


Pour le décryptage c'est pareil dans le sens inverse.

La fonction:
```c
  for (byte i = 0; i < keylen; i++) {
    data[i] = data1[ key[i] ];
  }
```
      data[0] = data1[ key[0] ]   <=>   data[0] = data1[6]   <=>   data[0] = 56
      data[1] = data1[ key[1] ]   <=>   data[1] = data1[8]   <=>   data[1] = 78
      data[2] = data1[ key[2] ]   <=>   data[2] = data1[7]   <=>   data[2] = 16
      data[3] = data1[ key[3] ]   <=>   data[3] = data1[9]   <=>   data[3] = 38
      data[4] = data1[ key[4] ]   <=>   data[4] = data1[5]   <=>   data[4] = 98
      data[5] = data1[ key[5] ]   <=>   data[5] = data1[4]   <=>   data[5] = 21
      data[6] = data1[ key[6] ]   <=>   data[6] = data1[3]   <=>   data[6] = 18
      data[7] = data1[ key[7] ]   <=>   data[7] = data1[2]   <=>   data[7] = 85
      data[8] = data1[ key[8] ]   <=>   data[8] = data1[1]   <=>   data[8] = 91
      data[9] = data1[ key[9] ]   <=>   data[9] = data1[0]   <=>   data[9] = 61

Cela nous donne:

    data1 --> {61, 91, 85, 18, 21, 98, 56, 16, 78, 38}
    data --> {56, 78, 16, 38, 98, 21, 18, 85, 91, 61}
    
Ce tableau correspond à celui du début.
