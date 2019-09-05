# two_gadget

这是一个two_gadget的poc, 这个poc的灵感源于hitcon2017(不记得是不是了)的two, 使用两个gadget来getshell

这里的思路是第一个gadget调用某个函数, 让函数正常返回, 并且能够设置寄存器的值为0

第二gadget调用one_gadget来进行getshell

### 依赖

基于python 2.7 
	--> pwntools

idapython

### 使用方法

0. 先编译prog目录下的pow.c文件, 编译命令在文件头, 需要自行修改代码获取so的基地址
1. 将被测试的so文件和运行所需要的ld文件放入`tested_libc`文件夹
2. 打开IDA 加载 `dump_func.py`
3. 运行 `python testreg.py` 记得先修改脚本中的参数
4. 运行 `python parser.py outfile_in_db`
5. 运行 `python find.py outfile_in_db "reg1&reg2"` 即可返回可能的two_gadget

### 目录结构
```
.
├── clean.sh	清理上一次生成的文件, 主要是out文件夹下的文件
├── db 		存放find.py搜索的文件
├── dump_func.py  	IDApython脚本, 从IDA dump出so文件的所有函数名和偏移
├── find.py 	搜索符合需要的寄存器
├── out 		testreg.py的输出文件
├── parser.py	分析out中的文件, 加入到db中
├── prog		存放程序所使用的程序和数据
│   ├── dumpfunc.txt	IDApython dump下来的函数名和偏移
│   ├── pow 			pow.c生成的二进制文件
│   └── pow.c			进行遍历so文件中函数的文件源代码, 需要修改来获得库基址嗷
├── README.md
├── tested_libc			需要测试的库文件
│   ├── ld-2.23.so
│   └── libc-2.23.so
└── testreg.py			用来测试的pow的脚本
```
### TODO

0. TODO肯定是不会去do的啦.... 
1. 不知道怎么样能精准获得库文件的基址. 难顶
2. 将导出函数和偏移的任务用其他语言实现. 舍弃掉IDApython

### 致谢

@lxf
