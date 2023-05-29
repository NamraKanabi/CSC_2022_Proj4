#include "lab13.h"

int valid(char *t){
    char arr[10][20] = {NA,EU,JP,OT,GB,Y,N,P,G,PU};

    for(int i=0; i<SORT_CAT; i++){
        if( strcmp(t,arr[i])==0 ){
            return i;
        }
    }

    return -1;
}

void sort_y(struct game *ara){
    qsort(ara, MAX_GAMES, sizeof(struct game), compare_y);
    qsort(ara, MAX_GAMES, sizeof(struct game), compare_ya);

    for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
        ara[i].rank=i+1;
    }
}

int compare_y(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return xx.year - yy.year;
}

int compare_ya(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    if( xx.year != yy.year ){
        return 0;
    }
    else{
        return strcmp(xx.name, yy.name);
    }
}

void sort_REG(struct game *ara, int flag){
    if( flag==0 ){
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_NA);
    }

    if( flag==1 ){
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_EU);
    }

    if( flag==2 ){
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_JP);
    }

    if( flag==3 ){
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_OT);
    }

    if( flag==4 ){
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_GB);
    }

    for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
        ara[i].rank=i+1;
    }
}

int compare_NA(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return COMPARE(xx.NA_sales, yy.NA_sales);
}

int compare_EU(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return COMPARE(xx.EU_sales, yy.EU_sales);
}

int compare_JP(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return COMPARE(xx.JP_sales, yy.JP_sales);
}

int compare_OT(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return COMPARE(xx.other_sales, yy.other_sales);
}

int compare_GB(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return COMPARE(xx.global_sales, yy.global_sales);
}

void sort_NAM(struct game *ara){
    qsort(ara, MAX_GAMES, sizeof(struct game), compare_n);

    for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
        ara[i].rank=i+1;
    }
}

int compare_n(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return strcmp(xx.name, yy.name);
}

int compare_PL(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return strcmp(xx.platform, yy.platform);
}

int compare_PLA(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    if( strcmp(xx.platform, yy.platform)!=0 ){
        return 0;
    }
    else{
        return strcmp(xx.name, yy.name);
    }
}

int compare_GE(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return strcmp(xx.genre, yy.genre);
}

int compare_GEA(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    if( strcmp(xx.genre, yy.genre)!=0 ){
        return 0;
    }
    else{
        return strcmp(xx.name, yy.name);
    }
}

int compare_PU(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    return strcmp(xx.publisher, yy.publisher);
}

int compare_PUA(const void *x, const void *y){
    struct game xx = *(struct game*)x;
    struct game yy = *(struct game*)y;

    if( strcmp(xx.publisher, yy.publisher)!=0 ){
        return 0;
    }
    else{
        return strcmp(xx.name, yy.name);
    }
}

void uni_sorter(struct game *ara, int flag){
    if( flag>=0 && flag<5){ //sort by REGIONAL_sales
        sort_REG(ara,flag);
    }

    if( flag == 5){ //sort by year
        sort_y(ara);
    }

    if( flag == 6){ //sort by name
        sort_NAM(ara);
    }

    if( flag == 7){ //sort by platform
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_PL);
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_PLA);

        for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
            ara[i].rank=i+1;
        }
    }

    if( flag == 8){ //sort by genre
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_GE);
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_GEA);

        for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
            ara[i].rank=i+1;
        }
    }

    if( flag == 9){ //sort by publisher
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_PU);
        qsort(ara, MAX_GAMES, sizeof(struct game), compare_PUA);

        for(int i=0; i< MAX_GAMES; i++){//reranks after sorting
            ara[i].rank=i+1;
        }
    }
}

void write_category(struct game *ara, int flag){
    FILE *new;

    char names[10][40]={"gamesales_NA_sales.csv","gamesales_EU_sales.csv","gamesales_JP_sales.csv",
                        "gamesales_other_sales.csv","gamesales_global_sales.csv","gamesales_year.csv",
                        "gamesales_name_sales.csv","gamesales_platform.csv","gamesales_genre.csv","gamesales_publisher.csv"};

    new = fopen(names[flag],"w");

    if( new==NULL ){
        printf("Failure to create file\n");
        return;
    }

    fprintf(new, "Rank,Name,Platform,Year,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales\n");

    for(int i=0; i<MAX_GAMES; i++){
        fprintf(new,
                    "%d,%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                    ara[i].rank,ara[i].name,ara[i].platform,ara[i].year,ara[i].genre,ara[i].publisher,
                    ara[i].NA_sales,ara[i].EU_sales,ara[i].JP_sales,ara[i].other_sales,ara[i].global_sales);
    }

    fclose(new);
}