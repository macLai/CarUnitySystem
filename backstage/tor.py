import tornado.websocket
import tornado.ioloop
import tornado.web
import random
from threading import Timer

DEVICE = ['navi', 'meta', 'hud']
FRAME = {
    'navi': {
        '1': 'Navi1Screen',
        '2': 'Navi2Screen',
        '3': 'Navi3Screen',
    },
    'meta': {
        '1': 'Meta1Screen',
        '2': 'Meta2Screen',
        '3': 'Meta3Screen',
    },
    'hud': {
        '0': 'Hud0Screen',
        '1': 'Hud1Screen',
        '2': 'Hud2Screen',
        '3': 'Hud3Screen',
    },
}
MODE = [
    'navi',
    'audio',
    'aircon'
]
ACTIVE_MODE = {
    'status': 'modelists',
    'navi': {
        'frame': 'Navi3Screen',
        'mode': 'navi|audio|aircon'
    },
    'meta': {
        'frame': 'Meta2Screen',
        'mode': 'navi|audio'
    },
    'hud': {
        'frame': '0',
        'mode': 'Hud0Screen'
    }
}

def randomMode():
    for device in DEVICE:
        frame = random.randrange(1,4)
        random.shuffle(MODE)
        modeStr = '|'.join(MODE[:frame])
        if device == 'hud':
            modeStr = ''
            frame = '0'
        ACTIVE_MODE[device]['frame'] = FRAME[device][str(frame)]
        ACTIVE_MODE[device]['mode'] = modeStr

class ChatSocketHandler(tornado.websocket.WebSocketHandler):
    waiters = set()

    def open(self):
        print 'client opened'
        ChatSocketHandler.waiters.add(self)

    def on_close(self):
        print 'client closed'
        ChatSocketHandler.waiters.remove(self)

    @classmethod
    def send_updates(cls, chat):
        for waiter in cls.waiters:
            try:
                waiter.write_message(chat)
            except:
                print ('Error sending message')

    def on_message(self, message):
        print ('got message %r', message)
        req = eval(message)
        print req
        if req['action'] == 'getall':
            global ACTIVE_MODE
            print ACTIVE_MODE
            self.write_message(ACTIVE_MODE)

class WebControlHandler(tornado.web.RequestHandler):
    def post(self):
        action = self.get_argument('action', None)
        if action == 'random':
            randomMode()
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            self.write(ACTIVE_MODE)
        if action == 'start':
            ChatSocketHandler.send_updates({'status':'car', 'run':'start'})
            MapPosHandler.timer_start()
        if action == 'stop':
            ChatSocketHandler.send_updates({'status':'car', 'run':'stop'})
            MapPosHandler.timer_stop()


class MapHandler(tornado.web.RequestHandler):
    def get(self):
        self.render('test.html')

def update_pos():
    MapPosHandler.pos['lng'] = MapPosHandler.pos['lng'] + 0.001
    print MapPosHandler.pos
    MapPosHandler.send_updates()
    MapPosHandler.timer_start()

class MapPosHandler(tornado.websocket.WebSocketHandler):
    waiters = set()
    pos = {'lat':31.161532, 'lng':121.553874}
    t = Timer(1, update_pos)
    

    def open(self):
        print 'MapPos client opened'
        MapPosHandler.waiters.add(self)

    def on_close(self):
        print 'MapPos client closed'
        MapPosHandler.waiters.remove(self)

    @classmethod
    def send_updates(cls):
        for waiter in cls.waiters:
            try:
                waiter.write_message(cls.pos)
            except:
                print ('Error sending message')

    @classmethod
    def timer_start(cls):
        cls.t = Timer(1, update_pos)
        cls.t.start()

    @classmethod
    def timer_stop(cls):
        cls.t.cancel()



def make_app():
    return tornado.web.Application([
        (r'/', ChatSocketHandler),
        (r'/webcontrol', WebControlHandler),
        (r'/map', MapHandler),
        (r'/map/pos', MapPosHandler),
    ])

if __name__ == '__main__':
    app = make_app()
    app.listen(8888)
    tornado.ioloop.IOLoop.current().start()