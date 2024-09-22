# Convertool

Ce projet est un logiciel de conversion de formats d'image développé en C utilisant la bibliothèque SDL2. Il permet de convertir des images entre différents formats couramment utilisés.

## Fonctionnalités

- Conversion entre les formats PNG, JPEG, BMP, et ICO
- Interface graphique simple et intuitive
- Préservation de la qualité d'image lors de la conversion

## Prérequis

Pour compiler et exécuter ce projet, vous aurez besoin de :

- GCC ou un compilateur C compatible
- SDL2, SDL2_image et SDL_ttf
- mingw32-make

## Installation

1. Clonez ce dépôt :
   ```
   git clone https://github.com/piteurcodeur/convertool.git
   cd convertool
   ```

2. Créez un répertoire de build et naviguez dedans :
   ```
   mkdir build && cd build
   ```

3. Compilez le projet :
   ```
   mingw32-make
   ```

## Utilisation

Lancez le programme depuis le terminal :

```
./Convertool.exe
```

Suivez les instructions à l'écran pour :
1. Drag and drop l'image source dans la zone
2. Choisir le format de sortie et cliquer le bouton correspondant

## Structure du Projet

```
Convertool/
│
├── src/
│   ├── main.c
│   ├── background.c
│   ├── png2ico.c
│   ├── texte.c
│   └── utils.c
│
├── include/
│   ├── png2ico/
│   │   └── png2ico.h
│   ├── SDL2/
│   │   └── ...
│   ├── stb/
│   │   └── ...
│   ├── texte.h
│   ├── background.h
│   ├── SDL_ttf.h
│   └── utils.h
│
├── share/
│   └── aclocal
│        └── sdl2.m4
│
├── lib/
│   ├── libSDL2.a
│   └── ...
│
├── res/
│   ├── icone-t.png
│   ├── output.ico
│   └── icon.rc
│
├── install.iss
├── LICENSE
├── Makefile
└── README.md
```

## Contribution

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou à soumettre une pull request.

## Licence

Ce projet est sous licence MIT. Voir le fichier [MIT License](https://github.com/piteurcodeur/convertool/blob/main/LICENSE) pour plus de détails.