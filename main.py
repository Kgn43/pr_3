from exchanger_server import *

from socketserver import TCPServer
from json import load
import json


def main():
    with open('cfg.json', 'r', encoding='utf-8') as cfg:
        config = json.load(cfg)
        dB_ip = config["DB_ip"]
        dB_port = config["DB_port"]
        stock_exchange_ip = config["stock_exchange_ip"]
        stock_exchange_port = config["stock_exchange_port"]
    try:
        connect_to_db(dB_ip, int(dB_port))
    except ConnectionRefusedError:
        print(f"Failed to connect to DB {dB_ip}:{dB_port}")
        return
    with TCPServer((stock_exchange_ip, int(stock_exchange_port)), Exchanger_server) as httpd:
        print("serving at port", stock_exchange_port)
        httpd.serve_forever()

    disconnect_from_db()
    

if __name__ == "__main__":
    main()
