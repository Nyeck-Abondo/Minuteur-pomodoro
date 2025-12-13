#!/bin/bash

MAGENTA='\033[1;35m'
RED='\033[1;31m'
BLUE='\033[1;32m'

#chemins vers les libs
$SDL3_DIR="-I./libs/SDL3/include"
$SDL="-L./libs/SDL3/lib"
#En temps normal ici
#commande de compilation
clang++ src/main.cpp -o build/main.exe $SDL3_DIR $SDL -lSDL3 -lSDL3_ttf

#verification de la reussite de la commande precedente
if [ $? -eq 0 ]
then
echo -e "${MAGENTA}🎉 compilation terminée qvec succes !!${NC}"
echo "commande d'execution: ./build/main.exe"
else
echo "${BLUE}👾 Erreur de compilation${NC}"
exit 1
fi