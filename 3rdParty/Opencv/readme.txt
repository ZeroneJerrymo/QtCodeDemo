linux安装opencv步骤：
1.安装cmake

2.安装libgtk2.0-dev 和 pkg-config（一定要相对于下面安装步骤提前安装）

3.进入opencv源码目录，cmake CMakeList

4.make && make install

5.配置环境变量 
sudo gedit /etc/ld.so.conf.d/opencv.conf（没有该文件的话自行创建），为文件添加内容/usr/local/lib

6.配置库
sudo ldconfig

7.更改环境变量
sudo gedit /etc/bash.bashrc,在文件末尾添加，PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig 
export PKG_CONFIG_PATH

8.重启终端使配置生效。


例程测试：
1.进入opencv/sample/c目录

2.终端输入 ./build_all.sh (如果build_all.sh没有执行权限，chmod +x build_all.sh使之获得执行权限)

3../facedetect --cascade="/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml" --scale=1.5 lena.jpg
(也可以不带参数，自行测试)


附注：本人windwows系统，ubuntu虚拟机，但是vmwrae切换摄像头设备时出现问题，导致虚拟机找不到/dev/video0摄像头设备，
望已经解决此问题的兄台指点一二，不胜感激。