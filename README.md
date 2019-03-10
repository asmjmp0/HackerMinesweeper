# HackerMinesweeper
作为一位外挂初学者如何用od和ida pro ce来写一份扫雷外挂
首先猜测一下扫雷的算法 自定义布局的时候会改变雷的数量和宽高
<br>废话不多说 打开CE查询数值 发现宽保存在`0x10056A8`而这是个全局变量(CE为绿色基址) 用相同的方法也能找到雷的数量和高度都是基址
* 第一步找到初始化函数遂转到od在`0x10056A8`上下内存访问断点
断在如图所示的地方往上找 找函数开始的地方分析得到函数头应该是 `0x0100367A`
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/HackerMinesweeper/master/1.png)
* 遂转到ida中查看 F5大法
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/HackerMinesweeper/master/2.png)
<br>关键算法应该在这里
```c
 while ( *(&byte_1005340[32 * v2] + v1) & 0x80 );
    *(&byte_1005340[32 * v2] + v1) |= 0x80u;
    --dword_1005330;
```
<br>我们可以得到`1005340`保存是一张表 一张整个雷的表
而且在这个地方 标志雷的位置
* 在od中用db的方式查看这张表并且加0x20(即是32)
发现这是以32为一个轮 排开开头10 就是31个 读到这里有人就可能会问了要是大于31怎么办这岂不是这个程序就会出错吗
<br>后来发现这个宽度最大只有30(完美避开了bug)
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/HackerMinesweeper/master/3.png)
显而易见`0x8F`就是代表着雷 这样算法就很简单了 只要开头读出这张表就能获得雷的位置 然后通过mouse_event就能开外挂了
* 怎么写一个外挂 假设我们是新手
  * 第一步我们得获取进程句柄就是这样的素质三连 handle就是我们所需
```c
hwnd=FindWindow(L"扫雷",nullptr);
GetWindowThreadProcessId(hwnd, &lppid);
handle=OpenProcess( PROCESS_ALL_ACCESS, false,lppid);
```
后面的就是读表 写算法 我都在代码中已经给出来了
<br>最后的效果
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/HackerMinesweeper/master/4.png)
<br>当然其他的文章大家也能看看
<br>最后就是我永远喜欢珂朵莉！！！
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/HackerMinesweeper/master/4.jpg)
