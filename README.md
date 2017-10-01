# morse_transmitter
Morse code transmitter for cubesats or hamradio activity
Data from 🛰 🌌 space

Source code by NEEDRONIX s.r.o. Slovakia, Europe (c)Robert Laszlo, OM1LD 2017
This C source code is from cubesat satellite skCUBE prepared for public use.

### Author
* Robert Laszlo, OM1LD

## skCube 
![img](skcube.jpg)

[video with real sound of this source](https://www.youtube.com/watch?v=ggRdPaawQAI)


### NOTE
	You can create any morse code with control characters "<" and ">"
  This option has a different size
  Special character - no pause between characters
  Sample: <EEE> = s; <ET> = a;
          <AR> | <ENN> | <AAE> | <EKE> | <EC> | <ETETE> = .-.-.

  /--------- Start character. Starting special text
  |/-------- First character
  || /------ More characters
  || | /---- End character. End of special text
  || | |
  <ab.z>


  You can use special command in text like speed change, long transmition or long pause with control characters "{" and "}"
  This option has a fixed size. Must be 5 byte long

  /--------- start character for command
  |/-------- command code  (c) {T,W,P,....}
  || /------ command value (NN) Decadic number from 0 to 99
  || |/----- end character for command (fixed length 5 bytes!)
  ||/||
  {cNN}

  Note: Command W must have a value from 5 to 50! Default speed is 20WPM



	### S A M P L E

  ...
	NX_morse_init();
	NX_morse_setwpm(15);
	NX_morse_tx("Hello world! {W25} Hello world! {T05} <AR> {W15}");
  ...

 or

  ...
	NX_morse_init();
	NX_morse_setwpm(15);
	memset(tx_buffer,0,strlen(tx_buffer);
	sprintf(tx_buffer,"{W15}de OM1LD = %3.2fDeg = Time%X = OUT 100mW {T04}<AR>{P05} ",temperature,timestamp);
	NX_morse_tx(tx_buffer);
  ...
