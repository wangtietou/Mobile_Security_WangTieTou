## 蓝牙安全 1)  从入门到放弃

### 1.基本概念



#### 蓝牙是个啥：

蓝牙是一个无线通信协议，让传输数据从有线到无线，让通信更加便捷。

其他无线协议：Wifi  ZigBee。

<img src="https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210926195838410.png" alt="image-20210926195838410" style="zoom: 50%;" />

#### 蓝牙名字由来

![153942642_3_20190211091550742](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/153942642_3_20190211091550742.jpg)

很久很久以前，一个维京海盗狠人，丹麦的国王(*Harald Blåtand* Gormsen)，可能像图上一样又壮又狠。

这个海贼王大佬统一了散乱的北欧，海贼王大佬的绰号是 蓝牙。

有这个绰号是因为， 这个狠人有一颗坏牙，很多人说是吃蓝莓吃成蓝色的了，大家就喊他蓝牙。

很多年后，巨头爱立信搞了一个无线协议，就用这个海贼王的绰号做了协议的名字。也可以看出爱立信当时野心不小，蛋糕就那么大，他想都吃了。

放到中国，可能就叫 秦牙，不，叫嬴政了。

---

#### 官网和官方文档

https://www.bluetooth.com

https://www.bluetooth.com/specifications/specs/core-specification/

![image-20210926230959654](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210926230959654.png)

打开官方文档是酱紫的

![image-20210927180721644](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210927180721644.png)

英语只有3.5级的我，对英语有密集恐惧症，害 难受



#### 相关版本

| 蓝牙版本    | 发布时间 |
|  ----  | ----  |
| 蓝牙5.3     | 2021.07.13 |
| 蓝牙5.2     | 2019.12.31 |
| 蓝牙5.1     | 2019.01.21 |
| 蓝牙5.0     | 2016.12.16 |
| 蓝牙4.2     | 2014.12.04 |
| 蓝牙4.1     | 2013.12.06 |
| **蓝牙4.0+BLE** | 2010.06.30 |
| 蓝牙3.0+HS  | 2009.04.21 |
| 蓝牙2.1+EDR | 2007.07.26 |
| 蓝牙2.0+EDR | 2004.11.09 |
| 蓝牙1.2     | 2003.11.05 |
| 蓝牙1.1     | 2001.02.22 |



今年7月13号  蓝牙已经发布了 5.3版本。特性我还没看，毕竟4.0我都没有搞清楚。

> ≥ 4.0 开始有了低功耗蓝牙    (Bluetooth Low Energy)

> < 4.0 的被称为经典蓝牙 	   (Classic Bluetooth)         



学不动了 太难了



#### 蓝牙分类 

#### ![单模蓝牙 双模蓝牙](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20210926222245.jpg)

Bluetooth ：经典蓝牙  （相关设备：蓝牙耳机）

Bluetooth Smart ：单模蓝牙 也就是 低功耗蓝牙 （相关设备：蓝牙锁）

Bluetooth Smart Ready：双模蓝牙 同时支持  经典蓝牙和低功耗蓝牙  （相关设备：手机)



#### 低功耗蓝牙 经典蓝牙区别

![image-20210926212817540](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210926212817540.png)

（表格来自某基百科，我简单改了改）

**简单总结。**

低功耗蓝牙：耗电量小，传输距离远， 速度快，适合数据量小 的传输。   		       （蓝牙锁，蓝牙灯泡）

经典蓝牙：    耗电量大，传输距离近，速度一般，适合数据量大的传输。				（蓝牙耳机 蓝牙音箱）



#### 基本用途

主要分为经典蓝牙 和  低功耗蓝牙

各自用途如下，左边是经典蓝牙，右边是低功耗蓝牙。

![image-20210926202942632](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210926202942632.png)







### 2.蓝牙安全威胁

#### 海量cve:

BlueBorne，Bleedingbit，Fixed Coordinate Invalid Curve Attack，SweynTooth，KNOB，KNOB，

Pairing Method Confusion，BlueFrag，Spectra，BLURtooth，BLESA，BleedingTooth，BlueMirror，

InjectaBLE，BrakTooth

![image-20210927195552597](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20210927195552597.png)

完整链接：

https://github.com/engn33r/awesome-bluetooth-security/



#### PIN码爆破：

pin码  （Personal Identification Number） 就是蓝牙配对的时候，弹窗让你输入的那个身份验证码。

蓝牙在认证配对过程中，会生成一个 Link key （链路密钥）。

Link key 用于蓝牙之间的身份认证 鉴权，也是 Encryption Key （加密密钥）的主要参数。

生成 Link key 的其他参数很容易被直接获取，Pin码是最后一道防护。

抓包蓝牙设备配对的数据包，然后相关软件爆破pin码后，蓝牙的整个加密认证体系就凉凉了。

![image-20220318134054068](https://gitee.com/wangtietou/net_pic/raw/master/essay/audition/life/image-20220318134054068.png)

#### 身份伪造：

每一个蓝牙都有一个唯一的设备地址 ，蓝牙mac地址。

攻击者可以修改自身的设备地址，来伪造身份。

或者扫描附近的蓝牙设备，把自己信息修改的和另一个设备一模一样，完成身份克隆。

这里一般和别的攻击配合使用。比如 **中继攻击**  和 **鉴权Dos攻击**。

![image-20211010183612429](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20211010183612429.png)



#### 中继攻击（Relay Attack）：

蓝牙传输范围是有限的。假设这里最远是100米。 你的车在500米开外。

现在很多车都安装了蓝牙数字钥匙，一般你的手机靠近车一定距离，车端蓝牙连接到你手机端蓝牙，车就会自动解锁。（很多车都有这个功能）



这时候我搞几个蓝牙信号增幅的设备，这几个设备啥也不干，就当搬运工，可以理解成基站类似的东西，一个设备放你身边，一个被法外狂徒带着，在你车旁边，你的车感受到了被搬运工设备传过来的蓝牙电波，还以为你已经靠近了车。

这时候法外狂徒直接拉车门就能把车开走了。

当前大多数设备都没有对这个问题做出防范。

油管上的蓝牙中继视频。是一个美女黑阔大佬录的，用蓝牙中继解锁了一个蓝牙智能锁。

![image-20211010163057144](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20211010163057144.png)

https://www.youtube.com/watch?v=3e4DBk5BKLg&t=239s 

美女又飒技术又好  推介去看看

![image-20211010170758216](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20211010170758216.png)



#### 拒绝服务攻击 （Denial Of Service Attack ） 

##### l2ping Dos  

用l2ping之类的工具对设备进行 Dos 连接，类似于ping 攻击，设备如果没有做安全防护，直接被打瘫，打到设备没电也是正常的。



##### 鉴权Dos攻击 

每次鉴权失败是有间隔时间的，就解锁手机，连续输错几次，发现要等得时间越来越长，蓝牙也是这样的。

修改设备Mac地址，伪装成发起方尝试连接目标设备，故意失败多次，间隔时间不断增大，达到一个最大值。

这时候，你伪装的那个设备，正主过来了，都不能连接了。



##### obex 文件Dos

利用 OBEX 协议, 大批量给目标设备发送文件，目标设备被大量请求打到瘫痪，啥事都不能干了。正常设备过来连也连不了了。



#### 中间人攻击

中间人攻击比较骚，同时欺骗两个设备，让设备A B 以为他们在正常通讯。

实际上，中间人设备在这里当搬运工，在这里偷窥双方传递了啥消息。

当然，中间人设备也可以不止是搬运工，他也可以修改双方传输的数据。

![image-20211001000526326](https://gitee.com/wangtietou/net_pic/raw/master/essay/bluetooth/image-20211001000526326.png)





#### 重放攻击：

跟很多协议的重放类似，没啥说的。



#### fuzz攻击

逆向分析设备端的逻辑，大概看看蓝牙发了啥指令，编写自动化脚本，构造随机，畸形指令进行大批量测试，看设备还能正常工作。



#### 位置暴露：

蓝牙设备如果没有设置随机地址，那么在处于可发现的状态时，每次开启都是固定地址。

如果设备是随身的，或者是车载蓝牙，那么这个设备被发现了，就说明你在附近了。

如果搞得高级一点，在你可能经过的地方布置一些蓝牙探测设备，那么就能完整的跟踪行程，方便后续搞一些，法外狂徒喜欢干的事。



### 3.蓝牙安全国家标准

这里关注一下 2020年4月28 发布的国标蓝牙安全指南 

**GB/T 38648-2020**

![image-20220318133923705](https://gitee.com/wangtietou/net_pic/raw/master/essay/audition/life/image-20220318133923705.png)