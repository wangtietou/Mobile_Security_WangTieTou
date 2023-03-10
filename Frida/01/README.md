今天分享的是frida 延时hook的三种方法

**应用场景：**

很多时候 我们在工作或者学习过程中。

如果去分析一些带壳APP，或者一些做了防护的APP话。

用frida直接去注入hook一些类，经常会注入失败，提示 Error: java.lang.ClassNotFoundException: Didn't find class "xxxx"    找不到类之类的。就像下图一样。

![image](https://upload-images.jianshu.io/upload_images/25193798-86abc067bc489a90.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240) 

**原理分析：**

那明明要hook的类在apk代码中是真实存在的，为啥hook不到哪？造成这种情况的原因是什么哪？

原因是这样的，当apk做了一些保护手段或者加了壳, 这时候代码文件或者dex 一般是加密存储在一个文件里的。我们直接去hook的时候，外壳程序可能还没有把加密的代码文件或者dex解密，还没有进行加载。

那这个时间点，我们去hook，hook不到就很正常了。那要怎么去解决哪？

* * *

**解决方案：**

第一种方案  命令行不加 --no-pause

![image](https://upload-images.jianshu.io/upload_images/25193798-d1f1f228793cf546.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

 加--no-pause与不加 --no-pause的区别主要是 hook时机的早晚。 --no-pause是即时hook, 而不加--no-pause 这个参数的话。frida会拉起进程，停在加载主界面之前，这时候 应用会出现白屏状态，就像

恢复主线程运行的话，这里要手动用 %resume关键字。

这种方法的原理是， 在手动用%resume关键字恢复主线程运行之前，frida已经拉起了进程，外壳程序已经在启动，所以这里等个几秒用%resume关键字恢复，有一定几率是可以hook到的。

 ![image](https://upload-images.jianshu.io/upload_images/25193798-d310fe8722a8ca12.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

**第二种方案 setTimeout**

setTimeout是一个js的函数。主要作用是让函数等待一段时间后执行。
```
`//参数1 要执行函数名`
`//参数2 要执行函数等待的时间 毫秒数`
`setTimeout(func, 5000);`
```

注意
注意
注意
重要的话说三遍

setTimeout函数跟sleep不同。 sleep函数是阻塞的，而setTimeout函数不阻塞
```
//执行Hook方法
function test()
{
    Java.perform(function () 
    {
        console.log("====start hook====");

        var cls_MainActivity = Java.use("com.example.test_trace.MainActivity");
        cls_MainActivity.show_test.implementation = function () 
        {
            console.log("start show_test");
            return this.show_test();
        };
    });
}


setImmediate(function(){
    //延迟5秒调用Hook方法
    setTimeout(test, 5000);
    console.log("====start ====");
    #''' 假装后面有代码'''
});

```

这里我写了一个例子，setTimeout函数的调用在第20行，不阻塞的意思是

在脚本执行第20行的时候 setTimeout(test, 5000); 这句代码的时候

会继续执行第21行代码，也会继续执行后续的代码

但是test函数会在5秒后被调用。

如果这里20行的代码是 sleep(5000), 就会有不同的效果。代码会卡在第20行不动，5秒后才会执行21行。

这里通过 setTimeout 函数也达到了一个延时hook的效果。

所以上面那段代码执行的效果就是

![image](https://upload-images.jianshu.io/upload_images/25193798-c4fda83f6cf81b2b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

 这里的5000 可以根据实际情况进行调整。

**第3种方案 hook上游关联的函数**

假如要hook的目标函数是enc函数
这时enc的调用层级是  a-->b-->c-->enc()

伪代码
```
//调用层级  a-->b-->c-->enc
class A
{
    void a(String str)
	{
		B.b();   
	}
}    

class B
{
    void b()
    {
        C.c();
    }
}  

class C
{
    int c()
    {
        """
        ENC.enc()
    }
}  

class ENC
{
    String enc()
    {
    }
}  
```
如果这个时候我们直接去hook ENC类的 enc方法hook不到的话，可以hook enc上游的方法。

在上游函数的hook代码里面去写hook enc的代码。也能达到延时hook的目的。
