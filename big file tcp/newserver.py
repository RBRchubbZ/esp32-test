import trio
from itertools import count
#for image
from PIL import Image, ImageFile
ImageFile.LOAD_TRUNCATED_IMAGES=True
import io


PORT = 8080


CONNECTION_COUNTER = count()

async def echo_server(server_stream):
    # Assign each connection a unique number to make our debug prints easier
    # to understand when there are multiple simultaneous connections.
    ident = next(CONNECTION_COUNTER)
    print(f"echo_server {ident}: started")
    img_data = b''
    try:
        async for data in server_stream:
            print(f"echo_server {ident}: received data ")
            img_data += data
            # b64 = base64.b64encode(data)
            # print(b64) 
            
        print(f"echo_server {ident}: connection closed")
   
    except Exception as exc:
        print(f"echo_server {ident}: crashed: {exc!r}")
    
    await show_image(img_data)

async def show_image(data):
    img = Image.open(io.BytesIO(data))
    img.show()
    

async def main():
    await trio.serve_tcp(echo_server, PORT)

trio.run(main)
