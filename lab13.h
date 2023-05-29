#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#ifndef lab13_h
#define lab13_h

#define MAX_LENGTH 92
#define MAX_GAMES 100
#define INPUT_LEN 20
#define SORT_CAT 10
#define NA "na_sales"
#define EU "eu_sales"
#define JP "jp_sales"
#define OT "other_sales"
#define GB "global_sales"
#define Y "year"
#define N "name"
#define P "platform"
#define G "genre"
#define PU "publisher"
#define COMPARE(a, b) (((a) > (b)) - ((a) < (b)))

struct game {
    int rank;
    int year;
    char *name;
    char *platform;
    char *genre;
    char *publisher;
    
    // sales below represented in millions
    float NA_sales;
    float EU_sales;
    float JP_sales;
    float other_sales;
    float global_sales;
};

/*FOLLOWING STRUCTS AND FUNCTIONS ARE INITIALISED IN PROCESSING.C
  THESE REPRESENT PART 1*/

struct pub { //stands for publication
              //stores info for each publication
    char *name;
    int game; //number of games publication has
    int capacity; //number of publications in total, for convienence 
};

struct game *reader(FILE *fp); //following functions for reading
void filler(struct game *ara);
void printer(struct game *ara); //prints all the data in ara //primarily for dev debugging
void writer(struct game *ara);
void clear(struct game *ara); //frees ara create by reader

struct pub *create(struct game *ara); //following functions for data management:publication
bool search(struct pub *list, char *s, int size);
void update(struct pub *list, struct game *ara, int size);
void sort(struct pub *list, int size);
void clear_pub(struct pub *list, int size); //frees list created by create

struct pub *game_s(struct game *ara); //following functions for data management:games
void g_update(struct pub *list, struct game *ara, int size);
void g_sort(struct pub *list, int size);

void print_per(struct game *ara); //prints sales percentages by region

void print_basic(struct game *ara); //prints summary stats

void print_pub(struct pub *list, int size); //prints common publisher

void print_rep(struct pub *list, int size); //prints repeated games

/*FOLLOWING STRUCTS AND FUNCTIONS ARE INITIALISED IN SORTING.C
  THESE REPRESENT PART2*/   

int valid(char *t); //validates whether user input is valid and return an int to further operations

void uni_sorter(struct game *ara, int flag); //sorting function that takes in flag sorts according to flag

void sort_y(struct game *ara); //sorts by year and then subsorts into dictionary order
int compare_y(const void *x, const void *y); //compares year
int compare_ya(const void *x, const void *y); //compare alphabetical order in sub section

void sort_REG(struct game *ara, int flag); //sorts by REGIONAL_sales
int compare_NA(const void *x, const void *y); //compares NA_sales(float)
int compare_EU(const void *x, const void *y); //compares EU_sales(flaot)
int compare_JP(const void *x, const void *y); //compares JP_sales(float)
int compare_OT(const void *x, const void *y); //compare other_sales(float)
int compare_GB(const void *x, const void *y); //compare global_sales(float)

void sort_NAM(struct game *ara); //sorts by game name
int compare_n(const void *x, const void *y); //compare game name

int compare_PL(const void *x, const void *y); //compare platform
int compare_PLA(const void *x, const void *y); //compare alphabetical order in sub section

int compare_GE(const void *x, const void *y); //compare genre
int compare_GEA(const void *x, const void *y); //compare alphabetical order in sub section

int compare_PU(const void *x, const void *y); //compare publisher
int compare_PUA(const void *x, const void *y); //compare alphabetical order in sub section

void write_category(struct game *ara, int flag); //creates a csv file and writes ara onto it

#endif