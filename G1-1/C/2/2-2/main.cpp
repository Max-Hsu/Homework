#include <iostream>
#include <stdio.h>


int main()
{
    float input_1,input_2,input_3;
    scanf("%f %f %f",&input_1,&input_2,&input_3);
    printf("��: %f\n�e: %f\n��: %f\n",input_1,input_2,input_3);
    printf("�P��: %f\n",(input_1+input_2+input_3)*4);
    printf("���n: %f\n",((input_1*input_2)+(input_3*input_1)+(input_2*input_3))*2);
    printf("��n: %f\n",input_1*input_2*input_3);

    return 0;
}
