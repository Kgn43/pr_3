from typing import List, Dict, Optional
from random import choice, randint # for generateon unic id
from string import hexdigits # for generateon unic id
import socket


def connect_to_db(ip: str, port: int):
    global DB_socket
    DB_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    DB_socket.connect((ip, port))
    print(f"Connected to DB {ip}:{port}")


def disconnect_from_db():
    global DB_socket
    DB_socket.close()


def send_message(message: str) -> None:
    print(f"[DEBUG]: {message = }")
    try:
        DB_socket.sendall(message.encode())
    except ConnectionResetError:
        print("Connection refused by server")
    except Exception as ex:
        print(f"Error while sending message: {ex}")


def receive_messages() -> Optional[str]:
    try:
        data = DB_socket.recv(1024).decode()
        if not data:
            print('Warning: received an empty data!')
            return None
        print(f"[DEBUG]: {data = }")
        if data == "EMPTY":
            return None
        return data

    except BlockingIOError:
        pass
    except ConnectionResetError:
        print('Connection closed by server')
    except Exception as ex:
        print(f"Error while sending message: {ex}")


def get_piece(query: str) -> Optional[str]:
    send_message(query)
    res = receive_messages()
    if not res:
        return None
    return res.strip()


def gen_id(length: int = 32) -> str:
    return ''.join(choice(hexdigits) for _ in range(length))


def new_user(username : str):
    if not username:
        raise ValueError("Please type a username")
    if get_piece(f"select users.user_name from users where users.user_name = '{username}'"):
        raise ValueError("This user already exist")
    user_id = randint(1, 1000)
    key = gen_id()
    send_message(f"insert into users values {user_id} {username} {key}")
    lot_ids = get_piece("select lot.lot_id FROM lot")
    for lot_id in lot_ids.strip().split('\n'):
        send_message(
            f"insert into user_lot values {user_id} {lot_id} 1000")

    return {"key": key}


def update():
    print(123)


def new_order(KEY, pair_id, quantity, price, Type):
    update()
    user_id = get_piece("select users.user_1 from users where users.key = {KEY}")
    order_id = randint(1, 1000)
    send_message(f"insert into order values {order_id} {username} {key}")

def get_order():
    # order_id, user_id, lot_id, quantity, Type, price, closed
    return "123"
                
    
