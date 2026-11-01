#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
double fa(double x) {

	double y;
	if (x <= 3) y = (x * x) - (3 * x) + 9;
	else y = 1 / ((x * x * x) + 3);
	return y;
}
double fb(double x) {
	double y;
	y = x * exp(sin(x * x));
	return y;
}

double sin_n(double x, int N) {
    double sum = 0.0;      
    double current_term; 
    for (int k = 1; k <= N; k++) {
        int power = 2 * k - 1;
        double fact = 1.0;
        for (int i = 1; i <= power; i++) {
            fact *= i;
        }
        int sign = (k % 2 == 1) ? 1 : -1;
        current_term = sign * (pow(x, power) / fact);
        sum += current_term;
    }

    return sum;
}

double sin_eps(double x, double eps) {
    double sum = 0.0;
    double current_term = x; 
    int k = 1;
    while (fabs(current_term) >= eps) {
        sum += current_term; 
        k++;
        current_term = -current_term * (x * x) / ((2.0 * k - 2.0) * (2.0 * k - 1.0));
    }

    return sum;
}
void main()
{
    double x, eps;
    int N;
	int choice;
	puts("Введите х");
	scanf("%lf", &x);
    printf("Введите количество членов ряда N: ");
    scanf("%d", &N);
    printf("Введите точность eps (например 0.0001): ");
    scanf("%lf", &eps);

	printf("Выберите действие:\n1 - fa(x), fb(x), 2 - произведение, 3 - разность квадратов, 4 - удвоенная сумма\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1: printf("fa(x)=%lf , fb(x)=%lf\n", fa(x), fb(x));break;
	case 2: printf("fa(x)*fb(x)=%lf\n", fa(x) * fb(x));break;
	case 3: printf("fa(x)^2-fb(x)^2=%lf\n", (fa(x) * fa(x)) - (fb(x) * fb(x))); break;
	case 4: printf("2*(fa(x)+fb(x))=%lf\n", 2 * (fa(x) + fb(x))); break;
	}
    double std_sin = sin(x);
    double my_sin_n = sin_n(x, N);
    double my_sin_eps = sin_eps(x, eps);
    printf("\nРезультаты:\n");
    printf("1) Стандартная sin(x) : %.10lf\n", std_sin);
    printf("2) Ряд (N членов)     : %.10lf | Отклонение: %e\n", my_sin_n, fabs(std_sin - my_sin_n));
    printf("3) Ряд (точность eps) : %.10lf | Отклонение: %e\n", my_sin_eps, fabs(std_sin - my_sin_eps));
}
