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
    },
}
MODE = {
    'opendoor': {
        'priority': 10,
        'display': '110'
    },
    'camera': {
        'priority': 8,
        'display': '010'
    },
    'crossroad': {
        'priority': 6,
        'display': '110'
    },
    'audio': {
        'priority': 1,
        'display': '011'
    },
    'phone': {
        'priority': 1,
        'display': '011'
    },
    'navi': {
        'priority': 1,
        'display': '011'
    }
}
ACTIVE_MODE = {
    'status': 'modelists',
    'navi': {
        'frame': 'Navi1Screen',
        'mode': 'navi'
    },
    'meta': {
        'frame': 'Meta1Screen',
        'mode': 'audio'
    },
    'hud': {
        'frame': 'Hud0Screen',
        'mode': ''
    }
}
ALL_MODE = ['audio', 'navi']

def randomMode():
    pass
    # for device in DEVICE:
    #     frame = random.randrange(1,4)
    #     random.shuffle(MODE)
    #     modeStr = '|'.join(MODE[:frame])
    #     if device == 'hud':
    #         modeStr = ''
    #         frame = '0'
    #     ACTIVE_MODE[device]['frame'] = FRAME[device][str(frame)]
    #     ACTIVE_MODE[device]['mode'] = modeStr

def mode_on(mode, modeOn ):
    global ACTIVE_MODE
    global ALL_MODE
    global FRAME

    if not MODE.has_key(mode):
        return
    modeList = {'hud': [], 'meta': [], 'navi': []}

    if modeOn == 'MODE_ON':
        for i in range(len(ALL_MODE)):
            if MODE[ALL_MODE[i]]['priority'] <= MODE[mode]['priority']:
                ALL_MODE.insert(i, mode)
                break
        ALL_MODE = sorted(list(set(ALL_MODE)), key = ALL_MODE.index)
    else:
        if mode in ALL_MODE:
            ALL_MODE.remove(mode)
        else:
            return

    print ALL_MODE

    # list_hud = [x for x in ALL_MODE if MODE[x]['display'][0] == '1']
    # if len(list_hud) > 0: modeList['hud'] = [list_hud[0]]

    list_without_hud = [x for x in ALL_MODE if x not in modeList['hud']]
    modeList['meta'] = list_without_hud[:int((len(list_without_hud)+1)/2)]
    modeList['navi'] = list_without_hud[len(modeList['meta']):]
    
    for device in DEVICE:
        ACTIVE_MODE[device]['frame'] = FRAME[device][str(len(modeList[device]))]
        ACTIVE_MODE[device]['mode'] = '|'.join(modeList[device])
    ACTIVE_MODE['hud']['frame'] = 'Hud0Screen'
    ACTIVE_MODE['hud']['mode'] = ''




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
        if action == 'modeon':
            mode = self.get_argument('mode', None)
            mode_on(str(mode), 'MODE_ON')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            self.write(ACTIVE_MODE)
        if action == 'modeoff':
            mode = self.get_argument('mode', None)
            mode_on(str(mode), 'MODE_OFF')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            self.write(ACTIVE_MODE)

    def get(self):
        self.render('WebControl.html')


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
        (r'/(.*)', tornado.web.StaticFileHandler, {'path': '.'}),
    ])

if __name__ == '__main__':
    app = make_app()
    app.listen(8888)
    tornado.ioloop.IOLoop.current().start()