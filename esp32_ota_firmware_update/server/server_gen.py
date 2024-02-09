import http.server
import socketserver
import socket  # Don't forget to import the 'socket' module

PORT = 8000  # You can choose any available port

Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving at http://{socket.gethostbyname(socket.gethostname())}:{PORT}/")
    httpd.serve_forever()
