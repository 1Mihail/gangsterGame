#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Gangster
{
    char name[30];
    int hp[11],totalDmg;
    long int totalTime,answersTime[11];
} gangster;
void reset(struct Gangster *gangster)
{
    int i;
    (*gangster).totalDmg=0;
    for(i=1; i<=10; i++)
    {
        (*gangster).hp[i]=0;
        (*gangster).answersTime[i]=0;
    }
    (*gangster).totalTime=0;
}
void show(struct Gangster gangster)
{
    int i;
    for(i=1; i<=10; i++)
        if(gangster.hp[i])
            printf("Round %i : %i dmg\n",i, gangster.hp[i]);
    for(i=1; i<=10; i++)
        printf("Round %i: You answered in %i of %i seconds.\n",i,gangster.answersTime[i],16-i);
}
void highscore()
{
    struct hs_board
    {
        char name[31],dif[31];
        int score;
    } x[999],aux;
    int n=0,i,j;
    FILE *f;
    f=fopen("highscore.in","r");
    if(f)
    {
        printf("Name       Score       Dificulty\n");
        while(++n&&fscanf(f,"%s%i%s",x[n].name, &x[n].score, x[n].dif )!=EOF);
        for(i=1; i<n; i++)
            for(j=i+1; j<=n; j++)
                if(x[i].score<x[j].score)
                {
                    aux=x[i];
                    x[i]=x[j];
                    x[j]=aux;
                }
        for(i=1; i<n; i++)
            printf("%i.%s       %i       %s\n",i,x[i].name,x[i].score,x[i].dif);
        printf("\n\n");
    }
    else printf("There are no entries!\n\n");
}
void highscoreData(char name[31],int score, int dificulty)
{
    FILE *f;
    f=fopen("highscore.in","a");
    if(dificulty==10)
        fprintf(f,"%s %i EASY\n",name,score);
    else if(dificulty==100)
        fprintf(f,"%s %i HARD\n",name,score);
    else fprintf(f,"%s %i EXPERT\n",name,score);
    fclose(f);
}
void newGame(int dificulty)
{
    int answer,i,dmg,t1,t2,ok=0,score;
    reset(&gangster);
    if(dificulty==1)
    {
        dificulty=10;
        score=900;
    }
    else if(dificulty==2)
    {
        dificulty=100;
        score=950;
    }
    else if(dificulty==3)
    {
        dificulty=1000;
        score=1000;
    }
    for(i=1; i<=10; i++)
    {
        if(ok) break;
        printf("\nRound %i.\n",i);
        t1=rand()%dificulty;
        t2=rand()%dificulty;
        time_t start_t, end_t;
        double diff_t;
        time(&start_t);
        printf("%i + %i = ? ",t1,t2);
        printf("Answer: ");
        scanf("%i",&answer);
        time(&end_t);
        diff_t = difftime(end_t, start_t);
        gangster.answersTime[i]=(long int)diff_t;
        gangster.totalTime+=(long int)diff_t;
        if(answer!=t1+t2)
        {
            dmg=rand()%5+1;
            printf("Incorrect answer! You received %i dmg\n",dmg);
            gangster.hp[i]=dmg;
            gangster.totalDmg+=dmg;
        }
        if(diff_t>16-i)
        {
            printf("___________________\nOut of time! You are dead!\n___________________\n~Stats~\n");
            show(gangster);
            ok=1;
        }
        else if(gangster.totalDmg>5)
        {
            printf("___________________\nYour life is 0!\n___________________\n~Stats~\n");
            show(gangster);
            ok=1;
        }
        else if(ok==0&&i==10)
        {
            printf("___________________\nCongratulations %s !!! You are a great gangster. Final score: %i\n___________________\n~Stats~\n",gangster.name,score-(gangster.totalTime)*10);
            highscoreData(gangster.name,score-(gangster.totalTime)*10,dificulty);
            show(gangster);
        }
    }
}
void help()
{
    FILE *f;
    f=fopen("help.txt","w");
    fprintf(f,"The purpose of the game is to answer as fast as possible to all questions.\nIf your answer is wrong, the enemy gangster will shot you and you will lose hp. If you are too slow, you will be killed by a headshow.\nVisit MihailProductions.com");
    fclose(f);
    printf("The help.txt file was generated. \n\n");
}
void about()
{
    int **a,i,j;
    system("cls");
    a=(int **)malloc(3*sizeof(int *));
    for(i=0; i<3; i++)
        *(a+i)=(int *)malloc(59*sizeof(int));

    for(i=0; i<2; i++)
        for(j=0; j<=59; j++)
            if(i%2==0)
                a[i][j]=0;
            else a[i][j]=1;
    for(i=0; i<2; i++)
    {
        for(j=0; j<=58; j++)
            if(a[i][j])
                printf("*");
            else printf("#");
        printf("\n");
    }
    printf("\n\n        MihailProductions.com - All rights reserved 2015        \n\n\n\n");
    for(i=0; i<2; i++)
    {
        for(j=0; j<=58; j++)
            if(a[i][j])
                printf("#");
            else printf("*");
        printf("\n");
    }
    printf("\n");
}
void changeName(struct Gangster *gangster)
{
    printf("Gangster's name: ");
    scanf("%s",(*gangster).name);
    system("cls");
}
void dificultyMenu()
{
    int dificulty;
    system("cls");
    printf("Dificulty:\n1.Easy\n2.Hard\n3.Expert\n4.Back\nOption: ");
    scanf("%i",&dificulty);
    switch(dificulty)
    {
    case 1:
        newGame(1);
        break;
    case 2:
        newGame(2);
        break;
    case 3:
        newGame(3);
        break;
    case 4:
        globalMenu();
        break;
    default:
        printf("Please choose a valid option! (1/2/3/4)");
    }
}
void globalMenu()
{
    int option;
    system("cls");
    do
    {
        printf("Gangster %s wants:\n1.Fight!\n2.Info\n3.Help\n4.Score\n5.New identity\n6.Retire\nOption: ",gangster.name);
        scanf("%i",&option);
        switch ( option )
        {
        case 1:
            dificultyMenu();
            break;
        case 2:
            about();
            break;
        case 3:
            system("cls");
            help();
            break;
        case 4:
            system("cls");
            highscore();
            break;
        case 5:
            changeName(&gangster);
            break;
        case 6:
            exit(1);
            break;
        default:
            system("cls");
            printf("Invalid option!\n");
            break;
        }
    }
    while(option);
}
int main()
{
    changeName(&gangster);
    globalMenu();
    return 0;
}
