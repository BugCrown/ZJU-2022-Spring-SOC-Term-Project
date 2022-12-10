# ZJU-2022-Spring-SOC-Term-Project
浙江大学 2021-2022学年春夏学期 信息与电子工程学院 **片上系统接口与模块设计** 课程项目（大作业）  
ZIM文本阅读器和编辑器  
基于 **Nexys4 DDR** 开发板和 **ILI9806G** 驱动的并行LCD实现类Vim的文本编辑和阅读器  
**没有用SD卡**  
## README
### bitsream
可以运行的本项目的bitstream
### imag
部分演示图片
### src
C文件夹中存放了cds工程文件中所需要的头文件和源文件，分别放在inc和src中  
python文件夹中存放了图片像素点颜色提取的代码和二进制文件转换成C的工具，分别存放在img_process和fileToC中  
IP核部分由老师给出，部分在小作业中自行设计  
# 引用
老师的部分代码  
cyan812的[fileToC](https://github.com/cyang812/tools.git)
