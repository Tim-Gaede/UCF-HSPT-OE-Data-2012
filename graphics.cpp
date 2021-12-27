#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;


char input[200];//each line of input will be kept in this variable
int R,C;//number of rows and columns in the grid
char mode[10];//The mode will be either "N" or "B"
char output[200][200];//the matrix will be used to keep the output grid
int r1,c1,r2,c2;//subrectangle of the replacement area
char replacechar[10]; //the character to be used as replacement


/*
updating the corresponding cell with the replacement character ch
if the mode is "N" the cell will be replaced
otherwise the cell will be replaced only if the cell is empty
*/
void update(int r,int c, char ch){
    if(mode[0]=='N') output[r][c] = ch;
    else if(output[r][c]==' ') output[r][c] = ch;    
}


int main(){
    int T,i,j;
    gets(input);
    T = atoi(input);
    for(int canvas = 1; canvas <= T; ++canvas){
        gets(input);
        sscanf(input,"%d%d%s",&R,&C,mode);
        /*
        initially feeling up all the cells with blank
        */
        for(i=0;i<R;++i){
            for(j=0;j<C;++j) output[i][j] = ' ';
            output[i][C] = 0;
        }
        while(gets(input)){
            if(strcmp(input,"END")==0){
                break;
            }
            sscanf(input,"%d%d%d%d%s",&r1,&c1,&r2,&c2,replacechar);
            for(i=r1;i<=r2;++i) for(j=c1;j<=c2;++j) update(i,j,replacechar[0]);//updates the subrectangle
        }
        printf("Canvas #%d\n",canvas);
        printf(" ");
        for(j=0;j<C;++j) printf("%d",j%10);//printing the last digit of each column
        printf("\n");
        for(i=0;i<R;++i){
            printf("%d",i%10);//printing the first digit of the row
            printf("%s",output[i]);
            printf("%d\n",i%10);//printing the last digit of the row
        }
        if(canvas<T) printf("\n");//print blank line after each case except the last one (accepted either way, though)
    }
    return 0;
}
