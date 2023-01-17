#Outils
CXX			:=	g++
LD			:= 	g++
RM			:= 	rm
ECHO		:= 	echo
MKDIR		:= 	mkdir

#Options
CXXFLAGS	:= 	-ansi -pedantic -Wall -std=c++11 -g
DEVFLAGS	:= 	-DMAP
RMFLAGS		:= 	-rf

#Fichiers
EXECUTABLE	:= 	TP4
SRC_DIR		:= 	src/
OBJ_DIR		:= 	bin/
SRC			:= 	$(wildcard $(SRC_DIR)*.cpp)
OBJ			:= 	$(SRC:${SRC_DIR}%.cpp=$(OBJ_DIR)%.o)


#Cibles
.PHONY: all dev run clean fclean info help

all: $(EXECUTABLE)

dev: CXXFLAGS+=$(DEVFLAGS)
dev: clean all
	@$(ECHO) [MAKE] -- MODE DEVELOPPEMENT --

run: all
	@./$(EXECUTABLE)

clean:
	@$(ECHO) [MAKE] Suppression du dossier $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_DIR)

fclean:
	@$(ECHO) [MAKE] Suppression du dossier $(OBJ_DIR) et de $(EXECUTABLE)
	@$(RM) $(RMFLAGS) $(EXECUTABLE) $(OBJ_DIR)

help:
	@$(ECHO) "[*] make         Compilation et édition des liens"
	@$(ECHO) "[*] make dev     Compilation en mode développement et édition des liens"
	@$(ECHO) "[*] make run     Compilation, édition des liens et exécution du programme"
	@$(ECHO) "[*] make clean   Suppression des fichiers objets"
	@$(ECHO) "[*] make fclean  Suppression des fichiers objets et de l'exécutable"
	@$(ECHO) "[*] make info    Informations sur les fichiers"

info:
	@$(ECHO) "[*] Exécutable:      ${EXECUTABLE}"
	@$(ECHO) "[*] Dossier sources: ${SRC_DIR}"
	@$(ECHO) "[*] Dossier objets:  ${OBJ_DIR}"
	@$(ECHO) "[*] Sources:         ${SRC:${SRC_DIR}%=%}"
	@$(ECHO) "[*] Objets:          ${OBJ:${OBJ_DIR}%=%}"


$(EXECUTABLE): $(OBJ)
	@$(ECHO) [MAKE] Création de l\'exécutable $(EXECUTABLE)
	@$(LD) $^ -o $@ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(ECHO) [MAKE] Compilation de $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(ECHO) [MAKE] Création du fichier $(OBJ_DIR)
	@$(MKDIR) -p $@
