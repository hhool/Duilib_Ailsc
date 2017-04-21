# Duilib

Duilib是一个Windows下免费开源的DirectUI界面库，由于简约易扩展的设计以及稳定高效的实现被各大互联网公司普遍接受，广泛应用于包括IM、视频客户端、股票行情软件、导航软件、手机辅助软件、安全软件等多个行业的众多pc客户端软件。Duilib还在不断的发展中，在文档、例子、动画、渲染引擎等多个方面将持续改进。

欢迎为Duilib提供功能改进、代码修补、bug反馈、使用文档和献计献策，让我们一起把Duilib做的更好！当然也欢迎你对duilib项目进行捐助（可以使用支付宝或微信扫码）。

# liulei Note：
1.使用虚表的时候，可能会导致滚动条无法推动，这是因为大量刷新消息导致的，因为内部会不停的set并且invalidate，此时优化一下Duilib的Set接口，没有改变就不用刷新
2.Duilib容器只对可见控件布局，如果控件不可见，则不调整该控件位置。此时如果容器位置改变，然后显示该控件，则会导致该控件位置不对。应尽量避免动态SetVisible，使用
showbkimg和showstatusimg两个属性来代替SetVisible
# Todo：
1、完善属性设置和保存

2、重写Tree

3、支持dpi

4、支持虚表

5、支持浮动窗口

6、支持功能性UI


### 支付宝扫码
![支付宝扫码](https://github.com/wangchyz/privatedata/blob/master/alipay.png)

### 微信扫码
![微信扫码](https://github.com/wangchyz/privatedata/blob/master/weixin.png)

# 基于Duilib的软件不完全列表
Duilib自2010年8月21日发布以来，获得了众多开发者和大公司的信赖，在各行各业的软件中得到了广泛应用，以下是一个作者知道不完全列表，欢迎大家补充指正
https://github.com/duilib/duilib/wiki/%E5%9F%BA%E4%BA%8EDuilib%E7%9A%84%E8%BD%AF%E4%BB%B6%E4%B8%8D%E5%AE%8C%E5%85%A8%E5%88%97%E8%A1%A8

