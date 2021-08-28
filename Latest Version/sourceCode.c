#include <stdio.h>



// Multiple Instance of Attributes
int global =9;
int multpleInstanceOfAttributes1( int var1){
      global =10;
      int global=2;
      int var1=global;
}
int multpleInstanceOfAttributes2( int var)  {
      int var1= global;
      int var1+= 2+var;
}

// Multiple Instance of Methods
int sum(int n1) {
      return n1;
}
void sum(int b2)
{
}
int sum(int n1,int n2)
{
      return n1+ n2;
}
int sum(int n1, double n2)
{
}




// Invalid Error
void invalid()          {
      int 1num = 0, num1 = 2;
      if( num1> ) {
      }
      else if(num1 ){
      }
      else
      {
      }
      else if(num1 >2) {
      }

      int a,b=4*54;
      a+b++;
      a+= b+9;
      a =a, b;
      a+=a++ + ++b;
      a=a+++++b;
      a+=num++;
      --a;
      a =a*b+;
}


// Missing Syntax
int sqrt(int number    ) {
      return number*number;
      for(int i=0; i>; ++i)
            i+;
}

int missing( int num)
{
      num = result;
      int sq;
      sq= sqrt(    )  ;
      sq =sqrt(num):
      sq= sqrt(25 );
      sq= sqrt( num) ;
      sqrt( num);
      return;
}

int main()
{
      int num;
      scanf("%d", num);
      printf("Your Number is %d", );

      return 0
}

// Unterminated Comment Issue
void unterminatedCommentIssue()
{

}
