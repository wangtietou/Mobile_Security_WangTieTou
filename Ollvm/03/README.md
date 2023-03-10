## 跟着铁头干混淆3 ubuntu下用docker编译ollvm(保证成功)

*OLLVM*(Obfuscator-LLVM) 是一套开源的,基于llvm的混淆工具。

国内的很多加固厂商，很多都使用了ollvm对代码进行混淆。

想要学习 ollvm去混淆，最好搭建一个环境自己写一些demo, 就像做渗透的自己搞个靶场去练习，也能学的更快。

---

在编译 ollvm的时候，有时候会因为一些，系统版本，编译器版本，cmake版本，或者另外的一些玄学的原因编译失败。

编译成功的人都是类似的，一次性成功。

编译失败，各自有自己的报错信息。

如果大佬们已经对自己编译ollvm失去了信心，累觉不爱。

这时候还是可以挣扎下的。

可能生活辜负了你，但是既然你看到了这篇文章，我，口碑好，靠得住，说你成功你就能成功

用这种方式去编译，基本上是可以保证编译通过的。

不管你机器上的，gcc ,g++， cmake是啥版本，都不重要。



**因为，这一次的编译，根本就，不依赖任何你自己电脑上的编译环境。**



是用docker镜像编译。

惊不惊喜，意不意外？

## docker方式编译ollvm步骤

1. 下载ollvm 4.0源码 （啥，觉得老？初学者的话 4.0跟12.0对你来说区别不大）

2. 安装docker编译环境

3. 编译 ollvm

4. 配置 ndk

   

## 1.下载ollvm 4.0源码

ollvm git地址： https://github.com/obfuscator-llvm/obfuscator

下载 ollvm 4.0代码

```shell
git clone -b llvm-4.0 --depth=1 https://github.com/obfuscator-llvm/obfuscator.git 
```

![image-20210702201853873](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702201853873.png)

这里  -b  llvm-4.0是选择 llvm-4.0的分支  

​		 --depth=1 表示只下载最后一次提交的版本

这样的话，项目文件就不会太大。毕竟github连接速度感人。



## 2.安装docker编译环境

这里安装docker编译环境 首先要下载docker(已经安装过就不用了)

```shell
sudo apt install docker.io				 
sudo docker pull nickdiego/ollvm-build   
```

安装docker

![image-20210701231550404](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210701231550404.png)

安装编译ollvm的docker环境

![image-20210701231650054](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210701231650054.png)

## 3.编译ollvm

编译这里 本来是这样用的

![image-20210702194634261](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702194634261.png)

 为了节省大佬们的时间， docker编译环境的作者简化了上面的命令

 还专门写了个脚本

 惊不惊喜，意不意外

 编译脚本下载：

```shell
git clone --depth=1 https://github.com/nickdiego/docker-ollvm
```

![image-20210702195406366](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702195406366.png)

使用：

```
sudo ./ollvm-build.sh ollvm源码目录
```

这里我自己的ollvm源码目录是 /home/wtt/env/ollvm/src/obfuscator/

所以我这里就应该执行

```shell
sudo ./ollvm-build.sh /home/wtt/env/ollvm/src/obfuscator/
```

如果你直接执行，出现了这种错误的话

![image-20210703182631462](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703182631462.png)

报错信息：

```
CMake Error at cmake/modules/AddLLVM.cmake:1163 (add_custom_target):
  add_custom_target cannot create target "check-llvm-bindings-ocaml" because
  another target with the same name already exists.  The existing target is a
  custom target created in source directory "/ollvm/src/test".  See
  documentation for policy CMP0002 for more details.
Call Stack (most recent call first):
  cmake/modules/AddLLVM.cmake:1226 (add_lit_target)
  test/CMakeLists.txt:150 (add_lit_testsuites)
```

这里我也遇到了这种错误，为了修正错误 我阅读了 ollvm-build.sh的源码

害，本来想着一键 简单高效省心，到头来还得自己上改脚本。

这里加了一句代码。 在150行  加入

```
DOCKER_CMD+=" -DLLVM_INCLUDE_TESTS=OFF"
```

![image-20210702205936060](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702205936060.png)

加入这行代码就大功告成了

![image-20210702204310084](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702204310084.png)

这里不用 执行make -j7 这种命令，脚本里面已经自动开始给你编译了

而且，编译依赖的各种环境，用的不是你本机的，那种会干啥啥不行，报错第一名的环境。

这里，用的编译环境是，靠得住的docker环境，大佬给安排好的环境。

![image-20210702220609025](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702220609025.png)

![image-20210703154654349](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703154654349.png)

## 4.配置 ndk

这里，上面那个脚本的作者，其实给了一个解决方案

![image-20210702223521101](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702223521101.png)

但是我用了下，这次没有上一次靠谱。

本来以为会把编译好的 clang文件直接替换到ndk里面，然而并没有。

所以，这里不推介使用这个脚本。

这里推介，大佬们自己动手，丰衣足食。

配置ndk分为以下几步。

### 1.下载ndk

根据自己需要去选版本，我这里选的是 ndk-16b

ndk下载网址：https://developer.android.google.cn/ndk/downloads/

这个网址只有最新版的ndk，想下载之前的版本，可以手动点击下面的链接，去找自己想要的版本

![image-20210702224252671](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702224252671.png)



![image-20210702224825629](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702224825629.png)

​	这里多说一句，如果嫌下载速度慢，除了花钱升级宽带，还可以复制链接去迅雷下。

​	这里我已经下载并解压到了本地  

![image-20210703155204978](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703155204978.png)

### 2.配置ndk环境变量

执行命令，打开配置文件

```
gedit ~/.bashrc
```

把下面这两行粘贴到文件末尾， 注意，替换路径成自己下载的ndk路径

```
export NDK_HOME=/home/wtt/env/android/ndk/android-ndk-r16b/
export PATH=$NDK_HOME:$PATH
```

![image-20210703164128962](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703164128962.png)

最后执行命令，使配置文件生效

```
source ~/.bashrc
```

![image-20210703164419699](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703164419699.png)

### 3.复制编译好的4个 clang 文件到ndk目录

好，这里大佬们已经下载完ndk了。这一步是把之前 ollvm编译好的文件复制到ndk目录

这一步比较简单， 直接复制粘贴就可。cv工程师的看家本领。

把olvm刚编译好的 clang clang-4.0 clang++ clang-format 文件

粘贴到ndk目录  

![image-20210703155705445](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703155705445.png)

粘贴到  

```
 你自己的ndk目录/toolchains/llvm/prebuilt/linux-x86_64/bin
```

![image-20210703160931810](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703160931810.png)

![image-20210703161123186](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703161123186.png)





### 4.复制build目录的 3个头文件到ndk目录

同时，为了避免后续的编译错误 

就像下图，会报错找不到头文件

```
fatal error 'Stddef.h' file not found
fatal error 'Stdarg.h' file not found
fatal error '__stddef_max_align_t.h' file not found
```

![image-20210704145539397](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210704145539397.png)

在build目录搜索3个文件 然后继续发挥大佬们的cv神功。

粘贴到 上面报错的路径 就ok了 

这个路径是你ndk目录下的 

```
sources/cxx-stl/system/include/
```

找到刚刚的build目录 也就是编译好文件的输出路径

![image-20210703173558875](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703173559944.png)

![image-20210703175049421](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703175049421.png)

![image-20210703175626716](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703175626716.png)

至此，环境部分，基本完成， 

## 大吉大利 晚上吃鸡

这个时候，大佬们可以尝试编译一波了

新建jni目录  目录下新建3个文件

Android.mk  

```makefile
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := wtt
LOCAL_SRC_FILES := test.cpp
include $(BUILD_EXECUTABLE)
```

Application.mk  

```makefile
APP_ABI := armeabi armeabi-v7a arm64-v8a
APP_PIE:= true
APP_CPPFLAGS := -frtti  -std=c++11 -mllvm -fla -mllvm -bcf -mllvm -sub 
```

test.cpp

```c++
#include <cstdio>

int main(int n_argc, char** argv)
{
	int n_num = n_argc * 2;
	//scanf("%2d", &n_num);

	if (20 == n_num)
	{
		puts("20");
	}
	if(10 == n_num)
	{
	  	puts("10");
	}
	if(2 == n_num)
	{
	  	puts("2");
	}

	puts("error");

	return -1;
}
```

![image-20210703172006830](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703172006830.png)

在jni同级目录 打开命令行 执行

```
ndk-build
```

![image-20210703181547131](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703181547131.png)

## 混淆效果

未混淆前流程图：

![image-20210629192742505](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210629192742505.png)

混淆后流程图：

![image-20210703182100982](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703182100982.png)

成功混淆

