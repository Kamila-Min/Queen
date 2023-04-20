#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <string.h>
#include <malloc.h>

int IsStrike(int x1, int y1, int x2, int y2, int n);

int Strike(int* X, int p, int n);

int main()
{
	int n = 0;
	printf("Enter the number of queens \n");
	scanf("%d", &n);

	int* X = (int*)calloc(n, sizeof(X));

	int p = 1;
	X[p] = 0;
	X[0] = 0;
    int k = 0;

    // цикл формирования размещения
    while (p > 0) // если p==0, то выход из цикла
    {
        X[p] = X[p] + 1;
        if (p == n) // последний элемент
        {
            if (X[p] > n)
            {
                while (X[p] > n) 
                    p--; // перемотать обратно
            }
            else
            {
                if (Strike(X, p, n) == 0) // зафиксировать размещение
                {
                    k++;
                    p--;
                }
            }
        }
        else // не последний элемент
        {
            if (X[p] > n)
            {
                while (X[p] > n) 
                    p--; // перемотать назад
            }
            else
            {
                if (Strike(X, p, n) == 0) // Если M[p] не накладывается за предыдущими M[1],M[2], ..., M[p-1]
                {
                    p++; // перейти на размещение следующего ферзя
                    X[p] = 0;
                }
            }
        }
    }

    // вывести количество вариантов размещения
    printf("The number of queen's swappings is %d \n", k);

    free (X);

    return 0;
}

// Проверка, накладывается ли последний элемент M[p]
// с элементами M[1], M[2], ..., M[p-1].
// Данная функция использует функцию IsStrike()
int Strike(int* X, int p, int n)
{
    int px, py, x, y;
    int i;

    px = X[p];
    py = p;

    for (i = 1; i <= p - 1; i++)
    {
        x = X[i];
        y = i;
        if (IsStrike(x, y, px, py, n) == 1)
            return 1;
    }
    return 0;
}

// Проверка, бъются ли 2 ферзя
int IsStrike(int x1, int y1, int x2, int y2, int n)
{
    // 1. Горизонталь, вертикаль
    // Ферзи бъют друг друга, если какие то 2 значения-параметра совпадают
    if ((x1 == x2) || (y1 == y2)) 
        return 1;

    // 2. Главная диагональ
    int tx, ty; // дополнительные переменные

    // 2.1. Влево-вверх
    tx = x1 - 1; 
    ty = y1 - 1;

    while ((tx >= 1) && (ty >= 1))
    {
        if ((tx == x2) && (ty == y2)) 
            return 1;
        tx--; 
        ty--;
    }

    // 2.2. Вправо-вниз
    tx = x1 + 1; 
    ty = y1 + 1;

    while ((tx <= n) && (ty <= n))
    {
        if ((tx == x2) && (ty == y2)) 
            return 1;
        tx++; 
        ty++;
    }

    // 3. Дополнительная диагональ
    // 3.1. Вправо-вверх
    tx = x1 + 1; 
    ty = y1 - 1;

    while ((tx <= n) && (ty >= 1))
    {
        if ((tx == x2) && (ty == y2)) 
            return 1;
        tx++; 
        ty--;
    }

    // 3.2. Влево-вниз
    tx = x1 - 1; 
    ty = y1 + 1;

    while ((tx >= 1) && (ty <= n))
    {
        if ((tx == x2) && (ty == y2)) 
            return 1;
        tx--; 
        ty++;
    }

    return 0;
}
