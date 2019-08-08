#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int a,b,c,d,e,f;
int find_x;
int powi(int low,int up)
{
    return (int)pow((float)low,(float)up);
}

int funcc(int nx)
{
    return a*powi(nx,5)+b*powi(nx,4)+c*powi(nx,3)+d*powi(nx,2)+e*powi(nx,1)+f;
}

float diffc(float nx)
{
    return a*pow(nx,5)+b*pow(nx,4)+c*pow(nx,3)+d*pow(nx,2)+e*pow(nx,1)+f;
}

float difff(float ox,int ntod)
{
    float nx=ox+(float)ntod;
    return diffc(nx)+f-(float)funcc(ntod);
}

float intera(float nx)
{
return a*pow(nx,6)/6+b*pow(nx,5)/5+c*pow(nx,4)/4+d*pow(nx,3)/3+e*pow(nx,2)/2+f;
}

void Differential_1(int ntod)
{
    for(float dx=0.1;dx>=0.01;dx-=0.01){
        printf("x���ܤƶq:%f    ���G��:%f\n",dx,difff(dx,ntod)/dx);
    }
}

void Differential_2(int nx)
{
    printf("%f\n",(float)(5*a*powi(nx,4)+4*b*powi(nx,3)+3*c*powi(nx,2)+2*d*powi(nx,1)+e));
}

void Intergral_1(int x_range_min,int x_range_max)
{
    for(float dx=0.1; dx>=0.01; dx-=0.01){
        float doa=0;
        for(float cx=x_range_min;cx<=x_range_max;cx+=dx){
            doa+=diffc(cx)*dx;

        }
        printf("x���ܤƶq:%f    ���G��:%f\n",dx,doa);
    }
}

void Intergral_2(int x_range_min,int x_range_max)
{
    printf("%f\n",intera(x_range_max)-intera(x_range_min));
}




int main()
{
    int x_range_min,x_range_max;
    printf("�п�J6�ӫY��:");
    scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
    printf("�п�Jx�b�d��:");
    scanf("%d %d",&x_range_min,&x_range_max);
    printf("�п�J���D���I��x��");
    scanf(" %d",&find_x);


    printf("\n");
    for(int x=-50; x<=50; x++)
    {

        for(int y=-40; y<=39; y++)
        {
            int func=funcc(x);
            if(func==y)
            {
                if(x==find_x)
                {
                    printf("P(%d,%d)",find_x,func);
                }
                else
                {
                    printf("*");
                }
            }

            else if((x%5)==0&&y==0)
            {
                printf("%d",x);
            }
            else if(y==0){
                printf("|");
            }
            else if (x==0){
                    if(y%5==0){
                        printf("+");
                    }
                    else{
                    printf("-");
                    }
            }
            else
            {
                printf(" ");
            }
        }


        printf("\n");
    }
    printf("�ϥέ˼ƷL���p�⪺���G\n");
    Differential_1(find_x);
    printf("�ϥηL���p�⪺���G��:");
    Differential_2(find_x);
    printf("�ϥξ��ҩM�p�⪺���G\n");
    Intergral_1(x_range_min,x_range_max);
    printf("�ϥοn���p�⪺���G��:");
    Intergral_2(x_range_min,x_range_max);

    return 0;
}
