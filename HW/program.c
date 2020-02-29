
int inzamam(int che)

int main()
{
    int n= 8+3;

    if(n> 0){
        n=4;
        printf("P");
    }
    if(n >= 0){
        n=4.0;
        printf("P");
    }
    if               ( n> 0){
        n=4;
        printf("P");
    }
    if (n==0){
        printf("N");
    }

    else if(n >= 0){
        n=4;
        printf("P");
    }
    else if               ( n> 0){n=4;
        printf("P");
        n=5;
    }
    else if (n==0){ printf("N");}

    else{
        printf("Z");
    }

    return 0;
}
