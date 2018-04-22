import struct
import socket
from threading import Thread

from flask import Flask
from flask import render_template
from flask_socketio import SocketIO
from flask import copy_current_request_context
from pexpect import pxssh

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app, binary=True)


@app.route('/')
def display():
    receipt_socket()
    return render_template('nbody.html')


def receipt_socket():
    @copy_current_request_context
    def start_socket():
        SERVER_PORT_SOCKET = 15556
        SERVER_ADDRESS_SOCKET = "0.0.0.0"
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        connected = False
        while not connected:
            try:
                s.bind((SERVER_ADDRESS_SOCKET, SERVER_PORT_SOCKET))
                connected = True
            except socket.error:
                pass

        s.listen(5)
        client, address = s.accept()
        res = True
        while res:
            response = client.recv(24)
            if response == b'':
                s.close()
                res = False
            elif response != "":
                """ Put the particle in the global fifo """
                response = struct.unpack('ddd', response)
                socketio.emit('data_cpp', response)
    t = Thread(target=start_socket, daemon=True)
    t.start()


def ssh_connexion():
    def co():
        try:
            child = pxssh.pxssh()
            child.force_password = True
            child.login(
                "ft2.cesga.es",
                "eisti011",
                "e.st.011",
                auto_prompt_reset=False,
                original_prompt='$ '
            )
            child.sendline('cd gsi_project/app')
            child.sendline('./bin/prog -f ../data/test.csv -s -p 15556 -a 163.172.162.210 -n 1000')
            child.close()
        except pxssh.ExceptionPxssh as e:
            print("[-] Error Connecting\n" + str(e))
    t2 = Thread(target=co, daemon=True)
    t2.start()


if __name__ == '__main__':
    socketio.run(app)
