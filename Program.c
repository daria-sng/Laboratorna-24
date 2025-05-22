#include <stdio.h>
#include <stdlib.h>

struct motorcycle {
    char brand [20];
    int number;
    int max_speed;
    int price;
};

int main(){
    system ("chcp 65001");
    int N;
    printf("Введіть кількість мотоциклів для запису: ");
    scanf("%d", &N);
    
    struct motorcycle *array = (struct motorcycle*)malloc(N*sizeof(struct motorcycle));

    int i;
    for(i=0;i<N;i+=1){
        printf("Марка %d мотоциклу ( на англійській мові ): ", i+1);
        scanf("%s", array[i].brand);
        printf("Номер мотоциклу: ");
        scanf("%d", &array[i].number);
        printf("Максимальна швидкість: ");
        scanf("%d", &array[i].max_speed);
        printf("Вартість ($): ");
        scanf("%d", &array[i].price);
    }

    FILE *moto = fopen ("Motorcycle.txt", "wb+");
    if(moto == NULL){
        printf("Не відбулося відкривання файлу Motorcycle.txt, спробуйте ще раз!");
        exit(1);
    }

    for(i=0;i<N;i+=1){
        fwrite(&array[i], sizeof(struct motorcycle), 1, moto);
    }
    rewind(moto);

    for(i=0;i<N;i+=1){ 
    if (fread(&array[i], sizeof(struct motorcycle), 1, moto) == 1){
        printf("Марка: %s, Номер: %d, Максимальна швидкість: %d, Початкова вартість ($): %d\n", array[i].brand, array[i].number, array[i].max_speed, array[i].price);
    }
    else {
        printf("Помилка при читанні даних!");
    }
    printf("Введіть нову вартість: ");
    scanf("%d", &array[i].price);
    fseek(moto, -(long)sizeof(struct motorcycle), 1);
    fwrite(&array[i], sizeof(struct motorcycle), 1, moto);
    fseek(moto, -(long)sizeof(struct motorcycle), 1);
    if (fread(&array[i], sizeof(struct motorcycle), 1, moto) == 1){
        printf("Марка: %s, Номер: %d, Максимальна швидкість: %d, Нова вартість ($): %d\n", array[i].brand, array[i].number, array[i].max_speed, array[i].price);
    }
    else{
        printf("Помилка при читанні даних!");
    };
    }

    fclose(moto);
    return 0;
}