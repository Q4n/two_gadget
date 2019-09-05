import json 
import collections
import os,json,sys

if len(sys.argv)==1:
    out="libc"
elif len(sys.argv)==2:
    out=sys.argv[1]
else:
    print "Usage: python parser.py outfile_in_db"
    
rootdir = './out/'
filelist = os.listdir(rootdir)
output=open("./db/"+out,"w")
for i in range(0,len(filelist)):
    path = os.path.join(rootdir,filelist[i])
    if os.path.isfile(path):
        res=dict()
        res=collections.OrderedDict()
        tmpfp=open(path,"r")
        tmp=tmpfp.readline().replace("\n","").split()
        if not tmp:
            break
        res[tmp[0][:-1]]=int(tmp[1],16)
        while True:
            tmp=tmpfp.readline()
            if not tmp or tmp=="\n":
                break
            tmp=tmp.replace("\n","").split()
            if int(tmp[1],16)==0:
                res[tmp[0][:-1]]=int(tmp[1],16)
                
        if len(res)>1:
            output.write(json.dumps(res)+"\n")
        tmpfp.close()

output.close()
print "Done"
