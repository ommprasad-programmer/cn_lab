# Computer Networks Laboratory Practical Programs

A comprehensive repository of standard Computer Networks laboratory practical experiments implemented in standard C (C99/C11). This repository covers core algorithms, protocols, and mechanisms across the Physical, Data Link, Network, Transport, and Application layers of the OSI / TCP-IP reference model.

---

## 1. Project Overview

- **Repository Structure**: Organised strictly by network layer (Sections 2 through 6).
- **Experiments**: 24 distinct laboratory practical experiments.
- **Language**: Standard ANSI/ISO C with POSIX socket APIs on Linux.
- **Quality & Portability**: Zero warnings with `-Wall -Wextra`, clean input validation, robust memory management, and deterministic error handling.
- **Comment Policy**: Zero comments within source code to adhere to strict laboratory examination guidelines.

---

## 2. Directory Structure

```text
CN-Lab-Programs/
├── Section-2-Physical-Layer/
│   ├── polar_nrz_l_nrz_i.c
│   ├── polar_manchester_differential_manchester.c
│   ├── 2b1q.c
│   ├── mlt_3.c
│   └── synchronous_tdm.c
├── Section-3-Data-Link-Layer/
│   ├── crc.c
│   ├── hamming_code.c
│   ├── character_stuffing.c
│   ├── bit_stuffing.c
│   ├── go_back_n_arq.c
│   ├── selective_repeat_arq.c
│   └── csma_cd.c
├── Section-4-Network-Layer/
│   ├── ipv4_validation.c
│   ├── subnet_information.c
│   ├── usable_host_ip_addresses.c
│   ├── vlsm.c
│   ├── ipv4_fragmentation_reassembly.c
│   ├── distance_vector_routing.c
│   └── link_state_routing.c
├── Section-5-Transport-Layer/
│   ├── udp_data_transfer/
│   │   ├── server.c
│   │   └── client.c
│   ├── tcp_message_exchange/
│   │   ├── server.c
│   │   └── client.c
│   └── tcp_congestion_control.c
├── Section-6-Application-Layer/
│   ├── dns_client.c
│   └── rsa_encryption_decryption.c
└── README.md
```

---

## 3. List of Experiments and Source Files

| Exp # | Experiment Title | Relative Source File Path |
| :---: | :--- | :--- |
| **2.1** | Polar NRZ-L and Polar NRZ-I Line Coding | `Section-2-Physical-Layer/polar_nrz_l_nrz_i.c` |
| **2.2** | Polar Manchester & Differential Manchester Line Coding | `Section-2-Physical-Layer/polar_manchester_differential_manchester.c` |
| **2.3** | 2B1Q (Two-Binary One-Quaternary) Multilevel Line Coding | `Section-2-Physical-Layer/2b1q.c` |
| **2.4** | MLT-3 (Multi-Level Transmit 3-Levels) Line Coding | `Section-2-Physical-Layer/mlt_3.c` |
| **2.5** | Synchronous Time Division Multiplexing (TDM) | `Section-2-Physical-Layer/synchronous_tdm.c` |
| **3.1** | Cyclic Redundancy Check (CRC) Error Detection | `Section-3-Data-Link-Layer/crc.c` |
| **3.2** | Hamming Code (7,4) Single-Bit Detection and Correction | `Section-3-Data-Link-Layer/hamming_code.c` |
| **3.3** | Character (Byte) Stuffing and Destuffing | `Section-3-Data-Link-Layer/character_stuffing.c` |
| **3.4** | Bit Stuffing and Destuffing | `Section-3-Data-Link-Layer/bit_stuffing.c` |
| **3.5** | Go-Back-N Automatic Repeat Request (ARQ) | `Section-3-Data-Link-Layer/go_back_n_arq.c` |
| **3.6** | Selective Repeat Automatic Repeat Request (ARQ) | `Section-3-Data-Link-Layer/selective_repeat_arq.c` |
| **3.7** | CSMA/CD with Binary Exponential Backoff | `Section-3-Data-Link-Layer/csma_cd.c` |
| **4.1** | IPv4 Address Validation and Class Identification | `Section-4-Network-Layer/ipv4_validation.c` |
| **4.2** | Determination of Subnet Information (Addresses & Hosts) | `Section-4-Network-Layer/subnet_information.c` |
| **4.3** | Generation of All Usable Host IP Addresses in a Subnet | `Section-4-Network-Layer/usable_host_ip_addresses.c` |
| **4.4** | Implementation of Variable Length Subnet Masking (VLSM) | `Section-4-Network-Layer/vlsm.c` |
| **4.5** | IPv4 Packet Fragmentation and Reassembly Simulation | `Section-4-Network-Layer/ipv4_fragmentation_reassembly.c` |
| **4.6** | Distance Vector Routing (Bellman-Ford Algorithm) | `Section-4-Network-Layer/distance_vector_routing.c` |
| **4.7** | Link State Routing (Dijkstra's Shortest Path Algorithm) | `Section-4-Network-Layer/link_state_routing.c` |
| **5.1** | UDP Bidirectional Data Transfer (Client/Server) | `Section-5-Transport-Layer/udp_data_transfer/{server.c, client.c}` |
| **5.2** | TCP Message Exchange (Client/Server) | `Section-5-Transport-Layer/tcp_message_exchange/{server.c, client.c}` |
| **5.3** | TCP Congestion Control (Slow Start & Tahoe/Reno Avoidance) | `Section-5-Transport-Layer/tcp_congestion_control.c` |
| **6.1** | Simulation of DNS Client (Forward Name Resolution) | `Section-6-Application-Layer/dns_client.c` |
| **6.2** | Educational RSA Public-Key Encryption and Decryption | `Section-6-Application-Layer/rsa_encryption_decryption.c` |

---

## 4. System Prerequisites

- **Operating System**: Linux (Ubuntu, Debian, Fedora, Arch, CentOS) or any POSIX-compliant Unix system.
- **Compiler**: GCC (`gcc` version 7.0 or higher recommended) or Clang.
- **Build Utilities**: GNU Make (optional), Glibc (`libc6-dev`).

---

## 5. Compilation and Execution Guide

### Section 2: Physical Layer Protocols and Techniques

```bash
cd Section-2-Physical-Layer

# Experiment 2.1: Polar NRZ-L and NRZ-I
gcc -Wall -Wextra polar_nrz_l_nrz_i.c -o polar_nrz_l_nrz_i
./polar_nrz_l_nrz_i

# Experiment 2.2: Polar Manchester and Differential Manchester
gcc -Wall -Wextra polar_manchester_differential_manchester.c -o polar_manchester_differential_manchester
./polar_manchester_differential_manchester

# Experiment 2.3: 2B1Q Line Coding
gcc -Wall -Wextra 2b1q.c -o 2b1q
./2b1q

# Experiment 2.4: MLT-3 Line Coding
gcc -Wall -Wextra mlt_3.c -o mlt_3
./mlt_3

# Experiment 2.5: Synchronous TDM
gcc -Wall -Wextra synchronous_tdm.c -o synchronous_tdm
./synchronous_tdm
```

---

### Section 3: Data Link Layer Protocols and Techniques

```bash
cd Section-3-Data-Link-Layer

# Experiment 3.1: CRC
gcc -Wall -Wextra crc.c -o crc
./crc

# Experiment 3.2: Hamming Code (7,4)
gcc -Wall -Wextra hamming_code.c -o hamming_code
./hamming_code

# Experiment 3.3: Character Stuffing
gcc -Wall -Wextra character_stuffing.c -o character_stuffing
./character_stuffing

# Experiment 3.4: Bit Stuffing
gcc -Wall -Wextra bit_stuffing.c -o bit_stuffing
./bit_stuffing

# Experiment 3.5: Go-Back-N ARQ
gcc -Wall -Wextra go_back_n_arq.c -o go_back_n_arq
./go_back_n_arq

# Experiment 3.6: Selective Repeat ARQ
gcc -Wall -Wextra selective_repeat_arq.c -o selective_repeat_arq
./selective_repeat_arq

# Experiment 3.7: CSMA/CD
gcc -Wall -Wextra csma_cd.c -o csma_cd
./csma_cd
```

---

### Section 4: Network Layer Protocols and Techniques

```bash
cd Section-4-Network-Layer

# Experiment 4.1: IPv4 Validation & Classification
gcc -Wall -Wextra ipv4_validation.c -o ipv4_validation
./ipv4_validation

# Experiment 4.2: Subnet Information Calculator
gcc -Wall -Wextra subnet_information.c -o subnet_information
./subnet_information

# Experiment 4.3: Usable Host IP Addresses Generator
gcc -Wall -Wextra usable_host_ip_addresses.c -o usable_host_ip_addresses
./usable_host_ip_addresses

# Experiment 4.4: VLSM Subnetting
gcc -Wall -Wextra vlsm.c -o vlsm
./vlsm

# Experiment 4.5: IPv4 Fragmentation & Reassembly
gcc -Wall -Wextra ipv4_fragmentation_reassembly.c -o ipv4_fragmentation_reassembly
./ipv4_fragmentation_reassembly

# Experiment 4.6: Distance Vector Routing
gcc -Wall -Wextra distance_vector_routing.c -o distance_vector_routing
./distance_vector_routing

# Experiment 4.7: Link State Routing
gcc -Wall -Wextra link_state_routing.c -o link_state_routing
./link_state_routing
```

---

### Section 5: Transport Layer Protocols and Techniques

#### Experiment 5.1: UDP Data Transfer

Open two separate terminal windows.

**Terminal 1 (Server):**
```bash
cd Section-5-Transport-Layer/udp_data_transfer
gcc -Wall -Wextra server.c -o server
./server 8080
```

**Terminal 2 (Client):**
```bash
cd Section-5-Transport-Layer/udp_data_transfer
gcc -Wall -Wextra client.c -o client
./client 127.0.0.1 8080
```
*Note: Type messages into the client terminal. Type `exit` to close both client and server gracefully.*

#### Experiment 5.2: TCP Message Exchange

Open two separate terminal windows.

**Terminal 1 (Server):**
```bash
cd Section-5-Transport-Layer/tcp_message_exchange
gcc -Wall -Wextra server.c -o server
./server 8081
```

**Terminal 2 (Client):**
```bash
cd Section-5-Transport-Layer/tcp_message_exchange
gcc -Wall -Wextra client.c -o client
./client 127.0.0.1 8081
```
*Note: Start the server first so it listens for connections. Type `exit` in the client terminal to terminate the session.*

#### Experiment 5.3: TCP Congestion Control Simulation

```bash
cd Section-5-Transport-Layer
gcc -Wall -Wextra tcp_congestion_control.c -o tcp_congestion_control
./tcp_congestion_control
```

---

### Section 6: Application Layer Protocols and Techniques

```bash
cd Section-6-Application-Layer

# Experiment 6.1: DNS Client Simulation
gcc -Wall -Wextra dns_client.c -o dns_client
./dns_client

# Experiment 6.2: RSA Public-Key Encryption and Decryption
gcc -Wall -Wextra rsa_encryption_decryption.c -o rsa_encryption_decryption
./rsa_encryption_decryption
```

---

## 6. Socket Programming Guidelines

1. **Port Selection**: Default ports (8080 and 8081) can be overridden by passing a custom port as a command-line argument (e.g. `./server 9000`).
2. **Order of Execution**: For TCP, the server must be running and listening prior to starting the client. For UDP, starting the server first ensures no initial datagrams are dropped.
3. **Loopback Testing**: Use `127.0.0.1` or `localhost` when testing both client and server on the same host machine.
4. **Clean Exit**: Both UDP and TCP implementations detect the keyword `exit` to cleanly close active connections and release OS socket descriptors.

---

## 7. Educational RSA Implementation Notice

Experiment 6.2 (`rsa_encryption_decryption.c`) is designed exclusively for laboratory and educational demonstrations of the RSA mathematical principles ($p \times q = n$, $\phi(n)$, modular inverse, and modular exponentiation). It operates with standard integer primitives (`long long` with `__int128` intermediate multiplication) and should not be deployed in production or security-critical environments where cryptographic libraries like OpenSSL or Libsodium are required.
