# GofOS
The mini os with RISC-V.  
The program can run in Linux and MacOS.  

Make sure the device is already installed riscv library and qemu. To get riscv library, please follow the guideline of [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).  

Add the appropriate directory to $PATH is required, You will need to update your shell's rc file (e.g. ~/.bashrc) :  
```
# Using Linux:
$ vim ~/.bashrc
$ export PATH=$PATH:/opt/riscv/bin  

# Using MacOS:
$ PATH=$PATH:/usr/local/opt/riscv-gnu-toolchain/bin
```

To install qemu, please using the instruction below:  
```
# Using Ubuntu:
$ sudo apt-get install 

# Using Fedora:
$ sudo dnf install qemu

# Using MacOS (with homebrew):
$ brew install qemu
```
  
## Introduction  
Inspired by the cources hold by Jserv, the professor from CSIE of NCKU. I decide to write the simple OS that can implement some OS operations.  
   
The functions which GofOS have :  
1. gets() : Get the input from Qemu's UART
2. puts() : Set the output to Qemu's UART
3. printf() : Using printf() functions to print string
4. malloc() : Using malloc() to manage heap space  
  
5. multitasking
* context-switch : Switch different task to operate  
* timer : Using timer to calculate the time  
* trap-handler : Using trap-handler to do preemptive

## Reference
https://ithelp.ithome.com.tw/users/20110850/ironman/3859  
https://github.com/cccriscv/mini-riscv-os  
https://github.com/mit-pdos/xv6-riscv  
