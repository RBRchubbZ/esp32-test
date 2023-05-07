from fastapi import FastAPI, UploadFile, File
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from datetime import datetime


class User(BaseModel):
    name: str


origins = ["*"]
app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/")
async def hello():
    return "Hello World"

@app.post("/sayhi")
async def hi(user : User):
    return f"Hi {user.name}"

@app.post("/uploadimage")
async def upload_img(file : UploadFile = File(...)):
    now = datetime.now()
    dt_string = f'{now.strftime("%Y_%m_%d-%I_%M_%S_%p")}.jpg'
    path = "img/"

    image = await file.read()

    with open(f"{path}{dt_string}", "wb") as f:
        f.write(image)

    return {"Success"} 