#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET_COLOR "\x1b[0m"

//----------Funciones Auxiliares----------

void clearBuffer() {
  while((getchar()) != '\n');
}

char getYesOrNo(){
    char option;

    while(1){

        option = getchar();

        if (option == 'Y' || option == 'N'){
            break;

        }else{
            printf(RED "Letra invalida\n" CYAN "Por favor ingrese Y o N:" RESET_COLOR "\n");
        }
    }

    return option;
}

char getDifficulty(){
    char difficulty;

    while(1){

        difficulty = getchar();

        if (difficulty == 'F' || difficulty == 'M' || difficulty == 'D'){
            break;

        }else{
            printf(RED "Letra invalida\n" CYAN "Por favor ingrese F o M o D:" RESET_COLOR "\n");
        }
    }

    return difficulty;
}

char getTheAnswer(){
    char character;

    while(1){

        character = getchar();

        if (character == 'A' || character == 'B' || character == 'C'){
            break;

        }else{
            printf(RED "Letra invalida\n" CYAN "Por favor ingrese A o B o C:" RESET_COLOR "\n");
        }
    }

    return character;
}

bool validateQuestionID(char questionID[]){
    int size = strlen(questionID) - 1;

    if (questionID[0] != 'P'){
        return false;
    }

    for (int i = 1; i < size; i++){

        if (! isdigit(questionID[i])){
            return false;
        }
    }

    return true;
}

bool validateAnswersID(char answerID[]){
    int size = strlen(answerID) - 1;

    if (answerID[0] != 'R'){
        return false;
    }

    for (int i = 1; i < size; i++){

        if (! isdigit(answerID[i])){
            return false;
        }
    }

    return true;
}

bool validateCategory(char category[]){

    char history[] = "Historia", geography[] = "Geografia", biodiversity[] = "Biodiversidad";

    if (strcmp(category, history) == 0){
        return true;
    }
    if (strcmp(category, geography) == 0){
        return true;
    }
    if (strcmp(category, biodiversity) == 0){
        return true;
    }

    return false;
}

void CostaRicanFlag(){
    int i;

    for (i = 1; i <= 20; i++){
      printf(BLUE "%c" RESET_COLOR, 254);
    }

    printf("\n");

    for (i = 1; i <= 20; i++){
      printf(WHITE "%c" RESET_COLOR, 254);
    }

    printf("\n");

    for (i = 1; i <= 20; i++){
      printf(RED "%c" RESET_COLOR, 254);
    }

    printf("\n");

    for (i = 1; i <= 20; i++){
      printf(RED "%c" RESET_COLOR, 254);
    }

    printf("\n");

    for (i = 1; i <= 20; i++){
      printf(WHITE "%c" RESET_COLOR, 254);
    }

    printf("\n");

    for (i = 1; i <= 20; i++){
      printf(BLUE "%c" RESET_COLOR, 254);
    }

    printf("\n");
}

void removeLineBreak(char string[]){

    string[strlen(string) - 1] = '\0';

}

bool validateIdentificationCard(char identificationCard[]){

    int size = strlen(identificationCard);

    if (size != 9){
        return false;
    }

    for (int i = 0; i < size; i++){

        if (!isdigit(identificationCard[i])){
            return false;
        }
    }

    return true;
}

bool validateIsAlpha(char name[]){
    
    int size = strlen(name);

    for (int i = 0; i < size; i++){

        if (!isalpha(name[i]) && !isspace(name[i])){
            return false;
        }
    }

    return true;
}

bool validateDates(char date[]){

    int size = strlen(date);

    if (size != 8){
        return false;
    }

    for (int i = 0; i < size; i++){

        if (i == 2 || i == 5){
            if (date[i] != 47){
                return false;
            }
            else{
                continue;
            }
        }

        if (!isdigit(date[i])){
            return false;
        }
    }

    return true;
}

bool validateMail(char mail[]){
    
    if (!isalpha(mail[0])){
        return false;
    }

    int at = -1, dot = -1;
    int count = 0;

    for (int i = 0; i < strlen(mail); i++){
        
        if (mail[i] == '@'){
            at = i;
            count++;
        }
        else if (mail[i] == '.'){
            dot = i;
        }
    }

    if (at == -1 || dot == -1){
        return false;
    }

    if (count != 1){
        return false;
    }

    if (at > dot){
        return false;
    }

    return !(dot >= (strlen(mail) -1));
}

bool validateIsNum(char num[]){
    
    int size = strlen(num);

    for (int i = 0; i < size; i++){

        if (!isdigit(num[i])){
            return false;
        }
    }

    return true;
}

//----------Registrar pregunta y respuesta----------

/*
    Para las preguntas.
Entradas: ID de pregunta, pregunta, categoría y dificultad.
Salidas: La pregunta registrada y almacenada en la lista de pregintas.
Restricciones: ID de pregunta debe tener formato P000 y la dificultad debe ser una letra (F para facil, M para medio, D para dificil)

    Para las respuestas.

Entradas: ID de respuesta, tres respuestas, indicador de respuesta correcta.
Salidas: La respuesta registrada y almacenada en la lista de respuestas.
Restricciones: ID de respuesta debe tener formato R000 y el indicador debe ser una letra (A o B o C).
*/

typedef struct questionList{
    char questionID[10];
    char question[200];
    char category[50];
    char difficulty;
    struct questionList* head;
    struct questionList* next;
}questionNode;

void uploadQuestions(questionNode** questionList){

    FILE * ptrFile = fopen("QUESTIONS.csv", "r");

    char data[4][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        questionNode *newNode = (questionNode *) malloc(sizeof(questionNode));
        char aux[1];

        strcpy(newNode->questionID, data[0]);
        strcpy(newNode->question, data[1]);
        strcpy(newNode->category, data[2]);
        strcpy(aux, data[3]);
        newNode->difficulty = aux[1];

        newNode->next = NULL;

        if (*questionList == NULL){
            *questionList = newNode;
        }
        else{
            questionNode *last = *questionList;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void registerQuestion(questionNode** questionList){
    questionNode *newNode = (questionNode *) malloc(sizeof(questionNode));
    questionNode *last = *questionList;
    char currentQuestionID[10];
    int resultID;

    clearBuffer();

    printf(CYAN "Ingrese el ID de la pregunta (Ejemplo P036):\n" RESET_COLOR);

    while(1){

        fgets(currentQuestionID, 10, stdin);
        removeLineBreak(currentQuestionID);

        resultID = validateQuestionID(currentQuestionID);

        if (resultID == true){
            break;

        }else{
            printf(RED "El ID es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->questionID, currentQuestionID);

    char currentQuestion[200];

    printf(CYAN "Ingrese la pregunta:\n" RESET_COLOR);
    fgets(currentQuestion, 200, stdin);
    removeLineBreak(currentQuestion);
    strcpy(newNode->question, currentQuestion);

    char currentCategory[50];

    printf(CYAN "Ingrese la categoria:\n" RESET_COLOR);
    fgets(currentCategory, 50, stdin);
    removeLineBreak(currentCategory);
    strcpy(newNode->category, currentCategory);

    printf(CYAN "Ingrese la dificultad\n" RESET_COLOR);
    printf(YELLOW "F = Facil -> M = Media -> D = Dificl\n" RESET_COLOR);
    newNode->difficulty = getDifficulty();

    newNode->next = NULL;

    if (*questionList == NULL){
        *questionList = newNode;
        printf(GREEN "Pregunta registrada exitosamente\n" RESET_COLOR);
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
    printf(GREEN "Pregunta registrada exitosamente\n" RESET_COLOR);

    clearBuffer();
    return;
}

int getSizeQuestionsList(questionNode** questionList){
    int size = 0;
    questionNode* current = *questionList;

    while (current != NULL){
        size++;
        current = current->next;
    }

    return size;
}

typedef struct answersList{
    char answersID[10];
    char answerA[100];
    char answerB[100];
    char answerC[100];
    char indicator;
    struct answersList* head;
    struct answersList* next;
}answersNode;

void uploadAnswers(answersNode** answersList){

    FILE * ptrFile = fopen("ANSWERS.csv", "r");

    char data[5][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }
               
        answersNode *newNode = (answersNode *) malloc(sizeof(answersNode));
        char aux[1];

        strcpy(newNode->answersID, data[0]);
        strcpy(newNode->answerA, data[1]);
        strcpy(newNode->answerB, data[2]);
        strcpy(newNode->answerC, data[3]);
        strcpy(aux, data[4]);
        newNode->indicator = aux[1];

        newNode->next = NULL;

        if (*answersList == NULL){
            *answersList = newNode;
        }
        else{
            answersNode *last = *answersList;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void registerAnswers(answersNode** answersList){
    answersNode *newNode = (answersNode *) malloc(sizeof(answersNode));
    answersNode *last = *answersList;
    char currentAnswerID[10];
    int resultID;

    clearBuffer();

    printf(CYAN "Ingrese el ID de la respuesta (Ejemplo R036):\n" RESET_COLOR);

    while (1){

        fgets(currentAnswerID, 10, stdin);
        removeLineBreak(currentAnswerID);

        resultID = validateAnswersID(currentAnswerID);

        if (resultID == true){
            break;

        }else{
            printf(RED "El ID es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->answersID, currentAnswerID);

    char currentAnswerA[100];

    printf(CYAN "Ingrese la respuesta A:\n" RESET_COLOR);
    fgets(currentAnswerA, 100, stdin);
    removeLineBreak(currentAnswerA);
    strcpy(newNode->answerA, currentAnswerA);

    char currentAnswerB[100];

    printf(CYAN "Ingrese la respuesta B:\n" RESET_COLOR);
    fgets(currentAnswerB, 100, stdin);
    removeLineBreak(currentAnswerB);
    strcpy(newNode->answerB, currentAnswerB);

    char currentAnswerC[100];

    printf(CYAN "Ingrese la respuesta C:\n" RESET_COLOR);
    fgets(currentAnswerC, 100, stdin);
    removeLineBreak(currentAnswerC);
    strcpy(newNode->answerC, currentAnswerC);

    printf(CYAN "¿Cual es la respuesta correcta? ¿A o B o C?\n" RESET_COLOR);
    newNode->indicator = getTheAnswer();

    newNode->next = NULL;

    if (*answersList == NULL){
        *answersList = newNode;
        printf(GREEN "Respuesta registrada exitosamente\n" RESET_COLOR);
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
    printf(GREEN "Respuesta registrada exitosamente\n" RESET_COLOR);

    clearBuffer();
    return;
}

//----------Modificar o remover pregunta----------
/*
Entradas: ID de pregunta.
Salidas: Los datos: pregunta, categoria, dificultad, respuestas e indicador modificador o removidos según lo desee el usuario.
Restricciones: ID de pregunta debe tener formato P000, la dificultad debe ser una letra (F para facil, M para medio, D para dificil),
               ID de respuesta debe tener formato R000 y el indicador debe ser una letra (A o B o C).
*/

char modifyOrRemoveQuestion(){
    char choice;

    clearBuffer();

    while (1){

        choice = getchar();

        if (choice == 'M' || choice == 'R'){
            break;

        }else{
            printf(RED "Opcion invalida\n" CYAN "Por favor ingrese M o R\n" RESET_COLOR);
        }
    }

    return choice;
}

void modifyQuestion(questionNode** questionList, answersNode** answersList){

    questionNode *ptrQuestion = *questionList;
    answersNode *ptrAnswer = *answersList;
    int resultID;
    char yesOrNo_1, yesOrNo_2, yesOrNo_3, yesOrNo_4, yesOrNo_answer;
    char newQuestion[200], newCategory[50], qID[10];
    int resultAnswerID;
    char yesOrNo_5, yesOrNo_6, yesOrNo_7, yesOrNo_8;
    char newAnswerA[100], newAnswerB[100], newAnswerC[100], aID[10];

    printf(CYAN "Ingrese el ID de la pregunta (Ejemplo P036):\n" RESET_COLOR);

    while(1){

        fgets(qID, 10, stdin);
        removeLineBreak(qID);
        resultID = validateQuestionID(qID);

        if (resultID == true){
            break;

        }else{
            printf(RED "El ID es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    while (ptrQuestion != NULL){
        if (strcmp(ptrQuestion->questionID, qID) == 0){

            printf(CYAN "¿Quieres modificar la pregunta? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
            yesOrNo_1 = getYesOrNo();

            if (yesOrNo_1 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese la nueva pregunta:\n" RESET_COLOR);
                fgets(newQuestion, 200, stdin);
                removeLineBreak(newQuestion);
                strcpy(ptrQuestion->question, newQuestion);

            }else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "¿Quieres modificar la categoria? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
            yesOrNo_2 = getYesOrNo();

            if (yesOrNo_2 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese la nueva categoria:\n" RESET_COLOR);
                fgets(newCategory, 200, stdin);
                removeLineBreak(newCategory);
                strcpy(ptrQuestion->category, newCategory);

            }else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "¿Quieres modificar la dificultad? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
            yesOrNo_3 = getYesOrNo();

            if (yesOrNo_3 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese la nueva dificultad:\n" RESET_COLOR);
                printf(YELLOW "F = Facil -> M = Media -> D = Dificl\n" RESET_COLOR);
                ptrQuestion->difficulty = getDifficulty();

            }else{
                printf(CYAN "Ok\n" RESET_COLOR);
            }

            printf(GREEN "Pregunta modificada exitosamente\n" RESET_COLOR);

            break;
        }

        ptrQuestion = ptrQuestion->next;
    }

    if (ptrQuestion == NULL){
        printf(YELLOW "Pregunta no encontrada\n" RESET_COLOR);
        return;
    }

    printf(CYAN "¿Quieres modificar la respuesta asociada a esta pregunta? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
    yesOrNo_answer = getYesOrNo();

    if (yesOrNo_answer == 'Y'){
        
        printf(CYAN "Ingrese el ID de la respuesta (Ejemplo R036):\n" RESET_COLOR);

        while(1){

            fgets(aID, 10, stdin);
            removeLineBreak(aID);
            resultAnswerID = validateAnswersID(aID);

            if (resultAnswerID == true){
                break;

            }else{
                printf(RED "El ID es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
            }
        }

        while (ptrAnswer != NULL){
            if (strcmp(ptrAnswer->answersID, aID) == 0){

                printf(CYAN "¿Quieres modificar la respuesta A? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
                yesOrNo_5 = getYesOrNo();

                if (yesOrNo_5 == 'Y'){
                    clearBuffer();
                    printf(CYAN "Ingrese la nueva respuesta:\n" RESET_COLOR);
                    fgets(newAnswerA, 100, stdin);
                    removeLineBreak(newAnswerA);
                    strcpy(ptrAnswer->answerA, newAnswerA);

                }else{
                    printf(CYAN "Ok\n" RESET_COLOR);
                    clearBuffer();
                }

                printf(CYAN "¿Quieres modificar la respuesta B? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
                yesOrNo_6 = getYesOrNo();

                if (yesOrNo_6 == 'Y'){
                    clearBuffer();
                    printf(CYAN "Ingrese la nueva respuesta:\n" RESET_COLOR);
                    fgets(newAnswerB, 100, stdin);
                    removeLineBreak(newAnswerB);
                    strcpy(ptrAnswer->answerB, newAnswerB);

                }else{
                    printf(CYAN "Ok\n" RESET_COLOR);
                    clearBuffer();
                }

                printf(CYAN "¿Quieres modificar la respuesta C? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
                yesOrNo_7 = getYesOrNo();

                if (yesOrNo_7 == 'Y'){
                    clearBuffer();
                    printf(CYAN "Ingrese la nueva respuesta:\n" RESET_COLOR);
                    fgets(newAnswerC, 100, stdin);
                    removeLineBreak(newAnswerC);
                    strcpy(ptrAnswer->answerC, newAnswerC);

                }else{
                    printf(CYAN "Ok\n" RESET_COLOR);
                    clearBuffer();
                }

                printf(CYAN "¿Quieres modificar el indicador? Ingrese Y para afirmar o N para negar\n" RESET_COLOR);
                yesOrNo_8 = getYesOrNo();

                if (yesOrNo_8 == 'Y'){
                    clearBuffer();
                    printf(CYAN "Cual es la nueva respuesta correcta? A o B o C?:\n" RESET_COLOR);
                    ptrAnswer->indicator = getTheAnswer();

                }else{
                    printf(CYAN "Ok\n" RESET_COLOR);
                }

                printf(GREEN "Respuesta modificada exitosamente\n" RESET_COLOR);

                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        if (ptrAnswer == NULL){
            printf(YELLOW "Respuesta no encontrda\n" RESET_COLOR);
            return;
        }

    }else{
        printf(CYAN "Ok\n" RESET_COLOR);
    }
}

void removeQuestion(questionNode **questionList, answersNode **answersList){
    questionNode *currentQuestion = *questionList, *previousQuestion;
    answersNode *currentAnswer = *answersList, *previousAnswer;
    int resultQuestionID;
    int resultAnswerID;
    char qID[10];
    char rID[10];
    char qIDaux[10];

    printf(CYAN "Ingrese el ID de la pregunta a eliminar (Ejemplo P036):\n" RESET_COLOR);

    while(1){

        fgets(qID, 10, stdin);
        removeLineBreak(qID);
        resultQuestionID = validateQuestionID(qID);

        if (resultQuestionID == true){
            break;

        }else{
            printf(RED "El ID es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(qIDaux, qID);
    qIDaux[0] = 'R';
    strcpy(rID, qIDaux);

    if (currentQuestion != NULL && strcmp(currentQuestion->questionID, qID) == 0){
        *questionList = currentQuestion->next;
        printf(GREEN "Se ha eliminado la pregunta %s\n" RESET_COLOR, currentQuestion->questionID);
        free(currentQuestion);
    }

    if (currentAnswer != NULL && strcmp(currentAnswer->answersID, rID) == 0){
        *answersList = currentAnswer->next;
        printf(GREEN "Se ha eliminado la respuesta %s\n" RESET_COLOR, currentAnswer->answersID);
        free(currentAnswer);
        return;
    }

    while (currentQuestion != NULL && strcmp(currentQuestion->questionID, qID) != 0){
        previousQuestion = currentQuestion;
        currentQuestion = currentQuestion->next;
    }

    while (currentAnswer != NULL && strcmp(currentAnswer->answersID, rID) != 0){
        previousAnswer = currentAnswer;
        currentAnswer = currentAnswer->next;
    }

    if (currentQuestion == NULL){
        printf(RED "Pregunta no encontrada\n" RESET_COLOR);
        return;
    }

    previousQuestion->next = currentQuestion->next;
    previousAnswer->next = currentAnswer->next;

    printf(GREEN "Se ha eliminado la pregunta %s\n" RESET_COLOR, currentQuestion->questionID);
    printf(GREEN "Se ha eliminado la respuesta %s\n" RESET_COLOR, currentAnswer->answersID);

    free(currentQuestion);
    free(currentAnswer);
}

//----------Consultar lista de preguntas registradas----------
/*
Entradas: no hay
Salida: la lista de preguntas y respuestas registradas en el sistema.
Restricciones: no hay.
*/

void showQuestionList(questionNode *questionList){
    questionNode *i;

    if (questionList == NULL){
        printf(RED "Lista vacia\n" RESET_COLOR);
        return;
    }

    printf(CYAN "Las preguntas registradas son:\n" RESET_COLOR);
    
    for (i = questionList; i != NULL; i = i->next){
        printf(YELLOW "     ID Pregunta: %s     \n" RESET_COLOR, i->questionID);
        printf(CYAN "Pregunta:" RESET_COLOR " %s\n", i->question);
        printf(CYAN "Categoria:" RESET_COLOR " %s\n", i->category);
        printf(CYAN"Dificultad:" RESET_COLOR " %c\n", i->difficulty);
    }
    
    printf("\n");
}

void showAnswersList(answersNode *answersList){
    answersNode *i;

    if (answersList == NULL){
        printf(RED "Lista vacia\n" RESET_COLOR);
        return;
    }

    printf(CYAN "Las respuestas registradas son:\n" RESET_COLOR);
    
    for (i = answersList; i != NULL; i = i->next){
        printf(YELLOW "     ID Respuesta: %s     \n" RESET_COLOR, i->answersID);
        printf(CYAN "Respuesta A:" RESET_COLOR " %s\n", i->answerA);
        printf(CYAN "Respuesta B:" RESET_COLOR " %s\n", i->answerB);
        printf(CYAN "Respuesta C:" RESET_COLOR " %s\n", i->answerC);
        printf(CYAN "Respuesta correcta:" RESET_COLOR " %c\n", i->indicator);
    }
    
    printf("\n");
}

//----------Registrar jugador----------
/*
Entradas: cédula del jugador, nickname, nombre completo, fecha de nacimiento, correo, lugar de residencia.
Salida: el jugador registrado en la lista circular doblemente enlazada utilizada para el registro de los jugadores. 
Restricciones: el numero de cedula debe estar compuesto de numeros, la fecha de nacimiento debe tener formato xx/xx/xxxx,
               el correo debe cumplir con el formato ejemplo@dominio.prefijo. 
*/

typedef struct playersList{
    char IdentificationCard[15];
    char nickname[30];
    char playerName[50];
    char lastName[50];
    char SecondLastName[50];
    char bornDate[15];
    char mail[100];
    char place[30];
    struct playersList* next;
    struct playersList* previous;
}playersNode;

void uploadPlayers(playersNode** playersList){

    FILE * ptrFile = fopen("PLAYERS.csv", "r");

    char data[8][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        playersNode *newNode = (playersNode *) malloc(sizeof(playersNode));

        strcpy(newNode->IdentificationCard, data[0]);
        strcpy(newNode->nickname, data[1]);
        strcpy(newNode->playerName, data[2]);
        strcpy(newNode->lastName, data[3]);
        strcpy(newNode->SecondLastName, data[4]);
        strcpy(newNode->bornDate, data[5]);
        strcpy(newNode->mail, data[6]);
        strcpy(newNode->place, data[7]);

        if (*playersList == NULL){
            newNode->next = newNode->previous = newNode;
            *playersList = newNode;
        }
        else{
            playersNode *last = (*playersList)->previous;
            newNode->next = *playersList;
            (*playersList)->previous = newNode;
            newNode->previous = last;
            last->next = newNode;
        }
    }

    fclose(ptrFile);
}

void appendPlayers(playersNode** playersList){
    playersNode *newNode = (playersNode *) malloc(sizeof(playersNode));

    char currentID[15];
    bool resID;
    printf(CYAN "Ingrese la cedula del jugador:\n" RESET_COLOR);

    while (1){

        fgets(currentID, sizeof(currentID), stdin);
        removeLineBreak(currentID);

        resID = validateIdentificationCard(currentID);

        if (resID){
            break;
        }
        else{
            printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }
    
    strcpy(newNode->IdentificationCard, currentID);

    char currentNickname[30];
    printf(CYAN "Ingrese el nickname del jugador:\n" RESET_COLOR);
    fgets(currentNickname, sizeof(currentNickname), stdin);
    removeLineBreak(currentNickname);
    strcpy(newNode->nickname, currentNickname);

    char currentPlayerName[50];
    bool resName;
    printf(CYAN "Ingrese el nombre del jugador:\n" RESET_COLOR);
    
    while (1){

        fgets(currentPlayerName, sizeof(currentPlayerName), stdin);
        removeLineBreak(currentPlayerName);

        resName = validateIsAlpha(currentPlayerName);

        if (resName){
            break;
        }
        else{
            printf(RED "El nombre es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->playerName, currentPlayerName);

    char currentLastName[50];
    bool resLastName;
    printf(CYAN "Ingrese el primer apellido del jugador:\n" RESET_COLOR);
    
    while (1){

        fgets(currentLastName, sizeof(currentLastName), stdin);
        removeLineBreak(currentLastName);

        resLastName = validateIsAlpha(currentLastName);

        if (resLastName){
            break;
        }
        else{
            printf(RED "El apellido es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->lastName, currentLastName);

    char currentSecondLastName[50];
    bool resSecLastName;
    printf(CYAN "Ingrese el segundo apellido del jugador:\n" RESET_COLOR);
    
    while (1){

        fgets(currentSecondLastName, sizeof(currentSecondLastName), stdin);
        removeLineBreak(currentSecondLastName);

        resSecLastName = validateIsAlpha(currentSecondLastName);

        if (resSecLastName){
            break;
        }
        else{
            printf(RED "El apellido es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->SecondLastName, currentSecondLastName);

    char currentBornDate[15];
    bool resDate;
    printf(CYAN "Ingrese la fecha de nacimiento del jugador en formato xx/xx/xxxx:\n" RESET_COLOR);

    while (1){

        clearBuffer();

        fgets(currentBornDate, sizeof(currentBornDate), stdin);
        removeLineBreak(currentBornDate);
        resDate = validateDates(currentBornDate);

        if (resDate){
            break;
        }
        else{
            printf(RED "La fecha es invalida\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    strcpy(newNode->bornDate, currentBornDate);

    char currentMail[100];
    bool resMail;
    printf(CYAN "Ingrese el mail del jugador:\n" RESET_COLOR);
    
    while (1){

        fgets(currentMail, sizeof(currentMail), stdin);
        removeLineBreak(currentMail);

        resMail = validateMail(currentMail);

        if (resMail){
            break;
        }
        else{
            printf(RED "El mail es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }
    
    strcpy(newNode->mail, currentMail);

    char currentPlace[30];
    bool resPlace;
    printf(CYAN "Ingrese el lugar de residencia del jugador:\n" RESET_COLOR);

    while (1){

        fgets(currentPlace, sizeof(currentPlace), stdin);
        removeLineBreak(currentPlace);

        resPlace = validateIsAlpha(currentPlace);

        if (resPlace){
            break;
        }
        else{
            printf(RED "El lugar de residencia es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }
    
    strcpy(newNode->place, currentPlace);

    if (*playersList == NULL){
        newNode->next = newNode->previous = newNode;
        *playersList = newNode;
        printf(GREEN "Jugador registrado exitosamente\n" RESET_COLOR);
        return;
    }

    playersNode *last = (*playersList)->previous;
    newNode->next = *playersList;
    (*playersList)->previous = newNode;
    newNode->previous = last;
    last->next = newNode;
    printf(GREEN "Jugador registrado exitosamente\n" RESET_COLOR);
}

//----------Modificar información del jugador----------
/*
Entradas: numero de cédula de jugador.
Salidas: el sistema permite la modificación de los datos asociados al jugador
Restricciones: el numero de cedula debe estar compuesto de numeros, la fecha de nacimiento debe tener formato xx/xx/xxxx,
               el correo debe cumplir con el formato ejemplo@dominio.prefijo.
*/

void modifyPlayer(playersNode** playersList){

    playersNode *ptrPlayer = *playersList;

    char currentID[15];
    bool resID;
    printf(CYAN "Ingrese la cedula del jugador a modificar:\n" RESET_COLOR);

    while (1){

        fgets(currentID, sizeof(currentID), stdin);
        removeLineBreak(currentID);

        resID = validateIdentificationCard(currentID);

        if (resID){
            break;
        }
        else{
            printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    char newNickname[30], newName[50], newLastName[50], newSecondLastName[50], newBornDate[10], newMail[100], newPlace[30];

    char yesOrNo_1, yesOrNo_2, yesOrNo_3, yesOrNo_4, yesOrNo_5, yesOrNo_6, yesOrNo_7;

    bool resName, resLast, restSecLast, resDate, resMail, resPlace;

    do{

        if (strcmp(ptrPlayer->IdentificationCard, currentID) == 0){

            printf(CYAN "Quieres modificar el nickname? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_1 = getYesOrNo();

            if (yesOrNo_1 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese el nuevo nickname:\n" RESET_COLOR);
                fgets(newNickname, sizeof(newNickname), stdin);
                removeLineBreak(newNickname);
                strcpy(ptrPlayer->nickname, newNickname);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar el nombre? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_2 = getYesOrNo();

            if (yesOrNo_2 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese el nuevo nombre:\n" RESET_COLOR);

                while (1){

                    fgets(newName, sizeof(newName), stdin);
                    removeLineBreak(newName);

                    resName = validateIsAlpha(newName);

                    if (resName){
                        break;
                    }
                    else{
                        printf(RED "El nombre es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                
                strcpy(ptrPlayer->playerName, newName);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar el primer apellido? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_3 = getYesOrNo();

            if (yesOrNo_3 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese el nuevo apellido:\n" RESET_COLOR);

                while (1){

                    fgets(newLastName, sizeof(newLastName), stdin);
                    removeLineBreak(newLastName);

                    resLast = validateIsAlpha(newLastName);

                    if (resLast){
                        break;
                    }
                    else{
                        printf(RED "El nombre es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }

                strcpy(ptrPlayer->lastName, newLastName);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar el segundo apellido? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_4 = getYesOrNo();

            if (yesOrNo_4 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese el nuevo apellido:\n" RESET_COLOR);

                while (1){

                    fgets(newSecondLastName, sizeof(newSecondLastName), stdin);
                    removeLineBreak(newSecondLastName);

                    restSecLast = validateIsAlpha(newSecondLastName);

                    if (restSecLast){
                        break;
                    }
                    else{
                        printf(RED "El nombre es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                
                strcpy(ptrPlayer->SecondLastName, newSecondLastName);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar la fecha de nacimiento? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_5 = getYesOrNo();

            if (yesOrNo_5 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese la nueva fecha en formato xx/xx/xxxx:\n" RESET_COLOR);

                while (1){

                    fgets(newBornDate, sizeof(newBornDate), stdin);
                    removeLineBreak(newBornDate);

                    resDate = validateDates(newBornDate);

                    if (resDate){
                        break;
                    }
                    else{
                        printf(RED "La fecha es invalida\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
               
                strcpy(ptrPlayer->bornDate, newBornDate);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar el mail? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_6 = getYesOrNo();

            if (yesOrNo_6 == 'Y'){

                printf(CYAN "Ingrese el nuevo mail:\n" RESET_COLOR);

                while (1){

                    fgets(newMail, sizeof(newMail), stdin);
                    removeLineBreak(newMail);

                    resMail = validateMail(newMail);

                    if (resMail){
                        break;
                    }
                    else{
                        printf(RED "El mail es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                
                strcpy(ptrPlayer->mail, newMail);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(CYAN "Quieres modificar el lugar de residencia? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);
            yesOrNo_7 = getYesOrNo();

            if (yesOrNo_7 == 'Y'){
                clearBuffer();
                printf(CYAN "Ingrese el nuevo lugar de residencia:\n" RESET_COLOR);

                while (1){

                    fgets(newPlace, sizeof(newPlace), stdin);
                    removeLineBreak(newPlace);

                    resPlace = validateIsAlpha(newPlace);

                    if (resPlace){
                        break;
                    }
                    else{
                        printf(RED "El lugar de residencia es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                
                strcpy(ptrPlayer->place, newPlace);
            }
            else{
                printf(CYAN "Ok\n" RESET_COLOR);
                clearBuffer();
            }

            printf(GREEN "Informacion del jugador modificada exitosamente\n" RESET_COLOR);
            
            return;
        }
        ptrPlayer = ptrPlayer->next;

    } while (ptrPlayer != *playersList);

    printf(YELLOW "Jugador no encontrado\n" RESET_COLOR);
}

//Cargar pila con informacion de las partidas de juego para utilizar los datos en las proximas funciones

typedef struct gameInfoNode{
    char id[15];
    int goodQuestions;
    int badQuestions;
    int points;
    char gameDate[10];
    struct gameInfoNode *next;
}nodeStackGameInfo;

typedef struct gameInformation{
    nodeStackGameInfo *top;
}gameInfoSatck;

void uploadGameInfo(gameInfoSatck *gameInfo){

    FILE * ptrFile = fopen("GAMEINFO.csv", "r");

    char data[5][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        int good, bad, pts;

        good = atoi(data[1]);
        bad = atoi(data[2]);
        pts = atoi(data[3]);

        nodeStackGameInfo *newNode = (nodeStackGameInfo *) malloc(sizeof(nodeStackGameInfo));

        newNode->next = NULL;

        strcpy(newNode->id, data[0]);
        newNode->goodQuestions = good;
        newNode->badQuestions = bad;
        newNode->points = pts;
        strcpy(newNode->gameDate, data[4]);

        newNode->next = gameInfo->top;
        gameInfo->top = newNode;
    }

    fclose(ptrFile);
}

//----------Consultar información del jugador----------
/*
Entradas: el número de cédula del jugador a consultar
Salidas: la información asociada al jugador.
Restricciones: el número de cédula debe estar conformado por números. 
*/
void showPlayersList(playersNode *playersList, gameInfoSatck *gameInfo){
    playersNode *aux = playersList;
    nodeStackGameInfo *i;
    char yesOrNo;
    bool flag = false;

    if (aux == NULL){
        printf(RED "Lista vacia\n" RESET_COLOR);
        return;
    }

    printf(CYAN "Los jugadores registrados son:\n" RESET_COLOR);
    
    do{
        printf(YELLOW "     Cedula: %s     \n" RESET_COLOR, aux->IdentificationCard);
        printf(CYAN "Nombre:" RESET_COLOR " %s %s %s\n", aux->playerName, aux->lastName, aux->SecondLastName);

        aux = aux->next;
    } while (aux != playersList);

    printf(CYAN "Desea consultar un jugador en particular? Ingrese Y para afirmar o N para negar:\n" RESET_COLOR);

    yesOrNo = getYesOrNo();

    if (yesOrNo == 'Y'){
        char currentID[15];
        bool resID;
        printf(CYAN "Ingrese la cedula del jugador a consultar:\n" RESET_COLOR);

        while (1){

            fgets(currentID, sizeof(currentID), stdin);
            removeLineBreak(currentID);

            resID = validateIdentificationCard(currentID);

            if (resID){
                break;
            }
            else{
                printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
            }
        }

        aux = playersList;

        do{
            if (strcmp(aux->IdentificationCard, currentID) == 0){

                printf(YELLOW "     Jugador: %s     \n" RESET_COLOR, aux->nickname);
                printf(CYAN "Cedula:" RESET_COLOR " %s\n", aux->IdentificationCard);
                printf(CYAN "Nombre:" RESET_COLOR " %s\n", aux->playerName);
                printf(CYAN "Apellido 1:" RESET_COLOR " %s\n", aux->lastName);
                printf(CYAN "Apellido 2:" RESET_COLOR " %s\n", aux->SecondLastName);
                printf(CYAN "Nacimiento:" RESET_COLOR " %s\n", aux->bornDate);
                printf(CYAN "Mail:" RESET_COLOR " %s\n", aux->mail);
                printf(CYAN "Residencia:" RESET_COLOR " %s", aux->place);

                for (i = gameInfo->top; i != NULL; i = i->next){

                    if (strcmp(i->id, currentID) == 0){

                        flag = true;

                        printf(CYAN "Fecha de juego:" RESET_COLOR " %s", i->gameDate);
                        printf(CYAN "Puntaje obtenido:" RESET_COLOR " %d\n", i->points);
                    }
                }

                if (flag == false){
                    printf(RED "\nEl jugador no tiene partidas asociadas\n" RESET_COLOR);
                }

                return;
            }

            aux = aux->next;
            
        } while (aux != playersList);
        
        printf(YELLOW "Jugador no encontrado\n" RESET_COLOR);
    }
    else{
        printf(CYAN "Ok\n" RESET_COLOR);
        clearBuffer();
        return;
    }
}

//----------Eliminar información del jugador----------
/*
Entradas: el número de cédula del jugador a consultar
Salidas: la eliminación del jugador si no tiene partidas asociadas o mensaje de error si el jugador tiene partidas asociadas. 
Restricciones: el número de cédula debe estar conformado por números. 
*/
bool associatedMatch(gameInfoSatck *gameInfo, char playerID[]){

    nodeStackGameInfo *i;
    bool flag = false;

    for (i = gameInfo->top; i != NULL; i = i->next){

        if (strcmp(i->id, playerID) == 0){
            flag = true;
            return flag;
        }
    }

    return flag;
}

void deletePlayer(playersNode *playersList, gameInfoSatck *gameInfo){

    char currentID[15];
    bool resID;
    printf(CYAN "Ingrese la cedula del jugador a eliminar:\n" RESET_COLOR);
    
    while (1){

        fgets(currentID, sizeof(currentID), stdin);
        removeLineBreak(currentID);

        resID = validateIdentificationCard(currentID);

        if (resID){
            break;
        }
        else{
            printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    bool flag = associatedMatch(gameInfo, currentID);

    if (flag){

        printf(RED "Imposible eliminar el jugador %s porque tiene partidas asociadas\n" RESET_COLOR, currentID);
        return;
    }
    else{

        if (playersList == NULL){
            printf(RED "Lista vacia\n" RESET_COLOR);
            return;
        }

        playersNode *aux = playersList, *prevAux = NULL;

        while (strcmp(aux->IdentificationCard, currentID) != 0){

            if (aux->next == playersList){
                printf(RED "Jugador %s no registrado\n" RESET_COLOR, currentID);
                return;
            }

            prevAux = aux;
            aux = aux->next;
        }

        if (aux->next == playersList && prevAux == NULL){
            playersList = NULL;
            free(aux);
            printf(GREEN "Jugador eliminado exitosamente\n" RESET_COLOR);
            return;
        }

        if (aux == playersList){

            prevAux = playersList->previous;
            playersList = playersList->next;

            prevAux->next = playersList;
            playersList->previous = prevAux;

            free(aux);
            printf(GREEN "Jugador eliminado exitosamente\n" RESET_COLOR);
        }
        else if (aux->next == playersList){

            prevAux->next = playersList;
            playersList->previous = prevAux;

            free(aux);
            printf(GREEN "Jugador eliminado exitosamente\n" RESET_COLOR);
        }
        else{

            playersNode *temp = aux->next;

            prevAux->next = temp;
            temp->previous = prevAux;

            free(aux);
            printf(GREEN "Jugador eliminado exitosamente\n" RESET_COLOR);
        }
    }
}

//----------Modos de juego----------

//---Gallo Pinto---

//Cola que almacena las preguntas de dificultad facil 

typedef struct node{
    char questionID[10];
    char question[200];
    char category[50];
    char difficulty;
    struct node* next;
}easyNode;

typedef struct queue{
    easyNode *rear;
    easyNode *front;
}easyQuestionQueue;

easyQuestionQueue * newEasyQueue(){

    easyQuestionQueue *queue;
    
    queue = (easyQuestionQueue *) malloc(sizeof(easyQuestionQueue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enqueueEasyQueue(easyQuestionQueue *easyQuestions, char newID[], char newQuestion[], char newCategory[], char newDifficulty){
    
    easyNode *newNode = (easyNode*) malloc(sizeof(easyNode));

    strcpy(newNode->questionID, newID);
    strcpy(newNode->question, newQuestion);
    strcpy(newNode->category, newCategory);
    newNode->difficulty = newDifficulty;

    newNode->next = NULL;

    if (easyQuestions->rear == NULL){
        easyQuestions->front = easyQuestions->rear = newNode;
        return;
    }
    
    easyQuestions->rear->next = newNode;
    easyQuestions->rear = newNode;
}

void easyMode(easyQuestionQueue *easyQuestions, questionNode **questionList){

    questionNode *ptrQuestion = *questionList;

    char qID[10], currentQuestion[200], currentCategory[50];
    char currentDifficulty;

    if (ptrQuestion == NULL){
        printf(RED "Error. Lista de preguntas vacia\n" RESET_COLOR);
        return;
    }

    while (ptrQuestion != NULL){

        if (ptrQuestion->difficulty == 'F'){

            strcpy(qID, ptrQuestion->questionID);
            strcpy(currentQuestion, ptrQuestion->question);
            strcpy(currentCategory, ptrQuestion->category);
            currentDifficulty = ptrQuestion->difficulty;

            enqueueEasyQueue(easyQuestions, qID, currentQuestion, currentCategory, currentDifficulty);
        }

        ptrQuestion = ptrQuestion->next;
    }
}

void dequeueEasyQueue(easyQuestionQueue *easyQuestions){

    if (easyQuestions->front == NULL){
        printf(YELLOW "No hay mas preguntas de dificultad facil\n" RESET_COLOR);
        return;
    }
    
    easyNode *aux = easyQuestions->front;

    printf(YELLOW "     ID: %s\n" RESET_COLOR, aux->questionID);
    printf(CYAN "Pregunta:" RESET_COLOR " %s\n", aux->question);
    printf(CYAN "Categoria:" RESET_COLOR " %s\n", aux->category);
    printf(CYAN "Dificultad:" RESET_COLOR " %c\n", aux->difficulty);

    easyQuestions->front = easyQuestions->front->next;

    if (easyQuestions->front == NULL){
        easyQuestions->rear = NULL;
    }

    free(aux);
}

void showEasyQueue(easyQuestionQueue *easyQuestions){

    easyNode *i;

    printf(YELLOW "     Las preguntas faciles son:\n" RESET_COLOR);

    for (i = easyQuestions->front; i != NULL; i = i->next){
        printf("ID: %s\n", i->questionID);
        printf("Pregunta: %s\n", i->question);
        printf("Categoria: %s\n", i->category);
        printf("Dificultad: %c\n", i->difficulty);
    }
}

//---Casado---

//Cola que almacena las preguntas de dificultad media 

typedef struct nodeM{
    char questionID[10];
    char question[200];
    char category[50];
    char difficulty;
    struct nodeM* next;
}mediumNode;

typedef struct queueM{
    mediumNode *rear;
    mediumNode *front;
}mediumQuestionQueue;

mediumQuestionQueue * newMediumQueue(){

    mediumQuestionQueue *queue;
    
    queue = (mediumQuestionQueue *) malloc(sizeof(mediumQuestionQueue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enqueueMediumQueue(mediumQuestionQueue *mediumQuestions, char newID[], char newQuestion[], char newCategory[], char newDifficulty){
    
    mediumNode *newNode = (mediumNode*) malloc(sizeof(mediumNode));

    strcpy(newNode->questionID, newID);
    strcpy(newNode->question, newQuestion);
    strcpy(newNode->category, newCategory);
    newNode->difficulty = newDifficulty;

    newNode->next = NULL;

    if (mediumQuestions->rear == NULL){
        mediumQuestions->front = mediumQuestions->rear = newNode;
        return;
    }
    
    mediumQuestions->rear->next = newNode;
    mediumQuestions->rear = newNode;
}

void mediumMode(mediumQuestionQueue *mediumQuestions, questionNode **questionList){

    questionNode *ptrQuestion = *questionList;

    char qID[10], currentQuestion[200], currentCategory[50];
    char currentDifficulty;

    if (ptrQuestion == NULL){
        printf(RED "Error. Lista de preguntas vacia\n" RESET_COLOR);
        return;
    }

    while (ptrQuestion != NULL){

        if (ptrQuestion->difficulty == 'M'){

            strcpy(qID, ptrQuestion->questionID);
            strcpy(currentQuestion, ptrQuestion->question);
            strcpy(currentCategory, ptrQuestion->category);
            currentDifficulty = ptrQuestion->difficulty;

            enqueueMediumQueue(mediumQuestions, qID, currentQuestion, currentCategory, currentDifficulty);
        }

        ptrQuestion = ptrQuestion->next;
    }
}

void dequeueMediumQueue(mediumQuestionQueue *mediumQuestions){

    if (mediumQuestions->front == NULL){
        printf(YELLOW "No hay mas preguntas de dificultad media\n" RESET_COLOR);
        return;
    }
    
    mediumNode *aux = mediumQuestions->front;

    printf(YELLOW "     ID: %s\n" RESET_COLOR, aux->questionID);
    printf(CYAN "Pregunta:" RESET_COLOR " %s\n", aux->question);
    printf(CYAN "Categoria:" RESET_COLOR " %s\n", aux->category);
    printf(CYAN "Dificultad:" RESET_COLOR " %c\n", aux->difficulty);

    mediumQuestions->front = mediumQuestions->front->next;

    if (mediumQuestions->front == NULL){
        mediumQuestions->rear = NULL;
    }

    free(aux);
}

void showMediumQueue(mediumQuestionQueue *mediumQuestions){

    mediumNode *i;

    printf(YELLOW "     Las preguntas media son:\n" RESET_COLOR);

    for (i = mediumQuestions->front; i != NULL; i = i->next){
        printf("ID: %s\n", i->questionID);
        printf("Pregunta: %s\n", i->question);
        printf("Categoria: %s\n", i->category);
        printf("Dificultad: %c\n", i->difficulty);
    }
}

//---Rice and Beans---

//Cola que almacena las preguntas de dificultad difícil 

typedef struct nodeH{
    char questionID[10];
    char question[200];
    char category[50];
    char difficulty;
    struct nodeH* next;
}hardNode;

typedef struct queueH{
    hardNode *rear;
    hardNode *front;
}hardQuestionQueue;

hardQuestionQueue * newHardQueue(){

    hardQuestionQueue *queue;
    
    queue = (hardQuestionQueue *) malloc(sizeof(hardQuestionQueue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enqueueHardQueue(hardQuestionQueue *hardQuestions, char newID[], char newQuestion[], char newCategory[], char newDifficulty){
    
    hardNode *newNode = (hardNode*) malloc(sizeof(hardNode));

    strcpy(newNode->questionID, newID);
    strcpy(newNode->question, newQuestion);
    strcpy(newNode->category, newCategory);
    newNode->difficulty = newDifficulty;

    newNode->next = NULL;

    if (hardQuestions->rear == NULL){
        hardQuestions->front = hardQuestions->rear = newNode;
        return;
    }
    
    hardQuestions->rear->next = newNode;
    hardQuestions->rear = newNode;
}

void hardMode(hardQuestionQueue *hardQuestions, questionNode **questionList){

    questionNode *ptrQuestion = *questionList;

    char qID[10], currentQuestion[200], currentCategory[50];
    char currentDifficulty;

    if (ptrQuestion == NULL){
        printf(RED "Error. Lista de preguntas vacia\n" RESET_COLOR);
        return;
    }

    while (ptrQuestion != NULL){

        if (ptrQuestion->difficulty == 'D'){

            strcpy(qID, ptrQuestion->questionID);
            strcpy(currentQuestion, ptrQuestion->question);
            strcpy(currentCategory, ptrQuestion->category);
            currentDifficulty = ptrQuestion->difficulty;

            enqueueHardQueue(hardQuestions, qID, currentQuestion, currentCategory, currentDifficulty);
        }

        ptrQuestion = ptrQuestion->next;
    }
}

void dequeueHardQueue(hardQuestionQueue *hardQuestions){

    if (hardQuestions->front == NULL){
        printf(YELLOW "No hay mas preguntas de dificultad dificil\n" RESET_COLOR);
        return;
    }
    
    hardNode *aux = hardQuestions->front;

    printf(YELLOW "     ID: %s\n" RESET_COLOR, aux->questionID);
    printf(CYAN "Pregunta:" RESET_COLOR " %s\n", aux->question);
    printf(CYAN "Categoria:" RESET_COLOR " %s\n", aux->category);
    printf(CYAN "Dificultad:" RESET_COLOR " %c\n", aux->difficulty);

    hardQuestions->front = hardQuestions->front->next;

    if (hardQuestions->front == NULL){
        hardQuestions->rear = NULL;
    }

    free(aux);
}

void showHardQueue(hardQuestionQueue *hardQuestions){

    hardNode *i;

    printf(YELLOW "     Las preguntas dificil son:\n" RESET_COLOR);

    for (i = hardQuestions->front; i != NULL; i = i->next){
        printf("ID: %s\n", i->questionID);
        printf("Pregunta: %s\n", i->question);
        printf("Categoria: %s\n", i->category);
        printf("Dificultad: %c\n", i->difficulty);
    }
}

//funciones auxiliares para obtener tamanio de las colas y lista de preguntas general

int getSizeEasyQuestions(easyQuestionQueue *easyQuestions){
    easyNode *i;
    int size = 0;

    for (i = easyQuestions->front; i != NULL; i = i->next){
        size++;
    }

    return size;
}
int getSizeMediumQuestions(mediumQuestionQueue *mediumQuestions){
    mediumNode *i;
    int size = 0;

    for (i = mediumQuestions->front; i != NULL; i = i->next){
        size++;
    }

    return size;
}
int getSizeHardQuestions(hardQuestionQueue *hardQuestions){
    hardNode *i;
    int size = 0;

    for (i = hardQuestions->front; i != NULL; i = i->next){
        size++;
    }

    return size;
}

int getQuantityQuestion(int choice, questionNode **questionList, easyQuestionQueue *easyQuestions, mediumQuestionQueue *mediumQuestions, hardQuestionQueue *hardQuestions){

    int quantity, size;

    while (1){

        printf(CYAN "Ingrese la cantidad de preguntas con las que desea jugar:\n" RESET_COLOR);
        scanf("%d",&quantity);

        if (choice == 1){

            size = getSizeEasyQuestions(easyQuestions);

            if (quantity <= size){
                return quantity;
            }
            else{
                printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
            }
        }
        else if(choice == 2){

            size = getSizeMediumQuestions(mediumQuestions);

            if (quantity <= size){
                return quantity;
            }
            else{
                printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
            }
        }
        else if (choice == 3){

            size = getSizeHardQuestions(hardQuestions);

            if (quantity <= size){
                return quantity;
            }
            else{
                printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
            }
        }
        else if(choice == 4){

            size = getSizeQuestionsList(questionList);

            if (quantity <= size){
                return quantity;
            }
            else{
                printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
            }
        }
        else if (choice == 6){

            size = getSizeQuestionsList(questionList);

            if (quantity <= size){
                return quantity;
            }
            else{
                printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
            }
        }
    }
}

int howManyCategories(questionNode **questionList, char selection[]){

    questionNode *i;
    int size = 0;

    for (i = *questionList; i != NULL; i = i->next){

        if (strcmp(i->category, selection) == 0){
            size++;
        }
    }

    return size;
}

int getQuantityForOptionFive(questionNode **questionList, char selection[]){

    int quantity, size;

    while (1){

        printf(CYAN "Ingrese la cantidad de preguntas con las que desea jugar:\n" RESET_COLOR);
        scanf("%d",&quantity);

        size = howManyCategories(questionList, selection);

        if (quantity <= size){
            return quantity;
        }
        else{
            printf(RED "Error. La cantidad ingresada supera el numero de preguntas para la modalidad escogida\n" RESET_COLOR);
        }
    }
}

//----------Generar partidad para jugador----------

//Funciones auxiliares para manipular la pila en la que se almacena la información de partida

gameInfoSatck *newStack(){

    gameInfoSatck *stack;
    stack = (gameInfoSatck *) malloc(sizeof(gameInfoSatck));
    stack->top = NULL;

    return stack;

}

nodeStackGameInfo* createNodeGameInfomation(char newID[], int newGoodQuestions, int newBadQuestions, int newPoints, char newDate[]){

    nodeStackGameInfo *newNode = (nodeStackGameInfo *) malloc(sizeof(nodeStackGameInfo));

    newNode->next = NULL;
    
    strcpy(newNode->id, newID);
    newNode->goodQuestions = newGoodQuestions;
    newNode->badQuestions = newBadQuestions;
    newNode->points = newPoints;
    strcpy(newNode->gameDate, newDate);

    return newNode;
}

void pushGameInformation(gameInfoSatck *gameInfo, char id[], int goodQuestions, int badQuestions, int points, char date[]){

    nodeStackGameInfo *newNode = createNodeGameInfomation(id, goodQuestions, badQuestions, points, date);

    newNode->next = gameInfo->top;
    gameInfo->top = newNode;

}

void showStackTop(gameInfoSatck *gameInfo){

    if (gameInfo->top == NULL){
        printf(RED "No hay informacion de partidas\n" RESET_COLOR);
    }
    else{
        printf(GREEN "Respuestas correctas:" RESET_COLOR " %d\n", gameInfo->top->goodQuestions);
        printf(RED "Respuestas incorrectas:" RESET_COLOR " %d\n", gameInfo->top->badQuestions);
        printf(CYAN "Puntaje obtenido:" RESET_COLOR " %d\n", gameInfo->top->points);
        printf(CYAN "Fecha de partida:" RESET_COLOR  " %s\n", gameInfo->top->gameDate);
    }
}   

void showStack(gameInfoSatck *gameInfo){

    nodeStackGameInfo *i;
    bool flag = false, resID;
    char currentID[15];

    printf(CYAN "Ingrese la cedula del jugador a modificar:\n" RESET_COLOR);

    while (1){

        fgets(currentID, sizeof(currentID), stdin);
        removeLineBreak(currentID);

        resID = validateIdentificationCard(currentID);

        if (resID){
            break;
        }
        else{
            printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    for (i = gameInfo->top; i != NULL; i = i->next){

        if (strcmp(i->id, currentID) == 0){
            
            flag = true;

            printf(YELLOW "     Jugador cedula: %s     \n" RESET_COLOR, i->id);
            printf(CYAN "Preguntas correctas:" RESET_COLOR " %d\n", i->goodQuestions);
            printf(CYAN "Preguntas incorrectas:" RESET_COLOR " %d\n", i->badQuestions);
            printf(CYAN "Puntaje obtenido:" RESET_COLOR " %d\n", i->points);
            printf(CYAN "Fecha de juego:" RESET_COLOR " %s\n", i->gameDate);
        }
    }

    if (flag == false){

        printf(RED "EL jugador no tiene partidas asociadas\n" RESET_COLOR);
        return;
    }
}

//---Selección del ganador---

typedef struct actualPlayersList{
    char id[10];
    int pts;
    struct actualPlayersList* next;
}actualPlayersNode;

typedef struct pointsList{
    int pts;
    struct pointsList* next;
}pointsNode;

void appendPoints(pointsNode ** pointsList, int points){

    pointsNode *newNode = (pointsNode *) malloc(sizeof(pointsNode));
    pointsNode *last = *pointsList;

    newNode->pts = points;

    newNode->next = NULL;

    if (*pointsList == NULL){
        *pointsList = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

void appendActualPlayers(actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, char playerID[], int points){

    actualPlayersNode *newNode = (actualPlayersNode *) malloc(sizeof(actualPlayersNode));
    actualPlayersNode *last = *actualPlayersList;

    strcpy(newNode->id, playerID);
    newNode->pts = points;
    appendPoints(pointsList, points);

    newNode->next = NULL;

    if (*actualPlayersList == NULL){
        *actualPlayersList = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}


void swap(pointsNode *numA, pointsNode *numB){
    int aux;
    
    aux = numA->pts;
    numA->pts = numB->pts;
    numB->pts = aux;
}

void bubbleSort(pointsNode *pointsList){
    int sort, i;
    pointsNode *ptrAux; 
    pointsNode *listAux = NULL;

    if (pointsList == NULL){
        return;
    }

    do{
        sort = 0;
        ptrAux = pointsList;

        while (ptrAux->next != listAux){
            if (ptrAux->pts < ptrAux->next->pts){
                swap(ptrAux, ptrAux->next);
                sort = 1;
            }

            ptrAux = ptrAux->next;
        }

        listAux = ptrAux;
    } while (sort);
}

typedef struct topFiveList{
    char id[15];
    int wins;
    struct topFiveList* next;
}topFiveNode;

void uploadWins(topFiveNode** topFiveList){

    FILE * ptrFile = fopen("WINS.csv", "r");

    char data[2][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        topFiveNode *newNode = (topFiveNode *) malloc(sizeof(topFiveNode));

        strcpy(newNode->id, data[0]);
        newNode->wins = atoi(data[1]);

        newNode->next = NULL;

        if (*topFiveList == NULL){
            *topFiveList = newNode;
        }
        else{
            topFiveNode *last = *topFiveList;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void appendTopFive(topFiveNode **topFiveList, char playerID[], int countWins){

    topFiveNode *newNode = (topFiveNode *) malloc(sizeof(topFiveNode));
    topFiveNode *last = *topFiveList;

    strcpy(newNode->id, playerID);
    newNode->wins = countWins;

    newNode->next = NULL;

    if (*topFiveList == NULL){
        *topFiveList = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

void findWinner(actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, topFiveNode **topFiveList){

    int winnerPoints;
    pointsNode *ptsAux = *pointsList;
    actualPlayersNode *i;
    topFiveNode *j;

    winnerPoints = ptsAux->pts;
    
    for (i = *actualPlayersList; i != NULL; i = i->next){

        if (i->pts == winnerPoints){

            printf(YELLOW "El ganador obtuvo %d puntos y es el jugador con la cedula:" RESET_COLOR " %s\n", i->pts, i->id);
            break;
        }
    }

    for (j = *topFiveList; j != NULL; j = j->next){

        if (strcmp(j->id, i->id) == 0){

            j->wins++;
            return;
        }
    }

    appendTopFive(topFiveList, i->id, 1);
}

typedef struct winsList{
    int win;
    struct winsList* next;
}winsNode;

void appendWins(winsNode ** winsList, int wins){

    winsNode *newNode = (winsNode *) malloc(sizeof(winsNode));
    winsNode *last = *winsList;

    newNode->win = wins;

    newNode->next = NULL;

    if (*winsList == NULL){
        *winsList = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

void copyWins(winsNode **winsList, topFiveNode **topFiveList){

    topFiveNode *i;

    for (i = *topFiveList; i != NULL; i = i->next){

        appendWins(winsList, i->wins);
    }
}

void swapWins(winsNode *numA, winsNode *numB){
    int aux;
    
    aux = numA->win;
    numA->win = numB->win;
    numB->win = aux;
}

void bubbleSortWins(winsNode *winsList){
    int sort, i;
    winsNode *ptrAux; 
    winsNode *listAux = NULL;

    if (winsList == NULL){
        return;
    }

    do{
        sort = 0;
        ptrAux = winsList;

        while (ptrAux->next != listAux){
            if (ptrAux->win < ptrAux->next->win){
                swapWins(ptrAux, ptrAux->next);
                sort = 1;
            }

            ptrAux = ptrAux->next;
        }

        listAux = ptrAux;
    } while (sort);
}

void findTopFiveWinners(topFiveNode **topFiveList, winsNode **winsList){

    copyWins(winsList, topFiveList);
    bubbleSortWins(*winsList);

    topFiveNode *j = *topFiveList;
    winsNode *aux = *winsList;

    int count = 0;

    printf(YELLOW "Top 5 ganadores:\n" RESET_COLOR);

    while (j != NULL){

        if (count == 5){
            return;
        }
            
        if (j->wins == aux->win){

            printf(CYAN "Cedula:" RESET_COLOR " %s\n", j->id);
            printf(CYAN "Victorias:" RESET_COLOR " %d\n", j->wins);

            count++;
            aux = aux->next;
            j = *topFiveList;
            continue;
        }

        j = j->next;
    }
}

typedef struct gameModeList{
    char gameMode[25];
    int count;
    struct gameModeList* next;
}gameModeNode;

typedef struct countGameModeList{
    int count;
    struct countGameModeList* next;
}countGameModeNode;

void uploadModeGame(gameModeNode** gameModeList){

    FILE * ptrFile = fopen("TOPGAMEMODE.csv", "r");

    char data[2][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        gameModeNode *newNode = (gameModeNode *) malloc(sizeof(gameModeNode));

        strcpy(newNode->gameMode, data[0]);
        newNode->count = atoi(data[1]);

        newNode->next = NULL;

        if (*gameModeList == NULL){
            *gameModeList = newNode;
        }
        else{
            gameModeNode *last = *gameModeList;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void modifyCountGameMode(gameModeNode** gameModeList, char mode[]){

    gameModeNode *i;

    for (i = *gameModeList; i != NULL; i = i->next){

        if (strcmp(i->gameMode, mode) == 0){

            i->count++;
            return;
        }
    }
}

void appendCount(countGameModeNode** countGameModeList, int count){

    countGameModeNode *newNode = (countGameModeNode *) malloc(sizeof(countGameModeNode));
    countGameModeNode *last = *countGameModeList;

    newNode->count = count;

    newNode->next = NULL;

    if (*countGameModeList == NULL){
        *countGameModeList = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

void copyCount(countGameModeNode** countGameModeList, gameModeNode **gameModeList){

    gameModeNode *i;

    for (i = *gameModeList; i != NULL; i = i->next){

        appendCount(countGameModeList, i->count);
    }
}

void swapCounts(countGameModeNode *numA, countGameModeNode *numB){
    int aux;
    
    aux = numA->count;
    numA->count = numB->count;
    numB->count = aux;
}

void bubbleSortCounts(countGameModeNode *countGameModeList){
    int sort, i;
    countGameModeNode *ptrAux; 
    countGameModeNode *listAux = NULL;

    if (countGameModeList == NULL){
        return;
    }

    do{
        sort = 0;
        ptrAux = countGameModeList;

        while (ptrAux->next != listAux){
            if (ptrAux->count < ptrAux->next->count){
                swapCounts(ptrAux, ptrAux->next);
                sort = 1;
            }

            ptrAux = ptrAux->next;
        }

        listAux = ptrAux;
    } while (sort);
}

void findTopFiveGameMode(gameModeNode **gameModeList, countGameModeNode **countGameModeList){

    copyCount(countGameModeList, gameModeList);
    bubbleSortCounts(*countGameModeList);

    gameModeNode *j = *gameModeList;
    countGameModeNode *aux = *countGameModeList;

    int count = 0;

    printf(YELLOW "Top 5 modos de juego:\n" RESET_COLOR);

    while (j != NULL){

        if (count == 5){
            return;
        }
            
        if (j->count == aux->count){

            printf(CYAN "Modo de juego:" RESET_COLOR " %s\n", j->gameMode);
            printf(CYAN "Cantidad de veces jugado:" RESET_COLOR " %d\n", j->count);

            count++;
            aux = aux->next;
            j = *gameModeList;
            continue;
        }

        j = j->next;
    }
}

void addGameInfoFile(char id[], int good, int bad, int points, char matchDate[]){

    FILE* ptrFile = fopen("GAMEINFO.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %d, %d, %d, %s\n", id, good, bad, points, matchDate);

    fclose(ptrFile);
}

//---Funcion para crear partida Gallo pinto---

void playingGalloPinto(answersNode **answersList, easyQuestionQueue *easyQuestions, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0;
    answersNode *ptrAnswer = *answersList;

    for (int count = 0; count < quantity; count++){

        strcpy(currentQuestion, easyQuestions->front->questionID);
        dequeueEasyQueue(easyQuestions);

        strcpy(questionAux, currentQuestion);
        questionAux[0] = 'R';
        strcpy(aID, questionAux);

        while (ptrAnswer != NULL){
            
            if (strcmp(ptrAnswer->answersID, aID) == 0){
                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
        printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
        printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
        printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
        printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

        clearBuffer();
        userAnswer = getTheAnswer();

        if (ptrAnswer->indicator == userAnswer){
            printf(GREEN "Respuesta correcta :)\n+2pts\n" RESET_COLOR);
            countGood++;
            countPoints += 2;
        }
        else{
            printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
            printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
            countBad++;
        }
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);
    
    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
    addGameInfoFile(playerID, countGood, countBad, countPoints, strDate);
}

//---Funcion para crear partida Casado---

void playingCasado(answersNode **answersList, mediumQuestionQueue *mediumQuestions, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0;
    answersNode *ptrAnswer = *answersList;

    for (int count = 0; count < quantity; count++){

        strcpy(currentQuestion, mediumQuestions->front->questionID);
        dequeueMediumQueue(mediumQuestions);

        strcpy(questionAux, currentQuestion);
        questionAux[0] = 'R';
        strcpy(aID, questionAux);

        while (ptrAnswer != NULL){
            
            if (strcmp(ptrAnswer->answersID, aID) == 0){
                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
        printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
        printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
        printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
        printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

        clearBuffer();
        userAnswer = getTheAnswer();

        if (ptrAnswer->indicator == userAnswer){
            printf(GREEN "Respuesta correcta :)\n+2pts\n" RESET_COLOR);
            countGood++;
            countPoints += 4;
        }
        else{
            printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
            printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
            countBad++;
        }
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);

    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
    addGameInfoFile(playerID, countGood, countBad, countPoints, strDate);
}

//---Funcion para crear partida Rice and beans---

void playingRiceAndBeans(answersNode **answersList, hardQuestionQueue *hardQuestions, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0;
    answersNode *ptrAnswer = *answersList;

    for (int count = 0; count < quantity; count++){

        strcpy(currentQuestion, hardQuestions->front->questionID);
        dequeueHardQueue(hardQuestions);

        strcpy(questionAux, currentQuestion);
        questionAux[0] = 'R';
        strcpy(aID, questionAux);

        while (ptrAnswer != NULL){
            
            if (strcmp(ptrAnswer->answersID, aID) == 0){
                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
        printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
        printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
        printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
        printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

        clearBuffer();
        userAnswer = getTheAnswer();

        if (ptrAnswer->indicator == userAnswer){
            printf(GREEN "Respuesta correcta :)\n+2pts\n" RESET_COLOR);
            countGood++;
            countPoints += 6;
        }
        else{
            printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
            printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
            countBad++;
        }
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);

    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
    addGameInfoFile(playerID, countGood, countBad, countPoints, strDate);
}

//---Funcion para crear partida Chifrijo---

void playingChifrijo(questionNode **questionList, answersNode **answersList, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0, count = 0;
    answersNode *ptrAnswer = *answersList;
    questionNode *i;

    for (i = *questionList; i != NULL; i = i->next){

        if (count == quantity){
            break;
        }

        printf(YELLOW "     ID Pregunta: %s     \n" RESET_COLOR, i->questionID);
        printf(CYAN "Pregunta:" RESET_COLOR " %s\n", i->question);
        printf(CYAN "Categoria:" RESET_COLOR " %s\n", i->category);
        printf(CYAN"Dificultad:" RESET_COLOR " %c\n", i->difficulty);

        strcpy(questionAux, i->questionID);
        questionAux[0] = 'R';
        strcpy(aID, questionAux);

        while (ptrAnswer != NULL){
            
            if (strcmp(ptrAnswer->answersID, aID) == 0){
                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
        printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
        printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
        printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
        printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

        clearBuffer();
        userAnswer = getTheAnswer();

        if (ptrAnswer->indicator == userAnswer){
            printf(GREEN "Respuesta correcta :)\n" RESET_COLOR);
            countGood++;
            
            if (i->difficulty == 'F'){
                printf(GREEN "+2pts\n" RESET_COLOR);
                countPoints += 2;
            }
            if (i->difficulty == 'M'){
                printf(GREEN "+4pts\n" RESET_COLOR);
                countPoints += 4;
            }
            if (i->difficulty == 'D'){
                printf(GREEN "+6pts\n" RESET_COLOR);
                countPoints += 6;
            }
        }
        else{
            printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
            printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
            countBad++;
        }
        count++;
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);

    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
    addGameInfoFile(playerID, countGood, countBad, countPoints, strDate);
}

//---Funcion para crear partida Horchata---

void playingHorchata(questionNode **questionList, answersNode **answersList, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char selection[], char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0, count = 0;
    answersNode *ptrAnswer = *answersList;
    questionNode *i;

    for (i = *questionList; i != NULL; i = i->next){

        if (count == quantity){
            break;
        }

        if (strcmp(i->category, selection) == 0){

            printf(YELLOW "     ID Pregunta: %s     \n" RESET_COLOR, i->questionID);
            printf(CYAN "Pregunta:" RESET_COLOR " %s\n", i->question);
            printf(CYAN "Categoria:" RESET_COLOR " %s\n", i->category);
            printf(CYAN"Dificultad:" RESET_COLOR " %c\n", i->difficulty);

            strcpy(questionAux, i->questionID);
            questionAux[0] = 'R';
            strcpy(aID, questionAux);

            while (ptrAnswer != NULL){
                
                if (strcmp(ptrAnswer->answersID, aID) == 0){
                    break;
                }

                ptrAnswer = ptrAnswer->next;
            }

            printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
            printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
            printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
            printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
            printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

            clearBuffer();
            userAnswer = getTheAnswer();

            if (ptrAnswer->indicator == userAnswer){
                printf(GREEN "Respuesta correcta :)\n" RESET_COLOR);
                countGood++;
                
                if (i->difficulty == 'F'){
                    printf(GREEN "+2pts\n" RESET_COLOR);
                    countPoints += 2;
                }
                if (i->difficulty == 'M'){
                    printf(GREEN "+4pts\n" RESET_COLOR);
                    countPoints += 4;
                }
                if (i->difficulty == 'D'){
                    printf(GREEN "+6pts\n" RESET_COLOR);
                    countPoints += 6;
                }
            }
            else{
                printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
                printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
                countBad++;
            }
            count++;
        }
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);

    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
}
//---Funciones auxiliares para crear partida Arracache---

int getMinutesComputerClock(){

    time_t actualTime;
    time(&actualTime);
    struct tm *time = localtime(&actualTime);

    return time->tm_min;
}

int getMinutesUser(){

    int minutes;

    printf("Ingrese la cantidad de minutos:\n");
    scanf("%d", &minutes);

    return minutes;
}

//---Funcion para crear partida Arracache---

void playingArracache(questionNode **questionList, answersNode **answersList, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, int quantity, char playerID[], char playerNickname[]){

    char currentQuestion[10], questionAux[10], aID[10]; 
    char userAnswer;
    int countGood = 0, countBad = 0, countPoints = 0, count = 0, gameMinutes, remainingMinutes;
    answersNode *ptrAnswer = *answersList;
    questionNode *i;

    gameMinutes = getMinutesComputerClock() + getMinutesUser();

    if (gameMinutes > 60){
        gameMinutes -= 60;
    }

    for (i = *questionList; i != NULL; i = i->next){

        remainingMinutes = getMinutesComputerClock();

        printf(CYAN "Minutos restantes: %d minutos\n" RESET_COLOR, gameMinutes - remainingMinutes);

        if ( (gameMinutes - remainingMinutes) < 0){
            printf(RED "Fin del tiempo\n" RESET_COLOR);
            break;
        }

        if (count == quantity){
            printf(CYAN "Se ha llegado a la cantidad total de preguntas indicadas\n" RESET_COLOR);
            break;
        }

        printf(YELLOW "     ID Pregunta: %s     \n" RESET_COLOR, i->questionID);
        printf(CYAN "Pregunta:" RESET_COLOR " %s\n", i->question);
        printf(CYAN "Categoria:" RESET_COLOR " %s\n", i->category);
        printf(CYAN"Dificultad:" RESET_COLOR " %c\n", i->difficulty);

        strcpy(questionAux, i->questionID);
        questionAux[0] = 'R';
        strcpy(aID, questionAux);

        while (ptrAnswer != NULL){
            
            if (strcmp(ptrAnswer->answersID, aID) == 0){
                break;
            }

            ptrAnswer = ptrAnswer->next;
        }

        printf(YELLOW "     Posibles respuestas:\n" RESET_COLOR);
        printf(CYAN "A) %s\n" RESET_COLOR, ptrAnswer->answerA);
        printf(CYAN "B) %s\n" RESET_COLOR, ptrAnswer->answerB);
        printf(CYAN "C) %s\n" RESET_COLOR, ptrAnswer->answerC);
        printf(YELLOW "Ingrese A o B o C segun corresponda:\n" RESET_COLOR);

        clearBuffer();
        userAnswer = getTheAnswer();

        if (ptrAnswer->indicator == userAnswer){
            printf(GREEN "Respuesta correcta :)\n" RESET_COLOR);
            countGood++;
            
            if (i->difficulty == 'F'){
                printf(GREEN "+2pts\n" RESET_COLOR);
                countPoints += 2;
            }
            if (i->difficulty == 'M'){
                printf(GREEN "+4pts\n" RESET_COLOR);
                countPoints += 4;
            }
            if (i->difficulty == 'D'){
                printf(GREEN "+6pts\n" RESET_COLOR);
                countPoints += 6;
            }
        }
        else{
            printf(RED "Respuesta incorrecta :(\n" RESET_COLOR);
            printf(CYAN "La respuesta correcta es la opcion: %c\n" RESET_COLOR, ptrAnswer->indicator);
            countBad++;
        }
        count++;
    }

    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    int day = tm.tm_mday, month = tm.tm_mon + 1, year = tm.tm_year + 1900;

    char strDay[5], strMonth[5], strYear[5];

    itoa(day, strDay, 10);
    itoa(month, strMonth, 10);
    itoa(year, strYear, 10);

    char strDate[10];
    char bar = '/';

    strcpy(strDate, strDay);
    strncat(strDate, &bar, 1);
    strcat(strDate, strMonth);
    strncat(strDate, &bar, 1);
    strcat(strDate, strYear);

    pushGameInformation(gameInfo, playerID, countGood, countBad, countPoints, strDate);

    printf(YELLOW "Fin del juego para %s\n" RESET_COLOR, playerNickname);
    printf(YELLOW "-----Resultados-----\n" RESET_COLOR);
    showStackTop(gameInfo);
    printf(YELLOW "--------------------\n" RESET_COLOR);
    appendActualPlayers(actualPlayersList, pointsList, playerID, countPoints);
    addGameInfoFile(playerID, countGood, countBad, countPoints, strDate);
}

//----------Registro de premios----------
/*
Entradas: nombre del premio, valor económico, cantidad disponible, descripción del premio.
Salida: el premio registrado exitosamente en la lista de premios.
Restricciones: el valor económico y la cantidad disponible deben ser un número entero.
*/

typedef struct rewardList{
    char nameReward[100];
    int value;
    int quantity;
    char description[100];
    struct rewardList* next;
}rewardNode;

typedef struct topRewards{
    char nameReward[100];
    int count;
    struct topRewards* next;
}topRewardsNode;

void uploadRewards(rewardNode** rewardList){

    FILE * ptrFile = fopen("REWARDS.csv", "r");

    char data[4][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        rewardNode *newNode = (rewardNode *) malloc(sizeof(rewardNode));

        strcpy(newNode->nameReward, data[0]);
        newNode->value = atoi(data[1]);
        newNode->quantity = atoi(data[2]);
        strcpy(newNode->description, data[3]);

        newNode->next = NULL;

        if (*rewardList == NULL){
            *rewardList = newNode;
        }
        else{
            rewardNode *last = *rewardList;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void uploadTopRewards(topRewardsNode** topRewards){

    FILE * ptrFile = fopen("TOPREWARDS.csv", "r");

    char data[2][120];
    char line[330];
    int count;

    while (fgets(line, sizeof(line), ptrFile)){

        char *token;

        token = strtok(line, ",");
        count = 0;

        while (token != NULL){

            strcpy(data[count], token);
            token = strtok(NULL, ",");
            count++;
        }

        topRewardsNode *newNode = (topRewardsNode *) malloc(sizeof(topRewardsNode));

        strcpy(newNode->nameReward, data[0]);
        newNode->count = atoi(data[1]);

        newNode->next = NULL;

        if (*topRewards == NULL){
            *topRewards = newNode;
        }
        else{
            topRewardsNode *last = *topRewards;

            while (last->next != NULL){
                last = last->next;
            }

            last->next = newNode;
        }  
    }

    fclose(ptrFile);
}

void appendReward(rewardNode **rewardList){

    rewardNode *newNode = (rewardNode *) malloc(sizeof(rewardNode));
    rewardNode *last = *rewardList;
    char currentNameReward[100];

    clearBuffer();

    printf(CYAN "Ingrese el nombre del premio:\n" RESET_COLOR);
    fgets(currentNameReward, 200, stdin);
    removeLineBreak(currentNameReward);
    strcpy(newNode->nameReward, currentNameReward);

    clearBuffer();

    char currentValue[12];
    bool resValue;

    printf(CYAN "Ingrese el valor economico del premio:\n" RESET_COLOR);

    while(1){

        fgets(currentValue, sizeof(currentValue), stdin);
        removeLineBreak(currentValue);

        resValue = validateIsNum(currentValue);

        if (resValue == true){
            break;

        }else{
            printf(RED "Monto ingresado es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    int numValue = atoi(currentValue);
    newNode->value = numValue;

    char currentQuantity[5];
    bool resQuantity;

    printf(CYAN "Ingrese la cantidad disponible:\n" RESET_COLOR);

    while(1){

        fgets(currentQuantity, sizeof(currentQuantity), stdin);
        removeLineBreak(currentQuantity);

        resValue = validateIsNum(currentValue);

        if (resValue == true){
            break;

        }else{
            printf(RED "Monto ingresado es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
        }
    }

    int numQuantity = atoi(currentQuantity);
    newNode->quantity = numQuantity;

    char currentDescription[100];

    printf(CYAN "Ingrese la descripcion del premio:\n" RESET_COLOR);
    fgets(currentDescription, 200, stdin);
    removeLineBreak(currentDescription);
    strcpy(newNode->description, currentDescription);

    newNode->next = NULL;

    if (*rewardList == NULL){
        *rewardList = newNode;
        printf(GREEN "Premio registrado exitosamente\n" RESET_COLOR);
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
    printf(GREEN "Premio registrado exitosamente\n" RESET_COLOR);
}

void showRewards(rewardNode *rewardList){

    rewardNode *i;

    printf(YELLOW "     Los premios disponibles son:\n" RESET_COLOR);

    for (i = rewardList; i != NULL; i = i->next){

        printf(CYAN "Nombre del premio:" RESET_COLOR " %s\n", i->nameReward);
        printf(CYAN "Valor economico:" RESET_COLOR " %d\n", i->value);
        printf(CYAN "Cantidad disponible:" RESET_COLOR " %d\n", i->quantity);
        printf(CYAN "Descripcion del premio:" RESET_COLOR " %s\n", i->description);
    }
}

int getSizeRewardsList(rewardNode** rewardList){
    int size = 0;
    rewardNode* current = *rewardList;

    while (current != NULL){
        size++;
        current = current->next;
    }

    return size;
}

void appendTopReward(topRewardsNode **topRewards, char name[], int count){

    topRewardsNode *newNode = (topRewardsNode *) malloc(sizeof(topRewardsNode));
    topRewardsNode *last = *topRewards;

    strcpy(newNode->nameReward, name);
    newNode->count = count;

    newNode->next = NULL;

    if (*topRewards == NULL){
        *topRewards = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

typedef struct countRewards{
    int count;
    struct countRewards* next;
}countRewardsNode;

void appendCountRewards(countRewardsNode** countRewards, int count){

    countRewardsNode *newNode = (countRewardsNode *) malloc(sizeof(countRewardsNode));
    countRewardsNode *last = *countRewards;

    newNode->count = count;

    newNode->next = NULL;

    if (*countRewards == NULL){
        *countRewards = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = newNode;
}

void copyCountRewards(countRewardsNode** countRewards, topRewardsNode **topRewards){

    topRewardsNode *i;

    for (i = *topRewards; i != NULL; i = i->next){

        appendCountRewards(countRewards, i->count);
    }
}

void swapCountsRewards(countRewardsNode *numA, countRewardsNode *numB){
    int aux;
    
    aux = numA->count;
    numA->count = numB->count;
    numB->count = aux;
}

void bubbleSortCountsRewards(countRewardsNode *countRewards){
    int sort, i;
    countRewardsNode *ptrAux; 
    countRewardsNode *listAux = NULL;

    if (countRewards == NULL){
        return;
    }

    do{
        sort = 0;
        ptrAux = countRewards;

        while (ptrAux->next != listAux){
            if (ptrAux->count < ptrAux->next->count){
                swapCountsRewards(ptrAux, ptrAux->next);
                sort = 1;
            }

            ptrAux = ptrAux->next;
        }

        listAux = ptrAux;
    } while (sort);
}

//Funcion que otorga el premio alatorio al jugador

void giveReward(rewardNode *rewardList, topRewardsNode *topRewards){

    rewardNode *i;
    topRewardsNode *j;
    int count = 0, position, size = getSizeRewardsList(&rewardList);

    srand(time(0));
    position = (rand() % (size - 1 + 1)) + 1;

    for (i = rewardList; i != NULL; i = i->next){

        count++;

        if (count == position){

            printf(YELLOW "     El premio otorgado es:\n" RESET_COLOR);
            printf(CYAN "Nombre del premio:" RESET_COLOR " %s\n", i->nameReward);
            printf(CYAN "Valor economico:" RESET_COLOR " %d\n", i->value);
            printf(CYAN "Descripcion del premio:" RESET_COLOR " %s\n", i->description);

            i->quantity--;

            for (j = topRewards; j != NULL; j = j->next){

                if (strcmp(j->nameReward, i->nameReward) == 0){

                    j->count++;
                    return;
                }
            }

            appendTopReward(&topRewards, i->nameReward, 1);
        }
    }
}

//funcion que elimina el premio cuando la cantidad el 0.

void removeReward(rewardNode *rewardList){

    rewardNode *aux = rewardList, *previus;
    
    if (aux != NULL && aux->quantity == 0){

        rewardList = aux->next; 
        free(aux); 
        return;
    }

    while (aux != NULL && aux->quantity != 0) {
        previus = aux;
        aux = aux->next;
    }
 
    if (aux == NULL)
        return;
 
    previus->next = aux->next;
 
    free(aux);
}

//-----Analisis de datos: top 5 de premios otrogados-----
/*
Entradas: la lista de premios
Salidas: el top 5 de los premios que más veces se han otorgado.
Restricciones: no hay.
*/

void findTopFiveRewards(topRewardsNode **topRewards, countRewardsNode **countRewards){

    copyCountRewards(countRewards, topRewards);
    bubbleSortCountsRewards(*countRewards);

    topRewardsNode *j = *topRewards;
    countRewardsNode *aux = *countRewards;

    int count = 0;

    printf(YELLOW "Top 5 premios otorgados:\n" RESET_COLOR);

    while (j != NULL){

        if (count == 5){
            return;
        }
            
        if (j->count == aux->count){

            printf(CYAN "Nombre del premio:" RESET_COLOR " %s\n", j->nameReward);
            printf(CYAN "Cantidad de veces otorgado:" RESET_COLOR " %d\n", j->count);

            count++;
            aux = aux->next;
            j = *topRewards;
            continue;
        }

        j = j->next;
    }
}

//----------Funcion principal para genera partidas----------
/*
Entradas: estructuras de datos necesarias para los modos de juego, premiación y análisis de datos,
          el usuario elije la modalidad de juego a traves de un menú de opciones.
Salidas: el juego según la modalidad escogida. Finalizado el juego se muestra la premiación. 
Restricciones: la selección del usuario debe ser un número entre 1 y 7.
*/

void play(questionNode **questionList, answersNode **answersList, playersNode **playersList, easyQuestionQueue *easyQuestions, mediumQuestionQueue *mediumQuestions, hardQuestionQueue *hardQuestions, gameInfoSatck *gameInfo, actualPlayersNode ** actualPlayersList, pointsNode ** pointsList, rewardNode *rewardList, topFiveNode **topFiveList, gameModeNode** gameModeList, topRewardsNode **topRewards){
    int choice = 0, quantityQuestion, count = 0;
    playersNode *ptrPlayer;
    char currentPlayerID[15], currentNickname[30];
    bool resID, resSelection, flag;
    char selection[30];
    char mode_1[] = "Gallo pinto", mode_2[] = "Casado", mode_3[] = "Rice and beans", mode_4[] = "Chifrijo", mode_5[] = "Horchata", mode_6[] = "Arracache";

    do{

        printf(YELLOW "Modalidades de juego\n" RESET_COLOR);
        printf(CYAN "1. Gallo Pinto -> Modalidad facil\n" RESET_COLOR);
        printf(CYAN "2. Casado -> Modalidad media\n" RESET_COLOR);
        printf(CYAN "3. Rice and beans -> Modalidad dificl\n" RESET_COLOR);
        printf(CYAN "4. Chifrijo -> Modalidad aleatoria\n" RESET_COLOR);
        printf(CYAN "5. Horchata -> El jugador elige la categoria\n" RESET_COLOR);
        printf(CYAN "6. Arracache -> Modalidad con limite de tiempo\n" RESET_COLOR);
        printf(CYAN "7. Dejar de jugar\n" RESET_COLOR);
        printf(YELLOW "Seleccione una modalidad\n" RESET_COLOR);

        scanf("%d",&choice); 

        switch (choice){

            case 1:

                modifyCountGameMode(gameModeList, mode_1);

                printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){
                        
                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);
                easyMode(easyQuestions, questionList);
                quantityQuestion = getQuantityQuestion(choice, questionList, easyQuestions, mediumQuestions, hardQuestions);
                playingGalloPinto(answersList, easyQuestions, gameInfo, actualPlayersList, pointsList, quantityQuestion, currentPlayerID, currentNickname);
                break;
            case 2:
                modifyCountGameMode(gameModeList, mode_2);

                printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){

                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);
                mediumMode(mediumQuestions, questionList);
                quantityQuestion = getQuantityQuestion(choice, questionList, easyQuestions, mediumQuestions, hardQuestions);
                playingCasado(answersList, mediumQuestions, gameInfo, actualPlayersList, pointsList, quantityQuestion, currentPlayerID, currentNickname);
                break;
            case 3:
                modifyCountGameMode(gameModeList, mode_3);

                printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){

                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);
                hardMode(hardQuestions, questionList);
                quantityQuestion = getQuantityQuestion(choice, questionList, easyQuestions, mediumQuestions, hardQuestions);
                playingRiceAndBeans(answersList, hardQuestions, gameInfo, actualPlayersList, pointsList, quantityQuestion, currentPlayerID, currentNickname);
                break;
            case 4:
                modifyCountGameMode(gameModeList, mode_4);

                printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){

                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);
                quantityQuestion = getQuantityQuestion(choice, questionList, easyQuestions, mediumQuestions, hardQuestions);
                playingChifrijo(questionList, answersList, gameInfo, actualPlayersList, pointsList, quantityQuestion, currentPlayerID, currentNickname);
                break;
            case 5:
                modifyCountGameMode(gameModeList, mode_5);

                printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){

                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }

                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);

                while (1){ 

                    printf(YELLOW "Las categorias disponibles son: Historia, Geografia y Biodiversidad.\n" RESET_COLOR);
                    printf(CYAN "Ingrese alguna de las mencionadas:\n" RESET_COLOR);

                    clearBuffer();

                    fgets(selection, sizeof(selection), stdin);
                    removeLineBreak(selection);

                    resSelection = validateCategory(selection);

                    if (resSelection){
                        break;
                    }
                    else{
                        printf(RED "La categoria es invalida.\n" RESET_COLOR);
                    }
                }

                quantityQuestion = getQuantityForOptionFive(questionList, selection);
                playingHorchata(questionList, answersList, gameInfo, actualPlayersList, pointsList, quantityQuestion, selection, currentPlayerID, currentNickname);
                break;
            case 6:
                modifyCountGameMode(gameModeList, mode_6);

                 printf(CYAN "Ingrese la cedula del jugador que va a jugar:\n" RESET_COLOR);

                while (1){

                    clearBuffer();

                    fgets(currentPlayerID, sizeof(currentPlayerID), stdin);
                    removeLineBreak(currentPlayerID);

                    resID = validateIdentificationCard(currentPlayerID);

                    if (resID){

                        ptrPlayer = *playersList;

                        do{
                            if (strcmp(ptrPlayer->IdentificationCard, currentPlayerID) == 0){
                                strcpy(currentNickname, ptrPlayer->nickname);
                                break;
                            }

                            ptrPlayer = ptrPlayer->next;

                        } while (ptrPlayer != *playersList);

                        break;
                    }
                    else{
                        printf(RED "El numero de cedula es invalido\n" CYAN "Intente de nuevo:\n" RESET_COLOR);
                    }
                }
                printf(WHITE "A" BLUE " jugar" RED " %s\n" RESET_COLOR, currentNickname);
                quantityQuestion = getQuantityQuestion(choice, questionList, easyQuestions, mediumQuestions, hardQuestions);
                playingArracache(questionList, answersList, gameInfo, actualPlayersList, pointsList, quantityQuestion, currentPlayerID, currentNickname);
                break;
            case 7:
                bubbleSort(*pointsList);
                findWinner(actualPlayersList, pointsList, topFiveList);
                giveReward(rewardList, *topRewards);
                removeReward(rewardList);
                printf(WHITE "Gracias " BLUE "por " RED "jugar" RESET_COLOR "\n");
                break;
            default:
                printf(RED "Incorrect option" CYAN "Intente de nuevo\n" RESET_COLOR);
                break;
        }

    } while (choice != 7 && choice != EOF);
}

//---Funciones auxiliares para la persistencia de datos en archivos .csv---

void addQuestionFile(char id[], char question[], char category[], char difficulty){

    FILE* ptrFile = fopen("QUESTIONS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %s, %s, %c\n", id, question, category, difficulty);

    fclose(ptrFile);
}

void addAnswerFile(char id[], char answerA[], char answerB[], char answerC[], char indicator){

    FILE* ptrFile = fopen("ANSWERS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %s, %s, %s, %c\n", id, answerA, answerB, answerC, indicator);

    fclose(ptrFile);
}

void addPlayersFile(char id[], char nickname[], char name[], char lastName[], char secondLastName[], char bornDate[], char mail[], char place[]){

    FILE* ptrFile = fopen("PLAYERS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %s, %s, %s, %s, %s, %s, %s\n", id, nickname, name, lastName, secondLastName, bornDate, mail, place);

    fclose(ptrFile);
}

void addRewardsFile(char name[], int value, int quantity, char description[]){

    FILE* ptrFile = fopen("REWARDS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %d, %d, %s\n", name, value, quantity, description);

    fclose(ptrFile);
}

void addWinsFile(char id[], int win){

    FILE* ptrFile = fopen("WINS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %d\n", id, win);

    fclose(ptrFile);
}

void addModeGameFile(char mode[], int count){

    FILE* ptrFile = fopen("TOPGAMEMODE.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %d\n", mode, count);

    fclose(ptrFile);
}

void addTopRewardsFile(char name[], int count){

    FILE* ptrFile = fopen("TOPREWARDS.csv", "a+");

    if (!ptrFile){
        printf(RED "Error al abrir el archivo\n" RESET_COLOR);
        return;
    }

    fprintf(ptrFile, "%s, %d\n", name, count);

    fclose(ptrFile);
}

void saveQuestions(questionNode **questionList){

    remove("QUESTIONS.csv");

    questionNode *aux;

    char qID[10], ques[200], cat[50];
    char diff;

    for (aux = *questionList; aux != NULL; aux = aux->next){

        strcpy(qID, aux->questionID);
        strcpy(ques, aux->question);
        strcpy(cat, aux->category);
        diff = aux->difficulty;

        addQuestionFile(qID, ques, cat, diff);
    }
}

void saveAnswers(answersNode **answersList){

    remove("ANSWERS.csv");

    answersNode *aux;

    char aID[10], ansA[100], ansB[100], ansC[100];
    char indi;

    for (aux = *answersList; aux != NULL; aux = aux->next){

        strcpy(aID, aux->answersID);
        strcpy(ansA, aux->answerA);
        strcpy(ansB, aux->answerB);
        strcpy(ansC, aux->answerC);
        indi = aux->indicator;

        addAnswerFile(aID, ansA, ansB, ansC, indi);
    }
}

void savePlayers(playersNode **playersList){

    remove("PLAYERS.csv");

    playersNode *aux = *playersList;

    char id[15], nick[30], name[50], lastN[50], secondLastN[50], date[12], mail[100], home[30];

    do{
        strcpy(id, aux->IdentificationCard);
        strcpy(nick, aux->nickname);
        strcpy(name, aux->playerName);
        strcpy(lastN, aux->lastName);
        strcpy(secondLastN, aux->SecondLastName);
        strcpy(date, aux->bornDate);
        strcpy(mail, aux->mail);
        strcpy(home, aux->place);

        addPlayersFile(id, nick, name, lastN, secondLastN, date, mail, home);

        aux = aux->next;

    } while (aux != *playersList);
}

void saveRewards(rewardNode **rewardList){

    remove("REWARDS.csv");

    rewardNode *aux;

    char name[100], description[100];
    int value, quantity; 

    for (aux = *rewardList; aux != NULL; aux = aux->next){

        strcpy(name, aux->nameReward);
        value = aux->value;
        quantity = aux->quantity;
        strcpy(description, aux->description);

        addRewardsFile(name, value, quantity, description);
    }
}

void saveWins(topFiveNode **topFiveList){

    remove("WINS.csv");

    topFiveNode *aux;

    char id[15];
    int win;

    for (aux = *topFiveList; aux != NULL; aux = aux->next){

        strcpy(id, aux->id);
        win = aux->wins;

        addWinsFile(id, win);
    }
}

void saveCount(gameModeNode **gameModeList){

    remove("TOPGAMEMODE.csv");

    gameModeNode *aux;

    char mode[25];
    int countMode;

    for (aux = *gameModeList; aux != NULL; aux = aux->next){

        strcpy(mode, aux->gameMode);
        countMode = aux->count;

        addModeGameFile(mode, countMode);
    }
}

void saveTopRewards(topRewardsNode **topRewards){

    remove("TOPREWARDS.csv");

    topRewardsNode *aux;

    char name[100];
    int count;

    for (aux = *topRewards; aux != NULL; aux = aux->next){

        strcpy(name, aux->nameReward);
        count = aux->count;

        addTopRewardsFile(name, count);
    }
}

//----------Función Main----------

int main(){

    //declaración e inicialización de variables y estructuras de datos.
    int choice = 0;
    char option;

    questionNode *questionList = NULL;
    answersNode *answersList = NULL;
    playersNode *playersList = NULL;
    easyQuestionQueue *easyQuestions;
    easyQuestions = newEasyQueue();
    mediumQuestionQueue *mediumQuestions;
    mediumQuestions = newMediumQueue();
    hardQuestionQueue *hardQuestions;
    hardQuestions = newHardQueue();
    gameInfoSatck *gameInfo;
    gameInfo = newStack();
    actualPlayersNode * actualPlayersList = NULL;
    pointsNode * pointsList = NULL;
    rewardNode *rewardList = NULL;
    topFiveNode *topFiveList = NULL;
    winsNode *winsList = NULL;
    gameModeNode *gameModeList = NULL;
    countGameModeNode *countGameModeList = NULL;
    topRewardsNode * topRewards = NULL;
    countRewardsNode * countRewards = NULL;

    //Muestra la bandera de Costa Rica
    CostaRicanFlag();

    //Cargar los datos de los archivos .csv a las estructuras de datos
    uploadQuestions(&questionList);
    uploadAnswers(&answersList);
    uploadPlayers(&playersList);
    uploadGameInfo(gameInfo);
    uploadRewards(&rewardList);
    uploadWins(&topFiveList);
    uploadModeGame(&gameModeList);
    uploadTopRewards(&topRewards);

    //Menú principal del programa
    do{
        printf("Juego trivial " WHITE "inde" BLUE "pend" RED "encia " WHITE "Cos" BLUE "ta R" RED "ica\n" RESET_COLOR);
        printf(YELLOW "Seleccione una opcion\n" RESET_COLOR);
        printf(CYAN "1. Registrar pregunta\n" RESET_COLOR);
        printf(CYAN "2. Modificar o remover pregunta\n" RESET_COLOR);
        printf(CYAN "3. Consultar lista de preguntas registradas\n" RESET_COLOR);
        printf(CYAN "4. Registrar jugador\n" RESET_COLOR);
        printf(CYAN "5. Modificar informacion de jugador\n" RESET_COLOR);
        printf(CYAN "6. Consultar informacion de jugador\n" RESET_COLOR);
        printf(CYAN "7. Eliminar informacion de jugador\n" RESET_COLOR);
        printf(CYAN "8. Configurar modo de juego y generar partida\n" RESET_COLOR);
        printf(CYAN "9. Consultar partidas de jugador\n" RESET_COLOR);
        printf(CYAN "10. Registro de premios\n" RESET_COLOR);
        printf(CYAN "11. Analisis de datos\n" RESET_COLOR);
        printf(CYAN "12. Salir\n" RESET_COLOR);
        
        scanf("%d",&choice); 

        switch(choice){
            case 1:
                registerQuestion(&questionList);
                registerAnswers(&answersList);
                break;
            case 2:
                printf(CYAN "Para modificar ingrese M | Para remover ingrese R\n" RESET_COLOR);
                option = modifyOrRemoveQuestion();
                if (option == 'M'){
                    clearBuffer();
                    modifyQuestion(&questionList, &answersList);
                }else{
                    clearBuffer();
                    removeQuestion(&questionList, &answersList);
                }
                break;
            case 3:
                showQuestionList(questionList);
                showAnswersList(answersList);
                break;
            case 4:
                clearBuffer();
                appendPlayers(&playersList);
                break;
            case 5:
                clearBuffer();
                modifyPlayer(&playersList);
                break;
            case 6:
                clearBuffer();
                showPlayersList(playersList, gameInfo); 
                break;
            case 7:
                clearBuffer();
                deletePlayer(playersList, gameInfo);
                break;
            case 8:
                clearBuffer();
                play(&questionList, &answersList, &playersList, easyQuestions, mediumQuestions, hardQuestions, gameInfo, &actualPlayersList, &pointsList, rewardList, &topFiveList, &gameModeList, &topRewards);
                break;
            case 9:
                clearBuffer();
                showStack(gameInfo);
                break;
            case 10:
                appendReward(&rewardList);
                showRewards(rewardList);
                break;
            case 11:
                findTopFiveWinners(&topFiveList, &winsList);
                findTopFiveGameMode(&gameModeList, &countGameModeList);
                findTopFiveRewards(&topRewards, &countRewards);
                break;
            case 12:
                saveQuestions(&questionList);
                saveAnswers(&answersList);
                savePlayers(&playersList);
                saveRewards(&rewardList);
                saveWins(&topFiveList);
                saveCount(&gameModeList);
                saveTopRewards(&topRewards);
                printf(WHITE "Gracias " BLUE "por " RED "jugar" RESET_COLOR "\n"); 
                break;
            default:
                printf(RED "Incorrect option" CYAN "Intente de nuevo\n" RESET_COLOR);
                break;
        } 
    } while (choice != 12 && choice != EOF);

    return 0;
}