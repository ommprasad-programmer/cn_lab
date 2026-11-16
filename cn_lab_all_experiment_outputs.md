# Computer Networks Laboratory — All Experiment Outputs

Sample terminal outputs transcribed from the supplied lab document. Inputs and outputs are shown as recorded in that source.

**Total experiments:** 24
**Experiments covered:** 2.1–2.5, 3.1–3.7, 4.1–4.7, 5.1–5.3, 6.1–6.2

## Experiment 2.1 NRZ-L (Non-Return-to-Zero Level) and NRZ-I (Non-Return-to-Zero Invert)

```text
Enter bin data:
nrz-encoding: | -  | +  | -  | -  | +  | +  | - 
IN NRZI | -  | -  | +  | -  | -  | -  | +
```

---

## Experiment 2.2 Manchester and Differential Manchester Encoding

```text
Enter the number of data bits: 

Enter the data bits (0 or 1) separated by space: 

Polar Manchester Encoding: | + to - | - to + | + to - | + to - | - to + | - to + |



Differential Manchester Encoding: | + to - | + to - | + to - | - to + | - to + | + to - |
```

---

## Experiment 2.3 2B1Q (Two-Binary One-Quaternary) Multilevel Line Coding

```text
Enter a binary string (of even length): 

2B1Q Encoded Output: | -3 | -1 | -3 | +1 |
```

---

## Experiment 2.4 MLT-3 (Multi-Line Transmission 3-Level) Encoding

```text
Enter the binary data stream (e.g., 1011001): 

MLT-3 Encoded Signal: | +V | +V | 0V |-V | -V | -V | 0V |
```

---

## Experiment 2.5 Synchronous Time Division Multiplexing (TDM)

```text
Synchronous TDM Simulation

==========================



Enter the number of channels: Enter the frame size (max. number of characters per channel): 

--- Input Phase ---

Enter data for channel 1 (max 4 characters without any space, or '-' for empty): Enter data for channel 2 (max 4 characters without any space, or '-' for empty): Enter data for channel 3 (max 4 characters without any space, or '-' for empty): 

--- Transmitting Frames (Round-Robin Schedule) ---

Time Slot Order: CH1 CH2 CH3 



Frame 1: D N L 

Frame 2: A E A 

Frame 3: T T B 

Frame 4: A W S
```

---

## Experiment 3.1 Cyclic Redundancy Check (CRC) Error Detection

```text
Enter the data to be sent (in binary): Enter the pre-determined divisor (in binary): 

-- Sender Side --

Data: 100100

Pre-determined divisor: 1101

Codeword (Data + CRC): 100100001



-- Receiver Side --

Data is correct (No errors detected)



Simulating an error...

Erroneous Received Data: 000100001

Data is incorrect (Error detected)
```

---

## Experiment 3.2 Hamming Code C(7,4) Single-Bit Error Detection & Correction

```text
Enter 4-bit dataword (a0 a1 a2 a3): 

Encoded 7-bit codeword (r0 r1 r2 a0 a1 a2 a3): 0 0 0 1 0 1 1 



Enter bit position to introduce error (1-7, 0 for no error): 

Codeword with error: 0 0 1 1 0 1 1 





--- Receiver Side ---



Error detected at bit position: 4



Corrected Codeword: 0 0 1 0 0 1 1
```

---

## Experiment 3.3 Character / Byte Stuffing and Destuffing

```text
Character used for starting and ending flag: #

Character used for escape character: \\



Enter the characters to be transmitted (without spaces): 

Stuffed Frame: #A\#B\\\\\\\C\#D#

Destuffed Data: A#B\\\C#D
```

---

## Experiment 3.4 Bit Stuffing and Destuffing (HDLC Framing)

```text
Enter the binary data stream to be transmitted: 

Stuffed Frame (with flags): 011111100111110101111100@01111110

Destuffed Data:             01111110111110@
```

---

## Experiment 3.5 Go-Back-N (GBN) Sliding Window ARQ Protocol

```text
--- Go-Back-N ARQ Simulation ---

Enter the total number of frames to send: Enter the window size: 

--- Transmission Started ---

Sender: Sending Frame 0

Sender: Sending Frame 1

Sender: Sending Frame 2

Receiver: Received Frame 0 successfully

Receiver: Sent ACK 1



Sender: Sending Frame 3

Receiver: Received Frame 1 successfully

Receiver: Sent ACK 2



Sender: Sending Frame 4



!!! Timeout: No ACK received for Frame 2 !!!

Go-Back-N Action: Retransmitting window starting from Frame 2



Sender: Sending Frame 2

Sender: Sending Frame 3

Sender: Sending Frame 4

Receiver: Received Frame 2 successfully

Receiver: Sent ACK 3



Receiver: Received Frame 3 successfully

Receiver: Sent ACK 4





!!! Timeout: No ACK received for Frame 4 !!!

Go-Back-N Action: Retransmitting window starting from Frame 4



Sender: Sending Frame 4

Receiver: Received Frame 4 successfully

Receiver: Sent ACK 5



--- All 5 frames successfully transmitted and acknowledged! ---
```

---

## Experiment 3.6 Selective-Repeat (SR) Sliding Window ARQ Protocol

```text
--- Selective-Repeat ARQ Simulation ---

Enter the total number of frames to send: Enter the window size: 

--- Transmission Started ---

Sender: Transmitting Frame 0

Sender: Transmitting Frame 1

Sender: Transmitting Frame 2



Receiver: Frame 0 received properly -> Sent ACK 1

Receiver: Frame 1 received properly -> Sent ACK 2

!!! Timeout: NAK generated or ACK missing for Frame 2 !!!



--- Sliding window base forward. Current Base Frame: 2 ---



Sender: Transmitting Frame 2

Sender: Transmitting Frame 3

Sender: Transmitting Frame 4



Receiver: Frame 2 received properly -> Sent ACK 3

Receiver: Frame 3 received properly -> Sent ACK 4

!!! Timeout: NAK generated or ACK missing for Frame 4 !!!



--- Sliding window base forward. Current Base Frame: 4 ---



Sender: Transmitting Frame 4



Receiver: Frame 4 received properly -> Sent ACK 5



--- Sliding window base forward. Current Base Frame: 5 ---



--- Success: All 5 frames successfully transmitted and acknowledged! ---
```

---

## Experiment 3.7 CSMA/CD (Carrier Sense Multiple Access with Collision Detection)

```text
--- CSMA/CD Protocol Simulation ---

Node is preparing to transmit data over the shared channel...



Attempt 1:

-> Sensing carrier... Channel appears IDLE. Starting transmission...

!!! CRITICAL: Collision detected during transmission !!!

-> Sending Jamming Signal to alert all network stations...

-> Backoff Algorithm: Waiting for a random interval of 1 time slots...



Attempt 2:

-> Sensing carrier... Channel appears IDLE. Starting transmission...

=> SUCCESS: Data packet transmitted completely without any collisions!

=> Channel frame transfer sequence finished.
```

---

## Experiment 4.1 IPv4 Address Validation and Class Identification

```text
=== IPv4 Address Validation and Class Identification ===

Enter an IPv4 Address (e.g., 192.168.1.10): 

Result: Valid IPv4 Address parsed successfully as: 192.168.1.10

Class Identification: Class C

Default Subnet Mask: 255.255.255.0

Network ID portion: 192.168.1.0

Host ID portion: 0.0.0.10
```

---

## Experiment 4.2 Subnet Evaluation: Network Address, Broadcast Address & Host Capacity

```text
=== Determination of Subnet Information ===

Enter Base IP Address (separated by spaces, e.g., 192 168 1 10): Enter CIDR Subnet Mask Prefix Length (e.g., 24 for 255.255.255.0): 

Computed Subnet Mask: 255.255.255.0

Network Address:   192.168.1.0

Broadcast Address: 192.168.1.255

Total Address Spaces in Subnet: 256

Total Usable Host Placements:   254
```

---

## Experiment 4.3 Generation of Usable Host IP Addresses within a Subnet

```text
=== Generation of All Usable Host IP Addresses ===

Enter Network Base IP (separated by spaces, e.g., 192 168 1 0): Enter Subnet CIDR Prefix (e.g., 28 to test shorter sample outputs safely): 

Network Scope Bounds identified as:

Network ID Base Reference:  192.168.1.0

Subnet Broadcast Terminal: 192.168.1.15



--- Generating List of Active Host IP Identifiers ---

Host #001 Address allocation: 192.168.1.1

Host #002 Address allocation: 192.168.1.2

Host #003 Address allocation: 192.168.1.3

Host #004 Address allocation: 192.168.1.4

Host #005 Address allocation: 192.168.1.5

Host #006 Address allocation: 192.168.1.6

Host #007 Address allocation: 192.168.1.7

Host #008 Address allocation: 192.168.1.8

Host #009 Address allocation: 192.168.1.9

Host #010 Address allocation: 192.168.1.10

Host #011 Address allocation: 192.168.1.11

Host #012 Address allocation: 192.168.1.12

Host #013 Address allocation: 192.168.1.13

Host #014 Address allocation: 192.168.1.14



Operation complete. Generated 14 unique executable client targets.
```

---

## Experiment 4.4 Variable Length Subnet Masking (VLSM)

```text
=== Variable Length Subnet Masking (VLSM) ===

Enter starting Network Base IP (separated by spaces, e.g., 192 168 1 0): Enter the number of subnets needed: Enter host requirement for Subnet 1: Enter host requirement for Subnet 2: Enter host requirement for Subnet 3: 

Allocated VLSM Subnets (assuming continuous block processing):

------------------------------------------------------------------------

Subnet  Req Allocated Hosts Network IP  Subnet Mask

------------------------------------------------------------------------

Sub 1 50  62    192.168.1.0/26  Active block boundary updated.

Sub 2 25  30    192.168.1.64/27 Active block boundary updated.

Sub 3 10  14    192.168.1.96/28 Active block boundary updated.

------------------------------------------------------------------------
```

---

## Experiment 4.5 IPv4 Packet Fragmentation and Reassembly

```text
=== IPv4 Fragmentation and Reassembly Simulator ===

Enter Unique Identification Number (Packet ID): Enter Total Packet Length (bytes, including 20-byte IP header): Enter Maximum Transmission Unit (MTU size in bytes): 

--- Generated Fragment Metadata Output ---

------------------------------------------------------------------------

Frag #  Total Len Header  Payload Offset  MF Flag

------------------------------------------------------------------------

1 1500    20  1480  0 1

2 1500    20  1480  185 1

3 1040    20  1020  370 0

------------------------------------------------------------------------

Reassembly Sequence Status: Success. Reconstructed 3 payloads into original packet layout.
```

---

## Experiment 4.6 Distance Vector Routing using Bellman-Ford Algorithm

```text
=== Distance Vector Routing Simulator ===

Enter total number of network routers
odes: Enter the cost adjacency matrix (use 999 for infinity):



Topology Routing Update Map for Router A:

Destination Shortest Distance Next Hop Route Node

A   0     A

B   2     B

C   3     B



Topology Routing Update Map for Router B:

Destination Shortest Distance Next Hop Route Node

A   2     A

B   0     B

C   1     C



Topology Routing Update Map for Router C:

Destination Shortest Distance Next Hop Route Node

A   3     B

B   1     B

C   0     C
```

---

## Experiment 4.7 Link State Routing using Dijkstra's Shortest Path Algorithm

```text
=== Link State Routing Simulator (Dijkstra) ===

Enter structural count of network routers: Enter Routing Link Cost Adjacency Matrix (use 999 for Unreachable/Infinite nodes):

Select local Root Source Router index ID (0 for A, 1 for B, etc.): 

Shortest Link-State Path Mapping from Source Router A:

Router Destination B: Minimum Metric Cost = 2 (Path Tracer Sequence: B <- A)

Router Destination C: Minimum Metric Cost = 3 (Path Tracer Sequence: C <- B <- A)

Router Destination D: Minimum Metric Cost = 6 (Path Tracer Sequence: D <- B <- A)
```

---

## Experiment 5.1 UDP Datagram Transmission Simulation (Connectionless)

```text
=== Simulation of UDP Data Transfer (Connectionless) ===

Enter Source Port (e.g., 8080): Enter Destination Port (e.g., 53): Enter message payload text (no spaces): 

--- Sender: Encapsulating UDP Datagram ---

Header -> Src Port: 8080 | Dest Port: 53 | Len: 26 bytes | Checksum: 0xFC

Transmitting message to the network medium...



--- Receiver: Processing Arrived Datagram ---

Received Packet Content from Port 8080: [ HelloWorld ]

Integrity Validation: Checksum matches (0xFC). Data accepted.
```

---

## Experiment 5.2 TCP Three-Way Handshake Connection Establishment

```text
=== Simulation of TCP Three-Way Handshake Connection ===



[STEP 1] Client -> Server: [SYN flag set]

          Sequence Number (Seq) = 1434



[STEP 2] Server -> Client: [SYN + ACK flags set]

          Sequence Number (Seq) = 15875 | Acknowledgment Number (Ack) = 1435



[STEP 3] Client -> Server: [ACK flag set]

          Sequence Number (Seq) = 1435 | Acknowledgment Number (Ack) = 15876



>>> STATUS: Connection Established successfully (ESTABLISHED state) <<<



--- Data Segment Transmission Phase ---

Client sends a data stream segment of size 250 bytes:

-> Packet Info: Seq = 1435, Ack = 15876

Server responds with standard Acknowledgment:

<- Packet Info: Seq = 15876, Ack = 1685 (Ready to receive next byte stream boundary)
```

---

## Experiment 5.3 TCP Congestion Control (Slow Start & Congestion Avoidance)

```text
=== Simulation of TCP Congestion Control Algorithm ===

Enter the total simulation runtime rounds to execute: Enter a specific execution round to introduce a Packet Drop Timeout (e.g., 7): 

Starting state conditions initialized: cwnd = 1 MSS | ssthresh = 16

-----------------------------------------------------------------------

Round Congestion Window (cwnd)  ssthresh  Active Engine Phase

-----------------------------------------------------------------------

1 1 MSS     16    Slow Start (Exponential)

2 2 MSS     16    Slow Start (Exponential)

3 4 MSS     16    Slow Start (Exponential)

4 8 MSS     16    Slow Start (Exponential)

5 16 MSS      16    Congestion Avoidance (Linear)

6 17 MSS      16    Congestion Avoidance (Linear)

7 18 MSS      16    Congestion Avoidance (Linear)



[!] NETWORK EVENT: Packet Timeout/Drop detected in Round 7 [!]

Action Taken: ssthresh updated to 9, cwnd window dropped to 1 MSS.



8 1 MSS     9   Slow Start (Exponential)

9 2 MSS     9   Slow Start (Exponential)

10  4 MSS     9   Slow Start (Exponential)

11  8 MSS     9   Slow Start (Exponential)

12  16 MSS      9   Congestion Avoidance (Linear)

-----------------------------------------------------------------------
```

---

## Experiment 6.1 Domain Name System (DNS) Client Simulator

```text
=== Domain Name System (DNS) Client Simulator ===

1\. Forward Lookup (Domain Name -> IP Address)

2\. Reverse Lookup (IP Address -> Domain Name)

Select operating lookup function module (1 or 2): Enter Domain Name to resolve (e.g., ://google.com): 

DNS Client: Sending query to local DNS resolver server...

DNS Resolver: Match identified in record tables.

>> Resolved IP Address: 142.250.68.68
```

```text
=== Domain Name System (DNS) Client Simulator ===

1. Forward Lookup (Domain Name -> IP Address)

2. Reverse Lookup (IP Address -> Domain Name)

Select operating lookup function module (1 or 2): Enter IPv4 Address to resolve (e.g., 142.250.68.68): 

DNS Client: Sending reverse lookup pointer query file...

DNS Resolver: Match identified in pointer records.

>> Resolved Hostname Name: ://google.com
```

---

## Experiment 6.2 RSA Public-Key Cryptography Algorithm

```text
=== Message Confidentiality Engine (RSA Cryptography) ===

Generated Key Parameters:

-> Public Encryption Coordinates (e, n): (17, 3233)

-> Private Decryption Coordinates (d, n): (2753, 3233)



Enter an integer message payload value to securely transmit (Must be < 3233): 

--- Encryption Sequence ---

Transforming plain text numerical data using Public Key configurations...

Resulting Ciphertext Package generated: 99



--- Decryption Sequence ---

Reconstructing payload string at target endpoint using Private Key keys...

Resulting Plaintext Package extracted:  89



Validation Integrity Status: Success. Message contents match perfectly without leakage.
```

---
