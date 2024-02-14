import socket
import json
import time

def create_socket_server():
    # Create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to a specific IP address and port
    host = '192.168.1.8'  # Use your desired IP address or 'localhost'
    port = 801         # Use any available port number

    server_socket.bind((host, port))

    # Listen for incoming connections
    server_socket.listen(1)

    print(f"Server is listening on {host}:{port}")

    while True:
        # Accept a connection
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")

        # Print the IP of the connected socket
        connected_ip = client_address[0]
        print(f"Connected socket IP: {connected_ip}")

        try:
            while True:
                # Prepare sample JSON data
                sample_data = {
                    "message": "Hello, this is a sample message.",
                    "link": "http://example.com"
                }

                # Convert the dictionary to JSON
                json_data = json.dumps(sample_data)

                # Send the JSON data to the client
                client_socket.send(json_data.encode())

                # Wait for 2 seconds before sending data again
                time.sleep(2)

        except (socket.error, BrokenPipeError):
            # Handle the case when the client disconnects
            print("Client disconnected.")
            client_socket.close()

if __name__ == "__main__":
    create_socket_server()
