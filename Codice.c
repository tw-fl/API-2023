#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct car{
    int aut;
    struct car *next;
} car_t;

typedef struct station{
    int dist;
    struct station *next;
    struct station *previous;
    struct car *carsList;
    int howManyCars;
} station_t;

typedef struct results{
    int result;
    struct results *previous;
} result_t;

station_t *stationListHead = NULL;
station_t *stationListTail = NULL;
int temp;

void addCarToStation(station_t * node){
    if(node -> carsList == NULL){
        node -> carsList = (car_t *)malloc(sizeof(car_t));
        node -> carsList -> next = NULL;
        node -> carsList -> aut = temp;
    }
    else{
        car_t *carNode = node -> carsList;
        if(temp > carNode -> aut){
            node -> carsList = (car_t *)malloc(sizeof(car_t));
            node -> carsList -> next = carNode;
            node -> carsList -> aut = temp;
        }
        else{
            while(carNode -> next != NULL){
                if(carNode -> next -> aut > temp){
                    carNode = carNode -> next;
                }
                else{
                    break;
                }
            }
            car_t *newCar = (car_t *)malloc(sizeof(car_t));
            newCar -> aut = temp;
            newCar -> next = carNode -> next;
            carNode -> next = newCar;
        }
    }
}



int main(){
    char inputCommand[20];

    while(scanf("%s", inputCommand) != EOF){
        if(strcmp(inputCommand, "aggiungi-stazione") == 0){
            bool flag = false;
            bool otherFlag = false;
            if(scanf("%d", &temp));
            station_t *node = stationListHead;
            int carsAmount;
            if(stationListHead == NULL){
                stationListHead = (station_t *)malloc(sizeof(station_t));
                stationListHead -> dist = temp;
                stationListHead -> previous = NULL;
                stationListHead -> next = NULL;
                stationListHead -> carsList = NULL;
                stationListTail = stationListHead;
                node = stationListHead;
                flag = true;
            }
            else {
                if(temp < node -> dist){
                    stationListHead = (station_t *)malloc(sizeof(station_t));
                    stationListHead -> next = node;
                    stationListHead -> previous = NULL;
                    stationListHead -> dist = temp;
                    stationListHead -> carsList = NULL;
                    node -> previous = stationListHead;
                    node = stationListHead;
                    flag = true;
                }
                else{
                    while(node -> next != NULL){
                        if(node -> next -> dist < temp){
                            node = node -> next;
                        }
                        else{
                            if(node -> next -> dist == temp)
                                otherFlag = true;
                            break;
                        }
                    }
                    if(otherFlag == true || node -> dist == temp){
                        printf("non aggiunta\n");
                    }
                    else{
                        station_t *newStation = (station_t *)malloc(sizeof(station_t));
                        newStation -> dist = temp;
                        newStation -> next = node -> next;
                        node -> next = newStation;
                        newStation -> previous = node;
                        newStation -> carsList = NULL;
                        if(newStation -> next != NULL){
                            newStation -> next -> previous = newStation;
                        }
                        else{
                            stationListTail = newStation;
                        }
                        node = newStation;
                        flag = true;
                    }
                }
            }

            if(scanf("%d", &carsAmount));
            node -> howManyCars = carsAmount;
            for(int i = 0; i < carsAmount; i++){
                if(scanf("%d", &temp));
                if(flag == true){
                    addCarToStation(node);
                }
            }
            temp = 0;
            addCarToStation(node);
            if(flag == true){
                printf("aggiunta\n");
            }
        }
        if(strcmp(inputCommand, "demolisci-stazione") == 0){
            if(scanf("%d", &temp));
            station_t *node = stationListHead;
            bool flag = false;
            if(stationListHead -> dist == temp){
                node = stationListHead;
                stationListHead = stationListHead -> next;
                flag = true;
            }
            else{
                while(node != NULL){
                    if(node -> dist == temp){
                        flag = true;
                        //if(node -> previous != NULL)
                            node -> previous -> next = node -> next;
                        if(node -> next != NULL)
                            node -> next -> previous = node -> previous;
                        else{
                            stationListTail = node -> previous;
                        }
                        break;
                    }
                    node = node -> next;
                }
            }
            if(flag == true){
                car_t *carsToDelete = node -> carsList;
                car_t *carToDelete = carsToDelete;
                while(carsToDelete != NULL){
                    carToDelete = carsToDelete;
                    carsToDelete = carsToDelete -> next;
                    free(carToDelete);
                }
                free(node);
                printf("demolita\n");
            }
            else
                printf("non demolita\n");
        }
        if(strcmp(inputCommand, "aggiungi-auto") == 0){
            if(scanf("%d", &temp));
            station_t *node = stationListHead;
            bool flag = false;
            while(node != NULL){
                if(node -> dist == temp){
                    flag = true;
                    break;
                }
                node = node -> next;
            }
            if(scanf("%d", &temp));

            if(node -> howManyCars >= 512){
                flag = false;
            }

            if(flag == true){
                addCarToStation(node);
                node -> howManyCars ++;
                printf("aggiunta\n");
            }
            else{
                printf("non aggiunta\n");
            }
        }
        if(strcmp(inputCommand, "rottama-auto") == 0){
            if(scanf("%d", &temp));
            station_t *node = stationListHead;
            bool found = false;
            while(node != NULL){
                if(node -> dist == temp){
                    found = true;
                    break;
                }
                node = node -> next;
            }

            if(scanf("%d", &temp));
            bool flag = false;

            if(found == true){
                car_t *carNode = node -> carsList;
                car_t *prev = NULL;
                while(carNode != NULL){
                    if(carNode -> aut == temp){
                        flag = true;
                        if(carNode == node -> carsList){
                            node -> carsList = carNode -> next;
                            free(carNode);
                        }
                        else{
                            prev -> next = carNode -> next;
                            free(carNode);
                        }
                        break;
                    }
                    prev = carNode;
                    carNode = carNode -> next;
                }
            }

            if(flag == true){
                node -> howManyCars --;
                printf("rottamata\n");
            }
            else{
                printf("non rottamata\n");
            }
        }
        if(strcmp(inputCommand, "pianifica-percorso") == 0){

            int startingPoint, endPoint, counter = 0;
            bool goesRight = true;
            if(scanf("%d", &startingPoint));
            if(scanf("%d", &endPoint));

            if(endPoint < startingPoint){
                goesRight = false;
            }

            //counting how many stations
            station_t *node;
            station_t *startingPointNode;

            if(goesRight){
                node = stationListHead;
                while(node -> dist != startingPoint)
                    node = node -> next;
                startingPointNode = node;
                while(node -> dist != endPoint){
                    counter++;
                    node = node -> next;
                }
                counter++;
            }
            else{
                node = stationListTail;
                while(node -> dist != startingPoint){
                    node = node -> previous;
                }
                startingPointNode = node;
                while(node -> dist != endPoint){
                    counter++;
                    node = node -> previous;
                }
                counter++;
            }

            //creating arrays as long as counter
            int stations[counter];
            int i = 0, j = 0;

            int *indexes;

            //filling stations array
            node = startingPointNode;
            if(goesRight){
                indexes = malloc(sizeof(int)*counter);

                while(node -> dist != endPoint){
                    stations[i] = node -> dist;
                    i++;
                    node = node -> next;
                }
                stations[i] = node -> dist;

                //filling indexes array
                node = startingPointNode;
                for(i = 0; i < counter; i++){
                    while(node -> dist + node -> carsList -> aut >= stations[j]){
                        indexes[j] = i;
                        j++;
                        if(j == counter)
                            break;
                    }
                    if(j == counter)
                        break;
                    node = node -> next;
                }
            }
            else{
                while(node -> dist != endPoint){
                    stations[i] = node -> dist;
                    i++;
                    node = node -> previous;
                }
                stations[i] = node -> dist;

                //no need to create indexes array, using a matrix method

                }


            //calculating reverse journey

            bool journeyExists = true;
            result_t *journey = (result_t *)malloc(sizeof(result_t));
            journey -> previous = NULL;
            journey -> result = stations[counter - 1];

            if(goesRight == true){
                //indexes method
                int lastPrint = -1, lastIndex = counter - 1;

                while(lastPrint != startingPoint){
                    lastPrint = stations[indexes[lastIndex]];
                    result_t *newResult = (result_t *)malloc(sizeof(result_t));
                    newResult -> result = lastPrint;
                    newResult -> previous = journey;
                    journey = newResult;
                    if(indexes[lastIndex] == lastIndex){
                        printf("nessun percorso\n");
                        journeyExists = false;
                        break;
                    }
                    lastIndex = indexes[lastIndex];
                }
                free(indexes);
            }
            else{
                //matrix method
                node = startingPointNode;
                int matrix[counter][counter];

                for(i = 0; i < counter; i++){
                        for(j = 0; j < counter; j++){
                            matrix[i][j] = 0;
                        }
                    }

                j = 1;
                matrix[0][0] = 0;
                for(i = 0; i < counter; i++){
                    while(stations[i] - node -> carsList -> aut <= stations[j]){
                        matrix[j][j] = matrix[i][i] + 1;
                        if(j == i){
                            journeyExists = false;
                            printf("nessun percorso\n");
                            break;
                        }
                        j++;
                        if(j == counter)
                            break;
                    }
                    if(journeyExists == false || j == counter){
                        break;
                    }
                    node = node -> previous;
                }
                node = startingPointNode;
                if(journeyExists == true){
                    for(i = 0; i < counter; i++){
                        for(j = i + 1; j < counter; j++){
                            if(stations[i] - node -> carsList -> aut <= stations[j]){
                                matrix[i][j] = matrix[i][i] + 1;
                            }
                            else{
                                matrix[i][j] = counter;
                            }
                        }
                        node = node -> previous;
                    }

                    int last = counter - 1;
                    j = matrix[last][last];

                    for(i = counter - 2; i > 0; i--){
                        if(matrix[i][last] == j){
                            result_t *newResult = (result_t *)malloc(sizeof(result_t));
                            newResult -> result = stations[i];
                            newResult -> previous = journey;
                            journey = newResult;
                            last = i;
                            j--;
                        }
                    }
                    result_t *newResult = (result_t *)malloc(sizeof(result_t));
                    newResult -> result = stations[0];
                    newResult -> previous = journey;
                    journey = newResult;
                }
            }


            //reversing and printing journey

            if(journeyExists == true){
                printf("%d", journey -> result);
                journey = journey -> previous;
                while(journey != NULL){
                    printf(" %d", journey -> result);
                    journey = journey -> previous;
                }
                printf("\n");
            }



        }
    }
}
