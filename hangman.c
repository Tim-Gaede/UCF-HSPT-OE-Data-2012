#include <stdio.h>

int complete(int alpha[]);

int main(){
    //Standard in
   FILE *fin;
   fin = stdin;
   
   int times, k;
   
   //Read in the number of lava pits to process.
   fscanf(fin, "%d\n", &times);
   
   for(k = 1; k <= times; k++){
      int feet, i;
      char password[101]; //Will store the password string
      char guesses[101]; //Will store the guessing string
      
      //Read case input
      fscanf(fin, "%d %s %s", &feet, password, guesses);
      
      //Declare and initialize a boolean array corresponding to each letter in the alphabet.
      int alpha[26]; 
      for(i = 0; i < 26; i++)
         alpha[i] = 0;
      
      //If a letter appears in password, we'll set it to true. This will allow us to keep track of Ali's guessing progress.  
      for(i = 0; i < 101 && password[i] != '\0'; i++)
         alpha[password[i]-'a'] = 1;
      
      i = 0; //From here on, i will iterate over guesses
      
      //The game only ends when we run out of feet or the password is guessed completely
      while(feet > 0 && !complete(alpha)){
         //For each character in guesses, it will either be a hit or miss
         if(alpha[guesses[i]-'a']){ //If the character is set to true, it's a hit! We set it to false and continue looping.
            alpha[guesses[i]-'a'] = 0;
         }else{ //Otherwise, we've either seen the character before or it doesn't exist. Either way, it's a miss. We lower Ali one foot closer to the lava.
            feet--;
         }
         i++; //Move to the next guess
      }
      
      //If we've completed the password, Ali survives! Otherwise, poor Ali.
      if(complete(alpha)){
         printf("Lava pit #%d: Ali survives!\n",k);
      }else{
         printf("Lava pit #%d: Poor Ali.\n",k);
      }
   }

   return 0;
}

//Iterates through all remaining hidden letters of the password, returning false if any remain. Otherwise, returns true.
int complete(int alpha[]){
   int i;
   for(i = 0; i < 26; i++)
      if(alpha[i])
         return 0;
   return 1;
}
