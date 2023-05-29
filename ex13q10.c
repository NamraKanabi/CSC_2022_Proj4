#include "lab13.h"

struct game *reader(FILE *fp){
    struct game *ara; //ara is a pointer to array of 100 game structs
    ara = (struct game *)malloc( MAX_GAMES * sizeof(struct game));

    int read=0, records=0; //category index , array index
    char buffer[MAX_LENGTH], liner[120];
    fgets( buffer, MAX_LENGTH, fp); //skips title lines
    fgets( buffer, MAX_LENGTH, fp);

    while( fgets(liner, 120, fp) ){ //loop to split file into lines and read values seperated by commas
        read=0;
        char *token;

        token = strtok(liner, ",");

        while( token!=NULL ){
            if ( read==0 ){ //reads rank
                ara[records].rank=atoi(token);
            }

            if ( read==1 ){ //reads name
                ara[records].name = (char *)malloc(strlen(token)+1);
                strcpy(ara[records].name,token);
            }

            if ( read==2 ){ //reads platform
                ara[records].platform = (char *)malloc(strlen(token)+1);
                strcpy(ara[records].platform,token);
            }

            if ( read==3 ){ //reads year
                ara[records].year=atoi(token);
            }

            if ( read==4 ){ //reads genre
                ara[records].genre = (char *)malloc(strlen(token)+1);
                strcpy(ara[records].genre,token);
            }

            if ( read==5 ){ //reads publication
                ara[records].publisher = (char *)malloc(strlen(token)+1);
                strcpy(ara[records].publisher,token);
            }

            if ( read==6 ){ //reads NA sales
                if ( strcmp(token," ")==0 ){
                    ara[records].NA_sales=-1;
                }
                else{
                    ara[records].NA_sales=atof(token);
                }
            }

            if ( read==7 ){ //reads EU sales
                if ( strcmp(token," ")==0 ){
                    ara[records].EU_sales=-1;
                }
                else{
                    ara[records].EU_sales=atof(token);
                }
            }

            if ( read==8 ){ //reads JP sales
                if ( strcmp(token," ")==0 ){
                    ara[records].JP_sales=-1;
                }
                else{
                    ara[records].JP_sales=atof(token);
                }
            }

            if ( read==9 ){ //reads other sales
                if ( strcmp(token," ")==0 ){
                    ara[records].other_sales=-1;
                }
                else{
                    ara[records].other_sales=atof(token);
                }
            }

            if ( read==10 ){ //reads global sales
                ara[records].global_sales=atof(token);
            }
            read++; //increments read so that each category is assgined correct values
            token = strtok(NULL, ",");
        }
        records++; //index for array
    }

    return ara;
}

void filler(struct game *ara){
    for(int i=0; i<MAX_GAMES ; i++){
        if( ara[i].NA_sales < 0){//checks and fills emopty na sales
            ara[i].NA_sales = ara[i].global_sales - ara[i].EU_sales - ara[i].JP_sales - ara[i].other_sales;
        }

        if( ara[i].EU_sales < 0){//checks and fills emopty eu sales
            ara[i].EU_sales = ara[i].global_sales - ara[i].NA_sales - ara[i].JP_sales - ara[i].other_sales;
        }

        if( ara[i].JP_sales < 0){//checks and fills emopty jp sales
            ara[i].JP_sales = ara[i].global_sales - ara[i].EU_sales - ara[i].NA_sales - ara[i].other_sales;
        }

        if( ara[i].other_sales < 0){//checks and fills emopty other sales
            ara[i].other_sales = ara[i].global_sales - ara[i].EU_sales - ara[i].JP_sales - ara[i].NA_sales;
        }
    }
}

void printer(struct game *ara){
    int n=0;
    for(n=0; n<MAX_GAMES; n++){
    printf("rank:%d | name:%s | plat:%s | year:%d | genre:%s | publisher:%s |",
            ara[n].rank,ara[n].name,ara[n].platform,ara[n].year,ara[n].genre,ara[n].publisher);
    printf(" na:%.2f | eu:%.2f | jp:%.2f | oth:%.2f | gb:%.2f\n",
            ara[n].NA_sales,ara[n].EU_sales,ara[n].JP_sales,ara[n].other_sales,ara[n].global_sales);}

    printf("success\n");
}

void writer(struct game *ara){
    FILE *new;
    new = fopen("processing.csv","w");

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

struct pub *create(struct game *ara){
    struct pub *list; //pointer of list of unique publications
    int cap=1,index=1; //capacity of list, index of list
    list = (struct pub *)malloc(cap*sizeof(struct pub));

    list[0].name = (char *)malloc(strlen(ara[0].publisher)+1); //initialising first member
    strcpy(list[0].name,ara[0].publisher);
    list[0].game = 0;

    for(int i=1; i<MAX_GAMES; i++){
        if( search(list, ara[i].publisher, cap) ){ //if publisher already in list: continue
            continue;
        }
        else{ //else add publisher to list and update capacity and index
            cap++;
            list = (struct pub *)realloc(list,cap*sizeof(struct pub));
            list[index].name = (char *)malloc(strlen(ara[i].publisher)+1);
            strcpy(list[index].name,ara[i].publisher);
            list[index].game = 0;
            index++;
        }
    }
    list[0].capacity = index; //to keep track of total number of elements in list, update capacity of first element
                              //rest of element need not be updated, this is only for convienence

    return list;
}

bool search(struct pub *list, char *s ,int size){
    if( list==NULL ){ //if list is NULL return false
        return false;
    }
    else{
        bool flag=false;
        for(int i=0; i<size; i++){
            if( strcmp(s,list[i].name)==0 ){ //if target is found: return true
                flag=true;
                return flag;
            }
        }
        return flag; //target is not found: return false
    }
}

void update(struct pub *list, struct game *ara, int size){
    for(int i=0; i<size; i++){ //updates pub.game , number of times publisher is repeated in ara
        for(int j=0; j<MAX_GAMES; j++){
            if( strcmp(list[i].name,ara[j].publisher)==0 ){
                list[i].game++;
            }
        }
    }
}

void sort(struct pub *list, int size){
    struct pub temp;

    for(int i=0; i<size-1; i++){ //sorts list into alphabetical order by publications(pub.name)
        for(int j=i+1; j<size; j++){
            if( strcmp(list[i].name,list[j].name) > 0 ){
                temp=list[j];
                list[j]=list[i];
                list[i]=temp;
            }
        }
    }

    list[0].capacity=size; //update first elem capacity
}

struct pub *game_s(struct game *ara){
    struct pub *glist; //pointer of list of unique games
    int cap=1,index=1; //capacity of list, index of list
    glist = (struct pub *)malloc(cap*sizeof(struct pub));

    glist[0].name = (char *)malloc(strlen(ara[0].name)+1); //initialising first member
    strcpy(glist[0].name,ara[0].name);
    glist[0].game = 0;

    for(int i=1; i<MAX_GAMES; i++){
        if( search(glist, ara[i].name, cap) ){ //if game already in list: continue
            continue;
        }
        else{ //else add game to list and update capacity and index
            cap++;
            glist = (struct pub *)realloc(glist,cap*sizeof(struct pub));
            glist[index].name = (char *)malloc(strlen(ara[i].name)+1);
            strcpy(glist[index].name,ara[i].name);
            glist[index].game = 0;
            index++;
        }
    }
    glist[0].capacity = index; //to keep track of total number of elements in list, update capacity of first element
                               //rest of element need not be updated, this is only for convienence

    return glist;
}

void g_update(struct pub *list, struct game *ara, int size){
    for(int i=0; i<size; i++){ //updates pub.game , number of times game is repeated in ara
        for(int j=0; j<MAX_GAMES; j++){
            if( strcmp(list[i].name,ara[j].name)==0 ){
                list[i].game++;
            }
        }
    }
}

void g_sort(struct pub *list, int size){
    struct pub temp;
    int max;

    for(int i=0; i<size-1; i++){ //sorts list into descending order of game repetetions(pub.game)
        max=i;
        for(int j=i+1; j<size; j++){
            if( list[max].game<list[j].game ){
                max=j;
            }

            if( max!=i){
                temp=list[max];
                list[max]=list[i];
                list[i]=temp;
            }
        }
    }

    for(int i=0; i<size-1; i++){ //sorts list into dictionary order if game repetetion is equal
        for(int j=i+1; j<size; j++){
            if( list[i].game==list[j].game && strcmp(list[i].name,list[j].name)>0 ){
                temp=list[j];
                list[j]=list[i];
                list[i]=temp;
            }
        }
    }

    list[0].capacity=size; //assign array size to first elem to keep track
}

void print_per(struct game *ara){
    printf("\n");
    printf("############ Sales Percentages ############\n");
    float na,eu,jp,ot;

    for(int i=0; i<MAX_GAMES; i++){
        na= (ara[i].NA_sales/ara[i].global_sales)*100;
        eu= (ara[i].EU_sales/ara[i].global_sales)*100;
        jp= (ara[i].JP_sales/ara[i].global_sales)*100;
        ot= (ara[i].other_sales/ara[i].global_sales)*100;

        printf("%s - NA: %.1f%c, EU: %.1f%c, JP: %.1f%c, Other: %.1f%c\n",ara[i].name,
                     na,37,eu,37,jp,37,ot,37);
    }
}

void print_basic(struct game *ara){
    printf("\n");
    printf("############ Summary Statistics ############\n");

    float mean,median,range;
    
    float sum=0; //calculate mean and print it
    for(int i=0; i<MAX_GAMES; i++){
        sum=sum+ara[i].global_sales;
    }
    mean=sum/MAX_GAMES;
    printf("Mean global sales: %.2f million\n",mean);

    int n= ( (MAX_GAMES+1)/2 ) -1; //calculate median and print it
    median = (ara[n].global_sales + ara[n+1].global_sales)/2;
    printf("Median global sales: %.2f million\n",median);

    float max,min; //calculate range and print it
    max=min=ara[0].global_sales;
    for(int i=0; i<MAX_GAMES; i++){
        if( ara[i].global_sales>max ){
            max=ara[i].global_sales;
        }
        if( ara[i].global_sales<min ){
            min=ara[i].global_sales;
        }
    }
    range=max-min;
    printf("Range of global sales: %.2f million\n",range);
}

void print_pub(struct pub *list, int size){
    printf("############ Common publishers: ############\n");

    for(int i=0; i<size; i++){
        if( list[i].game == 1 ){
            printf("%s: %d game\n",list[i].name,list[i].game);
        }
        else{
            printf("%s: %d games\n",list[i].name,list[i].game);
        }
    }
}

void print_rep(struct pub *list, int size){
    printf("\n");
    printf("############ Repeated games: ############\n");

    for(int i=0; i<size; i++){
        if( list[i].game == 1 ){
            printf("%s: %d time\n",list[i].name,list[i].game);
        }
        else{
            printf("%s: %d times\n",list[i].name,list[i].game);
        }
    }
}

void clear(struct game *ara){
    for(int i=0; i<MAX_GAMES; i++){
        free(ara[i].name);
        free(ara[i].platform);
        free(ara[i].genre);
        free(ara[i].publisher);
    }
    free(ara);
}

void clear_pub(struct pub *list, int size){
    for(int i=0; i<size; i++){
        free(list[i].name);
    }
    free(list);
}