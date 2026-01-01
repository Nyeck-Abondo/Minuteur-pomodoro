#!/bin/bash

#definition des couleurs
VERT='\033[0;32m'
ROUGE='\033[0;31m'
ORANGE='\033[38;5;208m'
JAUNE='\033[1;33m'
BLEU='\033[0;34m'
NC='\033[0m'

#definition des styles
GRAS='\033[1m'
CLIGNOTANT='\033[5m'

#definition des variables globales
VOID=" "
MODULE_DIR=""
LINK_HEADER=""

#cette fonction verifie si les dossiers des fichiers en tête sont effectivement présents
function verification_folder {
    if [ ! -z $1 ]
    then
        HEADER="-I./$1"
        LINK_HEADER="$LINK_HEADER$HEADER$VOID"
        echo -e "✅ ${VERT}Bibliothèque $2 trouvée${NC}"
        echo "Dessin des fenetres possibles. Aucun besoin de telechargement supplementaire"
        echo -e "${JAUNE}$LINK_HEADER${NC}"
        echo
    else
        echo -e "❌ ${ROUGE}ERREUR: bibliothèque $2 non trouvée !!${NC}"
        echo "Besoin impératif de la fibliotheque $2. Veillez vous la procurer"
        exit 1
    fi
}

#cors principal
echo -e "${JAUNE}${GRAS}======================================================================${NC}"
echo -e "${JAUNE}${GRAS}||LANCEMENT DU PROGRAMME DE COMPILATION DU PROJET MINUTEUR POMODORO ||${NC}"
echo -e "${JAUNE}${GRAS}======================================================================${NC}"
echo

#debut des phases de la compilation gnanga
echo -e "${VERT}${GRAS}[1/5]-collecte des emplacements des fichiers sources du code${NC}"
echo

##identification des fichiers sources présents dans src
if [ ! -z "src" ]
then
SRC="src"
    #parcours des element natifs de src
    for files in $(ls $SRC/*.cpp)
    do
        echo -e "🔃 ${BLEU}${GRAS} collecte des chemins d'acces des fichiers .cpp de :${NC} $files"
        sleep 0.75
        echo
        echo -e "fichier trouvé : ${ORANGE}$files${NC}"
        MODULE_DIR="$MODULE_DIR$files$VOID"
    done

    #parcours du dossier et de ses sous dossiers
    for folder in $(find "src" -mindepth 1 -maxdepth 2 -type d -print)
    do
        echo -e "🔃 ${BLEU}${GRAS} collecte des chemins d'acces des fichiers .cpp de :${NC} $folder"
        sleep 0.75
        #affichage des modules objets et des fichiers trouvés dans le dossier
        for file in $(ls $folder/*.cpp)
        do
        echo
        echo -e "fichier trouvé : ${ORANGE}$file${NC}"
        MODULE_DIR="$MODULE_DIR$file$VOID"
        done

        echo
    done
else
    echo "Abscence des fichiers source de src/ src non trouvé"
    exit 1
fi

#verification de l'existence de libs
if [ ! -z "libs" ]
then
    #parcours du dossier et de ses sous dossiers
    for folder in $(find "libs" -mindepth 1 -maxdepth 2 -type d -print)
    do
        echo -e "🔃 ${BLEU}${GRAS}collecte des chemins d'acces des fichiers .cpp de :${NC} $folder"
        sleep 0.75
        if [ $folder = "libs/ImGui_Arc_ProgressBar" ]
        then
            ARC=" libs/ImGui_Arc_ProgressBar/arc_progress_bar.cpp "
            MODULE_DIR="$MODULE_DIR$ARC"
        else
            #affichage des modules objets et des fichiers trouvés dans le dossier
            for file in $(ls $folder/*.cpp)
            do
                echo
                echo -e "fichier trouvé : ${ORANGE}$file${NC}"
                MODULE_DIR="$MODULE_DIR$file$VOID"
            done
        fi
    done
    echo

else
    echo "Abscence des bobliotheques statiques"
    exit 1
fi

echo "$MODULE_DIR"
echo -e "${ROUGE}${GRAS}[2/5]- verification de la présence des bibliotheques necessaire${NC}"
echo

echo "VERIFICATION DE LA PRESENCE DE LA SDL3"
echo
sleep 1
verification_folder "libs/SDL3" "SDL3"

echo "==========VERIFICATION DE LA PRESENCE DE IMGUI============="
echo
sleep 1
verification_folder "libs/imgui" "imgui"

echo "==========VERIFICATION DE LA PRESENCE DE IMGUI_TOGGLE============"
echo
sleep 1
verification_folder "libs/imgui_toggle" "imgui_toggle"

echo "===========VERIFICATION DE LA PRESENCE DE STB_IMGAGE================="
echo
sleep 1
verification_folder "libs/stb" "stb_image"

echo "==========VERIFICATION DE LA PRESENCE DE IMGUI_ARC_PROGRESS_BAR==============="
echo
sleep 1
verification_folder "libs/ImGui_Arc_ProgressBar" "imgui_arc_progressBar"

echo -e "${VERT}${GRAS}[3/5]-vérification de la presence du dossier build pour l'executables"

if [ ! -d "build" ]
then
    echo -e "${ROUGE}ABSCENCE DU DOSSIER ACCEUILLANT LES EXECUTABLES"
    sleep 0.5
    echo "🧰CREATION DU DOSSIER BUILD"
    mkdir build
else
    echo "✅ PRESESNCE DU DOSSIER BUILD POUR LA CREATION DE L'EXECUTABLE"
fi

echo -e "${VERT}${GRAS}[4/5]-vérification de la presence du dossier INCLUDE pour l'executables"
if [ ! -d "include" ]
then
    echo -e "${ROUGE}ABSCENCE DU DOSSIER ACCEUILLANT LES HEADERS LOCAUX"
    sleep 0.5
    echo "⚠️ARRET DU PROGRAMME DE COMPILATION"
    exit 1
else
    echo "✅ PRESESNCE DU DOSSIER INCLUDE POUR LES HEADERS LOCAUX"
    LOCAL_LINK=" -I./include -I./libs/imgui/backends -I./libs/SDL3/SDL3_image"
    LINK_HEADER="$LINKHEADER$LOCAL_LINK"
fi

echo -e "${JAUNE}${GRAS}[5/5] COMPILATION DES ELEMENTS DU PROJET${NC}"

COMPILER="clang++"
EXECUTABLE="build/pomodoro.exe"
LINKER="-lSDL3 -lSDL3_image"
VERSION="-std=c++17"

echo
echo "LANCEMENT DE LA COMMANDE DE COMPILATION...."
$COMPILER $MODULE_DIR -o  $EXECUTABLE $LINK_HEADER $LINKER $VERSION

echo "executez avec: ./build/pomodoro.exe"
#fin du programme en appuant sur une touche specifique
read -n 1 -s -p "appuyez sur n'importe quelle touche pour continuer"