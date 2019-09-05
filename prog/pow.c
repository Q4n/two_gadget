// gcc pow.c -o pow -g -masm=intel
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
void *libcbase;
size_t tmp;
void *func;
size_t rax_o,rbx_o,rcx_o,rdx_o,rdi_o,rsi_o,r8_o,r9_o,r10_o,r11_o,r12_o,r13_o,r14_o,r15_o,rbp_o;
size_t rbp_t;
size_t rsp_30; // beg: 0x28

int main(int argc,char *argv[]){
    // try to get libcbase
    __asm__(
        "mov libcbase,r11;"
    );
    libcbase-=0x20640;
    // printf("libc: 0x%llx\n",libcbase);

    if(argc!=2)
        exit(-1);
    FILE *p=fopen("./prog/dumpfunc.txt","r");
    char name[30]={0};
    int offset=0;
    int h=atoi(argv[1]); 
    for(int i=0;i<h;i++){
        fscanf(p, "%s%d", name, &offset);
    }
    fclose(p);
    srand(time(0));
    tmp=rand();
    *(int *)((char*)&tmp+4)=rand();
    func=libcbase+offset;
    printf("%s: 0x%llx\n",name,func);
    char filename[0x100]="./out/";
    strcat(filename,name);
    getchar();
    __asm__(
        "mov rax,tmp;"
        "mov rbx,tmp;"
        "mov rcx,tmp;"
        "mov rdx,tmp;"
        "mov rdi,tmp;"
        "mov rsi,tmp;"
        "mov r8,tmp;"
        "mov r9,tmp;"
        "mov r10,tmp;"
        "mov r11,tmp;"
        "mov r12,tmp;"
        "mov r13,tmp;"
        "mov r14,tmp;"
        "mov r15,tmp;"
        "mov rbp_t,rbp;"
        "mov rbp,tmp;"
        "call [func];"
    );   
    __asm__(
        "mov rax_o,rax;"
        "mov rbx_o,rbx;"
        "mov rcx_o,rcx;"
        "mov rdx_o,rdx;"
        "mov rdi_o,rdi;"
        "mov rsi_o,rsi;"
        "mov r8_o,r8;"
        "mov r9_o,r9;"
        "mov r10_o,r10;"
        "mov r11_o,r11;"
        "mov r12_o,r12;"
        "mov r13_o,r13;"
        "mov r14_o,r14;"
        "mov r15_o,r15;"     
        "mov rbp_o,rbp;"
        "mov rbp,rbp_t;"
    );
    printf("OK\n");

    p=fopen(filename,"w");
    fprintf(p,"%s: 0x%llx\n",name,offset);
    fprintf(p,"\trax: 0x%llx\n",rax_o);
    fprintf(p,"\trbx: 0x%llx\n",rbx_o);
    fprintf(p,"\trcx: 0x%llx\n",rcx_o);
    fprintf(p,"\trdx: 0x%llx\n",rdx_o);
    fprintf(p,"\trdi: 0x%llx\n",rdi_o);
    fprintf(p,"\trsi: 0x%llx\n",rsi_o);
    fprintf(p,"\tr8: 0x%llx\n",r8_o);
    fprintf(p,"\tr9: 0x%llx\n",r9_o);
    fprintf(p,"\tr10: 0x%llx\n",r10_o);
    fprintf(p,"\tr11: 0x%llx\n",r11_o);
    fprintf(p,"\tr12: 0x%llx\n",r12_o);
    fprintf(p,"\tr13: 0x%llx\n",r13_o);
    fprintf(p,"\tr14: 0x%llx\n",r14_o);
    fprintf(p,"\tr15: 0x%llx\n",r15_o);
    fprintf(p,"\trbp: 0x%llx\n",rbp_o);
    fclose(p);
    return 0;
}