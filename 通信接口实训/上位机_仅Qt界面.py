import sys
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
class QInputDialogDemo(QWidget):
    def __init__(self):
        super(QInputDialogDemo,self).__init__()
       #self.setLayout = master #定义内部变量root
	   #self.setLayout.geometry('%dx%d' % (600,360)) #设置窗口大小
        self.initUI()
    def initUI(self):
        self.setWindowTitle("上位机")
        #创建表单布局
        layout = QFormLayout()
        self.button1 = QPushButton("上位机语言选择")
        self.button1.clicked.connect(self.getItem)
        self.lineEdit1 = QLineEdit()
        layout.addRow(self.button1,self.lineEdit1)
 
        self.button2 = QPushButton("输入用户姓名")
        self.button2.clicked.connect(self.getText)
        self.lineEdit2 = QLineEdit()
        layout.addRow(self.button2, self.lineEdit2)

        self.button3 = QPushButton("数字1开始")
        self.button3.clicked.connect(self.getInt)
        self.lineEdit3 = QLineEdit()
        layout.addRow(self.button3, self.lineEdit3)
 
        self.button3 = QPushButton("数字2 +")
        self.button3.clicked.connect(self.getInt)
        #self.lineEdit3 = QLineEdit()
        layout.addRow(self.button3, self.lineEdit3)
 
        self.button3 = QPushButton("数字3 -")
        self.button3.clicked.connect(self.getInt)
        #self.lineEdit3 = QLineEdit()
        layout.addRow(self.button3, self.lineEdit3)
 
        self.button3 = QPushButton("数字4 切歌")
        self.button3.clicked.connect(self.getInt)
        #self.lineEdit3 = QLineEdit()
        layout.addRow(self.button3, self.lineEdit3)
        
        self.button3 = QPushButton("数字5 时分秒转换")
        self.button3.clicked.connect(self.getInt)
        #self.lineEdit3 = QLineEdit()
        layout.addRow(self.button3, self.lineEdit3)
 
     
        self.button4 = QPushButton("虚拟按键数字")
        self.button4.clicked.connect(self.getInt)
        self.lineEdit4 = QLineEdit()
        layout.addRow(self.button4, self.lineEdit3)
        
 
 
        self.setLayout(layout)
 
    def getItem(self):
        items = ("C","C++","Python","Java","Rudy")
        item,ok = QInputDialog.getItem(self,"上位机语言选择","语言列表",items)
        if ok and item:
            self.lineEdit1.setText(item)
    def getText(self):
        text, ok = QInputDialog.getText(self, "输入用户姓名", "输入姓名")
        if ok and text:
            self.lineEdit2.setText(text)
    def getInt(self):
        num,ok = QInputDialog.getInt(self,"数字输入","输入数字")
     #  if ok and num:
        #    self.lineEdit3.setText(str(num))
 
if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon('./images/t10.ico'))
    main = QInputDialogDemo()
    main.show()
    sys.exit(app.exec_())