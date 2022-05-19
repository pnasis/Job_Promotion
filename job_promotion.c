#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    char name[21];
    int year;
    int part;
    float prod[12];
    float mean;
}candidateT;

void ReadData(candidateT can[]);
float prospect(candidateT can);
void printf_results(float results[], candidateT can[]);

int main()
{
    candidateT can[3];
    int i;
    float results[3];


    //Reading Data
    ReadData(can);

    //Printing Candidates Name, Age and Mean Efficiency
    for(i=0; i<3; i++)
    {
        printf("\nCandidate: %s\n", can[i].name);
        printf("Age: %d\n", 2021-can[i].year);
        printf("Mean efficiency for past 12 months: %.2f\n", can[i].mean);
    }

    //Printing Candidate's Name and final candidacy
    for(i=0; i<3; i++)
    {
        results[i] = prospect(can[i]);
        printf("\nCandidate: %s\t\tCandidacy prospect: %.2f\n", can[i].name, results[i]);
    }

    //Printing Results
    printf_results(results, can);


return 0;
}


void ReadData(candidateT can[])
{
    //This function asks from the user to input the information about candidates
    int i, j;
    for(i=0; i<3; i++)
    {
        printf("Candidate #%d, please enter your name: ", i+1);
        scanf("%s", can[i].name); getchar();
        printf("please enter your year of birth: ");
        scanf("%d", &can[i].year);
        printf("how many years in company: ");
        scanf("%d", &can[i].part);
        can[i].mean=0;
        for(j=0; j<12; j++)
        {
            printf("enter productivity #%d: ", j+1);
            scanf("%f", &can[i].prod[j]);
            can[i].mean += can[i].prod[j];
            //Checking if the efficiency is between the range.
            if(can[i].prod[j]<0.0 || can[i].prod[j]>1.0)
            {
                printf("invalid productivity value - exit program\n");
                exit(-1);
            }
        }
        can[i].mean=can[i].mean/12;
        printf("\n");
    }
}

float prospect(candidateT can)
{
    int j, count=0;
    float value=0, prodF=0, yearsB=0;

    yearsB = can.part * 0.6;
    for(j=0; j<12; j++)
    {
        if(can.prod[j] > 0.68)
            prodF = prodF + 0.4;
        if(can.prod[j] < 0.2)
            count++;
    }
    if(can.part < 2 || count > 4)
        value=0.0;
    else
        value = yearsB + prodF;

    return value;
}

void printf_results(float results[], candidateT can[])
{
    int i, count1=1, count2=0; //count1: amount of candidates that have the same efficiency.
    float max;                 //count2: amount of candidates that have less than 6.67 final efficiency.

    max=results[0];
    for(i=1; i<3; i++)
    {
        if(results[i] > max){
            max = results[i];
            count1=1;
        }
        if(results[i]==max)
                count1++;
    }
    for(i=0; i<3; i++)
    {
        if(results[i] > 6.67)
        {

            if(count1!=3)
            {
                if(results[i]==max)
                    printf("\nCongratulations %s for your new promotion!\n", can[i].name);
            }
        }
        else count2++;
    }
    if (count2==3)
        printf("\nUnfortunately none of the candidates is eligible for promotion.\n");
    if(count1==3)
                printf("\nUnfortunately none of the candidates is eligible for promotion.\n");
}
