from http.server import SimpleHTTPRequestHandler as HTTP_handler
from json import loads, JSONDecodeError, dumps
from func import *


class Exchanger_server(HTTP_handler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length).decode('utf-8')
        print(f"Received POST request to {self.path}:")
        print(f"Headers: {self.headers}")
        try:
            data = loads(body)
            print(f"Body: {data}")
        except JSONDecodeError:
            return self.send_bad_response("Invalid JSON")

        try:
            if self.path == "/user":
                response_data = new_user(data.get("user"))
            elif self.path == "/order":
                response_data = new_order(
                    self.headers.get("X-USER-KEY"),
                    data.get("pair_id"),
                    data.get("quantity"),
                    data.get("price"),
                    data.get("type")
                )
            else:
                raise ValueError("Not found")
        except Exception as e:
            return self.send_bad_response(e)
        self.send_good_response(response_data)

    def do_GET(self):
        print(f"Received GET request to {self.path}:")
        print(f"Headers: {self.headers}")
        try:
            if self.path == "/order":
                response_data = get_order()
            elif self.path == "/lot":
                response_data = get_lot()
            elif self.path == "/pair":
                response_data = get_pair()
            elif self.path == "/balance":
                response_data = get_balance(self.headers.get("X-USER-KEY"))
            else:
                raise ValueError("Not Found")
        except Exception as ex:
            return self.send_bad_response(ex)
        self.send_good_response(response_data)

    def do_DELETE(self):
        print(f"Received DELETE request to {self.path}:")
        print(f"Headers: {self.headers}")
        try:
            if self.path == "/order":
                content_length = int(self.headers['Content-Length'])
                body = self.rfile.read(content_length).decode('utf-8')
                data = loads(body)
                print(f"Body: {data}")
                delete_order(
                    self.headers.get("X-USER-KEY"),
                    data.get("order_id")
                )
            else:
                raise ValueError("Not Found")
        except Exception as e:
            return self.send_bad_response(e)
        self.send_good_response(b"")

    def send_good_response(self, data):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        if data:
            self.wfile.write(dumps(data).encode())

    def send_bad_response(self, error):
        self.send_response(400)
        self.end_headers()
        self.wfile.write(str(error).encode())
