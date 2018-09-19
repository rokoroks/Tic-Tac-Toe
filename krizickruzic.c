#include<stdio.h>
#include<string.h>
#include<windows.h>
/* made by rokoroks */
void ispis(char a[])
{
    char novi[9];
    int i;
    for (i=0;i<=8;i++)
        if (a[i]!='1') novi[i]=a[i];
          else novi[i]=' ';
    system("cls");
    printf("\n");
    printf(" %c * %c * %c\n",novi[0],novi[1],novi[2]);
    printf("   *   *\n");
    printf(" *********\n");
    printf("   *   *\n");
    printf(" %c * %c * %c\n",novi[3],novi[4],novi[5]);
    printf("   *   *\n");
    printf(" *********\n");
    printf("   *   *\n");
    printf(" %c * %c * %c",novi[6],novi[7],novi[8]);
}

char jelpobjeda(char a[])
{
    if (a[0]==a[1] && a[1]==a[2] && a[0]!='1') return a[1];
    if (a[3]==a[4] && a[4]==a[5] && a[3]!='1') return a[4];
    if (a[6]==a[7] && a[7]==a[8] && a[6]!='1') return a[7];
    if (a[0]==a[3] && a[3]==a[6] && a[0]!='1') return a[0];
    if (a[1]==a[4] && a[4]==a[7] && a[1]!='1') return a[1];
    if (a[2]==a[5] && a[5]==a[8] && a[2]!='1') return a[2];
    if (a[0]==a[4] && a[4]==a[8] && a[0]!='1') return a[4];
    if (a[2]==a[4] && a[4]==a[6] && a[2]!='1') return a[4];
    return '1';
}

int jelgotovo(char a[])
{
    if (a[0]!='1' && a[1]!='1' && a[2]!='1' && a[3]!='1' && a[4]!='1' && a[5]!='1' && a[6]!='1' && a[7]!='1' && a[8]!='1') return 1;
    else return 0;
}

int provjeri (FILE *dat, char string[20])
{
int b,c,d;
char a[20];
  rewind(dat);
  while(fscanf(dat,"%s %d %d %d\n",a,&b,&c,&d)==4)
    {
    if(strcmp(a,string)==0) return 0;
    }
return 1;
}  /* 0 ako ih nade 1 ako ne */

void dajpobjedu(char strin[20], FILE *dat)
{
int w,d,l;
char check[20];
rewind(dat);
while(1)
  {
    fscanf(dat,"%s %d %d %d", check, &w, &d, &l);
    if (strcmp(check,strin)==0) break;
    fscanf(dat,"\n");
  }
w++;
fseek(dat, -14L, SEEK_CUR);
fprintf(dat,"%4d", w);
}

void dajnerjeseno(char strin[20], FILE *dat)
{
int w,d,l;
char check[20];
rewind(dat);
while(1)
  {
    fscanf(dat,"%s %d %d %d", check, &w, &d, &l);
    if (strcmp(check,strin)==0) break;
    fscanf(dat,"\n");
  }
d++;
fseek(dat, -9L, SEEK_CUR);
fprintf(dat,"%4d", d);
}

void dajporaz(char strin[20], FILE *dat)
{
int w,d,l;
char check[20];
rewind(dat);
while(1)
  {
    fscanf(dat,"%s %d %d %d", check, &w, &d, &l);
    if (strcmp(check,strin)==0) break;
    fscanf(dat,"\n");
  }
l++;
fseek(dat, -4L, SEEK_CUR);
fprintf(dat,"%4d", l);
}

void dajrezultat(FILE *dat, char strin[20])
{
char check[20];
int w,d,l;
while(1)
  {
    fscanf(dat,"%s %d %d %d", check, &w, &d, &l);
    if (strcmp(check,strin)==0) break;
    fscanf(dat,"\n");
  }
printf("%s: W: %d   D: %d   L: %d", strin, w, d, l);
}

void statistika(FILE *dat)
{
char strin[20];
int w,d,l,wpf;
double wp;
while (fscanf(dat,"%s %d %d %d", strin, &w, &d, &l)==4)
  {
    wp=(double)w/(w+d+l);
    if((w+d+l)==0) wp=0;
    wp=wp*100;
    wpf=wp;
    printf("Name:  %20s   W:  %4d   D:  %4d   L:  %4d   W%%:  %3d%%\n", strin, w, d, l, wpf);
  }
}


int main()
{

char a[9],c,prvis[20],drugis[20];
int i,t,upit1,upit2,pobjednik;
FILE *dat;

dat=fopen("povijest.txt","rt+wt");

printf("For stats press 1, to play press 2\n");
scanf("%c",&c);

if(c=='1'){
    printf("\n\n");
    statistika(dat);
    return 0;
}

printf("PLAYER 1...To login press 1, to register press 2, to play without name press 3\n");
scanf("%d",&upit1);

if(upit1==1)
{
while(1)
   {
   printf("Enter name:  ");
   scanf("%s",prvis);
   scanf("%c",&c);
   if (provjeri(dat,prvis)==0) break;
   if (provjeri(dat,prvis)==1) printf("\nERROR, name doesn't exist\n\n");
   }
}
if (upit1==2)
{
while(1)
{
   printf("Enter name:  ");
   scanf("%s",prvis);
   scanf("%c",&c);
   if (provjeri(dat,prvis)==0) printf("\nERROR, name already taken\n\n");
   if (provjeri(dat,prvis)==1) break;
}
fprintf(dat,"%s    0    0    0\n",prvis);
}

printf("\nPLAYER 2...To login press 1, to register press 2, to play without name press 3\n");
scanf("%d",&upit2);

if (upit2==1)
{
while(1)
   {
   printf("Enter name:  ");
   scanf("%s",drugis);
   scanf("%c",&c);
   if (provjeri(dat,drugis)==0 && strcmp(prvis,drugis)!=0) break;
   if (strcmp(prvis,drugis)==0) {printf("ERROR, name already taken\n\n"); continue;}
   if (provjeri(dat,drugis)==1) printf("\nERROR, name doens't exist\n\n");
   }
}
if (upit2==2)
{
while(1)
{
   printf("Enter name:  ");
   scanf("%s",drugis);
   scanf("%c",&c);
   if (provjeri(dat,drugis)==0) printf("\nERROR, name already taken\n\n");
   if (provjeri(dat,drugis)==1) break;
}
fprintf(dat,"%s    0    0    0\n",drugis);
}


for(i=0;i<=8;i++) a[i]='1';
for(i=1;1;i++)
{
            ispis(a);
            if(jelpobjeda(a)=='X')   {
                                                   if (upit1!=3) printf("\n\n%s WINS\n\n",prvis);
                                                   else printf("\n\nPLAYER 1 WINS\n\n");
                                                   pobjednik=1;
                                                   break;
            }
            if(jelpobjeda(a)=='0')   {
                                                   if (upit2!=3) printf("\n\n%s WINS\n\n",drugis);
                                                   else printf("\n\nPLAYER 2 WINS\n\n");
                                                   pobjednik=2;
                                                   break;
            }
            if(jelgotovo(a)==1)   {
                                                printf("\n\nDRAW\n\n");
                                                pobjednik=0;
                                                break;
            }


   if((upit1==3 && i%2==1) || (upit2==3 && i%2==0)) printf("\n\n  PLAY PLAYER %d: ",i%2 ? 1:2);
   else printf("\n\n  PLAY %s: ",i%2 ? prvis:drugis);

   scanf("%d",&t);
   scanf("%c",&c);

   if(t<1 || t>9){
          printf("\nERROR TRY AGAIN, press enter to continue\n");
          scanf("%c",&c);
          i--;
          continue;
    }
    if(a[t-1]!='1'){
         printf("\nERROR TRY AGAIN, press enter to continue\n");
         scanf("%c",&c);
         i--;
         continue;
    }

if(i%2==0) a[t-1]='0';
else a[t-1]='X';

}   /* kraj igre */


if (pobjednik==1)
    {
        if(upit1==1 || upit1==2) dajpobjedu(prvis,dat);
        if(upit2==1 || upit2==2) dajporaz(drugis,dat);
    }
if (pobjednik==2)
    {
        if(upit1==1 || upit1==2) dajporaz(prvis,dat);
        if(upit2==1 || upit2==2) dajpobjedu(drugis,dat);
    }
if (pobjednik==0)
    {
        if(upit1==1 || upit1==2) dajnerjeseno(prvis,dat);
        if(upit2==1 || upit2==2) dajnerjeseno(drugis,dat);
    }

rewind(dat);
if (upit1!=3) {
        dajrezultat(dat,prvis);
        printf("\n\n");
}
rewind(dat);
if (upit2!=3) {
        dajrezultat(dat,drugis);
        printf("\n\n");
}


fclose(dat);

    return 0;
}
