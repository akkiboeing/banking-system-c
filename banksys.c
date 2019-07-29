#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
int acc=31230000, gfc=50000, usrcnt=0, ptbal=0, pts=0;
int postlogin(int usrno);
int redeem(float amt,int userno,int ptcnt);

struct bank{
   int accno, points, giftcardno[10], pin[10]; 
   int giftcardcnt;
   char pass[16];
   float accbal, giftcardbal[3];
};

struct bank user[1000];

int main()
{
   int itr=0,choice;
   printf("---------BANKING SYSTEM----------");
   while(1){
   printf("\n1.Login\n2.Register\n3.Exit\nEnter your choice: ");
   scanf("%d",&choice);
   if(choice==2)
   {
   char temppass[16];
   printf("-------REGISTER---------\n");
   printf("Generating account number....\nAccount number generated successfully\nAccount number: %d\n",acc);
   user[usrcnt].accno=acc;
   printf("Enter password: ");
   scanf("%s",&user[usrcnt].pass);
   itr=0;
   strcpy(temppass,user[usrcnt].pass);
   for(itr; itr<strlen(user[usrcnt].pass); itr++)
       user[usrcnt].pass[itr]=(user[usrcnt].pass[itr])+1;
   printf("Enter initial deposit amount: ");
   scanf("%f",&user[usrcnt].accbal);    
   printf("\nREGISTERED SUCCESSFULLY AND DEPOSITED %.2f AMOUNT. REMEMBER THE FOLLOWING CREDENTIALS FOR LOGIN\nACC.NO: %d \nPASSWORD: %s\n",user[usrcnt].accbal,user[usrcnt].accno,temppass);
   usrcnt++;
   acc++;
   }
   else if(choice==1)
   {
     int traverse=0,tempacc,exitflag;
     char temppass[16];
     printf("\n------LOGIN-------\n");
     printf("Enter Account Number: ");
     scanf("%d",&tempacc);
     while(tempacc!=(user[traverse].accno)&&(traverse<usrcnt))
          traverse++;    
incp: if(tempacc==user[traverse].accno)
     {
        printf("Enter password: ");
        scanf("%s",&temppass);
        for(itr=0;itr<strlen(temppass);itr++)
            temppass[itr]=(temppass[itr])+1;
        if(!strcmp(temppass,user[traverse].pass))
           {
             printf("\nLogin Successful\n");
             exitflag = postlogin(traverse);
           }
        else
           {
           printf("\nIncorrect Password. Try again\n");
           goto incp; 
           break;
           }      
     }  
     else
    {
     printf("\nAccount not found\n");   
     break;
     }
    }
    else
      return 0;
   } 
}   
     
int postlogin(int usrno)
{
   int b, i=0,pindig, pchoice, tempgfc, temppin, cntr=0;
   float tempamt, tempaddamt, temptot;
   user[usrno].giftcardcnt=0;
login: printf("\n-----Welcome-----\n1.Create Giftcard\n2.TopUp\n3.Transaction history\n4.Block Giftcard \n5.Deposit Amount\n6.Logout\nEnter your choice: ");
   scanf("%d",&pchoice);
   switch(pchoice)
   {
      case 1: printf("\n-----CREATE GIFTCARD-----\n");
              b=user[usrno].giftcardcnt;
              printf("\nGenerating giftcard number......\nGeneration successful..\nGiftcard No: %d", gfc);
              user[usrno].giftcardno[b]=gfc;
              gfc++;
              user[usrno].giftcardcnt+=1;
        pinl: printf("\nEnter pin(4 digits): ");
              scanf("%d",&user[usrno].pin[b]);
              pindig = floor(log10(abs(user[usrno].pin[b]))) + 1;
              if((pindig)!=4)
              {
                 printf("\n4 digit pin not given. Enter a 4 digit pin.\n");
                 user[usrno].pin[b]=0;
                 goto pinl;
              }
              user[usrno].giftcardbal[b]=0;
              printf("\nGiftcard created successfully\n");
              goto login;
              break;
      case 2: printf("\n-----TOPUP-----\nEnter giftcard number to topup: ");
              cntr=0;
              scanf("%d",&tempgfc);
              while(((tempgfc!=user[usrno].giftcardno[cntr])&&(cntr<user[usrno].giftcardcnt)))
                    cntr++;  
              if(user[usrno].giftcardno[cntr]!=tempgfc)
              {
                 printf("\nCan't find giftcard. Try again\n");
                 goto login;
              }                                                  
        pint: printf("Enter the pin: ");
              scanf("%d",&temppin);
              if(temppin==user[usrno].pin[cntr])
              {      
              printf("Enter amount to topup:");
              scanf("%f",&tempamt);
              user[usrno].giftcardbal[cntr]+=tempamt;
              user[usrno].accbal-=tempamt;
              temptot+=tempamt;
              printf("Topped Up successfully\nGiftcard balance: %.2f", user[usrno].giftcardbal[cntr]);              
              }
              else
              {
                  printf("\nWrong pin. Try again");
                  goto pint;
              }
              redeem(tempamt, usrno, cntr);
              goto login;
              break;
      case 3: printf("\n------TRANSACTION HISTORY------\n");
              printf("Account Number: %d\t\tAccount Balance: %.2f",user[usrno].accno,user[usrno].accbal);
              for(i=0;i<user[usrno].giftcardcnt;i++)
                     printf("\nGift card Number: %d \t\t Giftcard balance: %.2f \t\t\n",user[usrno].giftcardno[i],user[usrno].giftcardbal[i]);
              printf("%.2f Deducted from account for topup\n",temptot);
              goto login;
              break;
      case 4: printf("\n------BLOCK GIFTCARD------\nEnter Giftcard number: ");
              i=0;
              cntr=0;
              scanf("%d",&tempgfc);
              while(((tempgfc!=user[usrno].giftcardno[cntr])&&(cntr<user[usrno].giftcardcnt)))
                    cntr++;  
              if(user[usrno].giftcardno[cntr]!=tempgfc)
              {
                 printf("\nCan't find giftcard. Try again\n");
                 goto login;
              }               
              printf("\nEnter the pin: ");
              scanf("%d",&temppin);
              if(temppin==user[usrno].pin[cntr])
              {  
                 user[usrno].accbal+=user[usrno].giftcardbal[cntr];
                 printf("Added %.2f money back to account from gifcard.\nBlocking card...\n",user[usrno].giftcardbal[cntr]);
                 user[usrno].giftcardbal[cntr]=0;
                 int tempno = user[usrno].giftcardno[0];
                 int temppi = user[usrno].pin[0];
	             for(i=cntr;i<((user[usrno].giftcardcnt-1));i++)
	               {
		                user[usrno].giftcardno[i] = user[usrno].giftcardno[i+1];
		                user[usrno].pin[i] = user[usrno].pin[i+1];
	               }
	             user[usrno].giftcardno[i]=0; 
	             user[usrno].pin[i]=0; 
                 (user[usrno].giftcardcnt)--;
                 printf("%d Blocked the giftcard. Remaining giftcards: ",user[usrno].giftcardcnt);
                 for(i=0; i<(user[usrno].giftcardcnt);i++)
                    printf("%d\n",user[usrno].giftcardno[i]);                 
              }
              goto login;
              break;
      case 5: printf("\n----------DEPOSIT AMOUNT----------\nEnter the amount to be deposited: ");
              scanf("%f",&tempaddamt);
              user[usrno].accbal+=tempaddamt;
              printf("Deposited Successfully\nAccount balance is: %.2f\n", user[usrno].accbal);       
              goto login;
              break; 
      case 6: printf("\nLogging out...\n");
              return 1;
              break;        
      default: printf("\nEnter a valid option\n");  
               goto login;      
   }
   return 0;
}       

int redeem(float amt,int usrno,int ptcnt)
{ 
   pts=0;
   pts = (int) amt/100;
   if((pts%10)==0)
   {
      user[usrno].accbal+=pts;      
   }
   else
   {
      ptbal-=pts;
   }
   printf(" Account Balance is %.2f\nRedeemed points and rewarded money for Gift card number:%d \n", user[usrno].accbal, user[usrno].giftcardno[ptcnt]);
   return 0;
}
   
