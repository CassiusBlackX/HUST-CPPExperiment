# 华中科技大学2022级计算机科学与计数c++实验整理
## 说明
这是华中科技大学2022级c++实验的源码，其中实验五因为具有一定的“不确定性”，因此专门把可执行程序也上传上去，
前四个实验忽略可执行程序，只保留源码，到时候有需要在VS中自行配置测试程序。

## 目录结构
每个文件夹下面对应一个实验，实验中main函数是用来自己测试，然后另外了几个类就是用来实现实验要求。

#### 实验一
`Queue.h`和`Queue.cpp`就是本实验需要实现的类。在`main.cpp`中只需要`include "Queue.h"`即可。
#### 实验二
`Queue.h`和`Queue.cpp`就是本实验需要实现的类。在`main.cpp`中只需要`include "Queue.h"`即可。
#### 实验三
`Queue`和`Stack`就是本实验需要的两个类。可在真正的main.cpp里面只需要`include "Stack.h"`就可以。

*以上三个实验中具体的类的名字不完全相同，为了能够通过测试程序，请务必专门把其中的类的名称修改得和实验指导一模一样*

#### 实验四
`MAT.h`是一整个包含头文件以及模板类以及相关的实现代码。
#### 实验五
- `include`文件夹下面是该项目所需要的所有头文件。
- `resources`文件夹下面是该项目所需要的资源文件，包括地图背景和各个公交站点的详细信息。
- `src`文件加下面就是整个工程羡慕的源代码。
- `CMakeLists.txt`是用来构建整个工程项目的，
其中如果要在本地使用CLion运行的化需要修改，把其中的`CMAKE_PREFIX_PATH`修改为自己本地的Qt路径。
- `cmake-build-debug`和`cmake-build-release`是cmake自动生成两个文件夹。
为了确保能够正常运行，因此专门上传这两个可执行文件。

## 实验五项目说明
### 使用说明
理论上clone下来就可以直接运行`cmake-build-release`或者`cmake-build-release`中的可执行文件。
如果遇到`缺少libgcc_s_seh-1.dll`之类的错误请自行参照网上的相关方法配置环境变量。

在CLion中直接打开`ex5`文件夹，先修改`CMakeLists.txt`中的`CMAKE_PREFIX_PATH`，修改为本地的Qt路径，然后重新cmake。
成功的话就可以直接编译运行了。

### 功能说明
由于在可执行文件中使用的是相对路径，因此如果想直接可执行程序的话请勿随意修改项目中的文件路径。

进入程序后，窗口最下面复选框中默认勾选“换乘次数最少”，用户可以鼠标单击“距离最近”或者“换乘次数最少”，都将选择跳转至另外一个没有被选中的复选框。

当用户鼠标悬停在地图上公交站点上方的时候，将会出现一个提示框，提示框内展示站点的相关内容。目前为了界面的整洁美观，防止过度拥挤的感觉，

用户在地图界面上第一次单机鼠标左键，界面上将会出现一个蓝色圆，指示用户第一次点击所在的位置，
然后用户可以在地图上另外一个位置点击以后将会出现红色圆，指示用户选择的终点位置所在。此时地图上将同时出现一条蓝色实线，
指示程序为用户规划的路线。值得说明的是，在用户选择终点前，仍然可以勾选复选框，改变路径的规划方式。
在路径规划出来以后，如果5秒内用户没有任何操作，规划出来的路径（包括起点和终点）将自动消失。
用户可以重新选择起点和终点。当然，如果在规划出路径以后用户在5秒内就重新选择了新的起点，
已经规划出来的路径也会消失，方便用户选择新路线的终点并展示。

用户可以通过点击窗口左上角菜单栏的查找的“查找地点 R”或者直接在当前焦点在本程序的情况下按键盘上的R案件来打开搜索框。
如果当前没有确定起点，则使用搜索框搜索到的地点将成为路径规划的起点；如果当前已经确定了起点，那么搜索框搜索到的路径将会成为路径规划的终点。
当然，用户也可以完全通过搜索框来指定路径的起点和终点。搜索支持模糊搜索，即用户不用完整输入地点名称也可以搜索到目的地。
如果用户搜索的地点名称不在给定的Organization.txt文件里面，则将会提示用户“查找失败”，
用户只需要关闭提示窗口或者点击“OK”按钮就可以回到程序主界面。

菜单栏剩下的两个选项，“文件”和“说明”都不具有对应的操作方法。
设置这两个选项，主要作用是为了程序美观，否则如果菜单栏只有一个选项的话有点不够好看。
其中，如果单机“文件”，将会展示本程序所依赖的三个文件的名称，用户也可以到对应的文件里面去直接修改文件内容，
比如新增地点名称和对应坐标，或者增加公交站点。点击“说明”以后会展示程序的简要使用说明。

### 不足与改进
目前本项目已经实现了实验指导书中的所有需求，但是老师可能提出额外的要求。目前本项目比实验指导书多实现了一个鼠标悬停实现站点信息的功能。

1. 该功能本身实现并不“优雅”。因为在项目早期开发的时候并没有预料到还有好虚新功能的需求，因此在最开始在主窗口中画站点的时候是直接使用`QPoint`画的，
但是为了实现悬停显示信息的功能，在项目后期才新增类`mywidget`，继承自`QtWidget`，重写了`enterEvent`和`leaveEvent`方法。
完全透明，在地图上公交站点所在的位置。
虽然主窗口上的同一位置上既有画出来的点，也有`mywidget`的实例，但是两者都是根据`resources`中的`stops.txt`生成的，
因此增加站点并不会影响该功能的正常运作。

    如果要增加提示信息中提示的内容，则请直接修改`mywidget`。
    当然，更加建议稍微修改一下站点的实现方法。直接在主窗口上描绘站点的时候就使用`mywidget`描绘站点（随便定一个颜色）直接画，而不需要在主窗口中额外画点。

2. 后续可以考虑添加的功能可以有地名搜索的时候不仅支持模糊搜索，还支持下拉菜单方便用户直接选择。
3. 由于整个项目是的界面是纯代码实现的，因此项目中各个窗口的大小都是在程序中写死的。如果可以的话最好携程能够动态调整大小的方法。
4. 理论上本项目的析构仍然存在一定的问题，但是当前版本的可执行文件是可以正确退出的。
5. 本项目中关于计时器的相关使用方法可能不完全正确，是自己凭着感觉和报错摸索出来的，如果有深入了解过的话敬请自行修改。