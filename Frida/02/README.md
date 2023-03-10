我们在逆向过程中，经常碰到这样的场景。
分析某个算法的时候，算法强度很大，做了很多骚操作，让你看了反编译的代码就直接回收站处理。
面对高强度算法，这时候我们的选择一般是

1. 硬钢（适合大佬和时间充足的选手）
2. firda rpc 远程调用
3. xposed rpc 远程调用
4. unicorn 模拟执行

**后续陆续更新上面提到4种方法。
这篇文章主要介绍frida rpc调用的简单实现**

## 开始正文

更多frida rpc调用 
1. rpc 调用java类方法 （静态java方法）
2. rpc 调用native类方法 (静态native方法）
3. rpc 调用实例方法（对象的java方法和  对象的native方法）
4. rpc 调用so层函数

## 原理图
![正向流程](https://upload-images.jianshu.io/upload_images/25193798-3238bf36ab5bd7d1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![反向流程](https://upload-images.jianshu.io/upload_images/25193798-f8baab17d447a042.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## rpc远程调用效果图
在尝试过几种frida rpc的框架后，我找到了很简单的一种实现方法，从启动环境到架设到外网直接访问调用，整个过程不要两分钟。首先看下效果图。

![](https://upload-images.jianshu.io/upload_images/25193798-243d71c879052a54.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![返回数据](https://upload-images.jianshu.io/upload_images/25193798-f669422bf79c7afa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
这里做一个演示 调用一个加密方法 输入参数 字符串111
![](https://upload-images.jianshu.io/upload_images/25193798-11255144e193ec9d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![frida rpc返回数据 网页查看](https://upload-images.jianshu.io/upload_images/25193798-23bba2593d4af475.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

**这里也可以直接执行命令行 返回一样的结果**
![命令执行](https://upload-images.jianshu.io/upload_images/25193798-83d2f6491a1bad18.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![frida rpc传递多个参数](https://upload-images.jianshu.io/upload_images/25193798-5542c715910dfca4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在真机上 输入同样的参数 返回一样的结果
![](https://upload-images.jianshu.io/upload_images/25193798-7cd6baa8c8b5b4c3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
注意！
注意！
注意！
在自动化测试的场景下 可以写个脚本 打到批量测试的目的
比如像下面这样 写个脚本批量去跑

![image-20220217141849410](https://gitee.com/wangtietou/net_pic/raw/master/essay/wp/2022/02/0209/image-20220217141849410.png)




这里之所以说简单，是因为使用简单，除了安装环境麻烦之外，**在安装好环境后，每次使用的时候，基本不用做啥重复性操作，编写脚本，启动环境，就ojbk了**
--
**注意 这里演示环境是ubuntu 但是实测windows和ubuntu都是可以的。操作过程基本没什么区别**

## 适用场景
frida远程调用不仅可以调用 java层的函数，也可以调用so层的函数。
但是，frida并不太稳定。frida rpc也不太稳定。有一些比较坑爹的问题。
也并不太适用于工业级，比如frida并不适用于 在一些高并发，多线程的场景。

frida rpc 的前提条件就是，手机里面正在运行要注入的app, 更适合一些测试场景，比如协助一些渗透同事做一些数据的加解密。
或者一些规模比较小的工业级调用

## frida 远程调用demo
假设 我们遇到的apk是这样子的：
![](https://upload-images.jianshu.io/upload_images/25193798-41a98d85f4e7f677.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


可以看到上面的app 有2个加密按钮 我们这次要用frida 远程调用的 也是这两个功能函数
1. AES加密
2. 菜鸡加密
##目标函数
![frida 远程调用函数](https://upload-images.jianshu.io/upload_images/25193798-2a2fad6e5f582cb3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上图是要远程调用的目标函数 函数声明如下
```Java
public static byte[] aes_dec(String str_dec)
public String caiji_enc(String str_data, int n_conunt) 
```

# frida 远程调用实现
frida rpc 远程调用算法是我们经常用的一种算法调用的手段，也有现成的一些解决方案，甚至有人已经写出了专门的框架来节省我们的时间，让我们不至于手动去每次搭建环境都费时费力。

### 1. 普通青年实现frida rpc  
frida + flask + nps 
在这个方案里：

1. frida 实现调用具体实现
2. flask提供网页访问相关接口
3. nps内网穿透 直接把内网映射到公网，让接口可以在外网直接被访问。

这种方法可以是可以，可是比较麻烦，一套流程下来，可能20分钟往上了。
而且nps这东西想要实现内网穿透，要么你自己有服务器,要么还得搞谷歌云的服务器，费时费力。
这个方法后续会写篇文章介绍
### 2. 优秀青年实现frida rpc
arida + 花生壳
实现步骤：

1. 编写frida js注入 脚本 (耗时95秒)
2. 修改配置文件         （耗时10秒）
3. 启动环境                 （耗时10秒）
4. 直接访问 配置好的公网地址 (耗时5秒)
这篇文章主要讲利用 arida + 花生壳 实现frida rpc 

## 0 前提 关于arida框架 和 花生壳
### arida
git地址[[https://github.com/lateautumn4lin/arida](https://github.com/lateautumn4lin/arida)]
看雪文章[[https://bbs.pediy.com/thread-262643.htm]
缺点：

1. 安装比较麻烦。git文档比较感人，我按文档安装失败多次。
建议观看视频 一步步来 我老王在安装环境的时候 反反复复搞了2-3天 踩了很多坑 
视频演示：[https://space.bilibili.com/430241559]

2. 参数支持 string 和 int，事实上大部分时间也用不到别的类型。特殊类型我们直接在注入的脚本里写就好了 不影响使用。

优点：
1. 使用简单 一条命令就可以自动注入 会自动搭建http相关环境
1. 使用简单。瞬间完成内网穿透

缺点：
1. http访问需要交6块大洋（巨款）的认证费。

## 第一步 frida rpc 编写js注入脚本
要注入的方法如下
```Java
public static byte[] aes_dec(String str_dec)
public String caiji_enc(String str_data, int n_conunt) 
```
注入代码如下：
```
//rpc函数  aes加密 
function test_aes(str_data) 
{
  var str_ret = null;

  Java.perform(function () 
  {
    console.log("===========>aes");

    // 获取类
    var obj = Java.use('com.wangtietou.test_rpc_all.Test_Enc_Dec');

    //调用类方法 因为这里是静态方法 所以可以直接调用
    var bytes_ret = obj.aes_enc(str_data);

    //返回值是byte[] 这里转换成 string
    str_ret = toHexString(bytes_ret);
    console.log("aes result: " + str_ret);
  });
  return str_ret;
}

//rpc函数 菜鸡加密 arida支持int参数 但是要配置
function test_caiji(str_data, str_ret) 
{
  var str_ret = null;
	
  Java.perform(function () 
  {	
		console.log("===========>caiji");
	    //获取内存中已有对象 主动调用
	    Java.choose("com.wangtietou.test_rpc_all.Test_Enc_Dec", 
        {
          //匹配到对象执行的回调函数
          onMatch: function (instance) 
          {
            var n_cnt = parseInt(str_cnt);
            str_ret = instance.caiji_enc(str_data, n_cnt);
          },
          //搜索完成后执行的回调函数
          onComplete: function () 
          {
          }
        });

    console.log("caiji result: " + str_ret);
  });
  return str_ret;
}

//功能函数  byte[] 转hexString
function toHexString(arrBytes) {
    var str = "";
    for (var i = 0; i < arrBytes.length; i++) {
        var tmp;
        var num = arrBytes[i];
        if (num < 0) {
            tmp = (255 + num + 1).toString(16);
        } else {
            tmp = num.toString(16);
        }
        if (tmp.length == 1) {
            tmp = "0" + tmp;
        }
        str += tmp;
    }
    return str;
}

//要导出 被远程调用的接口 这里要写一个配置
rpc.exports = {
  testAes: test_aes, 
  testCaiji: test_caiji
}  
```
这里 把写好的文件 命名为wtt.js

## 第2步 frida rpc 修改配置文件
arida代码目录下有个config.py 如图所示
![远程调用配置](https://upload-images.jianshu.io/upload_images/25193798-9fc615da45277c14.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

修改配置信息：

![](https://gitee.com/wangtietou/net_pic/raw/master/essay/wp/2022/02/0209/image-20220217141641703.png)
这里修改下配置文件  可以同时注入多个app 
这里要注入几个app就写几个配置信息

```Python
#INJECTION_APPS 这里面只写要启动的app 其他建议注释掉
INJECTION_APPS = [
    {
        "name": "test",   #项目名 随便写
        "path": "wtt",	  #你自己的脚本名字
        "package_name": "com.wangtietou.test_rpc_all"  #包名
    }
]
```
修改好之后，把之前写好的注入脚本文件放到 apps目录就可以了
![rpc 配置文件](https://upload-images.jianshu.io/upload_images/25193798-09ae780fb366e331.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![ifrida rpc远程调用脚本](https://upload-images.jianshu.io/upload_images/25193798-8d83dd6333a08b94.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 第3步 启动环境
启动环境比较简单
1. 启动frida_server
2. 进入arida目录 启动conda 环境 
执行 uvicorn main:app --reload 命令
如图所示：
![](https://upload-images.jianshu.io/upload_images/25193798-146e27a7393ee2aa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![frida rpc远程调用启动](https://upload-images.jianshu.io/upload_images/25193798-dce27793725c36d8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
完成这步之后 如果不需要映射到公网的同学 到这里就可以了
直接访问 http://127.0.0.1:8000/docs
如图
![frida rpc内网](https://upload-images.jianshu.io/upload_images/25193798-67ecc21e3cf1aedb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![frida 远程调用网页访问](https://upload-images.jianshu.io/upload_images/25193798-a8cdb8bad082721e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/25193798-c31ea273f0fdc3b7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![算法调用返回结果](https://upload-images.jianshu.io/upload_images/25193798-aad0e8fa1ad06dcc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 第四步 访问花生壳配置的公网地址
花生壳配置比较简单
![frida rpc 花生壳](https://upload-images.jianshu.io/upload_images/25193798-50079a0520c3905a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![花生壳配置](https://upload-images.jianshu.io/upload_images/25193798-521a911d4ceb70a5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![花生壳 网址](https://upload-images.jianshu.io/upload_images/25193798-42358c3af4c756c8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
启动花生壳客户端
![](https://upload-images.jianshu.io/upload_images/25193798-ee27f751fd8ddc48.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这时候 就可以在公网访问搭建在我们内网的 frida rpc了 
![frida rpc公网](https://upload-images.jianshu.io/upload_images/25193798-f4db7ffd9ace4545.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![远程调用app](https://upload-images.jianshu.io/upload_images/25193798-a8cdb8bad082721e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![frida rpc 云控](https://upload-images.jianshu.io/upload_images/25193798-c31ea273f0fdc3b7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![frida rpc算法调用返回结果](https://upload-images.jianshu.io/upload_images/25193798-aad0e8fa1ad06dcc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

**bingo 大功告成**