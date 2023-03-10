
#include <sys/ptrace.h>
#include <sys/time.h>
#include <sys/types.h>
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>


#define MAX_LENGTH 1024

int check_ptrace();
int get_tarce_pid();
int check_debug_port();
int check_debug_time();

extern "C"
JNIEXPORT jstring JNICALL
Java_com_wangtietou_debug_1test_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

int check_ptrace()
{
    // 被调试返回-1，正常运行返回0
    int n_ret = ptrace(PTRACE_TRACEME, 0, 0, 0);
    if(-1 == n_ret)
    {
        printf("阿偶，进程正在被调试\n");
        return -1;
    }

    printf("没被调试 返回值为:%d\n",n_ret);
    return 0;
}

//获取tracePid
int get_tarce_pid()
{
    //初始化缓冲区变量和文件指针
    char c_buf_line[MAX_LENGTH] = {0};
    char c_path[MAX_LENGTH] = {0};
    FILE* fp = 0;

    //初始化n_trace_pid 获取当前进程id
    int n_pid = getpid();
    int n_trace_pid = 0;

    //拼凑路径 读取当前进程的status
    sprintf(c_path, "/proc/%d/status", n_pid);
    fp = fopen(c_path, "r");

    //打不开文件就报错
    if (fp == NULL)
    {
        return -1;
    }

    //读取文件 按行读取 存入缓冲区
    while (fgets(c_buf_line, MAX_LENGTH, fp))
    {
        //如果没有搜索到TracerPid 继续循环
        if (0 == strstr(c_buf_line, "TracerPid"))
        {
            memset(c_buf_line, 0, MAX_LENGTH);
            continue;
        }

        //初始化变量
        char *p_ch = c_buf_line;
        char c_buf_num[MAX_LENGTH] = {0};

        //把当前文本行 包含的数字字符串 转成数字
        for (int n_idx = 0; *p_ch != '\0'; p_ch++)
        {
            //比较当前字符的ascii码  看看是不是数字
            if (*p_ch >= 48 && *p_ch <= 57)
            {
                c_buf_num[n_idx] = *p_ch;
                n_idx++;
            }
        }
        n_trace_pid = atoi(c_buf_num);
        break;
    }

    fclose(fp);
    return n_trace_pid;
}

//同时查找多个特征端口  返回找到的特征端口数量
#define NUM_STR_ARY(X) (sizeof(X) / sizeof(char*))
int check_debug_port()
{
    //特征端口字符串数组  0x5D8A是23946的十六进制 69a2是27042十六进制
    //这里为了提高精确度 加个 :
    char* p_strPort_ary[] = {":5D8A", ":69A2"};
    int n_port_num = NUM_STR_ARY(p_strPort_ary);  //特征端口数量

    //找到特征端口数量 返回值
    int n_find_num = 0;

    //初始化文件指针  路径  和缓冲区
    FILE* fp = 0;
    char c_line_buf[MAX_LENGTH] = {0};
    char* p_str_tcp = "/proc/net/tcp";

    fp = fopen(p_str_tcp, "r");
    if(NULL == fp )
    {
        return -1;
    }

    //读取文件 看当前文件包含了几个特征端口号
    while(fgets(c_line_buf, MAX_LENGTH - 1, fp))
    {
        for (int i = 0; i < n_port_num; ++i)
        {
            //如果从当前文本行 找到特定端口号
            char* p_line = p_strPort_ary[i];
            if(NULL != strstr(c_line_buf, p_line))
            {
                n_find_num++;
            }
        }
        memset(c_line_buf, 0, MAX_LENGTH);
    }

    fclose(fp);
    //返回找到的特征端口数量
    return n_find_num;
}

#define NUM_DEBUG 3
int check_debug_time ()
{
    //初始化时间变量
    time_t t_start = 0;
    time_t t_end = 0;

    //获取开始时间值  返回值是一个秒数 long型 从1970年至今的秒数
    time(&t_start);

    //假设这里就是关键逻辑 登录模块 关键算法之类的
    printf("假装这里有登录模块逻辑");
    printf("假装这里有算法逻辑");

    //获取结束时间值
    time(&t_end);
    if (t_end - t_start > NUM_DEBUG)
    {
        return 0;
    }

    return -1;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_wangtietou_debug_1test_MainActivity_test_1debug(JNIEnv *env, jobject thiz) {
    // TODO: implement test_debug()

    int n_ret = get_tarce_pid();
    printf("%d", n_ret);

    n_ret = check_ptrace();
    printf("%d", n_ret);

    n_ret = check_debug_port();
    printf("%d", n_ret);

    n_ret = check_debug_time();
    printf("%d", n_ret);

    std::string hello = "Hello from debug";
    return env->NewStringUTF(hello.c_str());
}