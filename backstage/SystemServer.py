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
    },
}
MODE = {
    'acclda': {
        'priority': 11,
        'display': '111'
    },
    'opendoor': {
        'priority': 10,
        'display': '111'
    },
    'camera': {
        'priority': 8,
        'display': '011'
    },
    'crossroad': {
        'priority': 6,
        'display': '111'
    },
    'energymonitor': {
        'priority': 1,
        'display': '011'
    },
    'driverinfo': {
        'priority': 1,
        'display': '011'
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
LOCK_MAP = -1
LOCK_HUD = -1
META_MIN = False
NAVI_MIN = False
CAR_RUN = False

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
    global LOCK_MAP
    global DEVICE
    global LOCK_HUD

    if not MODE.has_key(mode):
        return
    modeList = {'hud': [], 'meta': [], 'navi': []}

    if modeOn == 'MODE_ON':
        for i in range(len(ALL_MODE)):
            if MODE[ALL_MODE[i]]['priority'] <= MODE[mode]['priority']:
                ALL_MODE.insert(i, mode)
                break
        ALL_MODE = sorted(list(set(ALL_MODE)), key = ALL_MODE.index)
    elif modeOn == 'MODE_OFF':
        if mode in ALL_MODE:
            ALL_MODE.remove(mode)
        else:
            return


    print ALL_MODE

    if LOCK_HUD < 0:
        list_hud = [x for x in ALL_MODE if MODE[x]['display'][0] == '1']
        if len(list_hud) > 0: modeList['hud'] = [list_hud[0]]

    list_without_hud = [x for x in ALL_MODE if x not in modeList['hud']]
    len_navi = 0
    len_meta = 0

    print LOCK_MAP
    if LOCK_MAP == 0:
        len_navi = 1
        len_meta = (len(list_without_hud) - len_navi) > 3 and 3 or (len(list_without_hud) - len_navi)
    elif LOCK_MAP == 1:
        if len(list_without_hud) <=2:
            LOCK_MAP = -1
        else:
            if len(list_without_hud) <=4:
                len_navi = 2
                len_meta = len(list_without_hud) - len_navi
            else:
                len_meta = 3
                len_navi = (len(list_without_hud) - len_meta) > 3 and 3 or (len(list_without_hud) - len_meta)
    elif LOCK_MAP == 2:
        if len(list_without_hud) <= 2:
            LOCK_MAP = -1
        else:
            len_navi = 2
            len_meta = (len(list_without_hud) - len_navi) > 3 and 3 or (len(list_without_hud) - len_navi)
    elif LOCK_MAP == 3 or LOCK_MAP == 4:
        print len(list_without_hud)
        if len(list_without_hud) <= 3:
            LOCK_MAP = -1
        else:
            len_navi = 3
            len_meta = (len(list_without_hud) - len_navi) > 3 and 3 or (len(list_without_hud) - len_navi)

    if LOCK_MAP >= 0:
        list_without_hud = [x for x in list_without_hud if x != 'navi']
        len_navi = len_navi - 1
    elif META_MIN:
        len_meta = 1
        len_navi = (len(list_without_hud) - len_meta) > 3 and 3 or (len(list_without_hud) - len_meta)
    elif NAVI_MIN:
        len_navi = 1
        len_meta = (len(list_without_hud) - len_navi) > 3 and 3 or (len(list_without_hud) - len_navi)
    else:
        if len(list_without_hud) >= 6:
            len_meta = 3
            len_navi = 3
        else:
            len_meta = int((len(list_without_hud)+1)/2)
            len_navi = len(list_without_hud) - len_meta

    print 'LOCK_MAP : ' + str(LOCK_MAP)
    print 'len_navi : ' + str(len_navi)
    print 'len_meta : ' + str(len_meta)
    print 'list_without_hud : ' + str(list_without_hud)



    modeList['meta'] = list_without_hud[:len_meta]
    modeList['navi'] = list_without_hud[len_meta:len_navi+len_meta]
    if LOCK_MAP == 0 or LOCK_MAP == 1:
        modeList['navi'].insert(0, 'navi')
    elif LOCK_MAP == 2 or LOCK_MAP == 3:
        modeList['navi'].insert(1, 'navi')
    elif LOCK_MAP == 4:
        modeList['navi'].insert(2, 'navi')
    
    for device in DEVICE:
        ACTIVE_MODE[device]['frame'] = FRAME[device][str(len(modeList[device]))]
        ACTIVE_MODE[device]['mode'] = '|'.join(modeList[device])




class ChatSocketHandler(tornado.websocket.WebSocketHandler):
    waiters = set()

    def allow_draft76(self):
        # for iOS 5.0 Safari
        return True

    def open(self):
        global CAR_RUN
        global ACTIVE_MODE
        global LOCK_HUD
        global META_MIN
        global NAVI_MIN
        print 'client opened'

        displayControl = 'normal'
        if META_MIN:
            displayControl = 'metamin'
        elif NAVI_MIN:
            displayControl = 'navimin'
        ChatSocketHandler.waiters.add(self)
        self.write_message(ACTIVE_MODE)
        self.write_message({'status':'allmodes', 'mode':ALL_MODE})
        self.write_message({'status':'car', 'run':'start' if CAR_RUN else 'stop'})
        self.write_message({'status':'displayControl', 'lock':displayControl})
        self.write_message({'status':'hudlock', 'lock':LOCK_HUD>=0})

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
        global ACTIVE_MODE
        global LOCK_MAP
        if req['action'] == 'getall':
            print ACTIVE_MODE
            self.write_message(ACTIVE_MODE)
        elif req['action'] == 'lockmap':
            global LOCK_MAP
            LOCK_MAP = int(req['pos'])
            if LOCK_MAP >= 0:
                META_MIN = False
                NAVI_MIN = False
            mode_on('navi', '')
            print ACTIVE_MODE
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
        elif req['action'] == 'modeoff':
            mode = req['mode']
            mode_on(str(mode), 'MODE_OFF')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'allmodes', 'mode':ALL_MODE})
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})


class WebControlHandler(tornado.web.RequestHandler):
    def post(self):
        global LOCK_MAP
        global META_MIN
        global NAVI_MIN
        global LOCK_HUD
        global ALL_MODE
        global CAR_RUN
        action = self.get_argument('action', None)
        if action == 'random':
            randomMode()
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            self.write(ACTIVE_MODE)
        if action == 'start':
            if CAR_RUN:
                return
            CAR_RUN = True
            ChatSocketHandler.send_updates({'status':'car', 'run':'start'})
            MapPosHandler.timer_start()
        if action == 'stop':
            if not CAR_RUN:
                return
            CAR_RUN = False
            ChatSocketHandler.send_updates({'status':'car', 'run':'stop'})
            MapPosHandler.timer_stop()
        if action == 'modeon':
            mode = self.get_argument('mode', None)
            mode_on(str(mode), 'MODE_ON')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'allmodes', 'mode':ALL_MODE})
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
            self.write(ACTIVE_MODE)
            print ACTIVE_MODE
        if action == 'modeoff':
            mode = self.get_argument('mode', None)
            mode_on(str(mode), 'MODE_OFF')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'allmodes', 'mode':ALL_MODE})
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
            self.write(ACTIVE_MODE)
            print ACTIVE_MODE
        if action == 'metamin':
            META_MIN = True
            NAVI_MIN = False
            LOCK_MAP = -1
            mode_on('navi', 'META_MIN')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
            self.write(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'displayControl', 'lock':'metamin'})
        if action == 'navimin':
            META_MIN = False
            NAVI_MIN = True
            LOCK_MAP = -1
            mode_on('navi', 'NAVI_MIN')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
            self.write(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'displayControl', 'lock':'navimin'})
        if action== 'normal':
            META_MIN = False
            NAVI_MIN = False
            LOCK_MAP = -1
            mode_on('navi', 'normal')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'maplock', 'lock':LOCK_MAP})
            self.write(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'displayControl', 'lock':'normal'})
        if action == 'lockhud':
            LOCK_HUD = 1
            mode_on('navi', 'LOCK_HUD')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'hudlock', 'lock':True})
        if action == 'unlockhud':
            LOCK_HUD = -1
            mode_on('navi', 'LOCK_HUD')
            ChatSocketHandler.send_updates(ACTIVE_MODE)
            ChatSocketHandler.send_updates({'status':'hudlock', 'lock':False})

    def get(self):
        self.render('WebControl.html')


class MapHandler(tornado.web.RequestHandler):
    def get(self):
        self.render('test.html')

POS_NUM = 0
def update_pos():
    global POS_NUM
    print MapPosHandler.pos[POS_NUM]
    MapPosHandler.send_updates(POS_NUM)
    POS_NUM = (POS_NUM + 1) % len(MapPosHandler.pos)
    MapPosHandler.timer_start()

class MapPosHandler(tornado.websocket.WebSocketHandler):
    waiters = set()
    pos = [
        {'lat':31.161532, 'lng':121.553, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.554, 'cross': 'test1', 'len': 4, 'front': False},
        {'lat':31.161532, 'lng':121.555, 'cross': 'test1', 'len': 3, 'front': False},
        {'lat':31.161532, 'lng':121.556, 'cross': 'test1', 'len': 2, 'front': False},
        {'lat':31.161532, 'lng':121.557, 'cross': 'test1', 'len': 1, 'front': False},
        {'lat':31.161532, 'lng':121.558, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.559, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.560, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test2', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test2', 'len': 4, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test2', 'len': 3, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test2', 'len': 2, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test2', 'len': 1, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test3', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test3', 'len': 4, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test3', 'len': 3, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test3', 'len': 2, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test3', 'len': 1, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': '', 'len': 0, 'front': True},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test4', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test4', 'len': 4, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test4', 'len': 3, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test4', 'len': 2, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test4', 'len': 1, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
        {'lat':31.161532, 'lng':121.561, 'cross': 'test1', 'len': 5, 'front': False},
    ]
    t = Timer(1, update_pos)
    

    def open(self):
        print 'MapPos client opened'
        MapPosHandler.waiters.add(self)

    def on_close(self):
        print 'MapPos client closed'
        MapPosHandler.waiters.remove(self)

    @classmethod
    def send_updates(cls, i):
        for waiter in cls.waiters:
            try:
                waiter.write_message(cls.pos[i])
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