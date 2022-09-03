#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


const char simboluri[]    = {'A','7','K','Q','C','0','3'};
const float multipliers[] = { 2 , 10, 3 , 4 , 6 ,1.5, 5 };
const int lenSimboluri = 7;

char** pacanea;
int linii,coloane = 5;

void afisarePacanea(){
    for(int i = 0; i < linii; i++){
        for(int j = 0; j < coloane; j++){
            printf("%c ",pacanea[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void cautareCombinatie(int i, int j, int nr, int* total){
    nr++;
    if(j + 1 == coloane){
        if(nr < 3)
            nr = 0;
        else{
            char c = pacanea[i][j];
            pacanea[i][j] = '-';
            afisarePacanea();
            pacanea[i][j] = c;
        }
        (*total) += nr;
        return;
    }
    bool terminatCombinatie = true;
    if(i - 1 >= 0 && pacanea[i][j] == pacanea[i-1][j+1]){
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i - 1, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(pacanea[i][j] == pacanea[i][j+1]){
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(i + 1 < linii && pacanea[i][j] == pacanea[i+1][j+1]){
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i + 1, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(terminatCombinatie == true) {
        if(nr < 3)
            nr = 0;
        else{
            char c = pacanea[i][j];
            pacanea[i][j] = '-';
            afisarePacanea();
            pacanea[i][j] = c;
        }
        (*total) += nr;
        return;
    }
}

void joc(float* balanta, float miza){
    if(miza > *balanta){
        printf("Nu ai destui bani, nu joci responsabil!\n");
        return;
    }
    *balanta -= miza;
    int i,j;
    for(i = 0; i < linii; i++){
        for(j = 0; j < coloane; j++){
            pacanea[i][j] = simboluri[rand() % 7];
        }
    }
    afisarePacanea();
    float castig = 0;
    int total;

    total = 0;
    cautareCombinatie(0,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[0][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;

    total = 0;
    cautareCombinatie(1,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[1][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;

    total = 0;
    cautareCombinatie(2,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[2][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;
    *balanta += castig;

    printf("Ai castigat %f! Joaca responsabil\n",castig);

}

int main()
{

    printf("Multipliers:\n");
    for(int i = 0; i < lenSimboluri; i++){
        printf("%c -> %f x\n",simboluri[i],multipliers[i]);
    }

    srand(time(NULL));

    char c;

    float balanta,miza;

    printf("De cate linii sa fie pacaneaua? (cel putin 3)\n");
    scanf("%d",&linii);
    scanf("%c",&c); //citesc enter sa nu ramana necitit
    if(linii < 3){ ///trebuie introduse cel putin 3 linii
        printf("Data viitoare asculta indicatiile.\n"); ///
        printf("Apasa orice pentru a continua\n"); ///
        scanf("%c",&c);
        return 0;
    }
    pacanea = (char**)malloc(linii * sizeof(char*));
    for (int i = 0; i < linii; i++)
        pacanea[i] = (char*)malloc(coloane * sizeof(char));

    printf("Introdu balanta\n");
    scanf("%f",&balanta);
    scanf("%c",&c);

    bool running = true;

    printf("Seteaza miza si incepe sa joci\n");
    scanf("%f",&miza);
    scanf("%c",&c);

    while(running){

        printf("Balanta: %f\nMiza curenta: %f\n",balanta,miza);

        joc(&balanta,miza);

        printf("Noua balanta: %f\n",balanta);

        printf("Apasa q pentru a iesi\n");
        printf("Apasa s pentru a schimba miza\n");
        printf("Apasa enter pentru a continua cu aceeasi miza\n");

        scanf("%c",&c);

        if(c == 'q'){
            running = false;
            scanf("%c",&c);
            printf("Ma bucur ca te-ai distrat. Te mai asteptam. Joaca responsabil!\n");
        }
        else if(c == 's'){
            scanf("%c",&c);
            printf("Introdu miza\n");
            scanf("%f",&miza);
            scanf("%c",&c);
        }
        else if(c == '\n')
            printf("Continuam. Joaca responsabil!\n");

        if(balanta == 0){
            running = false;
            printf("Nu ai jucat responsabil, dar noi tot ne-am facut banii. Va mai asteptam. GGEZ\n");
        }

    }
    printf("Apasa orice pentru a continua\n");
    scanf("%c",&c);
    return 0;
}
