/**
  ******************************************************************************
  * @file    NX_morse.h
  * @author  (c)Ba55
  * @version V0.1.0
  * @date    25-September-2017
  * @brief   Morse code transmitter
  **/
//           Source code by NEEDRONIX s.r.o. (c) Robert Laszlo, OM1LD 2017
////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////
#ifndef NX_MORSE_H_INCLUDED
#define NX_MORSE_H_INCLUDED

void NX_morse_init (void);
void NX_morse_setwpm(int wpm);
void NX_morse_tx(char *data);

/**************************************************************************************** 
NOTE: This function Should not be modified!
      The functions must be implemented in the user file
*/
void NX_Delay(uint16_t);
void NX_Tx_on();
void NX_Tx_off();
/* 
 *    End of note
 */


#endif /* NX_MORSE_H_INCLUDED */
