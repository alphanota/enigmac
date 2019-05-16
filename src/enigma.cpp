//
// Created by angel on 5/16/19.
//

#include "enigma.h"
#include <string>



Enigma::Enigma(){
    walzenlage[0]=0;
    walzenlage[1]=0;
    walzenlage[2]=0;  // choice of rotors

    ringstellung[0]=0;
    ringstellung[1]=0;
    ringstellung[2]=0;  // choice of rotors

    grundstellung[0]=0; // current rotation of the rotors
    grundstellung[1]=0;
    grundstellung[2]=0;

    for(int i =0; i < 26; i++){
        plugBoard[i] = i;
    }


}

Enigma::Enigma(int w0,int w1,int w2, int r0, int r1, int r2, int g0, int g1, int g2){
    walzenlage[0]=w0;
    walzenlage[1]=w1;
    walzenlage[2]=w2;  // choice of rotors

    ringstellung[0]=r0;
    ringstellung[1]=r1;
    ringstellung[2]=r2;  // choice of rotors

    grundstellung[0]=g0; // current rotation of the rotors
    grundstellung[1]=g1;
    grundstellung[2]=g2;

    for(int i =0; i < 26;i++){
        plugBoard[i] = i;
    }
}

Enigma::Enigma(int w0,int w1,int w2, char r0, char r1, char r2, char g0, char g1, char g2){
    walzenlage[0]=w0;
    walzenlage[1]=w1;
    walzenlage[2]=w2;  // choice of rotors

    ringstellung[0]=r0-'A';
    ringstellung[1]=r1-'A';
    ringstellung[2]=r2-'A';  // choice of rotors

    grundstellung[0]=g0-'A'; // current rotation of the rotors
    grundstellung[1]=g1-'A';
    grundstellung[2]=g2-'A';

    for(int i =0; i < 26;i++){
        plugBoard[i] = i;
    }
}

void Enigma::setStecker(int plugs[],int plugSize){
    for(int p = 0; p < plugSize; p+=2){
        int a = plugs[p];
        int b = plugs[p+1];

        plugBoard[a] = b;
        plugBoard[b] = a;
    }
}

void Enigma::setStecker(std::string plugs){
    for(int p = 0; p < plugs.size(); p+=2){
        int a = plugs[p] - 'A';
        int b = plugs[p+1] - 'A';

        plugBoard[a] = b;
        plugBoard[b] = a;
    }
}

void Enigma::forward(uint32 steps){
    for(int i =0; i < steps; i++){
        bool doubleStep =   (grundstellung[1] == notches [walzenlage[1] ]+1) | (grundstellung[1] == notches2 [walzenlage[1]] +1);
        uint32 turnMiddle = (  (grundstellung[2] == notches [walzenlage[2] ]) | (grundstellung[2] == notches2 [walzenlage[2] ]) | doubleStep) &1;
        uint32 turnLeft =   ((  (  (grundstellung[1] == notches [walzenlage[1] ]) | (grundstellung[1] == notches2 [walzenlage[1] ]) )& turnMiddle ) | doubleStep)&1;
        //if( turnMiddle == 1) cout << "Middle rotor turns " << grundstellung[2] << endl;
        grundstellung[1]  = (grundstellung[1]+turnMiddle) % 26;
        grundstellung[0] =  (grundstellung[0]+turnLeft) % 26;
        grundstellung[2] = (grundstellung[2]+1)%26;              // rotate right rotor + 1
    }

}


void Enigma::rotorPass(uint32 &in, uint32 &rotor){
    in = ( in + grundstellung[rotor] - ringstellung[rotor] + 26)%26;
    in = (rings[ walzenlage[rotor] ][  in ] + ringstellung[rotor] + 26)%26;
    //cout << "right  in: "<< letters[rightIn] << endl;
    //cout << "right  out: "<< letters[rightOut] << endl;
    in = (in - grundstellung[rotor] + 26)%26;
}


void Enigma::reflect(uint32 &in){
    in = steckerB[in];
}


void Enigma::rotorPassInv(uint32 &in, uint32 &rotor){
    in = ( in + grundstellung[rotor] - ringstellung[rotor] + 26)%26;
    in = (ringsReverse[ walzenlage[rotor] ][  in ] + ringstellung[rotor] + 26)%26;

    //cout << "left inv in: "<< letters[leftInvIn] << endl;
    //cout << "left  inv out: "<< letters[leftInvOut] << endl;

    in = (in - grundstellung[rotor] + 26)%26;

}


/**
if the middle rotor is in a pre-notch position, when the right rotor reaches
a notch, the middle rotor will rotate, triggering a rotate in the left rotor also

     like:

         LMR
         011 + 001

      =  100
**/

void Enigma::encryptForward(){
    bool doubleStep =   (grundstellung[1] == notches [walzenlage[1] ]+1) | (grundstellung[1] == notches2 [walzenlage[1]] +1);
    uint32 turnMiddle = (  (grundstellung[2] == notches [walzenlage[2] ]) | (grundstellung[2] == notches2 [walzenlage[2] ]) | doubleStep) &1;
    uint32 turnLeft =   ((  (  (grundstellung[1] == notches [walzenlage[1] ]) | (grundstellung[1] == notches2 [walzenlage[1] ]) )& turnMiddle ) | doubleStep)&1;
    //if( turnMiddle == 1) cout << "Middle rotor turns " << grundstellung[2] << endl;
    grundstellung[1]  = (grundstellung[1]+turnMiddle) % 26;
    grundstellung[0] =  (grundstellung[0]+turnLeft) % 26;
    grundstellung[2] = (grundstellung[2]+1)%26;
}

int Enigma::encrypt(uint32 c){


    uint32 L=0;
    uint32 M=1;
    uint32 R=2;
/**
Keyboard:
When the operator presses the letter 'T' on the keyboard
it creates an electric signal that begins the journey
 through the Enigma machine wiring that will end with a
 lamp flashing on the lampboard.
**/

    encryptForward();

/**
Plugboard
The first stop on the journey is the plugboard. Here the
signal is connected to the 'T' input on the plugboard.
Some of the letters on the plugboard will be wired up to
other letters (the plugs), causing the signal to be diverted.
If the 'T' input is not plugged to another letter then our
signal will pass straight to the 'T output. In our case,
though the 'T' is plugged to the 'K', so the
signal is diverted to a new path, the letter is now 'K'.
**/
    uint32 letter= plugBoard[c];


/*
Static Rotor
The next stop is the static rotor, which as the name
suggests does nothing to the signal it simply turns wires
into contacts (the signal only passes when the contacts
touch). So our signal is still the letter 'K'. The static
rotor output is connected to the input of the
right rotor. This is where things get more complicated.
*/


/*
Rotors (Scramblers)
There are five possible rotors that can be used in any order for the three
rotor positions: right, middle, left. Each rotor has an
inner ring of contacts and an outer ring of contacts and
their purpose is to scramble the signal. The outer ring
contacts connect each rotor to the next rotor
(or the static rotor / reflector) as well as its own
inner ring. The inner ring contacts can be rotated
relative to the outer ring which results in even more
possible connections (and therefore, letter substitutions).
The whole rotor itself can be rotated relative to the
static rotor, so that the static rotor 'A' output is
not connected to 'A' input on the rotating rotor.

Furthermore, as each letter is entered the rotors rotate
by one position, so that the same letters are never
connected together in the same message. To add further
complication, each rotor has a notches (different rotors
have the notch in different positions) which when reached,
causes the next rotor to its left to step forward too.
In the case of the middle rotor, it causes the left rotor to step as well as itself (the infamous double stepping mechanism).

In our example, we are using rotor III in the right-hand
position.
*/
    rotorPass(letter,R);
    rotorPass(letter,M);
    rotorPass(letter,L);


/*
Reflector
The reflector takes the input and reflects back the electrical signal for
its return journey through the rotors. There are two possible reflectors,
each of which is wired up differently so that the input letter is transformed
to a different letter when reflected back. In our example, we are using
'Reflector B', which turns our input letter 'H' into output letter 'D'.

It is important that the signal is scrambled when reflected, because of the way
 the Enigma machine is designed -- if you enter the cipher text you get back
 the clear text. So if the reflector output is the same letter as its input
 when the signal passes back through the rotors they will just unscramble what
 was already scrambled and you would get your original letter back again
 unencrypted!
*/
    reflect(letter);
/*
				Reverse Journey
				The reflected signal now passes back through the rotors, which work in
				exactly the same way in reverse. So our letter 'D' passes through the
				left rotor and becomes 'G', which then passes through the middle rotor
				and becomes 'R', which then passes through the right rotor and becomes
				'W'. The signal remains unchanged as it passes through the static rotor
				again (connecting contacts to wires), before it passes through the
				plugboard - here the signal is again left as it is if there is no plug,
				or changed if the letter 'W' is plugged to another letter. In our case
				the 'W' is plugged to the letter 'G', so our plugboard output is 'G'.
*/
    rotorPassInv(letter,L);
    rotorPassInv(letter,M);
    rotorPassInv(letter,R);

/*
Lampboard
The final stop is the lampboard, where the plugboard output is connected to the
corresponding lamp for that letter. In our example, the letter 'G' lights up
meaning the original letter 'T' is encrypted as 'G'.

The Enigma machine operator notes down the output letter and then enters the
next letter in the message, and so on for every letter in the message.
*/
    letter = plugBoard[letter];

    return letter;

}




std::string Enigma::encode(std::string message){

    std::string text;
    text.assign(message);
    for(int i=0; i < message.size();i++){
        char c = text[i];
        int d = c-'A';
        char out = encrypt(d) + 'A';
        text[i] = out;
    }
    return text;
}
