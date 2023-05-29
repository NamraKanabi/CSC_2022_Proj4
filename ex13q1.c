#include "lab13.h"

#ifndef FLAG
#define FLAG 1
#endif

int main(int argc , char **argv){
    
    FILE *fp;

    if ( argc>=2 ){ //used to open file
        fp = fopen(argv[1], "r");
    }
    else{
        fp = fopen("gamesales.csv","r");
    }

    if ( fp == NULL ){
        printf("Error opening the file\n");
        return 1;
    }

    struct game *ara = reader(fp);
    fclose(fp);

    if( FLAG==1 ){ //COMPILE PROCESSOR
        //PART 1

        filler(ara);
        writer(ara);
        struct pub *list = create(ara);
        update(list,ara,list[0].capacity);
        sort(list,list[0].capacity);
        print_pub(list,list[0].capacity);

        struct pub *glist = game_s(ara);
        g_update(glist,ara,glist[0].capacity);
        g_sort(glist,glist[0].capacity);
        print_rep(glist,glist[0].capacity);

        print_per(ara);

        print_basic(ara);

        clear(ara);
        clear_pub(list, list[0].capacity);
        clear_pub(glist, glist[0].capacity);

        return 0;
    }

    if( FLAG==2){//COMPILE SORTING
        //PART 2    
        char input[INPUT_LEN];
        printf("Sort games by: ");
        scanf("%s",input);

        for(int i=0; i<strlen(input); i++){
            input[i] = tolower(input[i]);
        }

        int flag = valid(input);

        if( flag==-1 ){
            printf("Invalid Input\n");
            return 1;
        }

        else{
            uni_sorter(ara,flag);
        }

        write_category(ara,flag);

        clear(ara);

        return 0;
    }
}