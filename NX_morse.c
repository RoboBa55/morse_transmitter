/**
  ******************************************************************************
  * @file    NX_morse.c
  * @author  (c)Robert Laszlo
  * @version V0.1.0
  * @date    25-September-2017
  * @brief   Morse code transmitter
  */
//    Source code by NEEDRONIX s.r.o. Slovakia, Europe (c)Robert Laszlo, OM1LD 2017
//    This C source code is from cubesat satellite skCUBE prepared for public use.
/////////////////////////////////////////////////////////////////////////////////
//  * Redistribution and use in source and binary forms, with or without modification,
//  * are permitted provided that the following conditions are met:
//  *   1. Redistributions of source code must retain the above copyright notice,
//  *      this list of conditions and the following disclaimer.
//  *   2. Redistributions in binary form must reproduce the above copyright notice,
//  *      this list of conditions and the following disclaimer in the documentation
//  *      and/or other materials provided with the distribution.
//  *   3. Neither the name of NEEDRONIX s.r.o. nor the names of its contributors
//  *      may be used to endorse or promote products derived from this software
//  *      without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//     --- --- --- --- 
//    | 1 | 0 | 1 | 1 |
//     --- --- --- ---
//    | 1 | 0 | 1 | 0 |
//     --- --- --- ---
//    | 0 | 1 | 0 | 1 |
//     --- --- --- ---
//    | 0 | 1 | 0 | 1 |
//     --- --- --- ---
//
//     ---------------
//    | B   A   5   5 |
//     ---------------
//
//  *  End of copyright notice 
/////////////////////////////////////////////////////////////////////////////////
//
//	Note: You can create any morse code with control characters "<" and ">"
//  This option has a different size
//  Special character - no pause between characters
//  Sample: <EEE> = s; <ET> = a;
//          <AR> | <ENN> | <AAE> | <EKE> | <EC> | <ETETE> = .-.-.

//  /--------- Start character. Starting special text
//  |/-------- First character
//  || /------ More characters
//  || | /---- End character. End of special text
//  || | |
//  <ab.z>
//
/////////////////////////////////////////////////////////////////////////////////
//  Note: You can use special command in text like speed change, long transmition or long pause with control characters "{" and "}"
//  This option has a fixed size. Must be 5 byte long
//
//  /--------- start character for command
//  |/-------- command code  (c) {T,W,P,....}
//  || /------ command value (NN) Decadic number from 0 to 99
//  || |/----- end character for command (fixed length 5 bytes!)
//  ||/||
//  {cNN}
//
//  Note: Command W must have a value from 5 to 50! Default speed is 20WPM
//
/////////////////////////////////////////////////////////////////////////////////
//
//	S A M P L E
//
//  ...
//	NX_morse_init();
//	NX_morse_setwpm(15);
//	NX_morse_tx("Hello world! {W25} Hello world! {T05} <AR> {W15}");
//  ...
//
// or
//
//  ...
//	NX_morse_init();
//	NX_morse_setwpm(15);
//	memset(tx_buffer,0,strlen(tx_buffer);
//	sprintf(tx_buffer,"{W15}de OM1LD = %3.2fDeg = Time%X = OUT 100mW {T04}<AR>{P05} ",temperature,timestamp);
//	NX_morse_tx(tx_buffer);
//  ...
//
/////////////////////////////////////////////////////////////////////////////////


#include "NX_morse.h"

#define true 1
#define false 0
#define NXMORSECONST	(unsigned int)(60000)												//PARIS constant WPM
#define NXMAXCHAR		(unsigned char)((91-32)*2)
#define NXDEFAULTSPEED	(unsigned char)(20)

//global variable
unsigned int nx_morse_time;
unsigned int nx_spec_char = false;

/********************************************************************************
 *   NOTE : This function must be modified or
 *          implemented in your file
 */
void NX_Delay(unsigned int ms_time) {
	// Time delay in miliseconds!
	// delay(ms_time);
	/////////////////////////////////
	//unsigned int delay=1000;
	//while (ms_time--) {
	//	delay=100;
	//	while (delay--){};
	//}
}

void NX_tx_off(void) {
	// Function to set transmitter to listen (no TX) or
	// stop tone for transmition (PWM OFF)
	//////////////////////////////////
	//P1OUT &= ~(0x01);
}

void NX_tx_on(void) {
	// Function to set transmitter to TX or
	// generate tone for transmition (PWM ON)
	//////////////////////////////////
	//P1OUT |= 0x01;
}

/********************************************************************************
 *   NOTE : End
 */



//first initialisation
void NX_morse_init (void)  {
	NX_tx_off();
	NX_morse_setwpm(NXDEFAULTSPEED);															//Default initialisation
}

//set speed (by PARIS)
void NX_morse_setwpm(unsigned char wpm) {
	if ( (wpm > 4) && (wpm < 51) ) {
		nx_morse_time = ( NXMORSECONST / (wpm * 50) );		//element time by PARIS (50Element)
	}
	else nx_morse_time = (NXMORSECONST / 1000);										//default set to 20WPM
}

//transmit character
void NX_tx_char (char nx_ch) {
	unsigned char p_char;
	unsigned char nx_bit_num = 0;
	unsigned char nx_bits;
	unsigned char morsetable[]={
							0b00000000,0,	//    32
							0b00011000,5,	//	! 33
							0b00100100,6,   //  " 34
							0b00000000,0,   //    35
							0b00000000,0,   //    36
							0b00000000,0,   //    37
							0b00000000,0,   //    38
							0b00111100,6,   //  ' 39
							0b01011010,6,	//  ( 40
							0b01011010,6,	//  ) 41
							0b00000000,0,   //    42
							0b00000000,0,   //    43
							0b01100110,6,   //  , 44
							0b01000010,6,   //  - 45
							0b00101010,6,   //  . 46
							0b01001000,5,   //  / 47
							0b01111100,5,   //  0 48 -  Numbers
							0b00111100,5,   //  1 49 |
							0b00011100,5,   //  2 50 v
							0b00001100,5,   //  3 51
							0b00000100,5,   //  4 52
							0b00000000,5,   //  5 53
							0b01000000,5,   //  6 54
							0b01100000,5,   //  7 55 ^
							0b01110000,5,   //  8 56 |
							0b01111000,5,   //  9 57 -   End
							0b01110000,6,   //  : 58
							0b00000000,0,   //    59
							0b00000000,0,   //    60
							0b01000100,5,   //  = 61
							0b00000000,0,   //    62
							0b00011000,6,   //  ? 63
							0b00000000,0,   //    64
							0b00100000,2,	//  A 65  -  Alfabet
							0b01000000,4,   //  B 66  |
							0b01010000,4,   //  C 67  v
							0b01000000,3,   //  D 68
							0b00000000,1,   //  E 69
							0b00010000,4,   //  F 70
							0b01100000,3,   //  G 71
							0b00000000,4,   //  H 72
							0b00000000,2,   //  I 73
							0b00111000,4,   //  J 74
							0b01010000,3,   //  K 75
							0b00100000,4,   //  L 76
							0b01100000,2,   //  M 77
							0b01000000,2,   //  N 78
							0b01110000,3,   //  O 79
							0b00110000,4,   //  P 80
							0b01101000,4,   //  Q 81
							0b00100000,3,   //  R 82
							0b00000000,3,   //  S 83
							0b01000000,1,   //  T 84
							0b00010000,3,   //  U 85
							0b00001000,4,   //  V 86
							0b00110000,3,   //  W 87
							0b01001000,4,   //  X 88 ^
							0b01011000,4,   //  Y 89 |
							0b01100000,4,   //  Z 90 -   End
							0b00000000,0    //    91 =   Definition of last character in table
						};
	
	
	if (nx_ch >= 'a') nx_ch -= 32;													//lower to upper

	switch (nx_ch) {

		case '<':
			nx_spec_char = true;													//special character - no pause between characters <EEE> = s; <ET> = a; <AR> | <ENN> = .-.-.
			break;

		case '>':
			nx_spec_char = false;													//end of special character
			break;

		case ' ':
			NX_tx_off();															//char off
			NX_Delay(nx_morse_time*2);
			break;

		default:
			p_char = (unsigned char) ((nx_ch -' ')*2);
			if (p_char > NXMAXCHAR) p_char = NXMAXCHAR;
			nx_bits = morsetable[p_char];
			nx_bit_num = morsetable[p_char+1];
			while (nx_bit_num) {
				nx_bit_num--;
				if ( (nx_bits & 0b01000000) == 0b01000000) {
					NX_tx_on();														//dash on
					NX_Delay(nx_morse_time*3);
				}
				else {
					NX_tx_on();														//dot on
					NX_Delay(nx_morse_time);
				}
				nx_bits = nx_bits<<1;
				NX_tx_off();														//dot off
				NX_Delay(nx_morse_time);
			}
		}
	if(nx_spec_char==false) {
		NX_tx_off();																//char off
		NX_Delay(nx_morse_time*2);
	}
}

//command parser
void NX_tx_command (char cmd, char fval, char lval ) {
	unsigned char val;

	if ( (fval >= '0') && (fval <= '9') && (lval >= '0') && (lval <= '9')) {
		val = (unsigned char)( (( fval - '0' ) *10 ) + lval - '0');					//return value from 0 to 99
	}
	else val = 0;																	//wrong value,  return 0

	switch (cmd) {

		case 'T':																	//constant tone in seconds (for beacon)
			NX_tx_on();
			NX_Delay( (val * 1000) +100 );
			NX_tx_off();
			NX_Delay(nx_morse_time*6);
			break;

		case 'P':																	//Pause in seconds
			NX_tx_off();
			NX_Delay( (val * 1000) +100 );
			break;

		case 'W':
			NX_morse_setwpm( val);
			break;

		//Here you can write your own command code
		//case 'X':
		//User_function();
		//break;

		default:
		break;
	}

}

//transmit buffer
void NX_morse_tx(char *data) {
unsigned int p_dat=0;
char nx_ch;

	while ( (*(data + p_dat) != 0) && (*(data +p_dat) != '\n') )  {
		nx_ch = *(data + p_dat);
		if ( (nx_ch == '{') && ( *(data + p_dat + 4) == '}') ) {					//command captured
			NX_tx_command( *(data + p_dat + 1), *(data + p_dat + 2), *(data + p_dat + 3) );
			p_dat = p_dat+5;
		}
		else {
			NX_tx_char(nx_ch);
			p_dat++;
		}
	}
}

/******************************************************************************** 
 *                E N D of code by BA55
 */
