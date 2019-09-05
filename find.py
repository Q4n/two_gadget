import sys,json
from pwn import success,log,info

if len(sys.argv)!=3:
    log.critical("error") 
    info("Usage: python find.py file_in_db 'reg1(&|)reg2'") 
    info("we will find out reg1 and(or) reg2 == 0 for you") 
    info("Example: python find.py libc 'rax&rbx'")
    exit(0)

filename="./db/"+sys.argv[1]
inputbuf=sys.argv[2]
check=0
if '&' in inputbuf:
    check=1
    regs=inputbuf.replace("&"," ").split()
else:
    regs=inputbuf.replace("|"," ").split()

fp=open(filename,"r")
while True:
    tmp=fp.readline()
    if not tmp or tmp=='\n':
        break
    res=json.loads(tmp[:-1])
    if check:
        if res.get(regs[0])==0 and res.get(regs[1])==0:
            printbuf=''
            for i,j in res.items():
                printbuf+=i+":"+hex(j)+"  "
            printbuf+="\n"
            success(printbuf)
    else:
        if res.get(regs[0])==0 or res.get(regs[1])==0:
            printbuf=''
            for i,j in res.items():
                printbuf+=i+":"+hex(j)+"  "
            printbuf+="\n"
            success(printbuf)

fp.close()