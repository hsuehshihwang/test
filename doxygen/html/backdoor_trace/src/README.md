# Backdoor Service

> Version: 0.0.1
> Editor: Ralph Wang
> Date: 2007/08/23, 2023/05/30 updated. 

Networking PCs can use the backdoor utility to put the files to    
the device which enables the backdoor service. By these socket     
and command libraries, we can build more services for developers     
debugging. 


Function: Send files to device. Sending the directory and file tree 

## Files 

1. bd_svr: The backdoor server. Listen the specific TCP port, and handle 
   the command packet to receive the files from networking clients. 
2. bd_cli: The backdoor client. Send the files to the backdoor server. 
3. backdoor.conf: The server ip address configuration file for client tool. 

## Backdoor Client Installation Instruction

1. Do "make" in this directory. 
2. Put the "bd_svr" to the device you wanna hack and run it. 
3. Put the "backdoor.conf" file to in the "/etc", if you want to change 
   the definiton, please modify the "include/configs.h". 
4. Put the "bd_cli" to "/bin".   

## Bakdoor Client Usage

```bash
$ bd_cli <file name | directory>
# ex: 
$ bd_cli README.md
$ bd_cli ./
```
