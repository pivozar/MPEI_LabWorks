#include <stdio.h>

const int NMAX = 100;

int ReadArray(int *arr_size, double arr[], char *filename);
int ReadNum(double *num, char *filename);
void PrintArray(double arr[], int& sz, const char *filename);

int MoreThanGiven(double& mark, double arr[], int& sz);

int main(int argc, char *argv[]) {
    
    double a[NMAX], b[NMAX], c[NMAX];
    int a_size, b_size, c_size;
    int res_a, res_b, res_c, min_res;
    double set_num;

    if (argc < 5) {
        printf("More arguments required!\n");
        return 1;
    }

    if (!ReadNum(&set_num, argv[1])) {
        return 1;
    }

    if (!ReadArray(&a_size, a, argv[2])) {
        return 1;
    }
    if (!ReadArray(&b_size, b, argv[3])) {
        return 1;
    }
    if (!ReadArray(&c_size, c, argv[4])) {
        return 1;
    }

    printf("Input data:\nSet_num: %6.2lf\n", set_num);
    PrintArray(a, a_size, argv[2]);
    PrintArray(b, b_size, argv[3]);
    PrintArray(c, c_size, argv[4]);

    res_a = MoreThanGiven(set_num, a, a_size);
    res_b = MoreThanGiven(set_num, b, b_size);
    res_c = MoreThanGiven(set_num, c, c_size);

    min_res = res_a;

    if (res_b < min_res)
        min_res = res_b;
    else if (res_c < min_res)
        min_res = res_c;

    if (min_res == res_a)
        printf("Array A has minimal count of elements(%d), more than %lf\n", min_res, set_num);

    if (min_res == res_b)
        printf("Array B has minimal count of elements(%d), more than %lf\n", min_res, set_num);

    if (min_res == res_c)
        printf("Array C has minimal count of elements(%d), more than %lf\n", min_res, set_num);

    return 0;
}

int MoreThanGiven(double& mark, double arr[], int& sz) {
    int result = 0;

    for (int i = 0; i< sz; ++i) {
        if (arr[i] > mark) {
            result++;
        }
    }
    return result;
}


int ReadNum(double *num, char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }

    if (fscanf(file, "%lf", num) < 1) {
        printf("Error while reading file '%s'", filename);
        return 0;
    }
    return 1;
}

int ReadArray(int *arr_size, double arr[], char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }

    if (fscanf(file, "%d", arr_size) < 1) {
        printf("Error while reading file '%s'", filename);
        return 0;
    }

    if (*arr_size < 0 || *arr_size > NMAX) {
        printf("Array size must be from 1 to %d! (file: '%s')\n", NMAX, filename);
        return 0;
    }

    for (int i = 0; i < *arr_size; ++i) {
        if (fscanf(file,  "%lf", &arr[i]) < 1) {
            printf("Error while reading file '%s'", filename);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void PrintArray(double arr[], int& sz, const char *filename) {
    printf("%s : ", filename);
    for (int i=0; i < sz; ++i) {
        printf("%6.2lf ", arr[i]);
    }
    printf("\n");
}

