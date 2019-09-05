from idaapi import *
from idautils import *
from idc import *

fp=open("../prog/dumpfunc.txt","w")
func_list = Functions()
for func in func_list:
    name = GetFunctionName(func)
    fp.write(name+" "+str(func)+"\n")

fp.close()