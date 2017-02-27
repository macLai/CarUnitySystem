import tornado.websocket
import tornado.ioloop
import tornado.web
from tornado.escape import json_decode
import os

PRIORITY = {
    'device_priority': 'navi|meta|hud',
    'mode_priority': {
        'acclda': 8,
        'opendoor': 7,
        'camera': 6,
        'crossroad': 5,
        'energymonitor': 1,
        'driverinfo': 1,
        'audio': 1,
        'phone': 1,
        'navi': 1
    }
}

class ManagerHandler(tornado.web.RequestHandler):
    def get(self):
        global PRIORITY
        action = self.get_argument('action', None)
        if not action:
            self.render('manager.html')
        elif action == 'getConfigData':
            self.write(PRIORITY)
    def post(self):
        global PRIORITY
        action = self.get_argument('action', None)
        if action == 'postPriority':
            PRIORITY = eval(self.get_argument('data', None))
            writeConfig('../test.cnf')
            self.write(PRIORITY)
        if action == 'restart':
        	os.system('..\\test.bat')


def make_app():
    return tornado.web.Application([
        (r'/', ManagerHandler),
        (r'/(.*)', tornado.web.StaticFileHandler, {'path': '.'}),
    ])

def readConfig(fileName):
    global PRIORITY
    file_object = open(fileName)
    data = file_object.read()
    file_object.close()
    info = eval(data)
    PRIORITY = info

def writeConfig(fileName):
    global PRIORITY
    file_object = open(fileName, 'w')
    file_object.write(str(PRIORITY))
    file_object.close()

if __name__ == '__main__':
    readConfig('../test.cnf')
    app = make_app()
    app.listen(9999)
    tornado.ioloop.IOLoop.current().start()