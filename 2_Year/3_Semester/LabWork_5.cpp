#include <stdio.h>
#include <cmath>

/*
 * Определить в каком массиве меньше количество элементов, больших заданного числа.
 * Если в двух или трёх массивах количества искомых элементов совпадают,
 * вывести соответствующее сообщение.
 * 
 * Переделать задачу с тремя массивами так, чтобы вспомогательная функция (не main)
 * работала не с элементом массива Xi, а с выражением f(Xi), где f – некоторая функция,
 * указатель на которую передаётся через параметры. В качестве фактического параметра
 * передавать указатель на стандартную библиотечную функцию и указатель на пользовательскую функцию.
 * Ввод/вывод производить из файла/в файл.
*/

typedef double (*pFunc)(double);

const int NMAX = 100;

int FileInput(double *set_num, int *a_size, int *b_size, int *c_size,
		double a[], double b[], double c[], char *filename);

int ReadArray(int *arr_size, double arr[], FILE *file);
int PrintArray(double arr[], int sz, const char *filename);

int MoreThanGiven(double mark, double arr[], int sz, pFunc pf);

int main(int argc, char *argv[]) {
    
    double a[NMAX], b[NMAX], c[NMAX];
    int a_size, b_size, c_size;
    int res_a, res_b, res_c, min_res;
    double set_num;
    pFunc pf = &fabs;

    if (argc < 3) {
        printf("More arguments required!\n");
        return 1;
    }

    if (!FileInput(&set_num, &a_size, &b_size, &c_size, a, b, c, argv[1])) {
        return 1;
    }
    if (!PrintArray(a, a_size, argv[2]))
    	return 0;
    if (!PrintArray(b, b_size, argv[2]))
    	return 0;
    if (!PrintArray(c, c_size, argv[2]))
    	return 0;

    res_a = MoreThanGiven(set_num, a, a_size, pf);
    res_b = MoreThanGiven(set_num, b, b_size, pf);
    res_c = MoreThanGiven(set_num, c, c_size, pf);

    min_res = res_a;

    if (res_b < min_res)
        min_res = res_b;
    else if (res_c < min_res)
        min_res = res_c;

    FILE *file;

    if ((file = fopen(argv[2], "a")) == NULL) {
        printf("Impossible to open file '%s'\n", argv[2]);
        return 0;
    }

    if (min_res == res_a)
        fprintf(file, "Array A has minimal count of elements(%d), more than %lf\n", min_res, set_num);

    if (min_res == res_b)
        fprintf(file, "Array B has minimal count of elements(%d), more than %lf\n", min_res, set_num);

    if (min_res == res_c)
        fprintf(file, "Array C has minimal count of elements(%d), more than %lf\n", min_res, set_num);
    
    fclose(file);
    return 1;
}

int FileInput(double *set_num, int *a_size, int *b_size, int *c_size,
		double a[], double b[], double c[], char *filename) {
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }

    if (fscanf(file, "%lf", set_num) < 1) {
	printf("Impossible to read from file: '%s'\n", filename);
	return 0;
    }
    
    if (!ReadArray(a_size, a, file))
	return 0;
    if (!ReadArray(b_size, b, file))
	return 0;
    if (!ReadArray(c_size, c, file))
	return 0;
    
    fclose(file);
    return 1;
}



int MoreThanGiven(double mark, double arr[], int sz, pFunc pf) {
    int result = 0;

    for (int i = 0; i< sz; ++i) {
        if (pf(arr[i]) > mark) {
            result++;
        }
    }
    return result;
}

int ReadArray(int *arr_size, double arr[], FILE *file) {

    if (fscanf(file, "%d", arr_size) < 1) {
        printf("Error while reading file");
        return 0;
    }

    if (*arr_size < 0 || *arr_size > NMAX) {
        printf("Array size must be from 1 to %d!\n", NMAX);
        return 0;
    }

    for (int i = 0; i < *arr_size; ++i) {
        if (fscanf(file,  "%lf", &arr[i]) < 1) {
            printf("Error while reading file");
            return 0;
        }
    }
    return 1;
}

int PrintArray(double arr[], int sz, const char *filename) {
    FILE *file;

    if ((file = fopen(filename, "a")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }

    for (int i=0; i < sz; ++i) {
        fprintf(file, "%6.2lf ", arr[i]);
    }
    fprintf(file, "\n");
    fclose(file);

    return 1;
}

