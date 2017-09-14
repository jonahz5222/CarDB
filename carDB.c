/* 
 * Name: Jonah Zukosky
 * Pawprint: jbzmv8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINELENGTH 200
#define MAXCARPRICE 1000000

typedef struct node {
    char make[25];
    char model[25];
    int price;
    int year;
    char color[25];
    char type[25];
    int mileage;
    struct node* left;
    struct node* right;
}Node;

Node* get_cars(char* filename);
Node* add_to_tree(Node* head,Node* new);
int word_check(char* word,char* type);
void search_tree(Node* root,int year,int price,char* make,char* color,int* count);
void free_tree(Node* head);

int main(int argc,char** argv){
    if(argc != 2){
        printf("Incorrect Parameters. Exiting.\n");
        return 1;
    }

    Node* head;
    int stop = 0;
    int year = 0;
    int price = 0;
    int* count = malloc(sizeof(int));

    
    
    *count = 0;

    head = get_cars(*(argv+1));

    while(stop != -1){

        printf("To search for a vehicle newer than a specific year, enter: '1'\nTo search for a vehicle that costs less than a certain price enter: '2'\nTo search for a vehicle with both of the above parameters, enter '3'\nTo search for color price and make, enter '4'\nTo exit, enter: '-1'\n");
        scanf("%d", &stop);

        if(stop == 1){

            printf("Enter the year you would like the vehicles to be newer than: ");
            scanf("%d", &year);
            printf("\n");

            search_tree(head,year,MAXCARPRICE,"0","0",count);

        }
        else if(stop == 2){
            
            printf("Enter the price you would like the vehicles to be less than: ");
            scanf("%d", &price);
            printf("\n");
            year = 0;
            search_tree(head,year,price,"0","0",count);

        }
        else if(stop == 3){

            printf("Enter the year you would like the vehicles to be newer than: ");
            scanf("%d", &year);
            printf("\n");

            printf("Enter the price you would like the vehicles to be less than: ");
            scanf("%d", &price);
            printf("\n");

            search_tree(head,year,price,"0","0",count);

        }
        else if(stop == 4){
            
            char* make = malloc(sizeof(char)*20);
            char* color = malloc(sizeof(char)*20);
            printf("Enter the color you would like the car to be: ");
            scanf("%s", color);
            printf("\n");

            printf("Enter the make of the car: ");
            scanf("%s", make);
            printf("\n");

            printf("Enter the price you would like the vehicles to be less than: ");
            scanf("%d", &price);
            printf("\n");

            search_tree(head,0,price,make,color,count);
            free(make);
            free(color);
        }
        if(stop != -1 && stop != 1 && stop != 2 && stop != 3 && stop != 4){
            printf("Incorrect Input. Try again\n");
        }

        if(stop != -1){
            printf("There were %d cars found\n", *count);
            *count = 0;
        }
        
        

        

    }


free(count);
free_tree(head);
return 0;
}

Node* get_cars(char* filename){
    //Initializes head and New
    Node* head = NULL;
    Node* newPtr = malloc(sizeof(Node));
    newPtr->make[0] = '0';
    newPtr->model[0] = '0';
    newPtr->price = 0;
    newPtr->year = 0;
    newPtr->color[0] = '0';
    newPtr->type[0] = '0';
    newPtr->mileage = 0;

    char* newLine = malloc(sizeof(char)*MAXLINELENGTH);
    char* token;
    int count = 0;
    char* wordType;
    int wordCheck = 0;
    int check = 0;


    FILE* fp = fopen(filename,"r");

    if(fp == NULL){
        printf("Cannot open file. Exiting\n");
        exit(1);
    }

    
    
    while(fgets(newLine,MAXLINELENGTH,fp) != NULL){
         
        token = strtok(newLine, "|");
        while(token != NULL){
                
                count++;
                if(count%2 != 0){
                    wordType = token;
                }
                else{

                wordCheck = word_check(token,wordType);
                
                if(wordCheck == 1 && strcmp(wordType,"make") == 0){
                    strcpy(newPtr->make,token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"model") == 0){
                    strcpy(newPtr->model,token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"price") == 0){
                    newPtr->price = atoi(token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"year") == 0){
                    newPtr->year = atoi(token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"color") == 0){
                    strcpy(newPtr->color,token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"type") == 0){
                    strcpy(newPtr->type,token);
                    check++;
                }
                else if(wordCheck == 1 && strcmp(wordType,"mileage") == 0){
                    newPtr->mileage = atoi(token);
                    check++;
                }
                }
                
                token = strtok(NULL, "|");
        
        if(check){
            head = add_to_tree(head,newPtr);
            check = 0;
        }

        }
    }
    


fclose(fp);
free(newPtr);
free(newLine);
return head;   
}

int word_check(char* word,char* type){

    

    if(strcmp(type,"make") == 0){
        if( strcmp(word, "chevrolet") == 0 || strcmp(word,"ford")==0  || strcmp(word, "bmw")==0 ||  strcmp(word,"mercury")==0 || strcmp(word,"pontiac")==0 || strcmp(word,"mercedes")==0 || strcmp(word,"hundai")==0 || strcmp(word,"bugatti")==0 || strcmp(word,"toyota")==0 || strcmp(word,"gmc") ==0|| strcmp(word,"buick")==0 || strcmp(word,"audi")==0 || strcmp(word,"ferrari")==0 || strcmp(word,"honda")==0 || strcmp(word,"jeep")==0 || strcmp(word,"kia")==0 || strcmp(word,"dodge")==0 || strcmp(word,"porche") == 0){return 1;}

    }
    if(strcmp(type,"price") == 0){

        if( atoi(word) < MAXCARPRICE ){return 1;}

    }
    if(strcmp(type,"color") == 0){
        
        if( strcmp(word,"blue") == 0 || strcmp(word,"red") == 0 || strcmp(word,"orange") == 0 || strcmp(word,"silver") == 0 || strcmp(word,"black") == 0 || strcmp(word,"white") == 0 || strcmp(word,"green") == 0 || strcmp(word,"turquise") == 0){return 1;}

    }
    if(strcmp(type,"type") == 0){

        if(strcmp(word,"car") == 0 || strcmp(word,"truck") == 0 || strcmp(word,"van") == 0 || strcmp(word,"suv") == 0){return 1;}

    }
    if(strcmp(type,"mileage") == 0){
        
        if( atoi(word) >= 0){return 1;}

    }

    if(strcmp(type,"model") == 0){return 1;}

    if(strcmp(type,"year") == 0){

        if( atoi(word) > 1700 && atoi(word) < 2019 ){

            return 1;
        }
    }
    
return 0;
}

Node* add_to_tree(Node* head,Node* new){

    if(head == NULL){

        head = malloc(sizeof(Node));
        
        

        memcpy(head->make,new->make,25);
        memcpy(head->model,new->model,25);
        memcpy(head->color,new->color,25);
        memcpy(head->type,new->type,25);

    
        head->price = new->price;
        head->year = new->year;
        head->mileage = new->mileage;
        head->left = NULL;
        head->right = NULL;
        return head; 
    }
    
    Node* current = head;
    if(current->price < new->price){

        current->right = add_to_tree(current->right,new);
    }
    if(current->price > new->price){

        current->left = add_to_tree(current->left,new);
    }

    return head;

}

void search_tree(Node* root,int year,int price,char* make,char* color,int* count){

    
    if(root != NULL){ 
    
            search_tree(root->left,year,price,make,color,count);
            search_tree(root->right,year,price,make,color,count);
            
            if(strcmp(make,"0") != 0){
                if(root->price < price && strcmp(root->make,make) == 0 && strcmp(root->color,color) == 0){
                    printf(" %d %s %s %s that costs %d\n",root->year,root->make,root->color,root->model,root->price);
                    (*count)++;
                }
            }
            else{ 
                if(root->price < price && root->year > year){

                printf(" %d %s %s that costs %d\n", root->year,root->make,root->model,root->price);
                (*count)++;
                }
            }

    }

    
}

void free_tree(Node* head){

    if(head == NULL){return;}

    free_tree(head->left);
    free_tree(head->right);
    free(head);

}
