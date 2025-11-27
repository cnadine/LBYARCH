## Setup

### Prerequisites
- gcc x64 compiler
- nasm x64 compiler

### Running the Program

compile the .asm file using nasm
```bash
nasm -f win64 vector_dist.asm -o vector_dist.obj
```

compile the c file together with the created obj file
```bash
gcc vector.c vector_dist.obj -o vector.exe
```

run the executable
```bash
vector
```