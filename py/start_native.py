import sys
from Native.main import *

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)

    wnd = Main()
    wnd.show_and_raise()

    sys.exit(app.exec_())
