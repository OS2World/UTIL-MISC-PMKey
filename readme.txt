One-Time Password (OTP) Generator for OS/2

PMKey is a one-time password (OTP) generator for the one-time password
system described in RFC 1938.  It is based on the opiekey program from NRL's 
OPIE 2.x distribution, with enhancements for a graphical user interface.  

To use, type the OTP challenge in the "Challenge" field (or paste it with
<Shift-Ins>).  This should include an optional algorithm specifier ("otp-md4" 
or "otp-md5"), followed by a space and a positive integer sequence number, 
followed by a space and a seed string.  Then type the secret key into the 
"Password" field and hit <Enter> (or press the "Compute" button) to generate 
the OTP in the "Response" field.  You can then copy the response value with 
<Ctrl-Ins>.

This is a port of my WinKey program for Microsoft Windows, but has much fewer
features.  You may wish to use the 16-bit WinKey program instead.  I developed
this software with IBM Visual Age C++ (and the help of my wife, Kim Kizirian).  
The source code is provided hoping that someone will improve it!

The NRL OPIE copyright notice is contained in the file "COPYRIGH.NRL".

Please send comments and suggestions to David Aylesworth <dave@tlogic.com>.

David Aylesworth
Technologic, Inc.
http://www.tlogic.com/
