linux��װopencv���裺
1.��װcmake

2.��װlibgtk2.0-dev �� pkg-config��һ��Ҫ��������氲װ������ǰ��װ��

3.����opencvԴ��Ŀ¼��cmake CMakeList

4.make && make install

5.���û������� 
sudo gedit /etc/ld.so.conf.d/opencv.conf��û�и��ļ��Ļ����д�������Ϊ�ļ��������/usr/local/lib

6.���ÿ�
sudo ldconfig

7.���Ļ�������
sudo gedit /etc/bash.bashrc,���ļ�ĩβ��ӣ�PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig 
export PKG_CONFIG_PATH

8.�����ն�ʹ������Ч��


���̲��ԣ�
1.����opencv/sample/cĿ¼

2.�ն����� ./build_all.sh (���build_all.shû��ִ��Ȩ�ޣ�chmod +x build_all.shʹ֮���ִ��Ȩ��)

3../facedetect --cascade="/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml" --scale=1.5 lena.jpg
(Ҳ���Բ������������в���)


��ע������windwowsϵͳ��ubuntu�����������vmwrae�л�����ͷ�豸ʱ�������⣬����������Ҳ���/dev/video0����ͷ�豸��
���Ѿ�������������ָ̨��һ������ʤ�м���