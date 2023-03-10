

## 跟着铁头干混淆2 ubuntu20.04编译ollvm 

写这篇文章之前，我安装了一波ollvm环境，中间遇到了很多坑爹问题。然后几乎看完了网上所有的相关

文章。

还把ollvm git上面的几乎所有编译报错的反馈都看了。

终于解决了遇到的大部分问题，然后有了这篇文章。

初始环境：

```
ubuntu20.04 
gcc 9.3.0 
g++ 9.3.0 
cmake 3.16.3
```

![image-20210707221647195](https://i0.hdslb.com/bfs/article/329f753bd52b4f2375a2f9f29e902f9907ee5785.png@942w_464h_progressive.webp)

---

docker方式编译ollvm分为4步

1. 下载ollvm 4.0源码 （啥，觉得老？初学者的话 4.0跟12.0对你来说区别不大）
2. 配置编译工具 
3. 修改ollvm源码
4. 编译 ollvm
5. 配置 ndk

## 1.下载ollvm 4.0源码

ollvm git地址： https://github.com/obfuscator-llvm/obfuscator

下载 ollvm 4.0代码

```shell
git clone -b llvm-4.0 --depth=1 https://github.com/obfuscator-llvm/obfuscator.git 
```

![ollvm下载 4.0](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702201853873.png)

这里  -b  llvm-4.0是选择 llvm-4.0的分支  

	--depth=1 表示只下载最后一次提交的版本

这样的话，项目文件就不会太大。毕竟github连接速度感人。

## 2.配置编译工具  

编译ollvm要用到的工具是

```
cmake
gcc
g++
```

### 1) 安装cmake

这里 cmake 直接安装最新版就可以了

```
sudo apt-get install cmake -y
```

![ollvm环境搭建 下载cmake](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703195158561.png)

### 2) 安装 gcc-8 g++-8 降低版本

这里大佬们的环境 gcc 和 g++的版本如果就是 8.x.x 

这里就可以直接下一步了

这里有坑的是 gcc g++

这里大佬们的环境 如果 gcc g++的版本是8.x.x 可以直接忽略这一步，看下一步了

铁头实测， gcc-9 g++-9 编译一定会失败。

![ollvm混淆搭建 gcc g++](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703202040551.png)

会有这样的报错信息：

```
make: *** [Makefile:152：all] Error 2
```

![ollvm 编译报错](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703194603927.png)

所以，这里安装编译工具的时候，要安装gcc-8 g++-8

```
sudo apt-get install gcc-8 g++-8 -y
```

![ollvm gcc g++](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703205726800.png)

安装完之后，配置一下优先级，好让我们调用gcc g++的时候，默认调用的是 gcc8 g++8

下面的命令可以配置软件的优先级，可以根据需要去选择默认的版本

```
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 8
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9
```

![ollvm编译环境配置](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703211108018.png)

### 3) gcc切换版本 默认gcc 8

```
sudo update-alternatives --config gcc  
```

![ollvm gcc 设置优先级](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703211613143.png)

![ollvm gcc降级](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703212654179.png)

### 4) g++切换版本 默认g++ 8

```
sudo update-alternatives --config g++
```

![ollvm g++ 设置优先级](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703212210243.png)

成功切换版本

![ollvm g++ 降级](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703212606275.png)

## 3.修改ollvm源码

不修改的话，会有这样的报错信息

```shell
bfuscator/include/llvm/ExecutionEngine/Orc/OrcRemoteTargetClient.h:696:26: error: could not convert ‘((llvm::orc::remote::OrcRemoteTargetClient*)this)->callBllvm::orc::remote::OrcRemoteTargetRPCAPI::ReadMem(Src, Size)’ from ‘Expected<vector<unsigned char,allocator>>’ to ‘Expected<vector<char,allocator>>’ return callB(Src, Size);
```

进入   你的ollvm目录/include/llvm/ExecutionEngine/Orc/OrcRemoteTargetClient.h

定位到第690行 把char 改成 uint_8

![ollvm源码修改](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703214140124.png)



## 4.编译 ollvm

好的 ，到这里前期环境就配置好了 可以直接编译了

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_INCLUDE_TESTS=OFF ../obfuscator/
make -j7
```



![ollvm编译](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703214947546.png)



![ollvm编译 线程](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703215138676.png)

编译快慢看配置  2-3个小时正常的

![ollvm编译好的](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210706005456665.png)

编译到后面，即使没有到 100%全部成功， 只要4个关键文件clang clang++ clang-4.0 clang-format 是在的

照样进行混淆 不用慌，小场面

## 5.配置 ndk

 配置ndk分为以下几步。

### 1.下载ndk

根据自己需要去选版本，我这里选的是 ndk-16b

ndk下载网址：https://developer.android.google.cn/ndk/downloads/

这个网址只有最新版的ndk，想下载之前的版本，可以手动点击下面的链接，去找自己想要的版本



![安卓ndk下载](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702224252671.png)



![安卓ndk选择平台版本](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210702224825629.png)

​	这里多说一句，如果嫌下载速度慢，除了花钱升级宽带，还可以复制链接去迅雷下。

​	这里我已经下载并解压到了本地  

![ollvm编译 ndk配置](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703155204978.png)

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

![ndk编辑环境变量](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703164128962.png)

最后执行命令，使配置文件生效

```
source ~/.bashrc
```

![更新环境变量 ndk](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703164419699.png)

### 3.复制编译好的4个 clang 文件到ndk目录

好，这里大佬们已经下载完ndk了。这一步是把之前 ollvm编译好的文件复制到ndk目录

这一步比较简单， 直接复制粘贴就可。cv工程师的看家本领。

把olvm刚编译好的 clang clang-4.0 clang++ clang-format 文件

粘贴到ndk目录  

![image-20210707215018515](https://i0.hdslb.com/bfs/article/67bb48aeb1dfd2b4224a8d7ad1d40aee1fbb1b9e.png@942w_518h_progressive.webp)

粘贴到  

```
 你自己的ndk目录/toolchains/llvm/prebuilt/linux-x86_64/bin
```

![删除原有的clang文件](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703160931810.png)

粘贴4个文件

![image-20210707215406543](https://i0.hdslb.com/bfs/article/376f5437bac0bdaaeac15dfd1dd41459af1e5c35.png@942w_624h_progressive.webp)



### 4.复制build目录的 3个头文件到ndk目录

同时，为了避免后续的编译错误 

就像下图，会报错找不到头文件

```
fatal error 'Stddef.h' file not found
fatal error 'Stdarg.h' file not found
fatal error '__stddef_max_align_t.h' file not found
```

![ollvm 编译错误 头文件](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210704145539397.png)

在build目录搜索3个文件 然后继续发挥大佬们的cv神功。

粘贴到 上面报错的路径 就ok了 

这个路径是你ndk目录下的 

```
sources/cxx-stl/system/include/
```

找到刚刚的build目录 也就是编译好文件的输出路径

![image-20210707215659398](https://i0.hdslb.com/bfs/article/3d273ca593f52e48b652aef94c62242bad771fc8.png@942w_485h_progressive.webp)

搜索stdarg stddef  

![image-20210707220030404](https://i0.hdslb.com/bfs/article/36998401ba278554da181693a73bec483186ecb7.png@942w_218h_progressive.webp)

![img](https://i0.hdslb.com/bfs/article/abb9947f556ef7877ece6d2ce49da41a3c0ed236.png@942w_302h_progressive.webp)

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

在jni同级目录 打开命令行 执行

```
ndk-build
```

![ollvm编译so](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703181547131.png)

## 混淆效果

未混淆前流程图：

![ollvm混淆so文件效果](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210629192742505.png)

混淆后流程图：

![ollvm混淆后的流程图](https://gitee.com/wangtietou/net_pic/raw/master/essay/ollvm/2/image-20210703182100982.png)

成功混淆

