#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;


// g++ enigma.c -lgmpxx -lgmp -o enigma 
typedef unsigned int uint32;


const char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



float bigramScore[26][26];



void loadFrequencies(char *file){
    FILE *inputstream;
	inputstream = fopen(file,"r");
	int c;
	float p,l;
	char entry[2];
    while( fscanf (inputstream,"%s %d %f %f\n",&entry,&c,&p,&l) == 4){
    	//printf("%s %d %f %f\n",entry,c,p,l);
    	bigramScore[ entry[0]-'A' ][ entry[1]-'A' ] = l;
    	//printf(" %s %f \n",entry, bigramScore [ entry[0]-'A' ][ entry[1]-'A' ]);
    }
	fclose ( inputstream);
}


bool isLetter(int c){
    
    int d =  ( c - 65);
    
    if ( (d < 0) | (d > 25) ) {
        return false;
    }
    else return true;
}
void readsinkov(char *f){
    
	ifstream in(f, std::ifstream::binary);
	
	float sum = 0;
	
	int entry[2];
	
	
	for ( entry[0] = in.get(); entry[0] != EOF; entry[0] = in.get() ) {
        //  ...
         entry[1] = in.peek();
         
           
	    if (!isLetter(entry[0]) | !isLetter(entry[1])){
	        //cout << entry[0] << " , " << entry[1] << endl;
	        sum += 0;
	    }
	    
	   else  sum = sum + bigramScore[ entry[0]-65 ][ entry[1]-65 ];
    }
	
	
	in.close();
	
	cout << f << ", " << sum << endl;
}



int main(int argsc, char **args){
    loadFrequencies("english_bigrams.csv");
    readsinkov(args[1]);
    
    return 0;
     
}
