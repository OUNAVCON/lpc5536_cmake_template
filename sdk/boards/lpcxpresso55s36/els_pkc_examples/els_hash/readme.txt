Overview
========
The ELS PKC application provides examples which demonstrate usage of most available algorithms and a crypto library lightweight testing:
- AES-128/192/256 encryption/decryption, modes ECB/CBC/CTR/GCM/CMAC
- SHA2-224/256/384/512 (including sha-direct mode)
- KDF: CKDF (NIST SP 800-108 / SP800-56C), HKDF (RFC5869)
- HMAC
- ECC Sign/Verify/Keygen/Keyexchange (P-256)
- RFC3394 key wrapping/unwrapping
- Key Import/Export/Utilities/Provisioning
- Random number Generation (DRBG/PRNG)

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- Keil MDK  5.38.1
- GCC ARM Embedded  12.2
- MCUXpresso  11.8.0

Hardware requirements
=====================
- Mini/micro USB cable
- LPCXpresso55S36 board
- Personal Computer

Board settings
==============

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J1) on the board
2.  Open a serial terminal with the following settings (See Appendix A in Getting started guide for description how to determine serial port number):
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the ELS (Crypto Sub System) and PKC (Public-Key Crypto Coprocessor) demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ELS PKC hash example

SHA224 one block:pass
SHA256 one block:pass
SHA256 direct one block:pass
SHA384 one block:pass
SHA384 direct one block:pass
SHA512 one block:pass
HASH example:pass
HASH with secure counter example:pass

RESULT: All 8 test PASS!!
ELS example END
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
