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
LINK_HEADER=""
OBJECTFILE= ""
OBJEXTENTION=".o"
BUILD="build/"
COMPILER="g++"
EXECUTABLE="pomodoro.exe"
SDLLINKER=" -L./libs -lSDL3 -lSDL3_image"
LINKER="-L./libs -lSDL3 -lSDL3_image -lsfml-audio-3 -lsfml-system-3"
VERSION="-std=c++17 -O2"
WARNING="-Wall -Wextra"

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

function create_object_file {
    echo -e "${VERT}${GRAS}[-]-vérification de la presence du dossier build pour l'executables"

    if [ ! -d "build" ]
    then
        echo -e "${ROUGE}ABSCENCE DU DOSSIER ACCEUILLANT LES EXECUTABLES${NC}"
        echo "🧰CREATION DU DOSSIER BUILD"
        mkdir build
    else
        echo "✅ PRESESNCE DU DOSSIER BUILD POUR LA CREATION DE L'EXECUTABLE"
    fi

    if [ ! -z $1 ]
    then
        for FOLDER in $(find "$1" -mindepth 0 -maxdepth 1 -type d -print)
        do
            if [ "$FOLDER" != "libs/SDL3" ] && [ "$FOLDER" != "libs/SDL3/SDL3_image" ] && [ "$FOLDER" != "libs/SFML" ] && [ "$FOLDER" != "libs/stb" ]
            then
                echo "Dossier: $FOLDER"
                for FILE in $(ls $FOLDER/*.cpp)
                do
                    if [ "$1" = "src" ]
                    then
                        OBJECTNAME="${FILE##*/}"
                        OBJECTNAME="${OBJECTNAME%.cpp}"
                        OBJECTARGET="${OBJECTNAME}.o"
                        echo -e "objet: ${BLEU}$OBJECTARGET${NC}"
                        $COMPILER -c $FILE $2 $LINKER -o $BUILD$OBJECTARGET
                        OBJECTFILE="$OBJECTFILE$BUILD$OBJECTARGET$VOID"
                    else
                        OBJECTNAME="${FILE##*/}"
                        OBJECTNAME="${OBJECTNAME%.cpp}"
                        OBJECTARGET="${OBJECTNAME}.o"
                        echo -e "objet: ${BLEU}$OBJECTARGET${NC}"
                        $COMPILER -c $FILE -I./libs/imgui -o $BUILD$OBJECTARGET
                        OBJECTFILE="$OBJECTFILE$BUILD$OBJECTARGET$VOID"
                    fi
                done
            fi
        done
        echo -e "${BLEU}$OBJECTFILE${NC}"
    else
    echo "Abscence des fichiers source de $1 non trouvé"
    exit 1
    fi
}

#cors principal
echo -e "${JAUNE}${GRAS}======================================================================${NC}"
echo -e "${JAUNE}${GRAS}||LANCEMENT DU PROGRAMME DE COMPILATION DU PROJET MINUTEUR POMODORO ||${NC}"
echo -e "${JAUNE}${GRAS}======================================================================${NC}"
echo





echo "$MODULE_DIR"
echo -e "${ROUGE}${GRAS}[2/5]- verification de la présence des bibliotheques necessaire${NC}"
echo

echo "VERIFICATION DES HEADERS"
echo
verification_folder "include" "headers de compilation"

echo "VERIFICATION DE LA PRESENCE DE LA SDL3"
echo
verification_folder "libs/SDL3" "SDL3"
verification_folder "libs/SDL3/SDL3_image" "SDL3_image"

echo "VERIFICATION DE LA PRESENCE DE IMGUI"
echo
verification_folder "libs/imgui" "imgui"

echo "VERIFICATION DE LA PRESENCE DE SFML"
echo
verification_folder "libs/SFML" "SFML"
verification_folder "libs/SFML/System" "SFML/System"

echo "VERIFICATION DE LA PRESENCE DE STB_IMGAGE"
echo
verification_folder "libs/stb" "stb_image"

echo "VERIFICATION DE LA PRESENCE DE IMGUI_ARC_PROGRESS_BAR"
echo
verification_folder "libs/ImGui_Arc_ProgressBar" "imgui_arc_progressBar"

#debut des phases de la compilation gnanga
echo -e "${VERT}${GRAS}[1/5]-collecte des emplacements des fichiers sources du code${NC}"
echo

##identification des fichiers sources présents dans src
create_object_file "src" "$LINK_HEADER"

#verification de l'existence de libs
create_object_file "libs"


echo -e "${VERT}${GRAS}[4/5]-vérification de la presence du dossier INCLUDE pour l'executables"
if [ ! -d "include" ]
then
    echo -e "${ROUGE}ABSCENCE DU DOSSIER ACCEUILLANT LES HEADERS LOCAUX"
    echo "⚠️ ARRET DU PROGRAMME DE COMPILATION"
    exit 1
else
    echo "✅ PRESESNCE DU DOSSIER INCLUDE POUR LES HEADERS LOCAUX"
    LOCAL_LINK=" -I./include -I./libs/imgui/backends -I./libs/SDL3/SDL3_image"
    LINK_HEADER="$LINKHEADER$LOCAL_LINK"
fi

echo -e "${JAUNE}${GRAS}[5/5] COMPILATION DES ELEMENTS DU PROJET${NC}"



echo
echo -e "${CLIGNOTANT}LANCEMENT DE LA COMMANDE DE COMPILATION....${NC}"
$COMPILER $OBJECTFILE $LINKER $WARNING $VERSION -o  $EXECUTABLE

echo -e "${ROUGE}[-]suression des fichiers objet (.o)${NC}"
for object in $(ls build/*.o)
do
    rm $object
done

echo "executez avec: ./build/pomodoro.exe"
#fin du programme en appuant sur une touche specifique
read -n 1 -s -p "appuyez sur n'importe quelle touche pour continuer"