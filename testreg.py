from pwn import *
# context.log_level='debug'

your_ld_name="ld-2.23.so"
your_so_name="libc-2.23.so"

MAX_TEST = 0
filepath="./prog/dumpfunc.txt"
for index, line in enumerate(open(filepath,'r')):
    MAX_TEST += 1
for i in range(1,MAX_TEST):
    try:
        r=process(["./tested_libc/"+your_ld_name,"./prog/pow",str(i)],env={"LD_PRELOAD":"./tested_libc/"+your_so_name})
        r.sendline()
        r.sendline()
        r.recvuntil("OK",timeout=2)
    except:
        r.close()
