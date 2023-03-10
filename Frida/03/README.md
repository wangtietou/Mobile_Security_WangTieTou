

# frida版本管理 一个环境安装多个frida

### 写文章初衷：

网上关于frida安装的文章一搜一箩筐。

那我为什么要再写一篇？

我想保持周更，水一个简单的视频，所以就有了这一篇文章和配套视频

安装frida 两行命令就搞定了，写这个实在是没有啥技术含量。

但是，想安装多个不同版本的frida怎么搞？

毕竟不同的场合，不同的安卓版本，要使用不同版本的frida。毕竟frida会玄学出一些问题，你反复去找解决方案，然后发现换个版本就解决了。这个时候不知道你是咋想的，反正我是寄一个刀片，让大胡子刮了他的大胡子，让他好好写代码。



---

### 1.环境准备 安装miniconda

#### 1) ubuntu 安装miniconda 

关于安装多个版本，我看到有的大佬用pyenv，pyenv我之前用过，有些坑坑到我放弃了。

我这里用miniconda。

miniconda是一个虚拟环境，在虚拟环境里安装的软件是虚拟环境私有的，不会污染主环境。

miniconda下载地址：[https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/](https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/)
翻到页面下面 选择这个版本：

![ubuntu下载miniconda](https://upload-images.jianshu.io/upload_images/25193798-c63b68697a8d5fcd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)下载下来 进入当前目录 执行安装文件。

```cmd
sh Miniconda3-py38_4.9.2-Linux-x86_64.sh
```
![ubuntu安装 miniconda](https://upload-images.jianshu.io/upload_images/25193798-6f8d67c76612e5dc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
按回车键继续安装
![image-20210623214321428](https://upload-images.jianshu.io/upload_images/25193798-c786ed379fb06de0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

阅读完条款 选择 yes 接受软件声明

![ubuntu安装conda接受协议](https://upload-images.jianshu.io/upload_images/25193798-7290787543448b22.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

确认安装路径这里直接回车

![miniconda确认安装路径](https://upload-images.jianshu.io/upload_images/25193798-3259a81764676490.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

conda init 这里也输入 yes

![conda init yes](https://upload-images.jianshu.io/upload_images/25193798-353c2748015665d4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

安装完成

![ubuntu安装conda完成](https://upload-images.jianshu.io/upload_images/25193798-b0e7c0b3493e959f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这时候关掉当前的命令行 打开一个新的命令行
查看是否安装成功

```cmd
conda --version
```
![conda 查看版本](https://upload-images.jianshu.io/upload_images/25193798-9bcedf976140d576.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)安装成功
这里安装完成后  打开新的cmd窗口 在用户名之前 总是有个 （base)阴魂不散
这里是默认进入了 conda的环境

![conda 默认进入base](https://upload-images.jianshu.io/upload_images/25193798-46e0b68ce15efe04.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如果想关闭 直接执行一行命令 然后重新打开命令行就好

```cmd
conda config --set auto_activate_base false
```
![conda设置不进入base](https://upload-images.jianshu.io/upload_images/25193798-bef162d4f437e592.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
执行命令  重新打开命令行后 恢复正常

![conda ubutnu](https://upload-images.jianshu.io/upload_images/25193798-093eff30903d8d1c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2) 配置conda 软件源

这里的专业术语是 channels  意思是频道，其实通俗点讲就是下载软件的网址，我这里直接叫软件源
这里设置成北京外国语学院的软件源  因为用清华源的人实在是太多了  让那些用清华源的内卷去吧 我们猥琐发育就可
复制粘贴一波 执行下面的命令就好

```shell
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/cloud/bioconda/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/cloud/conda-forge/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/pkgs/main/
```

### 2.安装第一个frida 和 frida-tools

第一个frida的版本我选择 12.8.0 因为这个版本被一些大佬评价稳如老狗

所以先拿frida 12.8.0 开刀

以下是要安装的frida和 frida-tools版本

```
frida 12.8.0
frida-tools 5.3.0
```

#### 步骤1）conda创建新的python环境 >= 3.7

在frida官网关于安装的描述中，表示强烈推介安装最新的python 3.x版本，这里就表示推介安装最新的，目前最新的是3.9，在一些文章和我的实测中，这里建议安装 >= 3.7的版本

![frida安装](https://upload-images.jianshu.io/upload_images/25193798-ed64b465fef4e781.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这里一行命令搞定 

命令格式：conda create -n 环境名 python=python版本

这里我执行

```
conda create -n wtt_firda_1280 python=3.8
```

下图是安装过程   

![conda创建环境安装frida](https://upload-images.jianshu.io/upload_images/25193798-d8053e7cdfdc233c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![虚拟环境软件包](https://upload-images.jianshu.io/upload_images/25193798-977f1908dde0fdb9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

提示安装软件包的时候  输入Y即可

![image-20210619131151396](https://upload-images.jianshu.io/upload_images/25193798-9dfa0158083aa1a4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image-20210619131215530](https://upload-images.jianshu.io/upload_images/25193798-de3a4d1dadde1c46.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 步骤2) 安装frida 以及 frida-tools

在conda环境软件包  首选语法是 conda install 软件包=版本号 

但是这里有些软件包的版本号在conda软件源是没有的

我们这里可以用 pip安装

```shell
conda activate wtt_firda_1280   		  //激活conda环境
python -m pip install frida==12.8.0 	  //不要直接用pip安装 
python -m pip install frida-tools==5.3.0  //不要直接用pip安装 
```

安装的时候 注意 ，一定要激活虚拟环境，用户名前面看到 （虚拟环境名）就表示已经在虚拟环境里面了

![frida安装使用](https://upload-images.jianshu.io/upload_images/25193798-cc8cb250322d95f5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![安装frida 12.8.0](https://upload-images.jianshu.io/upload_images/25193798-25a11b53bebedd33.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![pip安装frida](https://upload-images.jianshu.io/upload_images/25193798-fb7bd77cb6eab841.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这里我的其他conda虚拟环境已经安装过这个版本的frida, 所以这里直接读了一些缓存之类的，安装变的很快，正常情况下，第一次安装花个20分钟也是比较常见的。

#### 步骤3 下载frida-server

frida server下载网址 ：https://github.com/frida/frida/releases

frida server12.8.0 下载网址https://github.com/frida/frida/releases/tag/12.8.0

![frida安装记录 frIda-server](https://upload-images.jianshu.io/upload_images/25193798-024c0cd3ebfef242.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



![frida与安卓对应版本](https://upload-images.jianshu.io/upload_images/25193798-0c02fdcd09a1d35a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这里可以执行命令查看架构去选择对应的frida-server

```shell
getprop ro.product.cpu.abi
```

就像下图 选择x86就可以了

![image-20210620021140832](https://upload-images.jianshu.io/upload_images/25193798-cb090016f9ad38b0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida手机安装](https://upload-images.jianshu.io/upload_images/25193798-c2706884e41e9cc5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)





下载解压 push到手机的 /data/local/tmp 目录 文件改名成frida_server_1280

```shell
wtt@ubuntu:frida-server$ adb push frida_server_1280 /data/local/tmp
frida_server_1280: 1 file pushed. 15.4 MB/s (38545744 bytes in 2.395s)
wtt@ubuntu:frida-server$ 
wtt@ubuntu:frida-server$ adb shell
riva:/ $ 
riva:/ $ cd /data/local/tmp
riva:/data/local/tmp $ su
riva:/data/local/tmp # 
riva:/data/local/tmp # chmod 777 frida_server_1280
riva:/data/local/tmp # 
riva:/data/local/tmp # ./frida_server_1280

```



![frida安装使用](https://upload-images.jianshu.io/upload_images/25193798-5e6d6bd39d871c06.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
conda activate wtt_frida_1280
frida-ps -U
```



![frida安装linux](https://upload-images.jianshu.io/upload_images/25193798-a105f1f44a6c4073.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![ubuntu安装frida](https://upload-images.jianshu.io/upload_images/25193798-8d71871eb64956dd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3.安装第二个frida 和 frida-tools

这里安装第二个流程基本上和第一个是一样的  也就是创建的虚拟环境不同 安装的frida版本不同而已

#### 步骤1）conda创建新的python环境 >= 3.7

命令格式：conda create -n 环境名 python=python版本

这里我执行

```
conda create -n wtt_firda_new python=3.7
```

上面的命令我换了虚拟环境的名字，毕竟虚拟环境是不能重名的，python版本换不换都行，我这里换成了3.7

![miniconda环境 frida多版本](https://upload-images.jianshu.io/upload_images/25193798-3a88c14dacad4c02.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上图是创建环境的全过程 跟安装第一个基本没有啥区别

#### 步骤2）安装frida 以及frida-tools

安装最新版的frida 和 frida-tools 都不用2条命令 

一行命令就可以了

```shell
conda activate wtt_firda_1280   		  //激活conda环境
python -m pip install frida-tools		  //会自动安装最新的frida 和frida-tools
```

![frida安装两个版本号](https://upload-images.jianshu.io/upload_images/25193798-98f37105a7521135.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 步骤3）下载frida-server

![下载frida-server最新版](https://upload-images.jianshu.io/upload_images/25193798-05cab7a0369a8526.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

网址：https://github.com/frida/frida/releases

![ubuntu安装frida](https://upload-images.jianshu.io/upload_images/25193798-cbffc20acda4831e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida 安卓 模拟器对应版本](https://upload-images.jianshu.io/upload_images/25193798-9c32066f10f71746.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

目前因为大家的cpu都是64位，所以一般选 arm64 

这里我选择的是 frida-server-14.2.18-android-arm64.xz

![image-20210619154218503](https://upload-images.jianshu.io/upload_images/25193798-44c6f94e9024ab5a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida server下载 迅雷](https://upload-images.jianshu.io/upload_images/25193798-5e74b77939d210cb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

下载慢的话，可以直接复制地址去迅雷下载

![ubuntu安装frida](https://upload-images.jianshu.io/upload_images/25193798-0c2de2e652a1ce81.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image-20210619155132223](https://upload-images.jianshu.io/upload_images/25193798-50446d61350e7d4c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida安装linux](https://upload-images.jianshu.io/upload_images/25193798-972eafa2a6abcf11.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

执行frida

```
conda activate wtt_firda_new
frida-ps -U
```

![frida-ps -U 查看进程](https://upload-images.jianshu.io/upload_images/25193798-abcf8f9d99d3aeb4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 4.安装第N个frida 和 frida-tools 和上面一样

上面我们创建了不同的虚拟环境  安装了2个不同版本的frida 

后续安装更多不同版本的frida 过程也是一样的，创建新的conda虚拟环境 安装frida就可以了

用的时候激活不同的虚拟环境，调用虚拟环境里的frida

![frida --version查看版本](https://upload-images.jianshu.io/upload_images/25193798-38929ba39afb0aad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida安装多个版本](https://upload-images.jianshu.io/upload_images/25193798-9c21ebf12139dc38.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

而且对我们主机的环境是没有任何影响的  因为虚拟环境安装的软件是虚拟环境私有的

对主机的环境并没有影响

![主机的frida没有污染](https://upload-images.jianshu.io/upload_images/25193798-e9fd06a2f830f582.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在主环境执行 frida 提示命令未找到  因为上面两个版本的frida并没有安装到主环境中

而是安装到了不同的虚拟环境中，对主环境没有任何污染 影响

上面的方法不仅可以安装多个不同版本的frida 也可以同时安装不同版本的其他软件

十分便捷
完结撒花
